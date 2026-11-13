# Accelerometer Tilt Demo — FRDM-MCXN236

This sample reads the on-board `FXLS8974` accelerometer and uses the RGB LED to indicate the board orientation.

Files:
- [src/main.c](./src/main.c)
- [boards/frdm_mcxn236.overlay](./boards/frdm_mcxn236.overlay)
- [prj.conf](./prj.conf)

## What this sample does

The board includes an accelerometer connected over I2C. This sample:

- initializes the `fxls8974` device from the board overlay
- fetches acceleration data on the X, Y, and Z axes
- logs the raw accelerometer values
- changes the RGB LED color based on the detected tilt/orientation

The board is treated as a simple tilt sensor:

- Z-axis negative tilt: white LED
- X-axis positive tilt: blue LED
- X-axis negative tilt: red LED
- Y-axis positive tilt: yellow LED
- Y-axis negative tilt: cyan LED
- level board: green LED

## Device tree configuration

The accelerometer is defined in the overlay file:

```dts
&flexcomm2_lpi2c2 {
    status = "okay";

    fxls8974: fxls8974@18 {
        compatible = "nxp,fxls8974";
        reg = <0x18>;
        status = "okay";
    };
};
```

The application uses the `DT_NODELABEL(fxls8974)` node and reads the device through the Zephyr sensor API.

## Sensor workflow

```text
FXLS8974 accelerometer
         │
         ▼
   sensor_sample_fetch()
         │
         ▼
  sensor_channel_get() for X/Y/Z
         │
         ▼
 convert to g values
         │
         ▼
 update RGB LED color
```

## Example output

```text
[00:00:00.500,000] <inf> main_accelerometer: IMU tilt indicator using the on-board FXLS8974 accelerometer
[00:00:01.000,000] <inf> main_accelerometer: X=0.00  Y=0.00  Z=9.81
[00:00:01.100,000] <inf> main_accelerometer: X=1.80  Y=-0.30  Z=9.40
```

## Build and flash

```bash
west build -p auto -b frdm_mcxn236 platform-zephyr/frdm-mcxn236/sample/04_accelerometer
west flash
```

## Notes

- The RGB output is controlled by the board LEDs aliased as `led0`, `led1`, and `led2`.
- The sample uses the accelerometer to detect tilt in real time and is intended to be a simple orientation indicator rather than a full motion-tracking application.

This sample demonstrates how to initialize a sensor, read acceleration values, and map the result to a user-visible LED output on the FRDM-MCXN236.
