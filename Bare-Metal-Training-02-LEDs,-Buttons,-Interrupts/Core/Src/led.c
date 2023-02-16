/*
 * led.c
 *
 *  Created on: 13 февр. 2023 г.
 *      Author: yabanzhialek
 */
#include <led.h>

extern uint32_t LED_QUANTITY;
extern LED leds[];
extern volatile uint32_t LedFlags[];
extern volatile uint32_t counter;
extern volatile uint32_t SW13Flag;
extern volatile uint32_t SW45Flag;

void Scheme1(void)
{
	for (uint32_t n=0; n<LED_QUANTITY; n++)
	      {
	        if (counter>=leds[n].startpoint)
	          {
		        if (((counter+leds[n].period-leds[n].startpoint)%(leds[n].period)==0)||  \
			         (((counter+leds[n].period-leds[n].startpoint-leds[n].DutyCycle)%(leds[n].period))==0))

		           {leds[n].pLedHandle(leds[n].color);}
		        else
		           {}
	          }
	      }
}
void Scheme2(void)
{
	for (uint32_t n=0; n<LED_QUANTITY; n++)
		      {
			        if (((counter+leds[n].period)%leds[n].period==0)||  \
				         (((counter+leds[n].period-leds[n].DutyCycle)%leds[n].period)==0))

		               {leds[n].pLedHandle(leds[n].color);}
			        else
			           {}
		          }

}
void Scheme3(void)
{
	if (counter%3==0)
	{


	    for (uint32_t n=0; n<LED_QUANTITY; n+=2)
		      {
			        if ((((counter+leds[n].period+leds[n].DutyCycle)%leds[n].period==0)||  \
				         (((counter+leds[n].period)%leds[n].period)==0)))

		               {leds[n].pLedHandle(leds[n].color);}
			        else
			           {}
		          }
	}
	else
	{
	    for (uint32_t n=1; n<LED_QUANTITY; n+=2)
		      {
			        if ((((counter+leds[n].period+leds[n].DutyCycle)%leds[n].period==0)||  \
				         (((counter+leds[n].period)%leds[n].period)==0)))

		               {leds[n].pLedHandle(leds[n].color);}
			        else
			           {}
		          }

	}

}

  void LedHandle( uint32_t color)
    {
	  for (uint32_t n=0; n<LED_QUANTITY; n++)
	    {
	      if (color==leds[n].color){LedFlags[n]=1;}
	    }
	 // HAL_GPIO_TogglePin(port, pin);
    }


