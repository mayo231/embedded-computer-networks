/*
 * main.c
 *
 * this is the skeleton for task 2
 *
 * author:    Dr. Alex Shenfield
 * date:      04/09/2018
 * purpose:   55-604481 embedded computer networks : lab 102
 */

// include the basic headers and hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "stm32746g_discovery_lcd.h"
#include "gpio.h"
#include "adc.h"

// LCD DEFINES
#define BOARDER     "****************************"

const char * welcome_message[2] = 
{
  "*     Hello LCD World!     *",
  "*      Welcome to SHU      *"
};

// CODE

// map the POT to the gpio pin PA0 and the LEDs to their pins
	gpio_pin_t pot = {PA_0, GPIOA, GPIO_PIN_0};
	gpio_pin_t led = {PI_1, GPIOI, GPIO_PIN_1};
	gpio_pin_t led2 = {PB_14, GPIOB, GPIO_PIN_14};
	gpio_pin_t led3 = {PB_15, GPIOB, GPIO_PIN_15}; 
	gpio_pin_t led4 = {PA_8, GPIOA, GPIO_PIN_8};
	
	
// declare our utility functions
	void configure_gpio(void);
	
// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
	init_adc(pot);
	init_gpio(led, OUTPUT);
	init_gpio(led2, OUTPUT);
	init_gpio(led3, OUTPUT);
	init_gpio(led4, OUTPUT);
	
	// initialise the lcd
  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, SDRAM_DEVICE_ADDR);
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

  // set the background colour to blue and clear the lcd
  BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
  BSP_LCD_Clear(LCD_COLOR_BLUE);
  
  // set the font to use
  BSP_LCD_SetFont(&Font24); 
  
  // print the welcome message ...
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_DisplayStringAtLine(0, (uint8_t *)BOARDER);
  BSP_LCD_DisplayStringAtLine(1, (uint8_t *)welcome_message[0]);
  BSP_LCD_DisplayStringAtLine(2, (uint8_t *)welcome_message[1]);
  BSP_LCD_DisplayStringAtLine(3, (uint8_t *)BOARDER);
	
	// delay a little ...
  HAL_Delay(2000);
	
	// enter main loop
	while(1)
	{
		uint16_t adc_val = read_adc(pot);
		
		// format a string based around the adc value and print to lcd
		char str[12];
		adc_val=(adc_val / 4095.0) * 100.0;
		sprintf(str, "ADC = %4d", adc_val);
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_DisplayStringAtLine(6, (uint8_t *)str);
		
		
		uint16_t bar_width = (adc_val / 100.0) * 480;
		uint16_t fill_width = 480 - bar_width;
		
		
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(0, 200, bar_width, 10);
		BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
		BSP_LCD_FillRect(bar_width, 200, fill_width, 10);
		
		if(adc_val<25)
		{
			write_gpio (led,0);
			write_gpio (led2,0);
			write_gpio (led3,0);
			write_gpio (led4,0);
		}
		
		if((adc_val>=25)&&(adc_val<50))
		{
			write_gpio (led,1);
			write_gpio (led2,0);
			write_gpio (led3,0);
			write_gpio (led4,0);
		}
		
		if((adc_val>=50)&&(adc_val<75))
		{
			write_gpio (led,1);
			write_gpio (led2,1);
			write_gpio (led3,0);
			write_gpio (led4,0);		
		}
		
		if((adc_val>=75)&&(adc_val<99))
		{
			write_gpio (led,1);
			write_gpio (led2,1);
			write_gpio (led3,1);
			write_gpio (led4,0);
		}
		
		if(adc_val>=99)
		{
			write_gpio (led,1);
			write_gpio (led2,1);
			write_gpio (led3,1);
			write_gpio (led4,1);
		}
		
		// HAL_Delay(250);
	}
}
