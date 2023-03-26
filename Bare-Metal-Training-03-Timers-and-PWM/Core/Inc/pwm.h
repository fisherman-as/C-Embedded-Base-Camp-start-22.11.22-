/*
 * pwm.h
 *
 *  Created on: 18 лют. 2023 р.
 *      Author: AS
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

#include "main.h"
#include "stm32f4xx_hal_tim.h"

typedef struct
    {
	  uint32_t Channel;     //channel number
	  uint32_t Frequency;
      uint32_t DutyCycle;
    }PWM;
typedef struct
	{
	  uint32_t SW1:10;
	  uint32_t SW2:10;
	  uint32_t SW3:10;
	  uint32_t SW4:10;
	  uint32_t SW5:10;
	}BUTTONCOUNTER;
	typedef enum
	{None=0,SW1,SW2,SW3,SW4,SW5}BUTTON;

void DefaultPWMSetup( TIM_HandleTypeDef, PWM*);
void StopChannels(TIM_HandleTypeDef); //stops all 4 PWM channels
void HandlePWM(BUTTON, BUTTONCOUNTER*, TIM_HandleTypeDef, PWM*);
void SW1Handler(TIM_HandleTypeDef, PWM*);//this button decreases a frequency
void SW2Handler(TIM_HandleTypeDef, PWM*);//this button selects the signal output
void SW3Handler(TIM_HandleTypeDef, PWM*);//this button increases a frequency
void SW4Handler(TIM_HandleTypeDef, PWM*);//this button increases the duty cycle
void SW5Handler(TIM_HandleTypeDef, PWM*);//this button decreases the duty cycle
void Tim4ReInit(TIM_HandleTypeDef, PWM*);//restart of the PWM with updated settings
void ButtonsHandler(TIM_HandleTypeDef);  //the main function, it monitors...
                                         //...PWM settings structure and restarts PWM

#endif /* INC_PWM_H_ */
