#include "matrix.h"
#include "gpio.h"
#include "wait.h"

// Suite16mx R83 multi-endpoint coupling diagnostic.
//
// Purpose: determine whether a single physical keypress electrically couples
// more than one row/column GPIO on the real keyboard, especially on the slave
// half. Unlike the earlier pair mapper, this scanner DOES NOT stop after the
// first detected pair. It records every candidate GPIO that participates in
// any conductive path while a key is held.
//
// Candidate index -> synthetic matrix position -> diagnostic keycode:
//   0  GP27 -> [0,0] -> R
//   1  GP28 -> [0,1] -> E
//   2  GP26 -> [0,2] -> W
//   3  GP29 -> [0,3] -> Q
//   4  GP12 -> [0,4] -> I
//   5  GP13 -> [0,5] -> U
//   6  GP14 -> [0,6] -> Y
//   7  GP15 -> [0,7] -> T
//   8  GP0  -> [1,0] -> F
//   9  GP1  -> [1,1] -> D
//   10 GP2  -> [1,2] -> S
//   11 GP3  -> [1,3] -> A
//
// A healthy single switch should therefore expose exactly TWO diagnostic
// endpoints: one row GPIO (R/E/W/Q) and one column GPIO (I/U/Y/T/F/D/S/A).
// Three or more simultaneous endpoints prove electrical coupling outside the
// normal one-row/one-column switch path.

static const pin_t diagnostic_pins[] = {
    GP27, GP28, GP26, GP29,
    GP12, GP13, GP14, GP15,
    GP0,  GP1,  GP2,  GP3,
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
    bool active[DIAGNOSTIC_PIN_COUNT] = {false};

    diagnostic_release_all();

    // Drive each candidate low in turn and sample every other candidate.
    // Because every pin gets a turn as the driver, diode direction does not
    // matter for discovery of a conductive switch path.
    for (uint8_t drive = 0; drive < DIAGNOSTIC_PIN_COUNT; drive++) {
        const pin_t drive_pin = diagnostic_pins[drive];

        gpio_write_pin_low(drive_pin);
        gpio_set_pin_output_push_pull(drive_pin);
        wait_us(DIAGNOSTIC_SETTLE_US);

        for (uint8_t sense = 0; sense < DIAGNOSTIC_PIN_COUNT; sense++) {
            if (sense == drive) {
                continue;
            }

            if (!gpio_read_pin(diagnostic_pins[sense])) {
                active[drive] = true;
                active[sense] = true;
            }
        }

        gpio_set_pin_input_high(drive_pin);
        wait_us(DIAGNOSTIC_SETTLE_US);
    }

    matrix_row_t new_matrix[MATRIX_ROWS] = {0};

    // Flatten the twelve endpoint indicators into the first twelve matrix
    // positions: row 0 cols 0..7, then row 1 cols 0..3.
    for (uint8_t i = 0; i < DIAGNOSTIC_PIN_COUNT; i++) {
        if (active[i]) {
            new_matrix[i / MATRIX_COLS] |= ((matrix_row_t)1 << (i % MATRIX_COLS));
        }
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
