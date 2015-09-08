#ifndef PERIPHERAL_HPP
#define PERIPHERAL_HPP

#include "bus.hpp"
#include "util.hpp"

namespace HAL {
    namespace Peripheral {
        template<
                typename B,
                __pointer _periph_base,
                __mask _enable_bit = 0x0
        >
        struct Peripheral {
            typedef B bus;
            static constexpr __pointer periph_base = _periph_base;
            static constexpr __mask enable_bit = _enable_bit;

            static void enable() {
                auto enable_register = (uint32_t *) bus::enable_register;

                if (enable_bit)
                    *enable_register |= enable_bit;
            }

            static void disable() {
                auto enable_register = (uint32_t *) bus::enable_register;

                if (enable_bit)
                    *enable_register &= ~enable_bit;
            }

            static bool is_enabled() {
                auto enable_register = (uint32_t *) bus::enable_register;

                return (!enable_bit || (*enable_register & enable_bit));
            }
        };


        //****************************************************************
        //* CORTEX M4 PERIPHERALS                                        *
        //****************************************************************

        // APB1 peripherals
        typedef Peripheral<Bus::b_APB1, (__pointer) (TIM2_BASE), RCC_APB1ENR_TIM2EN> p_TIM2;
        typedef Peripheral<Bus::b_APB1, (__pointer) (TIM3_BASE), RCC_APB1ENR_TIM3EN> p_TIM3;
        typedef Peripheral<Bus::b_APB1, (__pointer) (TIM4_BASE), RCC_APB1ENR_TIM4EN> p_TIM4;
        typedef Peripheral<Bus::b_APB1, (__pointer) (TIM5_BASE), RCC_APB1ENR_TIM5EN> p_TIM5;
        typedef Peripheral<Bus::b_APB1, (__pointer) (TIM6_BASE), RCC_APB1ENR_TIM6EN> p_TIM6;
        typedef Peripheral<Bus::b_APB1, (__pointer) (TIM7_BASE), RCC_APB1ENR_TIM7EN> p_TIM7;
        typedef Peripheral<Bus::b_APB1, (__pointer) (TIM12_BASE), RCC_APB1ENR_TIM12EN> p_TIM12;
        typedef Peripheral<Bus::b_APB1, (__pointer) (TIM13_BASE), RCC_APB1ENR_TIM13EN> p_TIM13;
        typedef Peripheral<Bus::b_APB1, (__pointer) (TIM14_BASE), RCC_APB1ENR_TIM14EN> p_TIM14;
        typedef Peripheral<Bus::b_APB1, (__pointer) (RTC_BASE), 0x0> p_RTC;
        typedef Peripheral<Bus::b_APB1, (__pointer) (WWDG_BASE), RCC_APB1ENR_WWDGEN> p_WWDG;
        typedef Peripheral<Bus::b_APB1, (__pointer) (IWDG_BASE), 0x0> p_IWDG;
        typedef Peripheral<Bus::b_APB1, (__pointer) (I2S2ext_BASE), 0x0> p_I2S2ext;
        typedef Peripheral<Bus::b_APB1, (__pointer) (SPI2_BASE), RCC_APB1ENR_SPI2EN> p_SPI2;
        typedef Peripheral<Bus::b_APB1, (__pointer) (SPI3_BASE), RCC_APB1ENR_SPI3EN> p_SPI3;
        typedef Peripheral<Bus::b_APB1, (__pointer) (I2S3ext_BASE), 0x0> p_I2S3ext;
        typedef Peripheral<Bus::b_APB1, (__pointer) (USART2_BASE), RCC_APB1ENR_USART2EN> p_USART2;
        typedef Peripheral<Bus::b_APB1, (__pointer) (USART3_BASE), RCC_APB1ENR_USART3EN> p_USART3;
        typedef Peripheral<Bus::b_APB1, (__pointer) (UART4_BASE), RCC_APB1ENR_UART4EN> p_UART4;
        typedef Peripheral<Bus::b_APB1, (__pointer) (UART5_BASE), RCC_APB1ENR_UART5EN> p_UART5;
        typedef Peripheral<Bus::b_APB1, (__pointer) (I2C1_BASE), RCC_APB1ENR_I2C1EN> p_I2C1;
        typedef Peripheral<Bus::b_APB1, (__pointer) (I2C2_BASE), RCC_APB1ENR_I2C2EN> p_I2C2;
        typedef Peripheral<Bus::b_APB1, (__pointer) (I2C3_BASE), RCC_APB1ENR_I2C3EN> p_I2C3;
        typedef Peripheral<Bus::b_APB1, (__pointer) (CAN1_BASE), RCC_APB1ENR_CAN1EN> p_CAN1;
        typedef Peripheral<Bus::b_APB1, (__pointer) (CAN2_BASE), RCC_APB1ENR_CAN2EN> p_CAN2;
        typedef Peripheral<Bus::b_APB1, (__pointer) (PWR_BASE), RCC_APB1ENR_PWREN> p_PWR;
        typedef Peripheral<Bus::b_APB1, (__pointer) (DAC_BASE), RCC_APB1ENR_DACEN> p_DAC;

        // APB2 peripherals
        typedef Peripheral<Bus::b_APB2, (__pointer) (TIM1_BASE), RCC_APB2ENR_TIM1EN> p_TIM1;
        typedef Peripheral<Bus::b_APB2, (__pointer) (TIM8_BASE), RCC_APB2ENR_TIM8EN> p_TIM8;
        typedef Peripheral<Bus::b_APB2, (__pointer) (USART1_BASE), RCC_APB2ENR_USART1EN> p_USART1;
        typedef Peripheral<Bus::b_APB2, (__pointer) (USART6_BASE), RCC_APB2ENR_USART6EN> p_USART6;
        typedef Peripheral<Bus::b_APB2, (__pointer) (ADC1_BASE), RCC_APB2ENR_ADC1EN> p_ADC1;
        typedef Peripheral<Bus::b_APB2, (__pointer) (ADC2_BASE), RCC_APB2ENR_ADC2EN> p_ADC2;
        typedef Peripheral<Bus::b_APB2, (__pointer) (ADC3_BASE), RCC_APB2ENR_ADC3EN> p_ADC3;
        typedef Peripheral<Bus::b_APB2, (__pointer) (SDIO_BASE), RCC_APB2ENR_SDIOEN> p_SDIO;
        typedef Peripheral<Bus::b_APB2, (__pointer) (SPI1_BASE), RCC_APB2ENR_SPI1EN> p_SPI1;
        typedef Peripheral<Bus::b_APB2, (__pointer) (SYSCFG_BASE), RCC_APB2ENR_SYSCFGEN> p_SYSCFG;
        typedef Peripheral<Bus::b_APB2, (__pointer) (EXTI_BASE), 0x0> p_EXTI;
        typedef Peripheral<Bus::b_APB2, (__pointer) (TIM9_BASE), RCC_APB2ENR_TIM9EN> p_TIM9;
        typedef Peripheral<Bus::b_APB2, (__pointer) (TIM10_BASE), RCC_APB2ENR_TIM10EN> p_TIM10;
        typedef Peripheral<Bus::b_APB2, (__pointer) (TIM11_BASE), RCC_APB2ENR_TIM11EN> p_TIM11;

        // AHB1 peripherals
        typedef Peripheral<Bus::b_AHB1, (__pointer) (GPIOA_BASE), RCC_AHB1ENR_GPIOAEN> p_GPIOA;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (GPIOB_BASE), RCC_AHB1ENR_GPIOBEN> p_GPIOB;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (GPIOC_BASE), RCC_AHB1ENR_GPIOCEN> p_GPIOC;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (GPIOD_BASE), RCC_AHB1ENR_GPIODEN> p_GPIOD;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (GPIOE_BASE), RCC_AHB1ENR_GPIOEEN> p_GPIOE;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (GPIOF_BASE), RCC_AHB1ENR_GPIOFEN> p_GPIOF;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (GPIOG_BASE), RCC_AHB1ENR_GPIOGEN> p_GPIOG;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (GPIOH_BASE), RCC_AHB1ENR_GPIOHEN> p_GPIOH;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (GPIOI_BASE), RCC_AHB1ENR_GPIOIEN> p_GPIOI;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (CRC_BASE), RCC_AHB1ENR_CRCEN> p_CRC;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (FLASH_R_BASE), 0x0> p_FLASH_R;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA1_BASE), RCC_AHB1ENR_DMA1EN> p_DMA1;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA1_Stream0_BASE), RCC_AHB1ENR_DMA1EN> p_DMA1_Stream0;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA1_Stream1_BASE), RCC_AHB1ENR_DMA1EN> p_DMA1_Stream1;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA1_Stream2_BASE), RCC_AHB1ENR_DMA1EN> p_DMA1_Stream2;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA1_Stream3_BASE), RCC_AHB1ENR_DMA1EN> p_DMA1_Stream3;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA1_Stream4_BASE), RCC_AHB1ENR_DMA1EN> p_DMA1_Stream4;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA1_Stream5_BASE), RCC_AHB1ENR_DMA1EN> p_DMA1_Stream5;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA1_Stream6_BASE), RCC_AHB1ENR_DMA1EN> p_DMA1_Stream6;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA1_Stream7_BASE), RCC_AHB1ENR_DMA1EN> p_DMA1_Stream7;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA2_BASE), RCC_AHB1ENR_DMA2EN> p_DMA2;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA2_Stream0_BASE), RCC_AHB1ENR_DMA2EN> p_DMA2_Stream0;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA2_Stream1_BASE), RCC_AHB1ENR_DMA2EN> p_DMA2_Stream1;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA2_Stream2_BASE), RCC_AHB1ENR_DMA2EN> p_DMA2_Stream2;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA2_Stream3_BASE), RCC_AHB1ENR_DMA2EN> p_DMA2_Stream3;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA2_Stream4_BASE), RCC_AHB1ENR_DMA2EN> p_DMA2_Stream4;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA2_Stream5_BASE), RCC_AHB1ENR_DMA2EN> p_DMA2_Stream5;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA2_Stream6_BASE), RCC_AHB1ENR_DMA2EN> p_DMA2_Stream6;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (DMA2_Stream7_BASE), RCC_AHB1ENR_DMA2EN> p_DMA2_Stream7;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (ETH_BASE), 0x0> p_ETH;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (ETH_MAC_BASE), 0x0> p_ETH_MAC;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (ETH_MMC_BASE), 0x0> p_ETH_MMC;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (ETH_PTP_BASE), 0x0> p_ETH_PTP;
        typedef Peripheral<Bus::b_AHB1, (__pointer) (ETH_DMA_BASE), 0x0> p_ETH_DMA;

        // AHB2 peripherals
        typedef Peripheral<Bus::b_AHB2, (__pointer) (DCMI_BASE), RCC_AHB2ENR_DCMIEN> p_DCMI;
//         typedef Peripheral<Bus::b_AHB2, (__pointer) (CRYP_BASE), RCC_AHB2ENR_CRYPEN> p_CRYP;
//         typedef Peripheral<Bus::b_AHB2, (__pointer) (HASH_BASE), RCC_AHB2ENR_HASHEN> p_HASH;
        typedef Peripheral<Bus::b_AHB2, (__pointer) (RNG_BASE), RCC_AHB2ENR_RNGEN> p_RNG;
    }
}

#endif //STM32_TIMER_HAL_PERIPHERAL_HPP
