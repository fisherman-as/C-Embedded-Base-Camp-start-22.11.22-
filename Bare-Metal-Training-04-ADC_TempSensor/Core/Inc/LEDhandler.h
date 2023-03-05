/*
 * LEDhandler.h
 *
 *  Created on: Feb 27, 2023
 *      Author: AS
 */

#ifndef INC_LEDHANDLER_H_
#define INC_LEDHANDLER_H_
#include "main.h"

typedef enum {GREEN, ORANGE, BLUE}COLOR;

typedef struct
    {
	  uint16_t Frequency;
      uint16_t DutyCycle[3]; //the duty cycle of three channels. 0=GREEN, 1=ORANGE, 2=BLUE
    }PWM;
typedef struct
{
	uint32_t VoltageFlag;
	uint32_t IntTempFlag;
	uint32_t ExtTempFlag;
}EMERGENCY_FLAG;

void HandleLedRedBlinkAlert(EMERGENCY_FLAG*);
void StopChannels(); //stops all 3 PWM channels
void Tim4ReInit(PWM*);//restart of the PWM with updated settings

#endif /* INC_LEDHANDLER_H_ */
