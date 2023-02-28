/*
 * ADChandler.c
 *
 *  Created on: Feb 26, 2023
 *      Author: AS
 */
#include "main.h"
#include "ADCHandler.h"

extern TIM_HandleTypeDef htim4;

void ADCConfChannel(ADC_HandleTypeDef* hadc, uint32_t channel, uint32_t rank, uint32_t SampleTime)
{
ADC_ChannelConfTypeDef sConfig;
sConfig.Channel=channel;
sConfig.Rank=rank;
sConfig.SamplingTime=SampleTime;
HAL_ADC_ConfigChannel(hadc, &sConfig);
}

uint32_t ReadADC(ADC_HandleTypeDef* adc, PWM* pTIMERSETTINGS)
{
	HAL_ADC_Start(adc);
  uint32_t adcValue=0;
  HAL_StatusTypeDef Status=HAL_ADC_Start(adc);
  if (Status!=HAL_OK)
    {LedRedBlinkAlert(htim4, pTIMERSETTINGS); return 0;}
  Status=HAL_ADC_PollForConversion(adc, 100);
  if (Status!=HAL_OK)
    {LedRedBlinkAlert(htim4, pTIMERSETTINGS); return 0;}
  else {adcValue = HAL_ADC_GetValue(adc);}
  HAL_ADC_Stop(adc);
  return adcValue;
}


void LedHandle(COLOR color, uint32_t DutyCycle, PWM* pTIMERSETTINGS) //Read ADC, then write parameters to PWM
{
  pTIMERSETTINGS->DutyCycle[color]=DutyCycle;
  Tim4ReInit(&htim4, pTIMERSETTINGS);
}

void HandleVoltageChannel(ADC_HandleTypeDef* adc, PWM* pTIMERSETTINGS)
{
  ADCConfChannel(adc, ADC_CHANNEL_3, 1, ADC_SAMPLETIME_480CYCLES);
  uint32_t temp=ReadADC(adc, pTIMERSETTINGS);
  uint16_t DutyCycle=(uint16_t)((temp*100)/4095);
  LedHandle(GREEN, DutyCycle, pTIMERSETTINGS);
}

void HandleExtTempChannel(ADC_HandleTypeDef* adc, PWM* pTIMERSETTINGS)
{
  ADCConfChannel(adc, ADC_CHANNEL_9, 2, ADC_SAMPLETIME_56CYCLES);
  uint32_t temp=ReadADC(adc, pTIMERSETTINGS);
  uint16_t DutyCycle=(uint16_t)((temp*100)/4095);
  LedHandle(ORANGE, DutyCycle, pTIMERSETTINGS);
}



