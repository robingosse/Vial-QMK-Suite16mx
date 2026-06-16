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
        KC_(KC_A), KC_(KC_Q), KC_(KC_A), KC_(KC_Z), KC_(KC_E), KC_(KC_F), KC_(KC_G), KC_(KC_H),
        KC_(KC_I), KC_(KC_W), KC_(KC_S), KC_(KC_X), KC_(KC_M), KC_(KC_N), KC_(KC_O), KC_(KC_P),
        KC_(KC_B), KC_(KC_E), KC_(KC_D), KC_(KC_C), KC_(KC_U), KC_(KC_V), KC_(KC_W), KC_(KC_X),
        KC_(KC_Y), KC_(KC_R), KC_(KC_F), KC_(KC_V), KC_(KC_3), KC_(KC_4), KC_(KC_5), KC_(KC_6)
    )
};
// clang-format on
