MCU = RP2040
BOOTLOADER = rp2040

RGB_MATRIX_ENABLE = no
RGBLIGHT_ENABLE = no
LED_MATRIX_ENABLE = no
BACKLIGHT_ENABLE = no
OLED_ENABLE = no
ENCODER_ENABLE = no
AUDIO_ENABLE = no

# R83 diagnostic: use rev1/matrix.c to expose every GPIO endpoint involved in
# a physical keypress instead of the normal matrix scanner.
CUSTOM_MATRIX = lite
SRC += matrix.c

LTO_ENABLE = yes
