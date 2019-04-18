/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/



#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "voice.h"

int main(void)
{
    setup_gpio();
 //   setup_adc();
    setup_dac();
    setup_timer2();
    while(1){
        ;
    }
}
