#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

int getkey(void);
void gpio_btn(void);

/* Debounce Algorithm*/
void update_button(uint8_t *button_history);

uint8_t is_button_up(uint8_t *button_history);
uint8_t is_button_down(uint8_t *button_history);
uint8_t is_button_press(uint8_t *button_history);
uint8_t is_button_release(uint8_t *button_history);

uint8_t read_button(void);
