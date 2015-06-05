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
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_TIM2_BASE)> TIM2;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_TIM3_BASE)> TIM3;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_TIM4_BASE)> TIM4;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_TIM5_BASE)> TIM5;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_TIM6_BASE)> TIM6;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_TIM7_BASE)> TIM7;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_TIM12_BASE)> TIM12;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_TIM13_BASE)> TIM13;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_TIM14_BASE)> TIM14;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_RTC_BASE)> RTC;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_WWDG_BASE)> WWDG;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_IWDG_BASE)> IWDG;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_I2S2ext_BASE)> I2S2ext;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_SPI2_BASE)> SPI2;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_SPI3_BASE)> SPI3;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_I2S3ext_BASE)> I2S3ext;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_USART2_BASE)> USART2;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_USART3_BASE)> USART3;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_UART4_BASE)> UART4;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_UART5_BASE)> UART5;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_I2C1_BASE)> I2C1;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_I2C2_BASE)> I2C2;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_I2C3_BASE)> I2C3;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_CAN1_BASE)> CAN1;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_CAN2_BASE)> CAN2;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_PWR_BASE)> PWR;
        typedef Peripheral<Bus::APB1, (__pointer) (__STM_32_DAC_BASE)> DAC;

        // APB2 peripherals
        typedef Peripheral<Bus::APB2, (__pointer) (__STM_32_TIM1_BASE)> TIM1;
        typedef Peripheral<Bus::APB2, (__pointer) (__STM_32_TIM8_BASE)> TIM8;
        typedef Peripheral<Bus::APB2, (__pointer) (__STM_32_USART1_BASE)> USART1;
        typedef Peripheral<Bus::APB2, (__pointer) (__STM_32_USART6_BASE)> USART6;
        typedef Peripheral<Bus::APB2, (__pointer) (__STM_32_ADC1_BASE)> ADC1;
        typedef Peripheral<Bus::APB2, (__pointer) (__STM_32_ADC2_BASE)> ADC2;
        typedef Peripheral<Bus::APB2, (__pointer) (__STM_32_ADC3_BASE)> ADC3;
        typedef Peripheral<Bus::APB2, (__pointer) (__STM_32_ADC_BASE)> ADC;
        typedef Peripheral<Bus::APB2, (__pointer) (__STM_32_SDIO_BASE)> SDIO;
        typedef Peripheral<Bus::APB2, (__pointer) (__STM_32_SPI1_BASE)> SPI1;
        typedef Peripheral<Bus::APB2, (__pointer) (__STM_32_SYSCFG_BASE)> SYSCFG;
        typedef Peripheral<Bus::APB2, (__pointer) (__STM_32_EXTI_BASE)> EXTI;
        typedef Peripheral<Bus::APB2, (__pointer) (__STM_32_TIM9_BASE)> TIM9;
        typedef Peripheral<Bus::APB2, (__pointer) (__STM_32_TIM10_BASE)> TIM10;
        typedef Peripheral<Bus::APB2, (__pointer) (__STM_32_TIM11_BASE)> TIM11;

        // AHB1 peripherals
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_GPIOA_BASE)> GPIOA;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_GPIOB_BASE)> GPIOB;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_GPIOC_BASE)> GPIOC;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_GPIOD_BASE)> GPIOD;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_GPIOE_BASE)> GPIOE;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_GPIOF_BASE)> GPIOF;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_GPIOG_BASE)> GPIOG;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_GPIOH_BASE)> GPIOH;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_GPIOI_BASE)> GPIOI;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_CRC_BASE)> CRC;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_RCC_BASE)> RCC;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_FLASH_R_BASE)> FLASH_R;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_DMA1_BASE)> DMA1;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_DMA1_Stream0_BASE)> DMA1_Stream0;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_DMA1_Stream1_BASE)> DMA1_Stream1;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_DMA1_Stream2_BASE)> DMA1_Stream2;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_DMA1_Stream3_BASE)> DMA1_Stream3;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_DMA1_Stream4_BASE)> DMA1_Stream4;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_DMA1_Stream5_BASE)> DMA1_Stream5;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_DMA1_Stream6_BASE)> DMA1_Stream6;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_DMA1_Stream7_BASE)> DMA1_Stream7;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_DMA2_BASE)> DMA2;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_DMA2_Stream0_BASE)> DMA2_Stream0;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_DMA2_Stream1_BASE)> DMA2_Stream1;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_DMA2_Stream2_BASE)> DMA2_Stream2;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_DMA2_Stream3_BASE)> DMA2_Stream3;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_DMA2_Stream4_BASE)> DMA2_Stream4;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_DMA2_Stream5_BASE)> DMA2_Stream5;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_DMA2_Stream6_BASE)> DMA2_Stream6;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_DMA2_Stream7_BASE)> DMA2_Stream7;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_ETH_BASE)> ETH;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_ETH_MAC_BASE)> ETH_MAC;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_ETH_MMC_BASE)> ETH_MMC;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_ETH_PTP_BASE)> ETH_PTP;
        typedef Peripheral<Bus::AHB1, (__pointer) (__STM_32_ETH_DMA_BASE)> ETH_DMA;

        // AHB2 peripherals
        typedef Peripheral<Bus::APB2, (__pointer) (__STM_32_DCMI_BASE)> DCMI;
        typedef Peripheral<Bus::APB2, (__pointer) (__STM_32_CRYP_BASE)> CRYP;
        typedef Peripheral<Bus::APB2, (__pointer) (__STM_32_HASH_BASE)> HASH;
        typedef Peripheral<Bus::APB2, (__pointer) (__STM_32_RNG_BASE)> RNG;
    }
}

#endif //STM32_TIMER_HAL_PERIPHERAL_HPP
