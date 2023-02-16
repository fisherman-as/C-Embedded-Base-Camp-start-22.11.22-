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
      uint32_t color;       // 1-2-3-4 (GREEN ORANGE RED BLUE)
      GPIO_TypeDef * port;  //LED port
      uint16_t pin;         //LED pin
      uint32_t startpoint;  //offset from startpoint of blinking
      uint32_t DutyCycle;   //the part of period when a LED is "on"
      uint32_t period;      //period
      void (*pLedHandle)(uint32_t color);//the pointer to function that handles this LED blinking
    }LED;

  void Scheme1(void);
  void Scheme2(void);
  void Scheme3(void);
  void LedHandle( uint32_t color);


#endif /* INC_LEDS_H_ */
