/*
 * LEDhandler.c
 *
 *  Created on: Feb 27, 2023
 *      Author: AS
 */
#include "main.h"
#include "LEDhandler.h"

#define TMR4FREQUENCY 400000

extern PWM TIMERSETTINGS;   //this structure contains PWM settings (now - default)
extern PWM* pTIMERSETTINGS; //pointer
EMERGENCY_FLAG EMERGENCY={0};
EMERGENCY_FLAG* pEMERGENCY=&EMERGENCY;
extern TIM_HandleTypeDef htim6;

void HandleLedRedBlinkAlert(EMERGENCY_FLAG* pEMERGENCY)
{
	HAL_TIM_Base_Start_IT(&htim6);
if (EMERGENCY.VoltageFlag+EMERGENCY.IntTempFlag+EMERGENCY.ExtTempFlag==0)
{
  HAL_TIM_Base_Stop(&htim6);
  //TIM6->ARR=0;
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
}
else if (EMERGENCY.VoltageFlag+EMERGENCY.IntTempFlag+EMERGENCY.ExtTempFlag==1)
  {TIM6->ARR=500;}
else if (EMERGENCY.VoltageFlag+EMERGENCY.IntTempFlag+EMERGENCY.ExtTempFlag==2)
  {TIM6->ARR=200;}
else if (EMERGENCY.VoltageFlag+EMERGENCY.IntTempFlag+EMERGENCY.ExtTempFlag==3)
  {TIM6->ARR=100;}
else
  {TIM6->ARR=1;}
}

void StopChannels(TIM_HandleTypeDef* timer)
{
	HAL_TIM_PWM_Stop(timer, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(timer, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(timer, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop(timer, TIM_CHANNEL_4);
}

void Tim4ReInit(TIM_HandleTypeDef* timer, PWM* pTIMERSETTINGS)
{
	HAL_TIM_PWM_Init(timer);
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
    HAL_TIM_PWM_Start(timer, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(timer, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(timer, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(timer, TIM_CHANNEL_4);
}
