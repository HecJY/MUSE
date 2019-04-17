#include "button.h"


int int_array[5][5] =   { {1,2,3,4,5},
                          {6,7,8,9,10},
                          {11,12,13,14,15},
                          {16, 17, 18, 19,20},
                          {21,22,23,24,25}};
uint8_t key_samples[5][5]  = { {0}, {0}, {0}, {0}, {0} };
uint8_t key_pressed[5][5]  = { {0}, {0}, {0}, {0}, {0} };
uint8_t key_released[5][5]  = { {0}, {0}, {0}, {0}, {0} };
int row[5] = {-1,-1,-1,-1,-1};
int col[5] = {-1,-1,-1,-1,-1};
int *getrow(){
    //the initial state of the row num

   if( GPIOB->IDR & 1<<5){
       row[0] = 1;
   }
   else if(GPIOB->IDR & 1<<6){
       row[1] = 1;
   }
   else if(GPIOB->IDR & 1<<7){
          row[2] = 1;
      }
   else if(GPIOB->IDR & 1<<8){
          row[3] = 1;
      }
   else if(GPIOB->IDR & 1<<9){
          row[4] = 1;
      }
   return row;
}
int *getcol(){

    if( GPIOB->IDR & 1<<0){
        col[0] = 1;
    }
    else if(GPIOB->IDR & 1<<1){
        col[1] = 1;
    }
    else if(GPIOB->IDR & 1<<2){
           col[2] = 1;
       }
    else if(GPIOB->IDR & 1<<3){
           col[3] = 1;
       }
    else if(GPIOB->IDR & 1<<4){
           col[4] = 1;
       }
    return col;
}
/* debounce process*/
void update_key_press() {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if ((key_samples[i][j] & KEY_PRESS_MASK) == 0b00000111) {
                key_pressed[i][j] = 1;
                key_samples[i][j] = 0xFF;
            }

            if ((key_samples[i][j] & KEY_REL_MASK) == 0b11100000) {
                key_released[i][j] = 1;
                key_samples[i][j] = 0x00;
            }
        }
    }
}

void gpio_btn(){
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    //Set the pins into outputs and cols
    GPIOB->MODER &= ~GPIO_MODER_MODER0 & ~GPIO_MODER_MODER1 & ~GPIO_MODER_MODER2 & ~GPIO_MODER_MODER3 & ~GPIO_MODER_MODER4;
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR0_1 | GPIO_PUPDR_PUPDR1_1 |GPIO_PUPDR_PUPDR2_1 | GPIO_PUPDR_PUPDR3_1 | GPIO_PUPDR_PUPDR4_1;
    //Set the pins into inputs/rows, pull down resistor
    GPIOB->MODER &=~GPIO_MODER_MODER5 & ~GPIO_MODER_MODER6 & ~GPIO_MODER_MODER7 & ~GPIO_MODER_MODER8 & ~GPIO_MODER_MODER9;
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR5_1 | GPIO_PUPDR_PUPDR6_1 |GPIO_PUPDR_PUPDR7_1 | GPIO_PUPDR_PUPDR8_1 | GPIO_PUPDR_PUPDR9_1;
}
//using gpioB

void setup_timer3() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    TIM3->CR1 &= ~TIM_CR1_DIR;
    TIM3->PSC = 480-1;
    TIM3->ARR =100-1;
    TIM3->DIER |= TIM_DIER_UIE;
    TIM3->CR1 |= TIM_CR1_CEN;
    NVIC -> ISER[0] = 1 << TIM3_IRQn;

}
void TIM3_IRQHandler() {
/*
    int current_row, pap;
    current_row = -1;
    pap = GPIOA->IDR;
    if ((pap & 1<<4))
        {current_row =0;}
    else if ((pap & 1<<5))
    {current_row = 1;}
    else if ((pap & 1<<6))
        {current_row =2;}
    else if ((pap & 1<<7))
        {current_row =3;}
    */
    get_key_pressed();
    update_key_press();
    //manipulate the voice
    voice();
    TIM3->SR &=~TIM_SR_UIF;
}

void get_key_pressed(){
    int *row;
    int *col;
    row = getrow();
    col = getcol();
    for(int a = 0; a<5;a++)
    {
        for(int b = 0; b< 5;b++)
        {
            if(row[a]&row[b]){
                key_pressed[a][b] = 1;
                key_released[a][b] = 0;
            }
        }
    }
}
void voice(){
    setup_gpio();
    //   setup_adc();
       setup_dac();

       setup_timer2();
}

