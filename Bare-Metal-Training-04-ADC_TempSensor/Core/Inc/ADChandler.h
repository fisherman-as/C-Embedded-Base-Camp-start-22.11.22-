/*
 * ADChandler.h
 *
 *  Created on: Feb 26, 2023
 *      Author: AS
 */

#ifndef SRC_ADCHANDLER_H_
#define SRC_ADCHANDLER_H_

#include "LEDHandler.h"

typedef enum {VOLTAGE, EXT_TEMP, INT_TEMP}ADC_CHANNEL;

void ADCConfChannel(ADC_HandleTypeDef*, uint32_t, uint32_t, uint32_t);
uint32_t ReadADC(ADC_HandleTypeDef*, PWM*);
void LedHandle(COLOR, uint32_t, PWM*);
void HandleVoltageChannel(ADC_HandleTypeDef*, PWM*);
void HandleExtTempChannel(ADC_HandleTypeDef*, PWM*);
#endif /* SRC_ADCHANDLER_H_ */
