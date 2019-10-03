/*
 * a_traffic_lights.c
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

// map the led to gpio pins
gpio_pin_t ledred = {PI_1, GPIOI, GPIO_PIN_1};
gpio_pin_t ledamber = {PB_14,  GPIOB, GPIO_PIN_14};
gpio_pin_t ledgreen = {PB_15,  GPIOB, GPIO_PIN_15};

// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();

	// initialise the gpio pins
  init_gpio(ledred, OUTPUT);
	init_gpio(ledamber, OUTPUT);
	init_gpio(ledgreen, OUTPUT);
	
	  // loop forever ...
	
	toggle_gpio(ledamber);
	HAL_Delay(2000);
  
	while(1)
  {
		
		toggle_gpio(ledred);
		toggle_gpio(ledamber);
		HAL_Delay(5000);
		
		toggle_gpio(ledamber);
		HAL_Delay(1000);
		
		toggle_gpio(ledred);
		toggle_gpio(ledamber);
		toggle_gpio(ledgreen);
		HAL_Delay(5000);
		
		toggle_gpio(ledgreen);
		toggle_gpio(ledamber);
		HAL_Delay(2000);
		
	}
}
