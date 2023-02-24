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
extern PWM* pTIMERSETTINGS;
extern const uint32_t PRESSNUM;

void StopChannels(TIM_HandleTypeDef timer) //THE FUNCTION DOESN'T WORK
{
	HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_4);
}
void SW1Handler(TIM_HandleTypeDef timer, PWM* pTIMERSETTINGS) //this button decreases a frequency
{
	if (pTIMERSETTINGS->Frequency>=5000)
	{
	  pTIMERSETTINGS->Frequency-=5000;
	}
	else {}
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
	  pTIMERSETTINGS->Channel=TIM_CHANNEL_ALL;
	  break;
  case TIM_CHANNEL_ALL:
	  pTIMERSETTINGS->Channel=TIM_CHANNEL_1;
	  break;
  default:
	  //pTIMERSETTINGS->Channel=TIM_CHANNEL_1;
	  break;
  }
}
void SW3Handler(TIM_HandleTypeDef timer, PWM* pTIMERSETTINGS) //this button increases a frequency
{
	pTIMERSETTINGS->Frequency+=5000;
	if (pTIMERSETTINGS->Frequency>FREQMAX)
	     {pTIMERSETTINGS->Frequency=FREQMAX;}
	else {}
}
void SW4Handler(TIM_HandleTypeDef timer, PWM* pTIMERSETTINGS) //this button increases the duty cycle
  {
	pTIMERSETTINGS->DutyCycle+=5;//+5% of the period
	if (pTIMERSETTINGS->DutyCycle>100)
	     {pTIMERSETTINGS->DutyCycle=100;}
	else {}
  }
void SW5Handler(TIM_HandleTypeDef timer, PWM* pTIMERSETTINGS) //this button decreases the duty cycle
  {
    #define STEP 5
	if (pTIMERSETTINGS->DutyCycle>=STEP)
	{pTIMERSETTINGS->DutyCycle-=STEP;}//-5% of the period
	else {}
    #undef STEP
  }

void Tim4ReInit(TIM_HandleTypeDef timer, PWM* pwm)
{
	static uint16_t ARRvalue=0;
	static uint16_t CCRvalue=0;
	if (pwm->Frequency>0)
	{
	  ARRvalue=(uint16_t)(TMR4FREQUENCY/pwm->Frequency)-1;
	  CCRvalue=(uint16_t)(((pwm->DutyCycle)*(ARRvalue+1))/100);
	}
	else {CCRvalue=0;}
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
    case TIM_CHANNEL_ALL:
      TIM4->CCR1=0;
      TIM4->CCR2=0;
      TIM4->CCR3=0;
      TIM4->CCR4=0;
	  break;
    default:
	  //TIM4->CCR1=CCRvalue;
	  break;
  }
  if (pwm->Channel!=TIM_CHANNEL_ALL)
    {HAL_TIM_PWM_Start(&timer, pwm->Channel);}

}

void ButtonsHandler(TIM_HandleTypeDef timer)
{
	static uint32_t TimeCounter=0;
	static struct
		  {
		    uint32_t SW1:10;
		    uint32_t SW2:10;
		    uint32_t SW3:10;
		    uint32_t SW4:10;
		    uint32_t SW5:10;
		  }PressCounter={0};
	if (TimeCounter<HAL_GetTick())
	{
		  if (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)==GPIO_PIN_RESET) {PressCounter.SW1++;}
		  else if (PressCounter.SW1>0) {PressCounter.SW1--;}
		  if (HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin)==GPIO_PIN_RESET) {PressCounter.SW2++;}
		  else if (PressCounter.SW2>0) {PressCounter.SW2--;}
		  if (HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)==GPIO_PIN_RESET) {PressCounter.SW3++;}
		  else if (PressCounter.SW3>0) {PressCounter.SW3--;}
		  if (HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin)==GPIO_PIN_RESET) {PressCounter.SW4++;}
		  else if (PressCounter.SW4>0) {PressCounter.SW4--;}
		  if (HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)==GPIO_PIN_RESET) {PressCounter.SW5++;}
		  else if (PressCounter.SW5>0) {PressCounter.SW5--;}
	}
	TimeCounter=HAL_GetTick();
	if (PressCounter.SW1>=PRESSNUM)
	{
		HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_1);
		HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_2);
		HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_3);
		HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_4);
		SW1Handler(timer, pTIMERSETTINGS);
		Tim4ReInit(timer, pTIMERSETTINGS);
		PressCounter.SW1=0;
	} //this button decreases a frequency
	if (PressCounter.SW2>=PRESSNUM)
	{
		HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_1);
		HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_2);
		HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_3);
		HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_4);
		SW2Handler(timer, pTIMERSETTINGS);
		Tim4ReInit(timer, pTIMERSETTINGS);
		PressCounter.SW2=0;
	} //this button selects the signal output
	if (PressCounter.SW3>=PRESSNUM)
	{
		HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_1);
		HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_2);
		HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_3);
		HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_4);
		SW3Handler(timer, pTIMERSETTINGS);
		Tim4ReInit(timer, pTIMERSETTINGS);
		PressCounter.SW3=0;
	} //this button increases a frequency
	if (PressCounter.SW4>=PRESSNUM)
	{
		HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_1);
		HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_2);
		HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_3);
		HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_4);
		SW4Handler(timer, pTIMERSETTINGS);
		Tim4ReInit(timer, pTIMERSETTINGS);
		PressCounter.SW4=0;
	} //this button increases the duty cycle
	if (PressCounter.SW5>=PRESSNUM)
	{
		HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_1);
		HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_2);
		HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_3);
		HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_4);
		SW5Handler(timer, pTIMERSETTINGS);
		Tim4ReInit(timer, pTIMERSETTINGS);
		PressCounter.SW5=0;
	} //this button decreases the duty cycle

}

