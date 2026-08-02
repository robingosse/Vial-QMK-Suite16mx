# SK8707 TrackPoint wiring

This revision enables a Sprintek SK8707 PS/2 TrackPoint module through the RP2040 PIO PS/2 driver.

## Confirmed wiring

| Wire | RP2040 Zero | SK8707 castellated pin | Function |
|---|---|---:|---|
| Red | `5V` | 5 | Module power |
| Yellow | `GND` | 1 | Ground |
| Blue | `GP14` | 2 | PS/2 data |
| White | `GP15` | 3 | PS/2 clock |
| Black | `GP26` | 4 | External reset, active high |

The firmware uses `GP14` for data and `GP15` for clock. The RP2040 PIO driver requires the clock pin to be exactly one GPIO number above the data pin, so this pair is valid.

`GP26` is presently left as a high-impedance input. The SK8707 reset input has an internal pull-down, so the module remains out of reset unless firmware deliberately drives this line high in a later revision. QMK also sends the normal PS/2 reset command during mouse initialization.

## Pull-ups

PS/2 data and clock are open-drain lines and need pull-up resistors. Use:

- 4.7 kΩ from `GP14` / DATA to `3V3`
- 4.7 kΩ from `GP15` / CLOCK to `3V3`

Do not pull either GPIO up to 5 V. The TrackPoint may be powered from 5 V, but RP2040 GPIO signalling must remain at 3.3 V.
