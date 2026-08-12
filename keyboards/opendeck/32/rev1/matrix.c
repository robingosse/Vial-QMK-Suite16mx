#include "matrix.h"
#include "gpio.h"
#include "wait.h"

// Suite16mx bring-up diagnostic scanner.
//
// This deliberately ignores the declared row/column matrix and diode direction.
// It tests every directed pair among GP0..GP12. All candidate pins are normally
// inputs with pull-ups; one pin at a time is driven low while every other pin is
// sampled. Because every pin gets a turn as the low-side driver, a switch+diode
// connection can be detected regardless of diode orientation.
//
// Any detected connection is reported as matrix position [0,0]. With the current
// Vial test keymap that position emits KC_R. Therefore: if ANY physical key causes
// the Vial Matrix Tester's [0,0] key to light (or types R), the PCB switch network
// is electrically reaching at least two of these MCU GPIOs.
//
// GP14/GP15 are intentionally excluded because they are reserved for TrackPoint
// PS/2 data/clock. GP26 reset is also untouched.

static const pin_t diagnostic_pins[] = {
    GP0, GP1, GP2, GP3, GP4, GP5, GP6,
    GP7, GP8, GP9, GP10, GP11, GP12,
};

#define DIAGNOSTIC_PIN_COUNT (sizeof(diagnostic_pins) / sizeof(diagnostic_pins[0]))
#define DIAGNOSTIC_SETTLE_US 10

static void diagnostic_release_all(void) {
    for (uint8_t i = 0; i < DIAGNOSTIC_PIN_COUNT; i++) {
        gpio_set_pin_input_high(diagnostic_pins[i]);
    }
}

void matrix_init_custom(void) {
    diagnostic_release_all();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool any_connection = false;

    diagnostic_release_all();

    for (uint8_t drive = 0; drive < DIAGNOSTIC_PIN_COUNT && !any_connection; drive++) {
        const pin_t drive_pin = diagnostic_pins[drive];

        // Preload the output latch low before enabling output mode.
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

        // Return the driven pin to a safe high-impedance pulled-up state.
        gpio_set_pin_input_high(drive_pin);
    }

    // Keep the exposed QMK matrix simple: any electrical pair closure becomes
    // one synthetic key at row 0, column 0. Everything else is forced released.
    const matrix_row_t new_row0 = any_connection ? (matrix_row_t)1 : (matrix_row_t)0;
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
