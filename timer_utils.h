/***************************************************************************
 *   Copyright (C) 2015 by Silvano Seva
 *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   As a special exception, if other files instantiate templates or use   *
 *   macros or inline functions from this file, or you compile this file   *
 *   and link it with other works to produce a work based on this file,    *
 *   this file does not by itself cause the resulting work to be covered   *
 *   by the GNU General Public License. However the source code for this   *
 *   file must still be made available in accordance with the GNU General  *
 *   Public License. This exception does not invalidate any other reasons  *
 *   why a work based on this file might be covered by the GNU General     *
 *   Public License.                                                       *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>   *
 ***************************************************************************/

#ifndef TIMER_H
#define TIMER_H

#include <miosix.h>

class PwmMeasure
{   
public:
    
    /**
     * Constructor.
     * \param timerNum: the timer number, eg. TIM4
     * \param busFreq: the frequency in Hertz of the APB bus the timer belongs to
     * \param counterFreq: the desired counter frequency in Hertz 
     */
    PwmMeasure(unsigned int timerNum, unsigned int busFreq, unsigned int counterFreq);
    
    /**
     * Check if the interrupt flag associated to PWM pulse width measure is set.
     * if it is set clears it.
     * \return true if the the flag is set, false otherwise
     */
    bool widthEvent();
    
    /**
     * Check if the interrupt flag associated to PWM period measure is set.
     * if it is set clears it.
     * \return true if the the flag is set, false otherwise
     */
    bool periodEvent();
    
    /**
     * \return the latest pulse width measured, expressed in counter ticks
     */
    unsigned int getPulseWidth();
    
    /**
     * \return the latest period measured, expressed in counter ticks
     */
    unsigned int getPeriod();
    
    ~PwmMeasure();
    
private:
    unsigned int timerNum;
};


class EncoderCount
{
public:
    
    /**
     * Constructor.
     * \param timerNum: the timer number, eg. TIM4
     */
    EncoderCount(unsigned int timerNum);
    ~EncoderCount();
    
    /**
     * \return the current counter's value
     */
    unsigned int getValue();
    
    /**
     * clears the counter register
     */
    void counterClear();
    
private:
    
    unsigned int timerNum;
};


class PwmGenerator
{
public:
    
    /**
     * Constructor.
     * \param timerNum: the timer number, eg. TIM4
     * \param busFreq: the frequency in Hertz of the APB bus the timer belongs to
     * \param counterFreq: the desired counter frequency in Hertz 
     * \param period: the desired period of pwm signal expressed in counter ticks
     * 
     * TODO: fix compatibility for STM32F100 and STM32F400, now is STM32F100 only!
     */
    PwmGenerator(unsigned int timerNum, unsigned int busFreq, unsigned int counterFreq, unsigned int period);
    ~PwmGenerator();
    
    /**
     * \param value: the number of counter ticks the pwm signal is high
     */
    void setDuty(unsigned int value);

private:
    
    unsigned int timerNum;
    unsigned int period;
};


class Counter
{
public:
    
    /**
     * Constructor.
     * \param timerNum: the timer number, eg. TIM4
     * \param busFreq: the frequency in Hertz of the APB bus the timer belongs to
     * \param counterFreq: the desired counter frequency in Hertz 
     * \param reloadVal: the maximum value reached by the counter before is rolled back to zero; default value is 65535
     */
    Counter(unsigned int timerNum, unsigned int busFreq, unsigned int counterFreq, unsigned int reloadVal = 65535);
    ~counter();
    
    /**
     * Starts the counter
     */
    void start();
    
    /**
     * Stops the counter
     */
    void stop();
    
    /**
     * clears the counter
     */
    void clear();
    
    /**
     * \return the current count value
     */
    unsigned int getValue();
    
    /**
     * Check if the counter value is equal or greater than the value passed
     * \param value: the value the counter is compared to
     * \return true if counter value is equal or greater than value, false otherwise
     */
    bool hasReached(unsigned int value);
    
private:
    
    unsigned int timerNum;
};
#endif // TIMER_H
