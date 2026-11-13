# Sample Applications

This directory contains the Zephyr sample applications for the FRDM-MCXN236 board.

## Included samples

- `01_led` — simple LED blink demo using the board LED and startup logging
- `02_rgb_led` — RGB LED sequence demo that toggles red, green, and blue channels one at a time
- `03_silicon_temp` — reads and logs the MCU's internal silicon temperature using the on-chip silicon temperature sensor
- `04_accelerometer` — reads the on-board FXLS8974 accelerometer and updates the RGB LED to indicate tilt/orientation

## Build a sample

From the Zephyr workspace root, build any sample with the board target `frdm_mcxn236`:

```sh
# 01_led
west build -p auto -b frdm_mcxn236 platform-zephyr/frdm-mcxn236/sample/01_led
west flash
```

```sh
# 02_rgb_led
west build -p auto -b frdm_mcxn236 platform-zephyr/frdm-mcxn236/sample/02_rgb_led
west flash
```

```sh
# 03_silicon_temp
west build -p auto -b frdm_mcxn236 platform-zephyr/frdm-mcxn236/sample/03_silicon_temp
west flash
```

```sh
# 04_accelerometer
west build -p auto -b frdm_mcxn236 platform-zephyr/frdm-mcxn236/sample/04_accelerometer
west flash
```

Adjust the board target or path if your local workspace layout differs.
