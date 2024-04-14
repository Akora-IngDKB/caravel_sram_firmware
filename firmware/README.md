# SRAM Firmware for Caravel SRAM Test Chip

## Caravel SRAM Test Chip [<sup>ref</sup>](https://github.com/mtomlin5/caravel_sram_test)
This is a simple project connecting a 256x32 SRAM block to the wishbone interface for testing. The SRAM block is directly connected to the wishbone bus at address 0x3000000. An additional peripheral was made to write to the io ports when address 0x30008000 is written to.


## Firmware
This firmware writes data to the SRAM and then reads the data to control the LED pin connected to the Management Area GPIO pin.

### Routine
1. Enable wishbone interface.
   
2. Write `1` to `0x30000000`. (Store 1 at address 0 of SRAM Block/Port 0)
   
3. Read data from `0x30000000` and send to Mgt GPIO register. (Read from address 0 of SRAM Block/Port 0)
   
4. Read data from `0x30800000` and send to Mgt GPIO register. (Read from address 0 of SRAM Block/Port 1)
5. etc...


## Setup

### Install Toolchain for Compiling Code

#### For Mac: https://github.com/riscv/homebrew-riscv
#### For Linux: https://github.com/riscv/riscv-gnu-toolchain


### Important !!! (Read before working on Nucleo)
- Set the FLASH mount path in the nucleo Makefile (nucleo/Makefile).
```Makefile
# Nucleo Flash volume path  (Line 1)
FLASH=/Volumes/PYBFLASH/  # (Line 2)
```
 - If running on Windows or Linux, uncomment Line 134.
```Makefile
setup: check-python                 # (Line 132)
   python3 -m pip install rshell    # (Line 133)
   python3 -m pip install mpy-cross # (Line 134)
   python3 -m pip install mpremote  # (Line 135)
   python3 -m pip install pyftdi    # (Line 136)
```

- Set the riscv-toolchain path to your correct local installation.
```Makefile
TOOLCHAIN_PATH=/opt/homebrew/opt/riscv-gnu-toolchain/bin/ # (Line 140)
TOOLCHAIN_PREFIX=riscv64                                  # (Line 144)
```

### Nucleo
First, go through the instructions in to configure the GPIOs through the STM Nucleo development board. [See here](nucleo/README.md)


## Flash Firmware
Flash the current firmware in [sram_firmware.c](sram_firmware/sram_firmware.c) to the Caravel SoC.

```cmd
$ cd firmware/sram_firmware
$ make clean flash_nucleo
```
This will delete old compiled files, recompile the firmware and upload to Caravel SoC.