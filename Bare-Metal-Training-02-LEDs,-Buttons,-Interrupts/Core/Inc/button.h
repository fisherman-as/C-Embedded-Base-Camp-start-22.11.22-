/*
 * button.h
 *
 *  Created on: Feb 15, 2023
 *      Author: yabanzhialek
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include "led.h"


void SW1Handler(void);
void SW2Handler(void);
void SW3Handler(void);
void SW4Handler(void);
void SW5Handler(void);

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

void ButtonsHandler(void);

#endif /* INC_BUTTON_H_ */
