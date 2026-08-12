MCU = RP2040
BOOTLOADER = rp2040

RGB_MATRIX_ENABLE = no
RGBLIGHT_ENABLE = no
LED_MATRIX_ENABLE = no
BACKLIGHT_ENABLE = no
OLED_ENABLE = no
ENCODER_ENABLE = no
AUDIO_ENABLE = no

# Temporary Suite16mx bring-up diagnostic: bypass the normal row/column scanner
# and use rev1/matrix.c to probe GP0..GP12 for any switch closure in either
# electrical direction.
CUSTOM_MATRIX = lite
SRC += matrix.c

LTO_ENABLE = yes
