#pragma once

#define VIAL_KEYBOARD_UID {0x52, 0x6F, 0x62, 0x69, 0x6E, 0x31, 0x36, 0x59}

// Diagnostic-only: allow Vial access without a physical unlock combo while
// the switch matrix itself is under test. Remove this for production firmware.
#define VIAL_INSECURE

#define VIAL_UNLOCK_COMBO_ROWS {0, 0}
#define VIAL_UNLOCK_COMBO_COLS {1, 0}
