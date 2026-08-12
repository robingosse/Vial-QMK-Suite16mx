#include QMK_KEYBOARD_H

// Suite16mx R83 coupling-diagnostic keymap.
// The first twelve synthetic matrix positions identify the twelve real matrix
// GPIOs. Tap one physical key and note which diagnostic letters appear.
//
// R = GP27   E = GP28   W = GP26   Q = GP29
// I = GP12   U = GP13   Y = GP14   T = GP15
// F = GP0    D = GP1    S = GP2    A = GP3
//
// A healthy physical key should produce exactly TWO letters: one from
// R/E/W/Q (row endpoint) and one from I/U/Y/T/F/D/S/A (column endpoint).
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_4x8(
        KC_R, KC_E, KC_W, KC_Q, KC_I, KC_U, KC_Y, KC_T,
        KC_F, KC_D, KC_S, KC_A, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    )
};
