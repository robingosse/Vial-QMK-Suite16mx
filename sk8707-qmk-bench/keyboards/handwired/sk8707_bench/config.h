#pragma once

/*
 * Proven SK8707 startup sequence from josch/qmk_firmware commit 56d9080:
 * hold the active-high hardware RESET line high for 600 ms, then release it.
 * The patched QMK core performs that sequence before starting the RP2040 PIO
 * PS/2 host. Do not disconnect the black RESET wire for this build.
 */
#define PS2_RESET_PIN GP26

/* Keep the first bench test as close as possible to the proven configuration. */
#define PS2_MOUSE_SCROLL_BTN_MASK 0

/* Diagnostic output for QMK Toolbox / hid_listen. */
#define PS2_MOUSE_DEBUG_RAW
#define PS2_MOUSE_DEBUG_HID
