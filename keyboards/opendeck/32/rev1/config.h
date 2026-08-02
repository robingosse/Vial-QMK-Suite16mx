#pragma once

/*
 * SK8707 TrackPoint diagnostics.
 *
 * HolyKeebs' maintained TrackPoint configuration uses remote mode because the
 * default PS/2 streaming mode can initialize unreliably with these modules.
 * The RP2040 PIO pin pair itself is generated from keyboard.json.
 */
#define PS2_MOUSE_USE_REMOTE_MODE

/* Keep the conservative QMK default while diagnosing power-up/initialization. */
#define PS2_MOUSE_INIT_DELAY 1000

/* Emit both raw PS/2 packets and the converted USB HID reports to qmk console. */
#define PS2_MOUSE_DEBUG_RAW
#define PS2_MOUSE_DEBUG_HID
