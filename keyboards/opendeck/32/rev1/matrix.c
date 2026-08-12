#include "matrix.h"
#include "gpio.h"
#include "wait.h"

// Suite16mx GPIO pair mapper.
//
// This diagnostic ignores the declared matrix topology and scans every directed
// pair among all signal GPIOs exposed by the RP2040-Zero footprint:
// GP0..GP15 and GP26..GP29.
//
// When a physical switch closure is found, BOTH GPIO endpoints are exposed as
// synthetic QMK matrix keys. Candidate index N maps to flattened matrix position N:
//   0..7   -> row 0, cols 0..7
//   8..15  -> row 1, cols 0..7
//   16..19 -> row 2, cols 0..3
//
// With the existing Suite16mx test keymap this gives a printable two-character
// signature for each physical switch, allowing the real PCB matrix wiring to be
// reconstructed without opening the keyboard.

static const pin_t diagnostic_pins[] = {
    GP0, GP1, GP2, GP3, GP4, GP5, GP6, GP7,
    GP8, GP9, GP10, GP11, GP12, GP13, GP14, GP15,
    GP26, GP27, GP28, GP29,
};

#define DIAGNOSTIC_PIN_COUNT (sizeof(diagnostic_pins) / sizeof(diagnostic_pins[0]))
#define DIAGNOSTIC_SETTLE_US 30

static void diagnostic_release_all(void) {
    for (uint8_t i = 0; i < DIAGNOSTIC_PIN_COUNT; i++) {
        gpio_set_pin_input_high(diagnostic_pins[i]);
    }
}

void matrix_init_custom(void) {
    diagnostic_release_all();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    int8_t endpoint_a = -1;
    int8_t endpoint_b = -1;

    diagnostic_release_all();

    for (uint8_t drive = 0; drive < DIAGNOSTIC_PIN_COUNT && endpoint_a < 0; drive++) {
        const pin_t drive_pin = diagnostic_pins[drive];

        gpio_write_pin_low(drive_pin);
        gpio_set_pin_output_push_pull(drive_pin);
        wait_us(DIAGNOSTIC_SETTLE_US);

        for (uint8_t sense = 0; sense < DIAGNOSTIC_PIN_COUNT; sense++) {
            if (sense == drive) {
                continue;
            }

            if (!gpio_read_pin(diagnostic_pins[sense])) {
                endpoint_a = (int8_t)drive;
                endpoint_b = (int8_t)sense;
                break;
            }
        }

        gpio_set_pin_input_high(drive_pin);
    }

    matrix_row_t new_matrix[MATRIX_ROWS] = {0};

    if (endpoint_a >= 0 && endpoint_b >= 0) {
        const uint8_t a = (uint8_t)endpoint_a;
        const uint8_t b = (uint8_t)endpoint_b;

        new_matrix[a / MATRIX_COLS] |= ((matrix_row_t)1 << (a % MATRIX_COLS));
        new_matrix[b / MATRIX_COLS] |= ((matrix_row_t)1 << (b % MATRIX_COLS));
    }

    bool changed = false;
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        if (current_matrix[row] != new_matrix[row]) {
            changed = true;
        }
        current_matrix[row] = new_matrix[row];
    }

    return changed;
}
