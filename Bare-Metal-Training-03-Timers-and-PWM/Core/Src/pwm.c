/*
 * pwm.c
 *
 *  Created on: 18 лют. 2023 р.
 *      Author: AS
 */
#include "pwm.h"

#define TMR4FREQUENCY 84000000 //depends on clock settings
extern const uint32_t FREQMIN;
extern const uint32_t FREQMAX;

void TimPWMStop(TIM_HandleTypeDef timer)
{
HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_ALL);
HAL_TIM_PWM_DeInit(&timer);
}
void SW1Handler(PWM* pTIMERSETTINGS) //this button decreases a frequency
{
	pTIMERSETTINGS->Frequency-=5000;
	if (pTIMERSETTINGS->Frequency<FREQMIN)
	     {pTIMERSETTINGS->Frequency=FREQMIN;}
	else
	     {}
}
void SW2Handler(PWM* pTIMERSETTINGS) //this button selects the signal output
{

}
void SW3Handler(PWM* pTIMERSETTINGS) //this button increases a frequency
{
	pTIMERSETTINGS->Frequency+=5000;
	if (pTIMERSETTINGS->Frequency>FREQMAX)
	     {pTIMERSETTINGS->Frequency=FREQMAX;}
	else
	     {}
}
void SW4Handler(PWM* pTIMERSETTINGS) //this button increases the duty cycle
  {
	pTIMERSETTINGS->DutyCycle+=(uint32_t)((TMR4FREQUENCY/pTIMERSETTINGS->Frequency)/20);//+5% from the period
	if (pTIMERSETTINGS->DutyCycle>100)
	     {pTIMERSETTINGS->DutyCycle=100;}
	else
	     {}
  }
void SW5Handler(PWM* pTIMERSETTINGS) //this button decreases the duty cycle
  {
	pTIMERSETTINGS->DutyCycle-=(uint32_t)((TMR4FREQUENCY/pTIMERSETTINGS->Frequency)/20);//+5% from the period
	if (pTIMERSETTINGS->DutyCycle<0)
	     {pTIMERSETTINGS->DutyCycle=0;}
	else
	     {}
  }
void DefaultChannelCreate(PWM* this)
{
this->Channel=TIM_CHANNEL_4;
this->Frequency=15000;
this->DutyCycle=70;
}

void Tim4ReInit(TIM_HandleTypeDef timer, PWM* PWM)
{
uint32_t ARRvalue=(uint32_t)(TMR4FREQUENCY/PWM->Frequency)-1;
uint32_t CCRvalue=(uint32_t)((PWM->DutyCycle*(ARRvalue+1))/100);
HAL_TIM_Base_Init(&timer);
HAL_TIM_Base_Start(&timer);
HAL_TIM_PWM_Init(&timer);
TIM4->ARR=ARRvalue;
HAL_TIM_PWM_Start(&timer, PWM->Channel);
switch (PWM->Channel)
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



}



