#include "../defs.h"
#include "../gpio_config/gpio_config_io.c"

// --------------------------------------------------------
// Firmware routines
// --------------------------------------------------------


// Define SRAM BLK 0 Addr 0
#define reg_wb_sram0_addr0   (*(volatile uint32_t*)0x30000000)
// Define SRAM BLK 0 Addr 1
#define reg_wb_sram0_addr1   (*(volatile uint32_t*)0x30000004)

// Define SRAM BLK 1 Addr 0
#define reg_wb_sram1_addr0   (*(volatile uint32_t*)0x30100000)
// Define SRAM BLK 1 Addr 1
#define reg_wb_sram1_addr1   (*(volatile uint32_t*)0x30100004)

// Define WB IO Peripheral Addr
#define reg_wb_io      (*(volatile uint32_t*)0x30800000) // Not used!!!



void set_registers() {
    // Configure all MPRJ_IO as User-Controlled Output Pins

    reg_mprj_io_0  = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_1  = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_2  = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_3  = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_4  = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_5  = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_6  = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_7  = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_8  = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_9  = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_10 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_11 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_12 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_13 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_14 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_15 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_16 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_17 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_18 = GPIO_MODE_USER_STD_OUTPUT;

    reg_mprj_io_19 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_20 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_21 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_22 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_23 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_24 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_25 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_26 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_27 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_28 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_29 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_30 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_31 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_32 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_33 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_34 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_35 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_36 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_37 = GPIO_MODE_USER_STD_OUTPUT;
}


void comm_sram_wb(int address, int block) {

    for (int i=0; i<2; i++) {
        int ram_out;

        // WRITE DATA
        if (address == 0) {
            // Write to address 0
            reg_wb_sram0_addr0 = i;
        } else {
            // Write to address 1
            reg_wb_sram0_addr1 = i;
        }

        // Delay
        delay(5000000);

        // READ DATA
        if (address == 0 && block == 0) {
            ram_out = reg_wb_sram0_addr0; // Read from SRAM BLK 0 ADDR 0

        } else if (address == 0 && block == 1) {
            ram_out = reg_wb_sram1_addr0; // Read from SRAM BLK 1 ADDR 0
 
        } else if (address == 1 && block == 0) {
            ram_out = reg_wb_sram0_addr1; // Read from SRAM BLK 0 ADDR 1

        } else {
            ram_out = reg_wb_sram1_addr1; // Read from SRAM BLK 1 ADDR 1
        }

        // Send SRAM data to GPIO
        reg_gpio_out = ram_out;

        // Delay
        delay(5000000);
    }
}


void main()
{

    // Configure Mgt Area GPIO Pin
    reg_gpio_mode1 = 1;
    reg_gpio_mode0 = 0;
    reg_gpio_ien = 1;
    reg_gpio_oe = 1;

    // Setup GPIO Register
    set_registers();

    // Configure GPIO registers
    gpio_config_io();

    // Initialize serial transfer
    reg_mprj_xfer = 1;
    // Wait till data is completely shifted into GPIO controller
    while (reg_mprj_xfer == 1);

    // Turn OFF Led at startup by driving the GPIO pin HIGH
    reg_gpio_out = 1;

    // Enable wishbone interface
    reg_wb_enable = 1;

	while(1) {

        // Write to Addr 0, Read from Blk 0
        comm_sram_wb(/*ADDR*/ 0, /*SRAM BLK*/ 0);

        // Write to Addr 0, Read from Blk 1
        comm_sram_wb(/*ADDR*/ 0, /*SRAM BLK*/ 1);

        // Write to Addr 1, Read from Blk 0
        comm_sram_wb(/*ADDR*/ 1, /*SRAM BLK*/ 0);

        // Write to Addr 1, Read from Blk 1
        comm_sram_wb(/*ADDR*/ 1, /*SRAM BLK*/ 1);

	}

}
