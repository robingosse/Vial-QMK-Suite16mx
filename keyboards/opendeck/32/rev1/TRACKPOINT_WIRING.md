# SK8707 TrackPoint wiring

This revision enables a Sprintek SK8707-01-004 PS/2 TrackPoint module through the RP2040 PIO PS/2 driver.

## Confirmed wiring

| Wire | RP2040 Zero | SK8707 castellated pin | Function |
|---|---|---:|---|
| Red | `3V3` | 5 | Module power |
| Yellow | `GND` | 1 | Ground |
| Blue | `GP14` | 2 | PS/2 data |
| White | `GP15` | 3 | PS/2 clock |
| Black | `GP26` or disconnected for initial testing | 4 | External reset, active high |

The firmware uses `GP14` for data and `GP15` for clock. The RP2040 PIO driver requires the clock pin to be exactly one GPIO number above the data pin, so this pair is valid.

For the first bench test, the reset wire may be left disconnected. The SK8707 reset input has an internal pull-down, so the module remains out of reset unless deliberately driven high. QMK sends the normal PS/2 reset command during mouse initialization.

## Pull-ups

PS/2 data and clock are open-drain lines and need pull-up resistors. Use:

- 4.7 kΩ from `GP14` / DATA to `3V3`
- 4.7 kΩ from `GP15` / CLOCK to `3V3`

The HolyKeebs bare sensor is the 3.3 V SK8707-01-004. Power the module and both pull-ups from `3V3`; do not connect the module VCC or either GPIO line to 5 V.
