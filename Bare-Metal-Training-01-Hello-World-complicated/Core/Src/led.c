/*
 * led.c
 *
 *  Created on: 13 февр. 2023 г.
 *      Author: yabanzhialek
 */
#include <led.h>

  void LedHandle(GPIO_TypeDef * port, uint16_t pin)
    {
	  HAL_GPIO_TogglePin(port, pin);
    }
