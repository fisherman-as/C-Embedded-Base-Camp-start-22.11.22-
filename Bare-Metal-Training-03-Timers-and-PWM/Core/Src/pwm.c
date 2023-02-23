/*
 * pwm.c
 *
 *  Created on: 18 лют. 2023 р.
 *      Author: AS
 */
#include "pwm.h"
#include "main.h"
#include "stm32f4xx_hal_tim.h"
extern const uint32_t TMR4FREQUENCY;
extern const uint32_t FREQMIN;
extern const uint32_t FREQMAX;
extern FLAGS ButtonFlag;
extern PWM* pTIMERSETTINGS;

void SW1Handler(TIM_HandleTypeDef timer, PWM* pTIMERSETTINGS) //this button decreases a frequency
{
	pTIMERSETTINGS->Frequency-=5000;
	if (pTIMERSETTINGS->Frequency<FREQMIN)
	     {pTIMERSETTINGS->Frequency=FREQMIN;}
	else
	     {}
}
void SW2Handler(TIM_HandleTypeDef timer, PWM* pTIMERSETTINGS) //this button selects the signal output
{
	uint32_t temp=pTIMERSETTINGS->Channel;
  switch (temp)
  {
  case TIM_CHANNEL_1:
	  pTIMERSETTINGS->Channel=TIM_CHANNEL_2;
	  break;
  case TIM_CHANNEL_2:
	  pTIMERSETTINGS->Channel=TIM_CHANNEL_3;
	  break;
  case TIM_CHANNEL_3:
	  pTIMERSETTINGS->Channel=TIM_CHANNEL_4;
	  break;
  case TIM_CHANNEL_4:
	  pTIMERSETTINGS->Channel=TIM_CHANNEL_1;
	  break;
  default:
	  pTIMERSETTINGS->Channel=TIM_CHANNEL_1;
	  break;
  }
}
void SW3Handler(TIM_HandleTypeDef timer, PWM* pTIMERSETTINGS) //this button increases a frequency
{
	pTIMERSETTINGS->Frequency+=5000;
	if (pTIMERSETTINGS->Frequency>FREQMAX)
	     {pTIMERSETTINGS->Frequency=FREQMAX;}
	else
	     {}
}
void SW4Handler(TIM_HandleTypeDef timer, PWM* pTIMERSETTINGS) //this button increases the duty cycle
  {
	pTIMERSETTINGS->DutyCycle+=5;//+5% of the period
	if (pTIMERSETTINGS->DutyCycle>100)
	     {pTIMERSETTINGS->DutyCycle=100;}
	else
	     {}
  }
void SW5Handler(TIM_HandleTypeDef timer, PWM* pTIMERSETTINGS) //this button decreases the duty cycle
  {
	pTIMERSETTINGS->DutyCycle-=5;//-5% of the period
	if (pTIMERSETTINGS->DutyCycle<0)
	     {pTIMERSETTINGS->DutyCycle=0;}
	else
	     {}
  }

void Tim4ReInit(TIM_HandleTypeDef timer, PWM* pwm)
{
uint32_t ARRvalue=(uint32_t)(TMR4FREQUENCY/pwm->Frequency)-1;
uint32_t CCRvalue=(uint32_t)(((pwm->DutyCycle)*(ARRvalue+1))/100);
TIM4->ARR=ARRvalue;
  switch (pwm->Channel)
  {
    case TIM_CHANNEL_1:
	  TIM4->CCR1=CCRvalue;
	  break;
    case TIM_CHANNEL_2:
	  TIM4->CCR2=CCRvalue;
	  break;
    case TIM_CHANNEL_3:
	  TIM4->CCR3=CCRvalue;
	  break;
    case TIM_CHANNEL_4:
   	  TIM4->CCR4=CCRvalue;
	  break;
    default:
	  TIM4->CCR1=CCRvalue;
	  break;
  }
  HAL_TIM_PWM_Start(&timer, pwm->Channel);
}

void ButtonsHandler(TIM_HandleTypeDef timer)
{
	if (!HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin))
	{
	    SW1Handler(timer, pTIMERSETTINGS); //this button decreases a frequency
    }
	else if (!HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin))
	{
		SW2Handler(timer, pTIMERSETTINGS); //this button selects the signal output
	}
	else if (!HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin))
	{
		SW3Handler(timer, pTIMERSETTINGS); //this button increases a frequency
	}
	else if (!HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin))
	{
		SW4Handler(timer, pTIMERSETTINGS); //this button increases the duty cycle
	}
	else if (!HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin))
	{
		SW5Handler(timer, pTIMERSETTINGS); //this button decreases the duty cycle
	}
	else
	{

	}
}

