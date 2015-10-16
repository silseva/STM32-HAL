
#ifndef PWM_MEASURE_HPP
#define PWM_MEASURE_HPP

#include "timer.hpp"

namespace HAL {
    namespace Timer {

        /**
         * PwmMeasure (type)
         *
         * A timer peripheral is used in input capture mode to measure
         * the period length and the Ton length of a PWM signal.
         * The period length is stored in CCR1, the Ton value in CCR2.
         * Both of them are expressed in terms of number of counter ticks
         * (one counter tick in seconds = 1/counter_freq)
         * 
         * Please refer to MCU's datasheet and programming manual
         * for further informations.
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
             * @param counter_freq: the timer's counting frequency in hertz, it determines
             * the tick width expressed in seconds.
             * Please note that the maximum counter_freq has to be equal to 65535 * pwm_freq,
             * otherwise the counter will incur in a rollover, leading to wrong measurements
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
            bool width_event()
            {
                if (periph_base->SR & TIM_SR_CC2IF)
                {
                    periph_base->SR &= ~TIM_SR_CC2IF;
                    return true;
                }
                
                return false;
            }

            /**
             * period_event (method)
             *
             * This checks whether the interrupt flag associated to PWM period measure is set.
             * If so, it clears the flag and returns true, otherwise returns false.
             *
             * @return true if the the flag is set, false otherwise
             */
            bool period_event()
            {
                if (periph_base->SR & TIM_SR_CC1IF)
                {
                    periph_base->SR &= ~TIM_SR_CC1IF;
                    return true;
                }
                
                return false;
            }

            /**
             * get_pulse_width (method)
             *
             * This inspects the timer register and returns the latest pulse width measure.
             *
             * @return the latest pulse width measure, expressed in counter ticks
             */
            uint32_t get_pulse_width()
            {
                return periph_base->CCR2;
            }

            /**
             * get_period (method)
             *
             * This inspects the timer register and returns the latest period measure.
             *
             * @return the latest period measure, expressed in counter ticks
             */
            uint32_t get_period()
            {
                return periph_base->CCR1;
            }
        };        
    }    
}

#endif
