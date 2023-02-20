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
      //the next is the pointer to function that configures PWM channel
      void (*pPWMHandle)(uint32_t Channel, uint32_t Frequency,uint32_t DutyCycle);
    }PWM;

void DefaultChannelCreate(PWM*);
void TimPWMStop(TIM_HandleTypeDef timer);
void SW1Handler(PWM* pTIMERSETTINGS);//this button decreases a frequency
void SW2Handler(PWM* pTIMERSETTINGS);//this button selects the signal output
void SW3Handler(PWM* pTIMERSETTINGS);//this button increases a frequency
void SW4Handler(PWM* pTIMERSETTINGS);//this button increases the duty cycle
void SW5Handler(PWM* pTIMERSETTINGS);//this button decreases the duty cycle
void Tim4ReInit(TIM_HandleTypeDef timer,PWM* this);

#endif /* INC_PWM_H_ */
