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
      uint32_t SW1FLAG:1;
      uint32_t SW2FLAG:1;
      uint32_t SW3FLAG:1;
      uint32_t SW4FLAG:1;
      uint32_t SW5FLAG:1;
    }FLAGS;

void SW1Handler(TIM_HandleTypeDef timer, PWM* pTIMERSETTINGS);//this button decreases a frequency
void SW2Handler(TIM_HandleTypeDef timer, PWM* pTIMERSETTINGS);//this button selects the signal output
void SW3Handler(TIM_HandleTypeDef timer, PWM* pTIMERSETTINGS);//this button increases a frequency
void SW4Handler(TIM_HandleTypeDef timer, PWM* pTIMERSETTINGS);//this button increases the duty cycle
void SW5Handler(TIM_HandleTypeDef timer, PWM* pTIMERSETTINGS);//this button decreases the duty cycle
void Tim4ReInit(TIM_HandleTypeDef timer,PWM* this);
void ButtonsHandler(TIM_HandleTypeDef timer);

#endif /* INC_PWM_H_ */
