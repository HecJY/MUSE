#ifndef VOICE_H
#define VOICE_H


#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void waveform_gen(void);
void setup_gpio(void);
void setup_dac(void);
void setup_timer2(void);
void TIM2_IRQHandler(void);




#endif
