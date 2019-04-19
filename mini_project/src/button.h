#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#define KEY_PRESS_MASK  0b11000111
#define KEY_REL_MASK    0b11100011
int *getrow(void);
int *getcol(void);
void gpio_btn(void);
int checkequal(int arr[],int arr1[]);
int hist_col[5];
int hist_row[5];
int row[5];
int col[5];
int row_pressed[5];
int col_pressed[5];
/* Debounce Algorithm*/
void update_button(void);
void setup_timer3(void);
void updatearr(int arr[],int arr1[]);

