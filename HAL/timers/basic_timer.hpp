
#ifndef BASIC_TIMER_HPP
#define BASIC_TIMER_HPP

#include "timer.hpp"

namespace HAL {
    namespace Timer {
        
        /**
         * BasicTimer (type)
         *
         * This represents a basic timer peripheral and supports only basic functions.
         * It is constituted of a 16 bit auto-reload upcounting register with user-defineable reload value
         * and it has a 16 bit programmable prescaler to divide the counter's input clock frequency.
         * Counter's original (not divided by prescaler) clock frequency can be get calling the bus_freq() method
         * 
         * refer to programming manual for further informations
         * 
         */
        template<typename P>
        class BasicTimer : public TimerBase<P> {
            //***************************
            //* Members                 *
            //***************************
        private:
//             uint32_t counter_freq;
//             uint16_t reload_val;

            //***************************
            //* Methods                 *
            //***************************
        public:
            using TimerBase<P>::periph_base;
            using TimerBase<P>::bus_freq;
            
            /**
             * The counter is incremented by one every 1/(counter_freq) seconds
             * and counts from 0 to reload_val, then restarts from 0
             * 
             * @param counter_freq: counter's tick frequency
             * @param reload_val: counter's auto reload value
             * 
             */

            BasicTimer(uint32_t counter_freq, uint16_t reload_val = 65535) /* :
                    counter_freq(counter_freq), reload_val(reload_val) */
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
             * 
             * When called enables the counter (it starts counting)
             * 
             */

            inline void start()
            {
                TimerBase<P>::enable();
            }
            
            /**
             * 
             * When called disables the counter (it stops counting)
             * 
             */

            inline void stop()
            {
                TimerBase<P>::disable();
            }

            /**
             * 
             * When called set timer's counter value to zero
             * 
             */
            
            void clear()
            {    
                periph_base->CNT = 0;
            }

            /**
             * 
             * @return: current counter's value
             * 
             * NOTE: it returns a 32 bit value for compatibility with
             * 32 bit timers present in some devices, but usually timers are 16 bit counters
             * 
             * Check device's datasheet for more informations
             * 
             */
            
            uint32_t getValue()
            {
                return periph_base->CNT;
            }

            
            /**
             * Chech if counter has reached (is equal to or greater than) a
             * defined value.
             * 
             * @return: true if counter's value equal to or greater than
             * parameter passed, false otherwise
             * @param value: the value the counter's value is compared to
             * 
             */
            
            bool has_reached(uint32_t value)
            {
                return (periph_base->CNT >= value);
            }
            
            /**
             * Sets the prescaler value.
             * Counter's frequency is CK_CNT = F_CK / (prescaler_value - 1)
             * with F_CK frequency before the prescaler, readable through bus_freq() method.
             * 
             * @param value: prescaler value to be set
             * 
             */
            
            void setPrescaler(uint16_t value)
            {
                periph_base->PSC = value;
            }
            
            /**
             * Gets the prescaler value.
             * @return actual prescaler value
             * 
             */
            
            uint16_t getPrescaler()
            {
                return (periph_base->PSC);
            }            
            
            /**
             * Sets auto reload register value. 
             * @param value: auto reload register value to be setPrescaler
             * 
             */
            
            void setAutoReload(uint32_t value)
            {
                periph_base->ARR = value;
            }
            
            /**
             * Gets auto reload register value.
             * @return actual auto-reload register value
             * 
             */
            
            uint32_t getAutoReload()
            {
                return (periph_base->ARR );
            }            
            
            /**
             * Check if counter has reached auto reload value and, consequently, has rolled back to zero.
             * In datasheet this is called update event.
             * Calling this function clears the bit
             * 
             * @return: true if reload event has occurred, false otherwise
             * 
             */
            
            bool checkReloadEvent()
            {
                if(periph_base->TIM_SR & TIM_SR_UIF)
                {
                    periph_base->TIM_SR &= ~TIM_SR_UIF;
                    return true;
                }
                
                return false;
            }
        };
    }
}


#endif