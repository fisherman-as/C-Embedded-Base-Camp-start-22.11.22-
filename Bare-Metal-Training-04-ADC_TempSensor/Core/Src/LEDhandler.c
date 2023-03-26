/*
 * LEDhandler.c
 *
 *  Created on: Feb 27, 2023
 *      Author: AS
 */
#include "main.h"
#include "LEDhandler.h"

#define TMR4FREQUENCY 400000
#define SENSORQUANTITY 3 //up to 4

extern PWM TIMERSETTINGS;   //this structure contains PWM settings
extern PWM* pTIMERSETTINGS; //pointer
EMERGENCY_FLAG EMERGENCY={0};
EMERGENCY_FLAG* pEMERGENCY=&EMERGENCY;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim6;

void HandleLedRedBlinkAlert(EMERGENCY_FLAG* pEMERGENCY)
{
  static uint32_t PreviousState=4;// when we start the program,...
                                  //we needn't any blinking (0,1,2,3 is harmful here)
  uint32_t CurrentState=EMERGENCY.VoltageFlag+EMERGENCY.IntTempFlag+EMERGENCY.ExtTempFlag;

  if (PreviousState==CurrentState)             // if there wasn't any changes in the statement...
    {return;}
  else if (PreviousState==0)                   //else if there was null, but it's not null now...
    {
	  PreviousState=CurrentState;
	  HAL_TIM_Base_Start_IT(&htim6);           //so, we need to start timer, because it was stopped
    }
  else
    {PreviousState=CurrentState;}              //if PreviousState wasn't null, we needn't restart timer

  switch (CurrentState)
  {
  case 0:
	  HAL_TIM_Base_Stop_IT(&htim6);
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
	  return;
	  break;
  case 1:
	  TIM6->ARR=500; //1Hz
	  break;
  case 2:
	  TIM6->ARR=200; //2.5Hz
	  break;
  case 3:
	  TIM6->ARR=100; //5Hz
	  break;
  default:
	  break;
	  return;
  }
}

void StopChannels()
{
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
	//HAL_TIM_PWM_Stop(timer, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
}

void Tim4ReInit(PWM* pTIMERSETTINGS)
{
	HAL_TIM_PWM_Init(&htim4);
	static uint16_t ARRvalue=0;
	static uint16_t CCRvalue[SENSORQUANTITY]={0};

	if (pTIMERSETTINGS->Frequency>0)
	{
		ARRvalue=(uint16_t)(TMR4FREQUENCY/pTIMERSETTINGS->Frequency)-1;
		for (uint32_t i=0; i<SENSORQUANTITY; i++)
		    {CCRvalue[i]=(uint16_t)(((pTIMERSETTINGS->DutyCycle[i])*(ARRvalue+1))/100);}
	}
	else
	    {for (uint32_t i=0; i<SENSORQUANTITY; i++) {CCRvalue[i]=0;}}

	TIM4->ARR=ARRvalue;
    TIM4->CCR1=CCRvalue[GREEN];
    TIM4->CCR2=CCRvalue[ORANGE];
    TIM4->CCR4=CCRvalue[BLUE];
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
}
