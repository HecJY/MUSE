#include "voice.h"
#include "wave.h"
int N = 1024;
char pressed[25] = {0};
int offset[25] = {0};
int step[25]={
        /*left half*/
        13.8591 * (1<<16), //C♯3/D♭3
        146.8324/10.0 * (1<<16), //D3
        155.5635/10.0 * (1<<16), //D♯3/E♭3
        164.8138/10.0 * (1<<16), //E3
        174.6141/10.0 * (1<<16), // F3
        184.9972/10.0 * (1<<16), //F♯3/G♭3
        195.9977/10.0 * (1<<16), //G3
        207.6523/10.0 * (1<<16), //G♯3/A♭3
        220.0000/10.0 * (1<<16), //A3
        233.0819/10.0 * (1<<16), //A♯3/B♭3
        246.9417/10.0 * (1<<16), //B3
        /*middle*/
        261.626/10.0 * (1<<16), //Major C, do
        /*right half*/
        277.1826/10.0 * (1<<16), //C major, D minor
        293.6648/10.0 * (1<<16), //D4
        311.1270/10.0 * (1<<16),
        329.6276/10.0 * (1<<16),
        349.2282/10.0 * (1<<16),
        369.9944/10.0 * (1<<16),
        391.9954/10.0 * (1<<16),
        415.3047/10.0 * (1<<16),
        440.0000/10.0 * (1<<16),
        466.1638/10.0 * (1<<16),
        493.8833/10.0 * (1<<16),
        523.2511/10.0 * (1<<16),
        554.3653/10.0 * (1<<16)
};

void setup_gpio() {
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA->MODER &= ~(0x33F);
    GPIOA->MODER |= 0x33F;
}


void setup_dac() {
    RCC->APB1ENR |= RCC_APB1ENR_DACEN;
    DAC->CR &= ~DAC_CR_EN1;
    DAC->CR &= ~DAC_CR_BOFF1;
    DAC->CR |= DAC_CR_TEN1;
    DAC->CR |= DAC_CR_TSEL1;
    DAC->CR |= DAC_CR_EN1;
}


void setup_timer2() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2->CR1 &= ~TIM_CR1_DIR;
    TIM2->PSC = 1200-1;
    TIM2->ARR = 4-1;
    TIM2->DIER |= TIM_DIER_UIE;
    TIM2->CR1 |= TIM_CR1_CEN;
   /* TIM2->CCER |= TIM_CCER_CC2E;
    TIM2->DIER |= TIM_DIER_CC2IE;
    TIM2->CCER |= TIM_CCER_CC1E;
    TIM2->DIER |= TIM_DIER_CC1IE;*/

    NVIC -> ISER[0] = 1 << TIM2_IRQn;
}

void TIM2_IRQHandler() {
    while((DAC->SWTRIGR & DAC_SWTRIGR_SWTRIG1) == DAC_SWTRIGR_SWTRIG1);
    int x;
    int sample = 0;

    for(x=0; x<25; x++) {
        if (pressed[x]) {
            offset[x] += step[x];

            if (offset[x] >= N<<16){
                offset[x] -= N<<16;
            }
            sample += wavetable[offset[x]>>16];
        }
    }
    sample = sample / 32 + 2048;
    if (sample > 4095){
        sample = 4095; // clip
    }
    else if (sample < 0)
        {
        sample = 0; // clip
        }
    DAC->DHR12R1 = sample;
    DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG1;
    TIM2->SR &=~TIM_SR_UIF;

}
