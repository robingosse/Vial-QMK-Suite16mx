MCU = RP2040
BOOTLOADER = rp2040

RGB_MATRIX_ENABLE = no
RGBLIGHT_ENABLE = no
LED_MATRIX_ENABLE = no
BACKLIGHT_ENABLE = no
OLED_ENABLE = no
ENCODER_ENABLE = no
AUDIO_ENABLE = no

# R84 timing test: use the normal QMK matrix scanner, but add an explicit
# settle delay after selecting each column before sampling the shared rows.
SRC += scan_delay.c

LTO_ENABLE = yes
