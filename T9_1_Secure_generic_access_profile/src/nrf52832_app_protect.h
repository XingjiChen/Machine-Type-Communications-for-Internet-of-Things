/*
Include this file after #include "mbed.h"
Execute nrf52_disable_approtect() in main() should ensure the debug port is open.

The change in nRF52832 Gx0 realted to that lock feature is explained in:
[Src1] https://devzone.nordicsemi.com/nordic/nordic-blog/b/blog/posts/working-with-the-nrf52-series-improved-approtect
Other references:
https://infocenter.nordicsemi.com/topic/com.nordic.infocenter.nrf52832.ps.v1.1/dif.html#concept_udr_mns_1s
https://infocenter.nordicsemi.com/topic/errata_nRF52832_Rev3/ERR/nRF52832/Rev3/latest/config_832_249.html

mbed os seems to have fallen behind in recent years due to some internal affairs at ARM:
https://forums.mbed.com/t/will-mbed-os-get-back-its-previous-pace-of-development/15839
It is obvious that for nrf52 they haven't updated the vendor (Nordic Semiconductor) provided support library for a long time.
https://github.com/ARMmbed/mbed-os/tree/mbed-os-6.16.0/targets/TARGET_NORDIC/TARGET_NRF5x/TARGET_SDK_15_0/modules/nrfx
(The latest version can be found at: https://github.com/NordicSemiconductor/nrfx)

Therefore some new header definition needs to be copied from:
[Src2] https://github.com/NordicSemiconductor/nrfx/blob/v2.10.0/mdk/nrf52.h
[Src3] https://github.com/NordicSemiconductor/nrfx/blob/v2.10.0/mdk/nrf52_bitfields.h#L14528
[Src4] https://github.com/NordicSemiconductor/nrfx/blob/v2.10.0/mdk/system_nrf52_approtect.h#L44
*/

// CREDITS: thanks to Zhang Tianshu, who has taken ELEC-E7221 in 2023 spring semester. 

#ifndef MBED_H
#include "mbed.h" // Just for code highlight when opened alone
#endif
#pragma once 
// Src2
typedef struct {                                /*!< (@ 0x40000000) APPROTECT Structure                                        */
  __IM  uint32_t  RESERVED[340];
  __IOM uint32_t  FORCEPROTECT;                 /*!< (@ 0x00000550) Software force enable APPROTECT mechanism until
                                                                    next reset. This register can only be written
                                                                    once.                                                      */
  __IM  uint32_t  RESERVED1;
  __IOM uint32_t  DISABLE;                      /*!< (@ 0x00000558) Software disable APPROTECT mechanism                       */
} NRF_APPROTECT_Type;                           /*!< Size = 1372 (0x55c)                                                       */

#define NRF_APPROTECT_BASE          0x40000000UL
#define NRF_APPROTECT               ((NRF_APPROTECT_Type*)     NRF_APPROTECT_BASE)
// Src3
#define UICR_APPROTECT_PALL_HwDisabled (0x5AUL) /*!< Hardware disable of access port protection for devices where access port protection is controlled by hardware and software */

// Src1
inline void nrf52_disable_approtect() {
    if ((NRF_UICR->APPROTECT & UICR_APPROTECT_PALL_Msk) !=
        (UICR_APPROTECT_PALL_HwDisabled << UICR_APPROTECT_PALL_Pos)) {

        NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen;
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}

        NRF_UICR->APPROTECT = ((NRF_UICR->APPROTECT & ~((uint32_t)UICR_APPROTECT_PALL_Msk)) |
            (UICR_APPROTECT_PALL_HwDisabled << UICR_APPROTECT_PALL_Pos));

        NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
    }

    // Src4
    /* Load APPROTECT soft branch from UICR.
       If UICR->APPROTECT is disabled, POWER->APPROTECT will be disabled. */
    NRF_APPROTECT->DISABLE = NRF_UICR->APPROTECT;
}
