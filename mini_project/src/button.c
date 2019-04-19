#include "button.h"

int press=0;
int release=1;
int update = -1;
int fang = -1;
int *getrow(){
    //the initial state of the row num
    int row1[5];
   if( GPIOB->IDR & 1<<5){
       row1[0] = 1;
   }
   else if(GPIOB->IDR & 1<<6){
       row1[1] = 1;
   }
   else if(GPIOB->IDR & 1<<7){
          row1[2] = 1;
      }
   else if(GPIOB->IDR & 1<<8){
          row1[3] = 1;
      }
   else if(GPIOB->IDR & 1<<9){
          row1[4] = 1;
      }
   return row1;
}
int *getcol(){
    int col1[5];
    if( GPIOB->IDR & 1<<0){
        col1[0] = 1;
    }
    else if(GPIOB->IDR & 1<<1){
        col1[1] = 1;
    }
    else if(GPIOB->IDR & 1<<2){
           col1[2] = 1;
       }
    else if(GPIOB->IDR & 1<<3){
           col1[3] = 1;
       }
    else if(GPIOB->IDR & 1<<4){
           col1[4] = 1;
       }
    return col1;
}
/* debounce process*/
void update_key_press() {
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            if ((checkequal(row,hist_row)) && (checkequal(col,hist_col))) {
                press+=1;
                if (press == 5)
                {
                    press = 0;
                    fang = -1;
                    update = 1;
                }
            }
            else
            {
                release += 1;
                if (release == 5) {
                    release = 0;
                    fang = 1;
                    update = -1;
                }
            }
        }
    }
}
int checkequal(int arr[],int arr1[]){
    for(int i = 0; i<5;i++){
        if (arr[i] != arr1[i]){
            return -1;
        }
    }
    return 1;


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
    int *temp;
    temp = getcol();
    updatearr(hist_col,temp);
    temp = getrow();
    updatearr(hist_row,temp);
    if(fang){
        temp = getcol();
        updatearr(col,temp);
        temp = getrow();
        updatearr(row,temp);
    }
    update_key_press();
    if(update){
        temp = getcol();
        updatearr(col_pressed,temp);
        temp = getrow();
        updatearr(row_pressed,temp);
    }
    micro_wait(1000000);
    TIM3->SR &=~TIM_SR_UIF;
}
void updatearr(int arr[],int arr1[]){
    for(int i=0;i <5; i++)
    {
       arr[i] = arr1[i];
}
}
