#ifndef STM32_TIMER_HAL_BUS_HPP
#define STM32_TIMER_HAL_BUS_HPP

#include "util.hpp"

namespace HAL {
    namespace Bus {
        template <
                __pointer _bus_base,
                __pointer _enable_register
        >
        struct Bus {
            static constexpr __pointer bus_base = _bus_base;
            static constexpr __pointer enable_register = _enable_register;

            static uint32_t bus_freq() {
                // TODO: Do the magic
            }
        };


        //****************************************************************
        //* CORTEX M4 BUSES                                              *
        //****************************************************************

        // Cortex M4 buses definition
        typedef Bus<(__pointer) (APB1PERIPH_BASE), (__pointer) &(RCC->APB1ENR)> b_APB1;
        typedef Bus<(__pointer) (APB2PERIPH_BASE), (__pointer) &(RCC->APB2ENR)> b_APB2;
        typedef Bus<(__pointer) (AHB1PERIPH_BASE), (__pointer) &(RCC->AHB1ENR)> b_AHB1;
        typedef Bus<(__pointer) (AHB2PERIPH_BASE), (__pointer) &(RCC->AHB2ENR)> b_AHB2;
    }
}

#endif //STM32_TIMER_HAL_BUS_HPP
