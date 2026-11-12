# Sample Applications

This directory contains Zephyr sample applications for the FRDM-MCXN236 board.

## Included samples

- `01_led` — simple LED blink demo using the board LED and startup logging
- `02_rgb_led` — RGB LED sequence demo that toggles red, green, and blue channels one at a time

## Build a sample

From the Zephyr workspace root:

```sh
west build -p auto -b frdm_mcxn236/mcxn236 sample/01_led
west flash
```

Or for the RGB sample:

```sh
west build -p auto -b frdm_mcxn236/mcxn236 sample/02_rgb_led
west flash
```

Update the board target or path as needed for your local setup.
