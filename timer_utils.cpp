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

#include "timer_utils.h"

PwmMeasure::PwmMeasure(unsigned int timerNum, unsigned int busFreq, unsigned int counterFreq) : timerNum(timerNum)
{
    timerNum->PSC = (busFreq/counterFreq)-1;         //set count frequency
    timerNum->CCMR1 |= TIM_CCMR1_CC1S_0;             //IC1 mapped on TI1
    timerNum->CCMR1 |= TIM_CCMR1_CC2S_1;             //IC2 mapped on TI1
    timerNum->SMCR |= TIM_SMCR_TS_2 | TIM_SMCR_TS_0; //trigger is T1FP1
    timerNum->SMCR |= TIM_SMCR_SMS_2;                //timer in reset mode, input's rising edge clears it
    timerNum->CCER |= TIM_CCER_CC2P | TIM_CCER_CC2E; //channel 2 enabled, falling edge
    timerNum->CCER |= TIM_CCER_CC1E;                 //capture enabled on channel 1, rising edge
    timerNum->CR1 |= TIM_CR1_CEN;                    //enables the timer
}

bool PwmMeasure::widthEvent()
{
    if(timerNum->SR & TIM_SR_CC2IF){
       timerNum->SR &= ~TIM_SR_CC2IF;
       return true;
    }
    
    return false;
}

bool PwmMeasure::periodEvent()
{
    if(timerNum->SR & TIM_SR_CC1IF){
       timerNum->SR &= ~TIM_SR_CC1IF;
       return true;
    }
    
    return false;
}

unsigned int PwmMeasure::getPeriod(){ return timerNum->CCR1; }

unsigned int PwmMeasure::getPulseWidth(){ return timerNum->CCR2; }

PwmMeasure::~PwmMeasure(){ timerNum->CR1 &= ~TIM_CR1_CEN; }


EncoderCount::EncoderCount(unsigned int timerNum) : timerNum(timerNum)
{
    timerNum->CCMR1 |= TIM_CCMR1_CC1S_0;
    timerNum->CCMR1 |= TIM_CCMR1_CC2S_0;
    timerNum->SMCR |= TIM_SMCR_SMS_1;               
    timerNum->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC1P;
    timerNum->CR1 |= TIM_CR1_CEN;
}

unsigned int EncoderCount::getValue(){ return timerNum->CNT; }

void EncoderCount::counterClear(){ timerNum->CNT = 0; }

EncoderCount::~EncoderCount(){ timerNum->CR1 &= ~TIM_CR1_CEN; }


PwmGenerator::PwmGenerator(unsigned int timerNum, unsigned int busFreq, unsigned int counterFreq, unsigned int period) :
timerNum(timerNum), period(period)
{
    timerNum->PSC = (busFreq/counterFreq)-1;      
    timerNum->ARR = period;                       
    timerNum->CCMR1 |= TIM_CCMR1_OC1M_1;          
    timerNum->CCMR1 |= TIM_CCMR1_OC1M_2;
    timerNum->CCMR1 |= TIM_CCMR1_OC1PE;
    timerNum->CCER |= TIM_CCER_CC1E;
    timerNum->CCR1 = 0;           
    timerNum->CNT = 0;
    timerNum->EGR=TIM_EGR_UG;
    timerNum->BDTR |= TIM_BDTR_MOE;
    timerNum->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
}

void PwmGenerator::setDuty(unsigned int value)
{
    if(value > period)
        return;
    
    timerNum->CCR1 = value;
}

PwmGenerator::~PwmGenerator(){ timerNum->CR1 &= ~TIM_CR1_CEN; }


Counter::Counter(unsigned int timerNum, unsigned int busFreq, unsigned int counterFreq, unsigned int reloadVal = 65535) : timerNum(timerNum)
{
    timerNum->PSC = (busFreq/counterFreq)-1;      
    timerNum->ARR = reloadVal;
    timerNum->CNT = 0;
    timerNum->CR1 |= TIM_CR1_ARPE;   
}

void Counter::clear(){ timerNum->CNT = 0; }

unsigned int Counter::getValue(){ return timerNum->CNT; }

bool Counter::hasReached(unsigned int value){ return (timerNum->CNT >= value) ? true : false; }

void Counter::start(){ timerNum->CR1 |= TIM_CR1_CEN; }

void Counter::stop(){ timerNum->CR1 &= ~TIM_CR1_CEN; }

Counter::~counter(){ stop(); }






