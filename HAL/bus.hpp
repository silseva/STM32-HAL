#ifndef STM32_TIMER_HAL_BUS_HPP
#define STM32_TIMER_HAL_BUS_HPP

#include "util.hpp"

namespace HAL {
    namespace Bus {
        template <
                __pointer _bus_base,
                uint32_t _bus_freq
        >
        struct Bus {
            static constexpr __pointer bus_base = _bus_base;
            static constexpr uint32_t bus_freq = _bus_freq;
        };


        //****************************************************************
        //* CORTEX M4 BUSES                                              *
        //****************************************************************

        // Cortex M4 buses definition
        typedef Bus<(__pointer) (__STM_32_APB1PERIPH_BASE), 0> APB1; // FIXME: set correct bus freqs
        typedef Bus<(__pointer) (__STM_32_APB2PERIPH_BASE), 0> APB2;
        typedef Bus<(__pointer) (__STM_32_AHB1PERIPH_BASE), 0> AHB1;
        typedef Bus<(__pointer) (__STM_32_AHB2PERIPH_BASE), 0> AHB2;
    }
}

#endif //STM32_TIMER_HAL_BUS_HPP
