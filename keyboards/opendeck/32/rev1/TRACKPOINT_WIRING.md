# SK8707 TrackPoint wiring

This revision enables a Sprintek SK8707 PS/2 TrackPoint module through the RP2040 PIO PS/2 driver.

## Bench-test wiring

| Wire | RP2040 Zero | SK8707 castellated pin | Function |
|---|---|---:|---|
| Red | `3V3` | 5 | Module power |
| Yellow | `GND` | 1 | Ground |
| Blue | `GP14` | 2 | PS/2 data |
| White | `GP15` | 3 | PS/2 clock |
| Black | disconnected during diagnosis | 4 | External reset, active high |

The firmware uses `GP14` for data and `GP15` for clock. The RP2040 PIO driver requires the clock pin to be exactly one GPIO number above the data pin, so this pair is valid.

The SK8707 reset input has an internal pull-down and Sprintek permits it to remain floating when external reset timing is not required. The black wire may later return to `GP26` if deliberate hardware-reset control is implemented, but the present diagnostic firmware does not drive it.

## Pull-ups

PS/2 data and clock are open-drain lines and need pull-up resistors. Use:

- 4.7 kΩ from `GP14` / DATA to `3V3`
- 4.7 kΩ from `GP15` / CLOCK to `3V3`

Both signal pull-ups must remain at 3.3 V because RP2040 GPIOs are 3.3 V logic. For this HolyKeebs SK8707-01-004 bench test, power the module itself from `3V3` as well.

## Diagnostic firmware behaviour

The audit firmware uses PS/2 remote mode, keeps a conservative 1000 ms initialization delay, enables raw and HID mouse debug output, and enables the QMK console. After flashing, run `qmk console`, reconnect the device, and move the pointing stick to see initialization messages and packet traffic.
