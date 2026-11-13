# Silicon Temperature Sensor Demo — FRDM-MCXN236

This sample reads the MCU's internal silicon temperature using the built-in `nxp,lpadc-temp40` sensor.

Files:
- [src/main.c](./src/main.c)
- [boards/frdm_mcxn236.overlay](./boards/frdm_mcxn236.overlay)

## What this component does

The temperature-sensing diode is built into the MCU silicon. Inside the SoC,
it is connected to the LPADC through input channel 26A. This connection is
inside the chip, so no external wire or board pin is needed. This sample:

- configures LPADC0 to select input channel 26A
- reads the temperature every second
- prints the value through Zephyr logging

This is a simple way to monitor the chip temperature without any external sensor.

## Why the LPADC setup is needed

The sensor does not connect like a normal external GPIO sensor. It uses the internal ADC path inside the MCU.

The important settings are:

- `reg = <0>`: selects command buffer 0; this is not physical ADC input channel 0
- `zephyr,input-positive = <MCUX_LPADC_CH26A>`: selects the internal sensor input
- `zephyr,gain` and `zephyr,reference`: configure the ADC conversion
- `zephyr,acquisition-time`: gives the internal sensor enough time to charge

The sensor driver uses 16-bit resolution and 7x oversampling for its
temperature measurements.

## How the internal sensor connects

```text
┌────────────────────── MCU SoC ──────────────────────┐
│                                                     │
│  Internal temperature diode                        │
│             │                                       │
│             │ built-in connection inside the chip  │
│             ▼                                       │
│  LPADC0 input mux: channel 26A ──► LPADC conversion │
│                                                     │
└─────────────────────────────────────────────────────┘
                         │
                         ▼
             Zephyr sensor driver/API
                         │
                         ▼
                  LOG_INF() output
```

Channel 26A is an LPADC input inside the SoC, not an external pin. In the
overlay, `zephyr,input-positive = <MCUX_LPADC_CH26A>` tells LPADC0 to read that
input. `reg = <0>` selects command buffer 0, which holds the ADC conversion
settings; it does not mean channel 0.

## Temperature reading flow

This shows what happens after LPADC0 selects the internal sensor on channel
26A:

```text
┌──────────────────────┐
│ Internal diode       │
│ (LPADC0 channel 26A) │
└──────────┬───────────┘
           ▼
┌──────────────────────┐
│ LPADC0 samples the   │
│ sensor voltage       │
└──────────┬───────────┘
           ▼
┌──────────────────────┐
│ ADC conversion       │
│ Gain: 1              │
│ Reference: EXTERNAL0 │
│ 16-bit, oversample 7 │
└──────────┬───────────┘
           ▼
┌──────────────────────┐
│ Sensor driver        │
│ converts reading to  │
│ temperature          │
└──────────┬───────────┘
           ▼
┌──────────────────────┐
│ Zephyr sensor API    │
│ and LOG_INF() output │
└──────────────────────┘
```

## Example output

```text
*** Booting Zephyr OS build v4.4.0-313-g4e7fcbb2d84d ***
[00:00:00.002,000] <inf> silicon_logger: Device temp0 is initialized successfully
[00:00:01.003,000] <inf> silicon_logger: Silicon Die Temperature: 32.40 C
[00:00:02.004,000] <inf> silicon_logger: Silicon Die Temperature: 32.41 C
[00:00:03.005,000] <inf> silicon_logger: Silicon Die Temperature: 32.41 C
```

The program reads and prints the temperature once every second.

## Build and flash

```bash
west build -p always -b frdm_mcxn236 platform-zephyr/frdm-mcxn236/sample/03_silicon_temp
west flash
```

## Troubleshooting

- Boot error: check that LPADC0 and the `temp0` sensor are enabled in the overlay.
- ADC setup error: verify that `zephyr,input-positive` is set to `MCUX_LPADC_CH26A`.

This sample demonstrates how Zephyr reads the MCU's internal silicon
temperature sensor through LPADC0.
