
A Zephyr-based embedded monitoring and communication platform for the NXP FRDM-MCXN236. The project brings together sensor acquisition, CAN FD, LoRa and cellular connectivity, actuator control, and IoT applications, with independent peripheral samples and a modular flagship application.

## Hardware

The target board is the [NXP FRDM-MCXN236](https://docs.zephyrproject.org/latest/boards/nxp/frdm_mcxn236/doc/index.html), built around the MCX-N236 Arm Cortex-M33 microcontroller. The board provides:

- 150 MHz Cortex-M33 MCU
- 1 MiB dual-bank on-chip flash and 352 KiB RAM
- Eight LP Flexcomm interfaces supporting SPI, I2C, or UART
- Two FlexCAN controllers with CAN FD support
- On-chip ADC, USB high-speed host/device, and an onboard MCU-Link debugger
- 8 MiB external QSPI flash

See the [FRDM-MCXN236 board documentation](https://docs.zephyrproject.org/latest/boards/nxp/frdm_mcxn236/doc/index.html) for the board pinout, supported Zephyr features, and hardware references. Peripheral wiring for external modules depends on the application.



## Component connections

The connections below combine the generated Zephyr DTS with the FRDM-MCXN236 [board manual (UM12041)](https://www.nxp.com/docs/en/user-manual/UM12041.pdf) and [schematic (SPF-90828)](https://www.nxp.com/webapp/Download?colCode=SPF-90828), including their connector pinouts and board-level sharing notes.

| Component | FRDM-MCXN236 connection | Notes |
| --- | --- | --- |
| Onboard LEDs | RGB LED D13: red P4_18, green P4_19, blue P4_17 | LEDs are active-low and are already on the board. |
| Onboard buttons | SW2: P0_20; SW3: P0_6 | Both read low when pressed. SW3 is also the ISP mode switch. |
| HC-05 Bluetooth UART | Flexcomm0 LPUART0: TX P0_16, RX P0_17 | Not enabled by the board DTS by default. The schematic shows these pins connected to the onboard PDM microphone through R96/R99, which are DNP by default; populating those links would make the functions conflict. |
| SIM800 cellular UART | Flexcomm2 LPUART2: TX P4_2 (Arduino D1), RX P4_3 (D0) | Connect module TX to MCU RX and module RX to MCU TX. These pins are also routed to the mikroBUS header. Their alternate MCU-Link VCOM links R55/R56 are DNP by default. Use a suitable external supply for the SIM800 and common ground; verify module I/O voltage. |
| Zephyr console UART | Flexcomm4 LPUART4: P1_8/P1_9 | This is the UART selected for the Zephyr console and shell in the DTS and the default MCU-Link VCOM route through populated R53/R54. |
| LM35 analog output | LPADC0 pin options in the generated DTS: P4_23, P4_15, or P4_19 | P4_15 is Arduino A1 and also CAN1 RX; P4_19 is the onboard green LED. P4_23 is not shown as an Arduino header pin in UM12041. Confirm header access and pinmux for the selected channel; do not share these pins with their other functions. P0_25 (Arduino header J2 pin 11, ADC0_B17) is connected to the onboard ambient-light sensor, so do not use it for the LM35 unless you isolate that circuit. |
| MPU6050 over SPI | Flexcomm3 SPI: Arduino D10-D13: CS P1_3, MOSI P1_0, MISO P1_2, SCK P1_1 | The MCU-Link USB-SPI bridge is also routed to D10-D12; check the schematic and board configuration before using those lines for an external device. D13 is also routed to mikroBUS. The MPU6050 is commonly used over I2C; use a bus/pinmux that is free in the application. |
| Onboard accelerometer / I2C sensors | Onboard FXLS8974CFR3 accelerometer U10 uses Flexcomm2 I2C: SDA P4_0, SCL P4_1 | These are the sensor's existing I2C lines; the board provides pull-ups. For external I2C devices, Arduino D18/SDA P1_16 and D19/SCL P1_17 are another board-mapped option, but those pins are also assigned to I3C1 in the DTS. Select only one function for the pins. |
| Servo PWM | FlexPWM1 PWM0: P2_7 (Arduino D5) or P3_12 (Arduino D3) | Configure the chosen PWM output and period in the application. P3_12 is also connected to the onboard QSPI flash through a selectable resistor; prefer D5 unless you have checked the board's resistor configuration. Use a suitable external servo supply and common ground. |
| CAN bus | Use the onboard CAN1 controller and TJA1057 transceiver; connect the bus at J13 | J13 pin 1 is 5 V, pin 2 CAN1_H, pin 3 GND, and pin 4 CAN1_L. No additional CAN transceiver is needed. The MCU-side pins are P4_16 (TX, Arduino A2) and P4_15 (RX, A1); they are shared with the Arduino header and should not be used for another function simultaneously. |
| LoRa module | Use a module-supported UART, SPI, or I2C interface | The board has no dedicated LoRa connector. Choose an available bus and account for the UART, SPI, and I2C pin-sharing notes above. SPI devices can share clock/data lines only when each has a separate chip-select and compatible electrical requirements. |

These are board signal routes, not a guarantee that every peripheral is enabled or every pin is free in a given application. Check the [FRDM-MCXN236 board documentation](https://docs.zephyrproject.org/latest/boards/nxp/frdm_mcxn236/doc/index.html), the [UM12041 user manual](https://www.nxp.com/docs/en/user-manual/UM12041.pdf), and the schematic before wiring. The GPIO uses 3.3 V logic; verify external modules' I/O voltage and power requirements. Flexcomm2 UART and I2C share a Flexcomm instance, while the D18/D19 I2C pins overlap with the I3C assignment.
