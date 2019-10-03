/*
 * b_led_dice.c
 *
 * this is the main application skeleton for the student exercises in task 3
 *
 */

// include the hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "gpio.h"
#include "random_numbers.h"

// map the led to gpio pins
gpio_pin_t ledTL = {PI_1,  GPIOI, GPIO_PIN_1};
gpio_pin_t ledML = {PB_14,  GPIOB, GPIO_PIN_14};
gpio_pin_t ledBL = {PB_15,  GPIOB, GPIO_PIN_15};
gpio_pin_t ledM = {PA_8,  GPIOA, GPIO_PIN_8};
gpio_pin_t ledTR = {PA_15,  GPIOA, GPIO_PIN_15};
gpio_pin_t ledMR = {PI_2,  GPIOI, GPIO_PIN_2};
gpio_pin_t ledBR = {PI_3,  GPIOI, GPIO_PIN_3};

// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
	
	// initialise the gpio pins
  init_gpio(ledTL, OUTPUT);
	init_gpio(ledML, OUTPUT);
	init_gpio(ledBL, OUTPUT);
	init_gpio(ledM, OUTPUT);
	init_gpio(ledTR, OUTPUT);
	init_gpio(ledMR, OUTPUT);
	init_gpio(ledBR, OUTPUT);
}
