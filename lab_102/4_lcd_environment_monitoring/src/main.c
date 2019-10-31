/*
 * main.c
 *
 * this is the skeleton for task 4
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
  "*   Enviroment Sensing!    *",
  "*         Joe Maye         *"
};

// Map Pins
gpio_pin_t light = {PA_0, GPIOA, GPIO_PIN_0};

// CODE

// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
	init_adc(light);


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
	
	// Calibrate LDR	
	uint32_t  currtick = HAL_GetTick();
	uint32_t  cal_time = 5000;
	
	uint16_t smax = 0;
	uint16_t smin = 10000;

	while((HAL_GetTick() - currtick) < cal_time)
	{
		uint16_t sval = read_adc(light);
		
		if(sval > smax)
			smax = sval;
		if(sval < smin)
			smin = sval;
	}

	char calstr[24];
	sprintf(calstr, "CAL = %4d:%4d", smax, smin);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_DisplayStringAtLine(5, (uint8_t *)calstr);
	
	
	// enter main loop
	while(1)
	{
		
		
		uint16_t adc_val = read_adc(light);
		
		// format a string based around the adc value and print to lcd
		char str[12];
		//adc_val=((adc_val-500) / 10);
		sprintf(str, "Light = %4d", adc_val);
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_DisplayStringAtLine(6, (uint8_t *)str);
		
		HAL_Delay(1000);
	}
}