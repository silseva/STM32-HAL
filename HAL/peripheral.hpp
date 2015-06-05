#ifndef STM32_TIMER_HAL_PERIPHERAL_HPP
#define STM32_TIMER_HAL_PERIPHERAL_HPP

#include "bus.hpp"
#include "util.hpp"

namespace HAL {
    namespace Peripheral {
        template<
                typename B,
                __pointer _periph_base
        >
        struct Peripheral {
            typedef B bus;
            static constexpr __pointer periph_base = _periph_base;
        };


        //****************************************************************
        //* CORTEX M4 PERIPHERALS                                        *
        //****************************************************************

        // APB1 peripherals
        typedef Peripheral<Bus::b_APB1, (__pointer) (TIM2_BASE)> p_TIM2;
        typedef Peripheral<Bus::b_APB1, (__pointer) (TIM3_BASE)> p_TIM3;
        typedef Peripheral<Bus::b_APB1, (__pointer) (TIM4_BASE)> p_TIM4;
        typedef Peripheral<Bus::b_APB1, (__pointer) (TIM5_BASE)> p_TIM5;
        typedef Peripheral<Bus::b_APB1, (__pointer) (TIM6_BASE)> p_TIM6;
        typedef Peripheral<Bus::b_APB1, (__pointer) (TIM7_BASE)> p_TIM7;
        typedef Peripheral<Bus::b_APB1, (__pointer) (TIM12_BASE)> p_TIM12;
        typedef Peripheral<Bus::b_APB1, (__pointer) (TIM13_BASE)> p_TIM13;
        typedef Peripheral<Bus::b_APB1, (__pointer) (TIM14_BASE)> p_TIM14;
        typedef Peripheral<Bus::b_APB1, (__pointer) (RTC_BASE)> p_RTC;
        typedef Peripheral<Bus::b_APB1, (__pointer) (WWDG_BASE)> p_WWDG;
        typedef Peripheral<Bus::b_APB1, (__pointer) (IWDG_BASE)> p_IWDG;
        typedef Peripheral<Bus::b_APB1, (__pointer) (I2S2ext_BASE)> p_I2S2ext;
        typedef Peripheral<Bus::b_APB1, (__pointer) (SPI2_BASE)> p_SPI2;
        typedef Peripheral<Bus::b_APB1, (__pointer) (SPI3_BASE)> p_SPI3;
        typedef Peripheral<Bus::b_APB1, (__pointer) (I2S3ext_BASE)> p_I2S3ext;
        typedef Peripheral<Bus::b_APB1, (__pointer) (USART2_BASE)> p_USART2;
        typedef Peripheral<Bus::b_APB1, (__pointer) (USART3_BASE)> p_USART3;
        typedef Peripheral<Bus::b_APB1, (__pointer) (UART4_BASE)> p_UART4;
        typedef Peripheral<Bus::b_APB1, (__pointer) (UART5_BASE)> p_UART5;
        typedef Peripheral<Bus::b_APB1, (__pointer) (I2C1_BASE)> p_I2C1;
        typedef Peripheral<Bus::b_APB1, (__pointer) (I2C2_BASE)> p_I2C2;
        typedef Peripheral<Bus::b_APB1, (__pointer) (I2C3_BASE)> p_I2C3;
        typedef Peripheral<Bus::b_APB1, (__pointer) (CAN1_BASE)> p_CAN1;
        typedef Peripheral<Bus::b_APB1, (__pointer) (CAN2_BASE)> p_CAN2;
        typedef Peripheral<Bus::b_APB1, (__pointer) (PWR_BASE)> p_PWR;
        typedef Peripheral<Bus::b_APB1, (__pointer) (DAC_BASE)> p_DAC;

        // APB2 peripherals
        typedef Peripheral<Bus::b_APB2, (__pointer) (TIM1_BASE)> p_TIM1;
        typedef Peripheral<Bus::b_APB2, (__pointer) (TIM8_BASE)> p_TIM8;
        typedef Peripheral<Bus::b_APB2, (__pointer) (USART1_BASE)> p_USART1;
        typedef Peripheral<Bus::b_APB2, (__pointer) (USART6_BASE)> p_USART6;
        typedef Peripheral<Bus::b_APB2, (__pointer) (ADC1_BASE)> p_ADC1;
        typedef Peripheral<Bus::b_APB2, (__pointer) (ADC2_BASE)> p_ADC2;
        typedef Peripheral<Bus::b_APB2, (__pointer) (ADC3_BASE)> p_ADC3;
        typedef Peripheral<Bus::b_APB2, (__pointer) (ADC_BASE)> p_ADC;
        typedef Peripheral<Bus::b_APB2, (__pointer) (SDIO_BASE)> p_SDIO;
        typedef Peripheral<Bus::b_APB2, (__pointer) (SPI1_BASE)> p_SPI1;
        typedef Peripheral<Bus::b_APB2, (__pointer) (SYSCFG_BASE)> p_SYSCFG;
        typedef Peripheral<Bus::b_APB2, (__pointer) (EXTI_BASE)> p_EXTI;
        typedef Peripheral<Bus::b_APB2, (__pointer) (TIM9_BASE)> p_TIM9;
        typedef Peripheral<Bus::b_APB2, (__pointer) (TIM10_BASE)> p_TIM10;
        typedef Peripheral<Bus::b_APB2, (__pointer) (TIM11_BASE)> p_TIM11;

        // AHB1 peripherals
        typedef Peripheral<Bus::b_AHB1, (__pointer) (GPIOA_BASE)> p_GPIOA;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (GPIOB_BASE)> p_GPIOB;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (GPIOC_BASE)> p_GPIOC;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (GPIOD_BASE)> p_GPIOD;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (GPIOE_BASE)> p_GPIOE;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (GPIOF_BASE)> p_GPIOF;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (GPIOG_BASE)> p_GPIOG;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (GPIOH_BASE)> p_GPIOH;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (GPIOI_BASE)> p_GPIOI;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (CRC_BASE)> p_CRC;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (RCC_BASE)> p_RCC;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (FLASH_R_BASE)> p_FLASH_R;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA1_BASE)> p_DMA1;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA1_Stream0_BASE)> p_DMA1_Stream0;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA1_Stream1_BASE)> p_DMA1_Stream1;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA1_Stream2_BASE)> p_DMA1_Stream2;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA1_Stream3_BASE)> p_DMA1_Stream3;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA1_Stream4_BASE)> p_DMA1_Stream4;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA1_Stream5_BASE)> p_DMA1_Stream5;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA1_Stream6_BASE)> p_DMA1_Stream6;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA1_Stream7_BASE)> p_DMA1_Stream7;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA2_BASE)> p_DMA2;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA2_Stream0_BASE)> p_DMA2_Stream0;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA2_Stream1_BASE)> p_DMA2_Stream1;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA2_Stream2_BASE)> p_DMA2_Stream2;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA2_Stream3_BASE)> p_DMA2_Stream3;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA2_Stream4_BASE)> p_DMA2_Stream4;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA2_Stream5_BASE)> p_DMA2_Stream5;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA2_Stream6_BASE)> p_DMA2_Stream6;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA2_Stream7_BASE)> p_DMA2_Stream7;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (ETH_BASE)> p_ETH;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (ETH_MAC_BASE)> p_ETH_MAC;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (ETH_MMC_BASE)> p_ETH_MMC;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (ETH_PTP_BASE)> p_ETH_PTP;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (ETH_DMA_BASE)> p_ETH_DMA;

        // AHB2 peripherals
        typedef Peripheral<Bus::b_APB2, (__pointer) (DCMI_BASE)> p_DCMI;
        typedef Peripheral<Bus::b_APB2, (__pointer) (CRYP_BASE)> p_CRYP;
        typedef Peripheral<Bus::b_APB2, (__pointer) (HASH_BASE)> p_HASH;
        typedef Peripheral<Bus::b_APB2, (__pointer) (RNG_BASE)> p_RNG;
    }
}

#endif //STM32_TIMER_HAL_PERIPHERAL_HPP
