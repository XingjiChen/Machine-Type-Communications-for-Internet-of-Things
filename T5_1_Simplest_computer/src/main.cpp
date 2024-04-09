/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#define UICR_APPROTECT_PALL_HwDisabled 0x5A // -> this is used to prevent device lock bit modifications

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms


int main()
{
    /////////////////////////////////////////////////////////
    // the following must always present in main files
    if ((NRF_UICR->APPROTECT & UICR_APPROTECT_PALL_Msk) !=
		(UICR_APPROTECT_PALL_HwDisabled << UICR_APPROTECT_PALL_Pos)) {

        NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen;
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}

        NRF_UICR->APPROTECT = ((NRF_UICR->APPROTECT & ~((uint32_t)UICR_APPROTECT_PALL_Msk)) |
		    (UICR_APPROTECT_PALL_HwDisabled << UICR_APPROTECT_PALL_Pos));

        NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
	}
    ///////////////////////////////////////////////////////////
    // Initialise the digital pin LED1 as an output

    /*---------------------------------------------------------*/
    // Start your implementation below
    DigitalOut led(LED1);
    DigitalIn button(BUTTON1);

    while (true) {
        //led = !led;
        if(button == 1) {
            led = 1;
        } else {
            led = 0;
        }
        
        ThisThread::sleep_for(BLINKING_RATE);
    }
}