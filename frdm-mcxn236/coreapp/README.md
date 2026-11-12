# CoreApp LED Demo

This core application demonstrates a minimal Zephyr firmware build for the FRDM-MCXN236 board. It combines a startup log message with an LED blink pattern to verify that the board, GPIO driver, and build configuration are working correctly.

## Features

- prints a startup message on boot
- configures the board LED as an output
- toggles the LED at a regular interval
- can be used as a simple baseline for further board-specific development

## Build

```sh
west build -p auto -b frdm_mcxn236/mcxn236 coreapp
west flash
```

This project is useful as a quick validation app before moving to more advanced samples or custom firmware.
