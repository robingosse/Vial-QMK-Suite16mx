/* Copyright 2020 cmdremily
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

void keyboard_post_init_user(void) {
    eeconfig_init();
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_4x8(
        KC_A, KC_Q, KC_A, KC_Z, KC_E, KC_F, KC_G, KC_H,
        KC_I, KC_W, KC_S, KC_X, KC_M, KC_N, KC_O, KC_P,
        KC_B, KC_E, KC_D, KC_C, KC_U, KC_V, KC_W, KC_X,
        KC_Y, KC_R, KC_F, KC_V, KC_3, KC_4, KC_5, KC_6
    )
};
// clang-format on
