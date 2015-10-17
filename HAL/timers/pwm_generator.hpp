
#ifndef PWM_GENERATOR_HPP
#define PWM_GENERATOR_HPP

#include "timer.hpp"

namespace HAL {
    namespace Timer {
        
        /**
         * PwmGenerator (type)
         *
         * A timer peripheral is used to generate a pwm signal and can support up to four channels
         * Please not that NOT all the timer peripherals can support up to four channels, some can
         * handle a maximum of two channels.
         * 
         * In order to make this class as general as possible actually only edge-aligned, pwm mode 1
         * signal generation is covered
         * 
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
//             uint32_t counter_freq;
            uint32_t period;

#ifdef _MIOSIX           
            miosix::GpioPin *pins[4];
#endif        

            //*************************** 
            //* Methods                 *
            //***************************
        public:
            using TimerBase<P>::periph_base;
            using TimerBase<P>::bus_freq;
            
            /**
             * @param counter_freq: the timer's counter counting frequency. It determines the tick width.
             * @param period: the generated pwm signal's period length expressed in counter ticks
             * @param isAdvanced: set it to true if you are using advanced control timers (TIM1 & TIM8)
             */

            PwmGenerator(uint32_t counter_freq, uint32_t period, bool isAdvanced = false) : /* counter_freq(counter_freq),*/ period(period)
            {
                // Set counter frequency through prescaler
                periph_base->PSC = (bus_freq() / counter_freq) - 1;
                
                // Set pwm period through reload register value
                periph_base->ARR = period;
                
                //clear counter register
                periph_base->CNT = 0;
                
                // Dummy update event in order to load registers
                periph_base->EGR = TIM_EGR_UG;
                
                /* this is a workaround made because advanced control timers must
                 * have MOE bit set in order to have outputs working properly.
                 * If MOE bit is cleared no output signal is generated at all */
                
                if(isAdvanced)
                    periph_base->BDTR |= TIM_BDTR_MOE;

                // Auto reload enabled
                periph_base->CR1 |= TIM_CR1_ARPE;
            }
            
            /**
             * Calling this constructor the pwm generator will create a signal with frequency
             * specified by sigFreq and whose duty cycle can be set using a value in the range
             * between 0 and 65535. Note that the counter frequency will be 65535 * sigFreq
             * 
             * @param sigFreq: the generated pwm signal's frequency expressed in hertz
             * @param isAdvanced: set it to true if you are using advanced control timers (TIM1 & TIM8)
             */
            PwmGenerator(uint32_t sigFreq, bool isAdvanced = false)
            {
                period(0xFFFF);
                
                // Set counter frequency through prescaler
                periph_base->PSC = (bus_freq() / (0xFFFF * sigFreq)) - 1;
                
                // Set pwm period through reload register value
                periph_base->ARR = 0xFFFF;
                
                //clear counter register
                periph_base->CNT = 0;
                
                // Dummy update event in order to load registers
                periph_base->EGR = TIM_EGR_UG;
                
                /* this is a workaround made because advanced control timers must
                 * have MOE bit set in order to have outputs working properly.
                 * If MOE bit is cleared no output signal is generated at all */
                
                if(isAdvanced)
                    periph_base->BDTR |= TIM_BDTR_MOE;

                // Auto reload enabled
                periph_base->CR1 |= TIM_CR1_ARPE;
            }
            
            /**
             * Starts the timer. Calling this function makes the timer generating
             * pwm signal(s) on its output(s)
             */
            inline void start()
            {
                if(TimerBase<P>::is_enabled())
                    return;
                
                TimerBase<P>::enable();
            }
            
            /**
             * Stops the timer. Calling this function makes the timer stop
             * generating pwm signal(s) on its output(s)
             */
            inline void stop()
            {
                if(!TimerBase<P>::is_enabled())
                    return;
                
                TimerBase<P>::disable();
            }           
            
            /**
             * Enables a channel. Calling this function will "connect" the channel to the
             * peripheral, making the corresponding output pin generating the pwm signal.
             * This function must be called with timer stopped.
             * 
             * NOTE: pin initialization to alternate mode and, eventually, alternate mode
             * mapping isn't done here, so it MUST be done somewhere before calling this function.
             * 
             * @param channel: the channel number, between 1 and 4. Please note that not all
             * the timers have four channels!!
             * 
             * TODO: make this function thread safe
             */
            
            void chEnable(uint8_t channel)
            {
                if(TimerBase<P>::is_enabled())
                    return;
                
                switch(channel)
                {
                    case 1:
                        periph_base->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE;
                        periph_base->CCER |= TIM_CCER_CC1E;
                        break;
                    
                    case 2:
                        periph_base->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE;
                        periph_base->CCER |= TIM_CCER_CC2E;
                        break;  
                    
                    case 3:
                        periph_base->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3PE;
                        periph_base->CCER |= TIM_CCER_CC3E;
                        break;
                        
                   case 4:
                        periph_base->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4PE;
                        periph_base->CCER |= TIM_CCER_CC4E;
                        break;
                }
            }

#ifdef _MIOSIX            
            /**
             * Enables a channel. Calling this function will "connect" the channel to the
             * peripheral, making the corresponding output pin generating the pwm signal.
             * This function must be called with timer stopped.
             * 
             * NOTE: pin initialization to alternate mode and, eventually, alternate mode
             * mapping isn't done here, so it MUST be done somewhere before calling this function.
             * 
             * @param channel: the channel number, between 1 and 4. Please note that not all
             * the timers have four channels!!
             * @param gpio: gpio Pin object (miosix dependent)
             * 
             * TODO: make this function thread safe
             */
            
            void chEnable(uint8_t channel, miosix::GpioPin *gpio)
            {
                if(TimerBase<P>::is_enabled())
                    return;
                
                pins[channel] = gpio;
                gpio->mode(miosix::Mode::ALTERNATE);
                gpio->alternateFunction(TimerBase<P>::mapAlternateFunction());
                
                switch(channel)
                {
                    case 1:
                        periph_base->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE;
                        periph_base->CCER |= TIM_CCER_CC1E;
                        break;
                    
                    case 2:
                        periph_base->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE;
                        periph_base->CCER |= TIM_CCER_CC2E;
                        break;  
                    
                    case 3:
                        periph_base->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3PE;
                        periph_base->CCER |= TIM_CCER_CC3E;
                        break;
                        
                   case 4:
                        periph_base->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4PE;
                        periph_base->CCER |= TIM_CCER_CC4E;
                        break;
                }              
            }
#endif
            /**
             * Disables a channel. Calling this function will "disconnect" the channel from the
             * peripheral, providing the corresponding output pin from generating the pwm signal.
             * This function must be called with timer stopped.
             * 
             * @param channel: the channel number, between 1 and 4. Please note that not all
             * the timers have four channels!!
             * 
             * TODO: make this function thread safe
             */
#ifndef _MIOSIX         
            void chDisable(uint8_t channel)
            {
                if(TimerBase<P>::is_enabled())
                    return;
                
                switch(channel)
                {
                    case 1:
                        periph_base->CCR1 = 0;
                        periph_base->CCER &= ~TIM_CCER_CC1E;
                        break;
                    
                    case 2:
                        periph_base->CCR2 = 0;
                        periph_base->CCER &= ~TIM_CCER_CC2E;
                        break;  
                    
                    case 3:
                        periph_base->CCR3 = 0;
                        periph_base->CCER &= ~TIM_CCER_CC3E;
                        break;
                        
                   case 4:
                       periph_base->CCR4 = 0;
                        periph_base->CCER &= ~TIM_CCER_CC4E;
                        break;
                }
            }
            
#else
            void chDisable(uint8_t channel)
            {
                if(TimerBase<P>::is_enabled())
                    return;
                
                switch(channel)
                {
                    case 1:
                        periph_base->CCR1 = 0;
                        periph_base->CCER &= ~TIM_CCER_CC1E;
                        break;
                    
                    case 2:
                        periph_base->CCR2 = 0;
                        periph_base->CCER &= ~TIM_CCER_CC2E;
                        break;  
                    
                    case 3:
                        periph_base->CCR3 = 0;
                        periph_base->CCER &= ~TIM_CCER_CC3E;
                        break;
                        
                   case 4:
                       periph_base->CCR4 = 0;
                        periph_base->CCER &= ~TIM_CCER_CC4E;
                        break;
                }
                
                pins[channel]->mode(miosix::Mode::INPUT);
            }
#endif
            
            /**
             * Sets channel's pwm signal logical High value duration expressed in counter ticks.
             * If value is equal to zero the output will be permanently low, if value is equal to
             * pwm signal's period the output will be permanently high.
             * If value is greater than pwm signal's period the value passed will be ignored
             * 
             * @param channel: the channel number, between 1 and 4. Please note that not all
             * the timers have four channels!!
             * @param value: the channel's High time period, expressed in counter ticks
             * 
             * TODO: make this function thread safe
             */
            void setOnPeriod(uint8_t channel, uint16_t value)
            {
                value = std::min(static_cast<uint16_t>(period),std::max(static_cast<uint16_t>(0),value));   //Ugly bugfix, perhaps it can be done better??
                
                switch(channel)
                {
                    case 1:
                        periph_base->CCR1 = value;
                        break;
                    
                    case 2:
                        periph_base->CCR2 = value;
                        break;  
                    
                    case 3:
                        periph_base->CCR3 = value;
                        break;
                        
                   case 4:
                        periph_base->CCR4 = value;
                        break;
                }  
            }
            
            /**
             * Sets pwm signal's duty cycle.
             * 
             * @param channel: the channel number, between 1 and 4. Please note that not all
             * the timers have four channels!!
             * @param duty: duty cycle to be set, between 0 to 100
             */
            void setDuty(uint8_t channel, uint8_t duty)
            {
                duty = std::min(100,std::max(0,static_cast<int>(duty)));     //(perhaps) another ugly bugfix...                
                setOnPeriod(channel, duty*(period/100));                
            }
            
            /**
             * Sets pwm signal's duty cycle.
             * 
             * @param channel: the channel number, between 1 and 4. Please note that not all
             * the timers have four channels!!
             * @param duty: duty cycle to be set, between 0.0f to 1.0f (floating point value
             */
            void setDuty(uint8_t channel, float duty)
            {
                duty = std::min(1.0f,std::max(0.0f,duty));
                
                setOnPeriod(channel, duty*period);                
            }
            
        };
    }
}
#endif // PWM_GENERATOR_H
