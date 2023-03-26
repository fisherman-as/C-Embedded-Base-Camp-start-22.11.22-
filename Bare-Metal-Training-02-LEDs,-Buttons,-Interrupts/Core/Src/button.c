/*
 * button.c
 *
 *  Created on: Feb 15, 2023
 *      Author: yabanzhialek
 */
#include "button.h"



extern volatile uint32_t SW13Flag;
extern volatile uint32_t SW2Flag;
extern volatile uint32_t SW45Flag;
extern LED leds[];
extern uint32_t LED_QUANTITY;
extern TIM_HandleTypeDef htim6;

void SW1Handler(void) //this button decreases blinking speed
{
	 if (SW13Flag>0)
	     {SW13Flag--;}
	 else
	     {SW13Flag=4;}
	 htim6.Init.Period = 1000/(SW13Flag+1);
	 HAL_TIM_Base_Init(&htim6);
	 HAL_TIM_Base_Start_IT(&htim6);
}
void SW2Handler(void) //this button turns on/off blinking
{
	SW2Flag^=1<<1;//0=StopBlink, 1=Blink
}
void SW3Handler(void) //this button increases blinking speed
{
	 if (SW13Flag<4)
	      {SW13Flag++;}
	 else
	      {SW13Flag=0;}
	 htim6.Init.Period = 1000/(SW13Flag+1);
	 HAL_TIM_Base_Init(&htim6);
	 HAL_TIM_Base_Start_IT(&htim6);
}
void SW4Handler(void) //this button calls the next blinking scheme
  {
   if (SW45Flag<2)
       {SW45Flag++;}
   else
       {SW45Flag=0;}

   for (uint32_t n=0; n<LED_QUANTITY; n++) //here we prepare start LED positions for blinking (off)
	     {HAL_GPIO_WritePin(leds[n].port, leds[n].pin, GPIO_PIN_RESET);}
  }
void SW5Handler(void) //this button calls the previous blinking scheme
  {
	 if (SW45Flag>0)
	     {SW45Flag--;}
	 else
	     {SW45Flag=2;}

	 for (uint32_t n=0; n<LED_QUANTITY; n++) //here we prepare start LED positions for blinking (off)
	     {HAL_GPIO_WritePin(leds[n].port, leds[n].pin, GPIO_PIN_RESET);}
  }

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  switch (GPIO_Pin)
    {
    case SW1_Pin:
      SW1Handler(); //this button decreases blinking speed
      break;
    case SW2_Pin:
      SW2Handler(); //this button turns on/off blinking
      break;
    case SW3_Pin:
      SW3Handler(); //this button increases blinking speed
      break;
    case SW4_Pin:
      SW4Handler(); //this button calls the next blinking scheme
      break;
    case SW5_Pin:
      SW5Handler(); //this button calls the previous blinking scheme
      break;
    default:
     break;
    }
}

void ButtonsHandler(void)
{
  switch (SW45Flag)
  {
    case 0:
	  Scheme1();
	  break;
    case 1:
	  Scheme2();
	  break;
    case 2:
	  Scheme3();
	  break;
    default:
	  break;
  }
}



