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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_4x8(
        LSFT(KC_A), LSFT(KC_Q), LSFT(KC_A), LCTL(KC_Z), LCTL(KC_E), LCTL(KC_F), LALT(KC_G), LALT(KC_H),
        LSFT(KC_I), LSFT(KC_W), LSFT(KC_S), LCTL(KC_X), LCTL(KC_M), LCTL(KC_N), LALT(KC_O), LALT(KC_P),
        LSFT(KC_B), LSFT(KC_E), LSFT(KC_D), LCTL(KC_C), LCTL(KC_U), LCTL(KC_V), LALT(KC_W), LALT(KC_X),
        LSFT(KC_Y), LSFT(KC_R), LSFT(KC_F), LCTL(KC_V), LCTL(KC_3), LCTL(KC_4), LALT(KC_5), LALT(KC_6)
    )
};
// clang-format on
