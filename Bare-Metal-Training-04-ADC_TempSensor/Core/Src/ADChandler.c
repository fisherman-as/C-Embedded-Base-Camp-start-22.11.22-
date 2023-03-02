/*
 * ADChandler.c
 *
 *  Created on: Feb 26, 2023
 *      Author: AS
 */
#include "main.h"
#include "ADCHandler.h"

extern TIM_HandleTypeDef htim4;

void HandleVoltageChannel(ADC_HandleTypeDef* adc, PWM* pTIMERSETTINGS)
{
	HAL_ADC_Start(adc);
	HAL_ADC_PollForConversion(adc, 100);
	uint16_t temp=HAL_ADC_GetValue(adc);
	pTIMERSETTINGS->DutyCycle[GREEN]=(uint16_t)((temp*100)/4095);
}

void HandleExtTempChannel(ADC_HandleTypeDef* adc, PWM* pTIMERSETTINGS)
{
	HAL_ADC_Start(adc);
	HAL_ADC_PollForConversion(adc, 100);
	uint16_t temp=HAL_ADC_GetValue(adc);
	pTIMERSETTINGS->DutyCycle[ORANGE]=(uint16_t)((temp*100)/4095);
}

void HandleIntTempChannel(ADC_HandleTypeDef* adc, PWM* pTIMERSETTINGS)
{
	HAL_ADC_Start(adc);
	HAL_ADC_PollForConversion(adc, 100);
	uint16_t temp=HAL_ADC_GetValue(adc);
	pTIMERSETTINGS->DutyCycle[BLUE]=(uint16_t)((temp*100)/4095);
}

void HandleChannels(ADC_HandleTypeDef* adc, PWM* pTIMERSETTINGS)
{
	HandleVoltageChannel(adc, pTIMERSETTINGS);
	HandleExtTempChannel(adc, pTIMERSETTINGS);
	HandleIntTempChannel(adc, pTIMERSETTINGS);
	HAL_ADC_Stop(adc);
	Tim4ReInit(&htim4, pTIMERSETTINGS);
}

