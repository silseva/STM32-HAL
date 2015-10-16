#ifndef TIMER_HPP
#define TIMER_HPP

#include "../peripheral.hpp"

#include <cmath>
#include <algorithm>

namespace HAL {
    namespace Timer {
        typedef TIM_TypeDef raw_timer_t;

        /**
         * TimerBase (type)
         *
         * This represents a raw timer, and only supports low-level operations, such as enabling/disabling.
         *
         */
        template<typename P>
        class TimerBase {
            //***************************
            //* Subtypes                *
            //***************************
        public:
            typedef P peripheral;

            //***************************
            //* Members                 *
            //***************************
        protected:
            // Real members
            bool enabled = false;

        public:
            static constexpr raw_timer_t* const periph_base = (raw_timer_t*) P::periph_base;
            static constexpr uint32_t bus_freq() {
                return P::bus::bus_freq();
            }

            //***************************
            //* Methods                 *
            //***************************
        public:
            TimerBase() {
                P::enable();
            }

            ~TimerBase() {
                disable();
                P::disable();
            }

            bool is_enabled() const {
                return enabled;
            }

            void enable() {
                if (!is_enabled()) {
                    periph_base->CR1 |= TIM_CR1_CEN;
                }
            }

            void disable() {
                if (is_enabled()) {
                    periph_base->CR1 &= ~TIM_CR1_CEN;
                }
            }
            
            static constexpr int mapAlternateFunction()
            {
                return P::periph_base == Peripheral::p_TIM1::periph_base? 1 :
                       P::periph_base == Peripheral::p_TIM2::periph_base? 1 :
                       P::periph_base == Peripheral::p_TIM3::periph_base? 2 :
                       P::periph_base == Peripheral::p_TIM4::periph_base? 2 :
                       P::periph_base == Peripheral::p_TIM5::periph_base? 2 :
                       P::periph_base == Peripheral::p_TIM8::periph_base? 3 :
                       P::periph_base == Peripheral::p_TIM9::periph_base? 3 :
                       P::periph_base == Peripheral::p_TIM10::periph_base? 3 :
                       P::periph_base == Peripheral::p_TIM11::periph_base? 3 : 0;  
            }
        };   
    }
}
#endif //STM32_TIMER_HAL_TIMER_BASE_HPP
