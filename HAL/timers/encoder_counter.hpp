
#ifndef ENCODER_COUNTER_HPP
#define ENCODER_COUNTER_HPP

#include "timer.hpp"

namespace HAL {
    namespace Timer {
        
        /**
         * Timer used in encoder interface mode.
         * Encoder interface mode acts simply as an external clock with direction selection. This
         * means that the counter just counts continuously between 0 and the auto-reload value in the
         * TIMx_ARR register (0 to ARR or ARR down to 0 depending on the direction
         */
        template<typename P>
        class EncoderCounter: public TimerBase<P> {
            //***************************
            //* Members                 *
            //***************************
        private:
//             uint32_t counter_freq;

            //***************************
            //* Methods                 *
            //***************************
        public:
            using TimerBase<P>::periph_base;
            using TimerBase<P>::bus_freq;
            
            enum mode
            {
                T1_ONLY,
                T2_ONLY,
                BOTH
            };
            
        /**
         * @param reload: auto-reload register value. Counter can count between 0 and this value.
         * @param mode: encoder interface mode.
         * Available modes:
         * -> T1_ONLY: counting only on TI1 edges only
         * -> T2_ONLY: counting only on TI2 edges only
         * -> BOTH: counting both on TI1 edges and TI2 edges
         * 
         */
        EncoderCounter(uint16_t reload = 0xFFFF, uint8_t mode = T1_ONLY)
        {
        }
        
        };        
    }
}

#endif