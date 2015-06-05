#ifndef STM32_TIMER_HAL_BUS_HPP
#define STM32_TIMER_HAL_BUS_HPP

#include "util.hpp"

namespace HAL {
    namespace Bus {
        template <
                __pointer _bus_base
        >
        struct Bus {
            static constexpr __pointer bus_base = _bus_base;

            static uint32_t bus_freq() {
                // TODO: Do the magic
            }

            static void set_bus_freq(uint32_t new_freq) {
                // TODO: Do the magic
                bus_freq = new_freq;
            }
        };


        //****************************************************************
        //* CORTEX M4 BUSES                                              *
        //****************************************************************

        // Cortex M4 buses definition
        typedef Bus<(__pointer) (__STM_32_APB1PERIPH_BASE)> APB1;
        typedef Bus<(__pointer) (__STM_32_APB2PERIPH_BASE)> APB2;
        typedef Bus<(__pointer) (__STM_32_AHB1PERIPH_BASE)> AHB1;
        typedef Bus<(__pointer) (__STM_32_AHB2PERIPH_BASE)> AHB2;
    }
}

#endif //STM32_TIMER_HAL_BUS_HPP
