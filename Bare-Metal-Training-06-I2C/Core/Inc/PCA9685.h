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

uint8_t Round(float X);
void ClearUartRxBuffer(void);

//Enable/Disable LEDs:
void PCA9685_Enable(STATE state);                  //ON = PCA9685 is Enabled; OFF = PCA9685 is Disabled

void PCA9685_LedStateWhenDisabled(STATE state);    //The LEDs will be turned ON or OFF when PCA9685 is Disabled
void PCA9685_SleepMode(STATE state);               //PCA9685 is in the SLEEP Mode when state=ON
void PCA9685_Restart();							   //Restarts PCA9685 after SLEEP mode
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
void PCA9685_SetFrequency(uint32_t frequency);

void PollUart(void);
void HandleUartData(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart);

/*-----------------------------------------The description of User API------------------------------------------------*/
/*
 *

ENBL NN  		//NN=00...15 (turn ON single LED) OR 16 (Enables all LEDs, but keeps their state (On or OFF when enabled)!!)
DSBL NN  		//NN=00...15 (turn OFF single LED) OR 16 (Disables all LEDs, but keeps their state (On or OFF when enabled)!!)
FR NNNN  		//NNNN=0024...1526, sets Frequency
DTCL NN  		//NN=00...99, sets the Duty Cycle, the real value will be 1...100, in percents; brightness inverted
SLEEP N			//N=0 (SLEEP Mode OFF) or 1 (SLEEP Mode ON)


*/
/*--------------------------------------------------The end-----------------------------------------------------------*/

#endif /* INC_PCA9685_H_ */
