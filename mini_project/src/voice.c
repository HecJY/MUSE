#include "voice.h"
int s1 = 0;
int s2 = 0;
int waveform[256];

int wavetable[256];

float freqtable[]={
        /*left half*/
        138.5913, //C♯3/D♭3
        146.8324, //D3
        155.5635, //D♯3/E♭3
        164.8138, //E3
        174.6141, // F3
        184.9972, //F♯3/G♭3
        195.9977, //G3
        207.6523, //G♯3/A♭3
        220.0000, //A3
        233.0819, //A♯3/B♭3
        246.9417, //B3
        /*middle*/
        261.626, //Major C, do
        /*right half*/
        277.1826, //C major, D minor
        293.6648, //D4
        311.1270,
        329.6276,
        349.2282,
        369.9944,
        391.9954,
        415.3047,
        440.0000,
        466.1638,
        493.8833,
        523.2511
};
int *waveform_gen(int key_index){
    float offset = 0.0;
    float amp = 32767;
    int n = 256;
    float freq = freqtable[key_index];
    for(int i=0; i< n; i++){
        float point =offset +amp* sin(i*2*M_PI*freq);
        waveform[i] = (int) point;
    }

    return waveform;

}

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
    wavetable = waveform_gen(12);
    NVIC -> ISER[0] = 1 << TIM2_IRQn;
}

void TIM2_IRQHandler() {
    while((DAC->SWTRIGR & DAC_SWTRIGR_SWTRIG1) == DAC_SWTRIGR_SWTRIG1);
    //wavetable = waveform_gen(12);
    float point_rn = (wavetabl[s1] + 32768)>>4;
    //float point_rn = waveform_gen(12)[s1];
    DAC->DHR12R1 = (int) point_rn;
    DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG1;
    s1 = s1%256;
    s1 +=1;
      /*  if (s1==100)
            {s1 = 0;}
        else if (s1!=100)
            {s1 +=1;}
        if (s2==100)
            {s2 = 0;}
        else if (s2!=100)
            {s2 +=2;}*/
    /*
    if (s1 < 100){
        s1 ++;
    }
    else{
        s1 = 0;*/
        /*
        s2 ++;
        if (s2 >= 24)
        {
           s2 =0;
        }*/
    //}
    //    s2 = (s2+2)%100;
        TIM2->SR &=~TIM_SR_UIF;

}


