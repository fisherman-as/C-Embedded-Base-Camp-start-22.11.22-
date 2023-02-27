/*
 * LEDhandler.h
 *
 *  Created on: Feb 27, 2023
 *      Author: AS
 */

#ifndef INC_LEDHANDLER_H_
#define INC_LEDHANDLER_H_
#include "main.h"


typedef struct
    {
	  uint16_t Frequency;
      uint16_t DutyCycle[4]; //the duty cycle of all the channels
    }PWM;

void StopChannels(TIM_HandleTypeDef); //stops all 4 PWM channels
void Tim4ReInit(TIM_HandleTypeDef, PWM*);//restart of the PWM with updated settings


/*-------------------User defined API-------------------------*/
extern void LedHandle(void);
/*----------------------------------------------------------- */

#endif /* INC_LEDHANDLER_H_ */
