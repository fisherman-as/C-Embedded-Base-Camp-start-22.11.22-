/*
 * LEDhandler.h
 *
 *  Created on: Feb 27, 2023
 *      Author: AS
 */

#ifndef INC_LEDHANDLER_H_
#define INC_LEDHANDLER_H_
#include "main.h"

typedef enum {GREEN, ORANGE, RED, BLUE}COLOR;

typedef struct
    {
	  uint16_t Frequency;
      uint16_t DutyCycle[4]; //the duty cycle of all the channels. 0=GREEN, 1=ORANGE, 2=RED, 3=BLUE
    }PWM;
typedef struct
{
	uint8_t VoltageFlag;
	uint8_t IntTempFlag;
	uint8_t ExtTempFlag;
}EMERGENCY_FLAG;

void HandleLedRedBlinkAlert(EMERGENCY_FLAG*);
void StopChannels(TIM_HandleTypeDef*); //stops all 4 PWM channels
void Tim4ReInit(TIM_HandleTypeDef*, PWM*);//restart of the PWM with updated settings


/*-------------------User defined API-------------------------*/
extern void LedHandle(COLOR, uint32_t, PWM*);
/*----------------------------------------------------------- */

#endif /* INC_LEDHANDLER_H_ */
