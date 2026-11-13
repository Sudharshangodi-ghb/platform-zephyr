# Sample 02 RGB LED

This sample configures and blinks the three RGB LED channels on the FRDM-MCXN236 board.

The application:

- validates that the LED GPIO devices are ready
- configures each LED channel as an output
- toggles each channel in sequence with a one-second delay

## Build

```sh
west build -p auto -b frdm_mcxn236 sample/02_rgb_led
west flash
```

The RGB LED will blink through its color channels in sequence while the program runs.
