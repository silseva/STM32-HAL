#ifndef BUS_HPP
#define BUS_HPP

#include "util.hpp"

#ifndef _MIOSIX
#include "cortex/stm32f4xx.h"
#else
#include "miosix.h"
#endif

namespace HAL {
    namespace Bus {
        template <
                __pointer _bus_base,
                __pointer _enable_register,
                __mask _prescaler_mask
        >
        struct Bus {
            static constexpr __pointer bus_base = _bus_base;
            static constexpr __pointer enable_register = _enable_register;
            static constexpr __mask prescaler_mask = _prescaler_mask;

            static uint32_t bus_freq() {
                uint32_t base_freq = SystemCoreClock;
                uint32_t prescaler_bits = (RCC->CFGR & prescaler_mask);

                uint32_t active_bit = prescaler_bits & ((prescaler_mask + 1) >> 1);
                if (active_bit)
                    base_freq /= ((base_freq - active_bit) / (base_freq & (-base_freq)));
                return base_freq;
            }
        };


        //****************************************************************
        //* CORTEX M4 BUSES                                              *
        //****************************************************************

        // Cortex M4 buses definition
        typedef Bus<
                (__pointer) (APB1PERIPH_BASE),
                (__pointer) &(RCC->APB1ENR),
                (__mask) RCC_CFGR_PPRE1
        > b_APB1;
        typedef Bus<
                (__pointer) (APB2PERIPH_BASE),
                (__pointer) &(RCC->APB2ENR),
                (__mask) RCC_CFGR_PPRE2
        > b_APB2;
        typedef Bus<
                (__pointer) (AHB1PERIPH_BASE),
                (__pointer) &(RCC->AHB1ENR),
                (__mask) RCC_CFGR_HPRE
        > b_AHB1;
        typedef Bus<
                (__pointer) (AHB2PERIPH_BASE),
                (__pointer) &(RCC->AHB2ENR),
                (__mask) RCC_CFGR_HPRE
        > b_AHB2;
    }
}

#endif //STM32_TIMER_HAL_BUS_HPP
