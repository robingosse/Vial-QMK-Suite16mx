# SK8707 RP2040 QMK Bench

A deliberately minimal, non-Vial QMK firmware for proving that a Sprintek SK8707 module can communicate with an RP2040 Zero as a USB HID mouse.

This bench target contains one dummy keyboard position only because QMK requires a matrix. There are no keyboard features, layers, encoders, RGB effects, VIA, or Vial to complicate the test.

## Why this build is different

The strongest directly relevant working example is josch's May 2026 test of an integrated Sprintek SK8707-01-005 on an RP2040. That build required a QMK core patch which:

1. drives the active-high hardware RESET line high for 600 ms and then low;
2. starts the RP2040 PIO PS/2 host after the hardware reset;
3. does not send the normal PS/2 software reset command, which was causing errors;
4. enables pull-ups in the RP2040 PIO pin configuration.

This repository pins that exact proven QMK commit:

- `josch/qmk_firmware@56d908063fc2641c6257c13ad23b8f072cb37579`

The keyboard definition changes only the board-specific pins to match this bench unit.

## Wiring

| SK8707 wire | RP2040 Zero | Function |
|---|---|---|
| Red | `3V3` | Module power |
| Yellow | `GND` | Ground |
| Blue | `GP14` | PS/2 DATA |
| White | `GP15` | PS/2 CLOCK |
| Black | `GP26` | Active-high hardware RESET |

Install external pull-ups:

- 4.7 kΩ from DATA / GP14 to 3V3
- 4.7 kΩ from CLOCK / GP15 to 3V3

The RP2040 PIO PS/2 driver requires CLOCK to be the GPIO immediately after DATA. GP14/GP15 satisfies that requirement.

**Do not disconnect the black RESET wire for this firmware.** It is the key difference from the earlier unsuccessful build.

## Deliberate first-test choices

- Standard QMK stream mode, matching the proven josch and joh RP2040 examples
- No scrolling, acceleration, rotation, TrackPoint register writes, VIA, or Vial
- Hardware reset sequence from the working SK8707 test
- External 4.7 kΩ pull-ups retained even though the pinned QMK patch also enables the RP2040 internal pull-ups
- Console heartbeat every two seconds

Expected console heartbeat:

```text
SK8707_BENCH: alive ps2_error=0x.. data=1 clock=1 reset=0
```

At idle, DATA and CLOCK should normally read high and RESET should read low.

## Build

The GitHub Actions workflow checks out the pinned working QMK fork, copies this keyboard definition into it, verifies that the reset and pull-up patches are present, compiles the firmware, and uploads the UF2 artifact.

The exact target is:

```text
handwired/sk8707_bench:default
```

## Flash and test

1. Hold BOOTSEL while connecting the RP2040 Zero.
2. Copy the generated UF2 to the `RPI-RP2` drive.
3. Open QMK Toolbox before reconnecting the board normally.
4. Confirm the repeating `SK8707_BENCH` heartbeat.
5. Move the TrackPoint and watch both the pointer and console.

## Sources followed

- QMK PS/2 mouse documentation and RP2040 PIO pin-order requirement
- `joh/crkbd-trackpoint`, a documented SK8707 + RP2040 QMK build
- `joh/qmk_firmware` RP2040 TrackPoint branch
- `qmk/qmk_firmware` PR #17893, the merged RP2040 PIO PS/2 driver
- `qmk/qmk_firmware` PR #25936, the proposed hardware-reset and RP2040 pull-up changes
- `josch/qmk_firmware@56d9080`, the exact 2026 SK8707-01-005 working implementation
- Sprintek's current SK8707-01 product specifications

This is a hardware-proving firmware. Once the sensor works reliably here, the same reset sequence and PS/2 configuration can be integrated into the eventual Vial-enabled keyboard firmware.
