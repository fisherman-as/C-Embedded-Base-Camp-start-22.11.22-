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

void StopChannels(TIM_HandleTypeDef); //stops all 4 PWM channels
void SW1Handler(TIM_HandleTypeDef, PWM*);//this button decreases a frequency
void SW2Handler(TIM_HandleTypeDef, PWM*);//this button selects the signal output
void SW3Handler(TIM_HandleTypeDef, PWM*);//this button increases a frequency
void SW4Handler(TIM_HandleTypeDef, PWM*);//this button increases the duty cycle
void SW5Handler(TIM_HandleTypeDef, PWM*);//this button decreases the duty cycle
void Tim4ReInit(TIM_HandleTypeDef, PWM*);//restart of the PWM with updated settings
void ButtonsHandler(TIM_HandleTypeDef);  //the main function, it monitors...
                                         //...PWM settings struct and restarts PWM

#endif /* INC_PWM_H_ */
