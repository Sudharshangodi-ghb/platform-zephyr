# Zephyr Smart Embedded Platform

## Getting started

Set up Zephyr and install the SDK using the official [Zephyr Getting Started Guide](https://docs.zephyrproject.org/latest/develop/getting_started/index.html) and [Zephyr SDK installation guide](https://docs.zephyrproject.org/latest/develop/toolchains/zephyr_sdk.html). Verify the board with the Zephyr Hello World sample before cloning this repository.

### 1. Check out Zephyr v4.4.2 in the existing workspace

If you already have the Zephyr repository cloned at `~/zephyrproject/zephyr`, switch to the supported `v4.4.2` release before building:

```sh
cd ~/zephyrproject/zephyr
git status
git checkout v4.4.2
git describe --tags --exact-match
west --version
```

`git describe --tags --exact-match` should report `v4.4.2`, and `west --version` should report a working `west` installation. If the Zephyr repository is not present, first create a Zephyr workspace by following the official getting-started guide, then run these commands from its `zephyr` directory.

### 2. Verify the board with Hello World

From the Zephyr repository directory, build the sample for the FRDM-MCXN236 and flash it to the connected board:

```sh
west build -b frdm_mcxn236/mcxn236 samples/hello_world
west flash
```

The board must be connected to the host through its onboard MCU-Link debugger. Consult the [board documentation](https://docs.zephyrproject.org/latest/boards/nxp/frdm_mcxn236/doc/index.html) if flashing or board setup needs additional configuration.

### 3. Clone this repository

After confirming the board and Zephyr toolchain work:

```sh
cd ~/zephyrproject
git clone https://github.com/Sudharshangodi-ghb/zephyr-smart-embedded-platform.git
cd zephyr-smart-embedded-platform
```
