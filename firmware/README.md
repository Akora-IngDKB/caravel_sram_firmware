# SRAM Firmware for Caravel SRAM Test Chip

## Caravel SRAM Test Chip [<sup>ref</sup>](https://github.com/mtomlin5/caravel_sram_test)
This is a simple project connecting a 256x32 SRAM block to the wishbone interface for testing. The SRAM block is directly connected to the wishbone bus at address 0x3000000. An additional perpherial was made to write to the io ports when address 0x30008000 is written to.


## Firmware
This firmware writes data to the SRAM and then reads the data to control the LED pin connected to the Management Area GPIO pin.

### Routine
1. Enable wishbone interface.
   
2. Write `1` to `0x30000000`. (Store 1 at address 0 of SRAM Block/Port 0)
   
3. Read data from `0x30000000` and send to Mgt GPIO register. (Read from address 0 of SRAM Block/Port 0)
   
4. Read data from `0x30800000` and send to Mgt GPIO register. (Read from address 0 of SRAM Block/Port 1)
5. etc...


## Setup

### Nucleo
First, go through the instructions in to configure the GPIOs through the STM Nucleo development board. [See here](nucleo/README.md)

### Flash Firmware
