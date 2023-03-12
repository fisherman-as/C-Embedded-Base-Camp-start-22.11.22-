/*
 * PCA9685.h
 *
 *  Created on: Mar 11, 2023
 *      Author: AS
 */

#ifndef INC_PCA9685_H_
#define INC_PCA9685_H_

typedef enum {OFF, ON}STATE;
typedef enum{LED0, LED1, LED2, LED3, LED4, LED5, LED6, LED7,\
	         LED8, LED9, LED10, LED11, LED12, LED13, LED14, LED15} led_t;

void ClearUartRxBuffer(void);

//Enable/Disable LEDs:
void PCA9685_Enable(STATE state);                  //ON = PCA9685 is Enabled; OFF = PCA9685 is Disabled

void PCA9685_LedStateWhenDisabled(STATE state);    //The LEDs will be turned ON or OFF when PCA9685 is Disabled
void PCA9685_SleepMode(STATE state);               //PCA9685 is in the SLEEP Mode when state=ON
void PCA9685_Start(void);                          //

//Set Duty Cycle for one LED (0...100 (brightness)):
void PCA9685_SetLed(led_t number, uint16_t brightness);    //number=0...15, brightness =0...100;

//Set Duty Cycle for one LED (0...11 (brightness)):
void PCA9685_SetLedAlt(led_t number, uint16_t brightness); //number=0...15, brightness = 0...11 (doubled with each grade);
                                                   //the human eye can certainly recognize brightness change if it was doubled

//Set Duty Cycle for all LEDs (0...100 (brightness)):
void PCA9685_SetLedAll(uint16_t brightness); //number=0...15, brightness =0...100;

//Set Duty Cycle for all LEDs (0...11 (brightness)):
void PCA9685_SetLedAllAlt(uint16_t brightness); //number=0...15, brightness = 0...11;

void PollUart(void);
void HandleUartData(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart);

/*-----------------------------------------The description of User API------------------------------------------------*/
/*
 *
HELP
ENBL ALL
DSBL ALL
ENBL NN
DSBL NN
FREQ NN
DTCL NN



*/
/*--------------------------------------------------The end-----------------------------------------------------------*/

#endif /* INC_PCA9685_H_ */
