/*
 * ADChandler.c
 *
 *  Created on: Feb 26, 2023
 *      Author: AS
 */
#include "main.h"
#include "ADCHandler.h"

extern TIM_HandleTypeDef htim4;
extern ADC_HandleTypeDef hadc1;
extern EMERGENCY_FLAG EMERGENCY;
extern EMERGENCY_FLAG* pEMERGENCY;

void HandleVoltageChannel(PWM* pTIMERSETTINGS)
{
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 100);
	uint16_t temp=HAL_ADC_GetValue(&hadc1);
	pTIMERSETTINGS->DutyCycle[BLUE]=(uint16_t)((temp*100)/4095);
	if (pTIMERSETTINGS->DutyCycle[BLUE]>60)
	  {EMERGENCY.VoltageFlag=1;}
	else {EMERGENCY.VoltageFlag=0;}
}

void HandleIntTempChannel(PWM* pTIMERSETTINGS)
{
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 100);
	uint16_t temp=HAL_ADC_GetValue(&hadc1);
	/*---------------------------------------------------*/
	//	(+0.0025V per 1C) or (+0.025V per 10C); Vref=3.3V, I did check it!!! Not 1.21V.
	//  0.71V -> 5C
	//	0.76V -> 25C
	//  0.86V -> 65C (25+40)
	//  0.885V -> 75C - it will be the threshold for red blinking
	//  0.96V -> 105C
	// So, we can imagine that voltage will be changed from 0.71V (880) to 0.96V (1200) in general(5C - 105C)
	// However, for the best result presenting, let's indicate  the range from ~25C to 105C only
	// Therefore, the ADC will give us the values from 1050 to 1200, threshold is ~1100
	// So, the DutyCycle will be 0% at temp=1050 and 100% at temp=1200
	// So, the formula is following: DutyCycle = (2*temp/3 - 700)
	/*--------------------------------------------------*/
	uint16_t DutyCycle=0;
	if (temp>1200)
	  {DutyCycle=100;}
	else if (temp<1050)
	  {DutyCycle=0;}
	else
	  {DutyCycle=(uint16_t)((2*temp/3)-700);}
	pTIMERSETTINGS->DutyCycle[ORANGE]=DutyCycle;
	if (pTIMERSETTINGS->DutyCycle[ORANGE]>33)
	  {EMERGENCY.IntTempFlag=1;}
	else {EMERGENCY.IntTempFlag=0;}
}

void HandleExtTempChannel(PWM* pTIMERSETTINGS)
{
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 100);
	uint16_t temp=HAL_ADC_GetValue(&hadc1);
	pTIMERSETTINGS->DutyCycle[GREEN]=(uint16_t)((temp*100)/4095);
	if (pTIMERSETTINGS->DutyCycle[GREEN]<30)
	  {EMERGENCY.ExtTempFlag=1;}
	else {EMERGENCY.ExtTempFlag=0;}
}

void HandleAdcChannels(PWM* pTIMERSETTINGS)
{
	HandleVoltageChannel(pTIMERSETTINGS);
	HandleIntTempChannel(pTIMERSETTINGS);
	HandleExtTempChannel(pTIMERSETTINGS);
	HAL_ADC_Stop(&hadc1);
	Tim4ReInit(pTIMERSETTINGS);
	HandleLedRedBlinkAlert(pEMERGENCY);
}

