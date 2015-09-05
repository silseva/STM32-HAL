#ifndef STM32_TIMER_HAL_UTIL_HPP
#define STM32_TIMER_HAL_UTIL_HPP

#include <cstdint>

#ifndef _MIOSIX
#include "cortex/stm32f4xx.h"
#else
#include "miosix.h"
#endif

namespace HAL {
    /**
     * __pointer (type)
     *
     * This is an ugly trick to work around the fact that C++ templates require non-type pointer arguments to be
     * valid pointers to variables or functions. We basically cast pointers to uint32_t back and forth to make
     * things work.
     */
    typedef uint32_t __pointer;

    /**
     * __mask (type)
     *
     * //TODO
     */
    typedef uint32_t __mask;
}

#endif //STM32_TIMER_HAL_UTIL_HPP
