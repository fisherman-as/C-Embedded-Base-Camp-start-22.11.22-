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

void HandleVoltageChannel(ADC_HandleTypeDef*, PWM*);
void HandleExtTempChannel(ADC_HandleTypeDef*, PWM*);
void HandleIntTempChannel(ADC_HandleTypeDef*, PWM*);
void HandleChannels(ADC_HandleTypeDef*, PWM*);
#endif /* SRC_ADCHANDLER_H_ */
