#include "matrix.h"
#include "gpio.h"
#include "wait.h"
#include "timer.h"

// Suite16mx bring-up diagnostic scanner.
//
// This build provides TWO independent signals in Vial Matrix Tester:
//   [0,0] = firmware heartbeat, toggles automatically every 500 ms
//   [0,1] = physical GPIO-pair detection
//
// The heartbeat proves that this custom matrix scanner is compiled, running,
// debounced by QMK, and reaching Vial. The physical detector independently tests
// every directed pair among all signal GPIOs exposed by the RP2040-Zero footprint:
// GP0..GP15 and GP26..GP29.
//
// There is no TrackPoint and no rotary encoder on this Suite16mx model, so no
// signal GPIOs are reserved during this diagnostic.

static const pin_t diagnostic_pins[] = {
    GP0, GP1, GP2, GP3, GP4, GP5, GP6, GP7,
    GP8, GP9, GP10, GP11, GP12, GP13, GP14, GP15,
    GP26, GP27, GP28, GP29,
};

#define DIAGNOSTIC_PIN_COUNT (sizeof(diagnostic_pins) / sizeof(diagnostic_pins[0]))
#define DIAGNOSTIC_SETTLE_US 30
#define HEARTBEAT_INTERVAL_MS 500

static uint32_t heartbeat_timer;
static bool heartbeat_on;

static void diagnostic_release_all(void) {
    for (uint8_t i = 0; i < DIAGNOSTIC_PIN_COUNT; i++) {
        gpio_set_pin_input_high(diagnostic_pins[i]);
    }
}

void matrix_init_custom(void) {
    diagnostic_release_all();
    heartbeat_timer = timer_read32();
    heartbeat_on = false;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool any_connection = false;

    if (timer_elapsed32(heartbeat_timer) >= HEARTBEAT_INTERVAL_MS) {
        heartbeat_timer = timer_read32();
        heartbeat_on = !heartbeat_on;
    }

    diagnostic_release_all();

    for (uint8_t drive = 0; drive < DIAGNOSTIC_PIN_COUNT && !any_connection; drive++) {
        const pin_t drive_pin = diagnostic_pins[drive];

        gpio_write_pin_low(drive_pin);
        gpio_set_pin_output_push_pull(drive_pin);
        wait_us(DIAGNOSTIC_SETTLE_US);

        for (uint8_t sense = 0; sense < DIAGNOSTIC_PIN_COUNT; sense++) {
            if (sense == drive) {
                continue;
            }

            if (!gpio_read_pin(diagnostic_pins[sense])) {
                any_connection = true;
                break;
            }
        }

        gpio_set_pin_input_high(drive_pin);
    }

    // [0,0] heartbeat, [0,1] physical connection detector.
    matrix_row_t new_row0 = 0;
    if (heartbeat_on) {
        new_row0 |= ((matrix_row_t)1 << 0);
    }
    if (any_connection) {
        new_row0 |= ((matrix_row_t)1 << 1);
    }

    bool changed = current_matrix[0] != new_row0;
    current_matrix[0] = new_row0;

    for (uint8_t row = 1; row < MATRIX_ROWS; row++) {
        if (current_matrix[row] != 0) {
            changed = true;
        }
        current_matrix[row] = 0;
    }

    return changed;
}
