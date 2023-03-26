/*
 * Leds.h
 *
 *  Created on: Feb 13, 2023
 *      Author: yabanzhialek
 */

#ifndef _LED_H_
#define _LED_H_

  #include "main.h"

  typedef struct
    {
      const char* color;    //isn't used
      GPIO_TypeDef * port;  //LED port
      uint16_t pin;         //LED pin
      uint32_t startpoint;  //offset from startpoint of blinking
      uint32_t DutyCycle;   //the part of period when a LED is "on"
      uint32_t period;      //period
      void (*pLedHandle)(GPIO_TypeDef * port, uint16_t pin);//the pointer to function that handles this LED blinking
    }LED;

  void LedHandle(GPIO_TypeDef *, uint16_t);

#endif /* INC_LEDS_H_ */
