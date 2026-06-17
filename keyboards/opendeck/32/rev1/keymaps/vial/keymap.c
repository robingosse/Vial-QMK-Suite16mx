#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_4x8(
KC_R,    KC_E,    KC_W,    KC_Q,    KC_I,    KC_U,    KC_Y,    KC_T,
KC_F,    KC_D,    KC_S,    KC_A,    KC_SCLN, KC_L,    KC_K,    KC_J,
KC_V,    KC_C,    KC_X,    KC_Z,    KC_COMM, KC_M,    KC_N,    KC_B,
KC_G,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_H
    )
};
// clang-format on
