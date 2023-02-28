/*
 * ADChandler.c
 *
 *  Created on: Feb 26, 2023
 *      Author: AS
 */
#include "main.h"
#include "ADCHandler.h"

extern TIM_HandleTypeDef htim4;



void ReadADC(ADC_HandleTypeDef adc, PWM* pTIMERSETTINGS)
{
  uint32_t adcValue=0;
  HAL_StatusTypeDef Status=HAL_ADC_Start(&adc);
  if (Status!=HAL_OK)
    {LedRedBlinkAlert(htim4, pTIMERSETTINGS);}
  Status=HAL_ADC_PollForConversion(&adc, 100);
  if (Status!=HAL_OK)
    {LedRedBlinkAlert(htim4, pTIMERSETTINGS);}
  else {adcValue = HAL_ADC_GetValue(&adc);}
  if (adcValue < 1680)
  {
	  LedHandle(GREEN, 50, pTIMERSETTINGS);
	  LedHandle(BLUE, 0, pTIMERSETTINGS);
  }
  else
  {
	  LedHandle(BLUE, 50, pTIMERSETTINGS);
	  LedHandle(GREEN, 0, pTIMERSETTINGS);
  }
}


void LedHandle(COLOR color, uint32_t DutyCycle, PWM* pTIMERSETTINGS ) //Read ADC, then write parameters to PWM
{
pTIMERSETTINGS->DutyCycle[color]=DutyCycle;
Tim4ReInit(htim4, pTIMERSETTINGS);
}
