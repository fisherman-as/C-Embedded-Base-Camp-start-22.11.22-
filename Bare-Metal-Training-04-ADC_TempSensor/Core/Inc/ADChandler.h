/*
 * ADChandler.h
 *
 *  Created on: Feb 26, 2023
 *      Author: AS
 */

#ifndef SRC_ADCHANDLER_H_
#define SRC_ADCHANDLER_H_

#include "LEDHandler.h"



void ReadADC(ADC_HandleTypeDef, PWM*);
void LedHandle(COLOR, uint32_t, PWM*);

#endif /* SRC_ADCHANDLER_H_ */
