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

void HandleVoltageChannel(PWM*);
void HandleExtTempChannel(PWM*);
void HandleIntTempChannel(PWM*);
void HandleAdcChannels(PWM*);
#endif /* SRC_ADCHANDLER_H_ */
