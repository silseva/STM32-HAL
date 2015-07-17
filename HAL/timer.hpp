#ifndef STM32_TIMER_HAL_TIMER_BASE_HPP
#define STM32_TIMER_HAL_TIMER_BASE_HPP

#include "peripheral.hpp"

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
        };

        /**
         * PwmMeasure (type)
         *
         * A timer peripheral is used to capture (aka measure)
         * the period length and the Ton length of a PWM signal
         * Please refer to MCU's datasheet and programming manual
         * for further informations.
         * The period value expressed in counter ticks is measured in CCR1,
         * the Ton value in CCR2 
         */
        template<typename P>
        class PwmMeasure : public TimerBase<P> {
            //***************************
            //* Members                 *
            //***************************
        private:
            uint32_t counter_freq;

            //***************************
            //* Methods                 *
            //***************************
        public:
            using TimerBase<P>::periph_base;
            using TimerBase<P>::bus_freq;

            /**
             * @param counter_freq: the timer's counting frequency. It determines the tick width.
             */
            
            PwmMeasure(uint32_t counter_freq) : counter_freq(counter_freq)
            {
                // Set count frequency
                periph_base->PSC = (bus_freq() / counter_freq) - 1;

                // IC1 mapped on TI1
                periph_base->CCMR1 |= TIM_CCMR1_CC1S_0;

                // IC2 mapped on TI1
                periph_base->CCMR1 |= TIM_CCMR1_CC2S_1;

                // Trigger is T1FP1
                periph_base->SMCR |= TIM_SMCR_TS_2 | TIM_SMCR_TS_0;

                // Timer in reset mode, input rising edge clears it
                periph_base->SMCR |= TIM_SMCR_SMS_2;

                // Channel 2 enabled, falling edge
                periph_base->CCER |= TIM_CCER_CC2P | TIM_CCER_CC2E;

                // Capture enabled on channel 1, rising edge
                periph_base->CCER |= TIM_CCER_CC1E;
            }

            /**
             * width_event (method)
             *
             * This checks whether the interrupt flag associated to PWM pulse width measure is set.
             * If so, it clears the flag and returns true, otherwise returns false.
             *
             * @return true if the the flag is set, false otherwise
             */
            bool width_event() {
                if (periph_base->SR & TIM_SR_CC2IF) {
                    periph_base->SR &= ~TIM_SR_CC2IF;
                    return true;
                } else {
                    return false;
                }
            }

            /**
             * period_event (method)
             *
             * This checks whether the interrupt flag associated to PWM period measure is set.
             * If so, it clears the flag and returns true, otherwise returns false.
             *
             * @return true if the the flag is set, false otherwise
             */
            bool period_event() {
                if (periph_base->SR & TIM_SR_CC1IF) {
                    periph_base->SR &= ~TIM_SR_CC1IF;
                    return true;
                } else {
                    return false;
                }
            }

            /**
             * get_pulse_width (method)
             *
             * This inspects the timer register and returns the latest pulse width measure.
             *
             * @return the latest pulse width measure, expressed in counter ticks
             */
            uint32_t get_pulse_width() {
                return periph_base->CCR2;
            }

            /**
             * get_period (method)
             *
             * This inspects the timer register and returns the latest period measure.
             *
             * @return the latest period measure, expressed in counter ticks
             */
            uint32_t get_period() {
                return periph_base->CCR1;
            }
        };

        /**
         * PwmGenerator (type)
         *
         * A timer peripheral is used to generate a pwm signal
         * Please refer to MCU's datasheet and programming manual
         * for further informations.
         * 
         */
        template<typename P>
        class PwmGenerator : public TimerBase<P> {
            //***************************
            //* Members                 *
            //***************************
        private:
            uint32_t counter_freq;
            uint32_t period;

            //***************************
            //* Methods                 *
            //***************************
        public:
            using TimerBase<P>::periph_base;
            using TimerBase<P>::bus_freq;
            
            /**
             * @param counter_freq: the timer's counting frequency. It determines the tick width.
             * @param period: the generated pwm signal's period, in counter ticks
             */

            PwmGenerator(uint32_t counter_freq, uint32_t period) : counter_freq(counter_freq), period(period)
            {
                // Set counter frequency through prescaler
                periph_base->PSC = (bus_freq() / counter_freq) - 1;
                
                // Set pwm period through reload register value
                periph_base->ARR = period;
                
                // Set timer's pwm mode 1, see programming manual
                periph_base->CCMR1 |= TIM_CCMR1_OC1M_1;
                periph_base->CCMR1 |= TIM_CCMR1_OC1M_2;
                
                // CCR1 preload at every update event
                periph_base->CCMR1 |= TIM_CCMR1_OC1PE;
                
                // Enables channel 1
                periph_base->CCER |= TIM_CCER_CC1E;
                periph_base->CCR1 = 0;
                periph_base->CNT = 0;
                
                // Dummy update event in order to load registers
                periph_base->EGR = TIM_EGR_UG;
                
#ifndef _ARCH_CORTEXM3_STM32
                // Only STM32F1xxx have it
                periph_base->BDTR |= TIM_BDTR_MOE;
#endif
                // Auto reload enabled
                periph_base->CR1 |= TIM_CR1_ARPE;
            }

            /**
             * Set pwm signal's ON period, expressed in counter ticks
             */
            
            void set_duty(uint32_t value) {

                if (value <= period)
                    periph_base->CCR1 = value;
            }

        };


        /**
         * Counter (type)
         *
         * A timer peripheral is used as a general
         * purpuose clock-driven counter
         * 
         */
        template<typename P>
        class Counter : public TimerBase<P> {
            //***************************
            //* Members                 *
            //***************************
        private:
            uint32_t counter_freq;
            uint32_t reload_val;

            //***************************
            //* Methods                 *
            //***************************
        public:
            using TimerBase<P>::periph_base;
            using TimerBase<P>::bus_freq;
            
            /**
             * @param counter_freq: counter's tick frequency
             * @param reload_val: counter's auto reload value
             * 
             */

            Counter(uint32_t counter_freq, uint32_t reload_val = 65535) :
                    counter_freq(counter_freq), reload_val(reload_val)
            {
                // Set counter frequency through prescaler
                periph_base->PSC = (bus_freq() / counter_freq) - 1;
                
                // Set counter's auto reload value
                periph_base->ARR = reload_val;
                
                // clear the counter
                periph_base->CNT = 0;
                
                // enable auto reload
                periph_base->CR1 |= TIM_CR1_ARPE;
            }

            /**
             * When called set counter's value to zero
             */
            
            void clear() {
                
                periph_base->CNT = 0;
            }

            /**
             * @return: current counter's value
             */
            
            uint32_t getValue() {

                return periph_base->CNT;
            }

            
            /**
             * @return: true if counter's value equal to or greater than
             * parameter passed, false otherwise
             * @param value: the value the counter's value is compared to
             * 
             */
            bool has_reached(uint32_t value) {

                return (periph_base->CNT >= value);
            }
            
            /**
             * When called it enables the counter (it starts counting)
             */

            void start() {
                TimerBase<P>::enable();
            }
            
            /**
             * When called it disables the counter (it stops counting)
             */

            void stop() {
                TimerBase<P>::disable();
            }
        };
    }
}

#endif //STM32_TIMER_HAL_TIMER_BASE_HPP
