/*
 * LEDhandler.c
 *
 *  Created on: Feb 27, 2023
 *      Author: AS
 */
#include "main.h"
#include "LEDhandler.h"

#define TMR4FREQUENCY 8000000

extern PWM TIMERSETTINGS;      //this structure contains PWM settings (now - default)
extern PWM* pTIMERSETTINGS; //pointer


void StopChannels(TIM_HandleTypeDef timer)
{
	HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop(&timer, TIM_CHANNEL_4);
}

void Tim4ReInit(TIM_HandleTypeDef timer, PWM* pTIMERSETTINGS)
{
	HAL_TIM_PWM_Init(&timer);
	static uint16_t ARRvalue=0;
	static uint16_t CCRvalue[3]={0};

	if (pTIMERSETTINGS->Frequency>0)
	{
		ARRvalue=(uint16_t)(TMR4FREQUENCY/pTIMERSETTINGS->Frequency)-1;
		for (uint32_t i=0; i<4;i++)
		    {CCRvalue[i]=(uint16_t)(((pTIMERSETTINGS->DutyCycle[i])*(ARRvalue+1))/100);}
	}
	else
	    {for (uint32_t i=0; i<4;i++) {CCRvalue[i]=0;}}

	TIM4->ARR=ARRvalue;
    TIM4->CCR1=CCRvalue[0];
    TIM4->CCR2=CCRvalue[1];
    TIM4->CCR3=CCRvalue[2];
    TIM4->CCR4=CCRvalue[3];
    //HAL_TIM_PWM_Start(&timer, TIM_CHANNEL_ALL);
    HAL_TIM_PWM_Start(&timer, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&timer, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&timer, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&timer, TIM_CHANNEL_4);
}
