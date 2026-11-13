# Sample 01 LED

This sample combines the Zephyr Hello World pattern with a simple LED blink application for the FRDM-MCXN236 board.

Build:

```sh
west build -p auto -b frdm_mcxn236 sample/01_led
west flash
```

The app prints a startup message and blinks the board LED every 500 ms.
