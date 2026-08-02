#include QMK_KEYBOARD_H
#include "gpio.h"
#include "ps2.h"

/*
 * quantum_init() reloads debug_config from EEPROM. led_init_ports() runs after
 * that reload but before ps2_mouse_init(), so this is early enough to expose
 * reset/BAT/DevID diagnostics without modifying more of QMK core.
 */
void led_init_ports(void) {
    debug_enable = true;
    debug_mouse  = true;
}

void keyboard_post_init_user(void) {
    debug_enable = true;
    debug_mouse  = true;
    dprintf("SK8707_BENCH: firmware started; DATA=GP14 CLOCK=GP15 RESET=GP26\n");
}

void housekeeping_task_user(void) {
    static uint32_t heartbeat_timer = 0;

    if (timer_elapsed32(heartbeat_timer) >= 2000) {
        heartbeat_timer = timer_read32();
        dprintf(
            "SK8707_BENCH: alive ps2_error=0x%02X data=%u clock=%u reset=%u\n",
            ps2_error,
            (unsigned)gpio_read_pin(GP14),
            (unsigned)gpio_read_pin(GP15),
            (unsigned)gpio_read_pin(GP26)
        );
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(KC_NO)
};
