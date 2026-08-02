#include QMK_KEYBOARD_H

/*
 * This hook runs after quantum_init() reloads debug_config from EEPROM, but
 * before ps2_mouse_init(). The earlier keyboard_pre_init_user() hook was too
 * early: quantum_init() overwrote the debug flags before the PS/2 reset/BAT
 * exchange began.
 *
 * This diagnostic keymap has no lock-LED pins, so overriding the weak
 * led_init_ports() hook is safe and gives us the precise startup point needed.
 */
void led_init_ports(void) {
    debug_enable = true;
    debug_mouse  = true;
}

/*
 * Emit a newline-terminated heartbeat after USB enumeration. This distinguishes
 * "QMK Toolbox/hid_listen is not attached" from "the TrackPoint is silent".
 */
void housekeeping_task_user(void) {
    static uint32_t heartbeat_timer = 0;

    if (timer_elapsed32(heartbeat_timer) >= 2000) {
        print("TRACKPOINT_DIAG: firmware alive; HID console working\n");
        heartbeat_timer = timer_read32();
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_1, KC_2, KC_3, KC_MUTE,
        KC_4, KC_5, KC_6, KC_7
    ),

    [1] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [2] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [3] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

#if defined(ENCODER_MAP_ENABLE)

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};

#endif
