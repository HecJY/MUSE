/*This file is built to enbale the gpio pins we will use*/
#include "stm32f0xx.h"
#include "stm32f0_discovery.h"


/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
     PC3   ------> I2S2_SD
     PA6   ------> SPI1_MISO
     PA7   ------> SPI1_MOSI
     PB10   ------> I2S2_CK
     PC7   ------> I2S3_MCK
     PC10   ------> I2S3_CK
     PC12   ------> I2S3_SD
*/
void enable_GPIOC(void){
    //ports enable
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    //general output purpose mode
    GPIOC->MODER &=~GPIO_MODER_MODER3 & ~GPIO_MODER_MODER7 & ~GPIO_MODER_MODER10 & ~GPIO_MODER_MODER12;
    GPIOC->MODER |= GPIO_MODER_MODER3_0;

    //output is output push-pull
    GPIOC->OTYPER &=~GPIO_OTYPER_OT_3;
    //speed is low
    GPIOC->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR3;
    //no pull
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR3;

}
void enable_GPIOA(void){
    //ports enable
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    //general output purpose mode
    GPIOA->MODER &=~GPIO_MODER_MODER6 & ~GPIO_MODER_MODER7;
    //change it to analog mode


}
void enable_GPIOB(void){
    //ports enable
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    //general output purpose mode
    GPIOB->MODER &=~GPIO_MODER_MODER10;

}



/*lab6 information*/
//DAC















