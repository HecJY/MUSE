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
//#include "button.h"

int main(void)
{
    //pass row num and col num
    //get the row and col num
    /*
    gpio_btn();
    int *row[5];
    int *col[5];
    row = getrow();
    col = getcol();
*/

    //gpio_btn();

    setup_gpio();
 //   setup_adc();
    setup_dac();

    setup_timer2();
    //constantly getting the keys pressed
    while(1){/*
        gpio_btn();

        setup_gpio();
     //   setup_adc();
        setup_dac();
        setup_timer3();
        for(int i=0;i <5; i++)
        {
            for(int a = 0;a<5;a++){
                if (row[a] && col[i]){
                    int index = 5*a + i;
                    pressed[index] = 1;
                }
            }
        }

        setup_timer2();


    }*/
}
