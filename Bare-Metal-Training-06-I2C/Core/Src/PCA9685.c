/*
 * PCA9685.c
 *
 *  Created on: Mar 11, 2023
 *      Author: AS
 */
#include "main.h"
#include "PCA9685.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define COMMANDLENGTH 10
#define CLKFREQ 50000000

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart3;
uint8_t  PCA9685_WriteAddr= 0x80;
uint8_t TxBuffer[8];
uint8_t UartReceiveBuffer[COMMANDLENGTH]={0};
uint32_t UartReceiveBufferIndex=0;
uint32_t ReceiveDataIsComplete=0;
uint32_t ReceiveDataHalfIsComplete=0;

void ClearUartRxBuffer(void)
{
	for (uint32_t i=0; i<COMMANDLENGTH; i++)
		{UartReceiveBuffer[i]=0;}
}

void PCA9685_Enable(STATE state)
{
  if (state==ON)
    {HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);}
  else if (state==OFF)
    {HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);}
}

void PCA9685_LedStateWhenDisabled(STATE state)
{
  TxBuffer[0] = 0x01;  // register MODE2
  if (state==ON)
    {TxBuffer[1] = 0x04;}  // OUTDRV=1 (push/pull); OUTNE=01 (LEDn=1 (turn on) when PCA9685 is Disabled)
  else if (state==OFF)
    {TxBuffer[1] = 0x05;}  // OUTDRV=1 (push/pull); OUTNE=01 (LEDn=1 (turn off) when PCA9685 is Disabled)
  HAL_I2C_Master_Transmit(&hi2c1, PCA9685_WriteAddr, (uint8_t*) &TxBuffer, 2, 100);
}

void PCA9685_SleepMode(STATE state)
{
  TxBuffer[0] = 0x00;  // register MODE1
  if (state==OFF)
    {TxBuffer[1] = 0x01;}  // SLEEP=0
  else if (state==ON)
	{TxBuffer[1] = 0x11;}  // SLEEP=1
  HAL_I2C_Master_Transmit(&hi2c1, PCA9685_WriteAddr, (uint8_t*) &TxBuffer, 2, 100);
}

void PCA9685_Start(void)
{
  PCA9685_LedStateWhenDisabled(OFF);
  PCA9685_SleepMode(OFF); //Normal Mode
  PCA9685_Enable(ON);
}

void PCA9685_SetLed(led_t number, uint16_t brightness) //number=0...15, brightness =0...100;
{
  if (number>15||number<0) {number=0;}
  if (brightness>100||brightness<0) {brightness=0;}
  uint16_t RegBrightnessValue=(uint16_t)(4096-(uint16_t)(4096*brightness/100));

  TxBuffer[0] = 0x07+4*number;  // LEDn_ON_H
  TxBuffer[1] = 0x00;
  HAL_I2C_Master_Transmit(&hi2c1, 0x80, (uint8_t*) &TxBuffer, 2, 100);

  TxBuffer[0] = 0x06+4*number;  // LEDn_ON_L
  TxBuffer[1] = 0x00;
  HAL_I2C_Master_Transmit(&hi2c1, 0x80, (uint8_t*) &TxBuffer, 2, 100);

  TxBuffer[0] = 0x09+4*number;  // LEDn_OFF_H
  TxBuffer[1] = RegBrightnessValue>>8;
  HAL_I2C_Master_Transmit(&hi2c1, 0x80, (uint8_t*) &TxBuffer, 2, 100);

  TxBuffer[0] = 0x08+4*number;  // LEDn_OFF_L
  TxBuffer[1] = (uint8_t)RegBrightnessValue;
  HAL_I2C_Master_Transmit(&hi2c1, 0x80, (uint8_t*) &TxBuffer, 2, 100);
}

void PCA9685_SetLedAlt(led_t number, uint16_t brightness) //number=0...15, brightness = 0...11;
{
  if (number>15||number<0) {number=0;}
  if (brightness>11||brightness<0) {brightness=0;}
  uint16_t RegBrightnessValue=(4096-(4096>>(11-brightness)));

  TxBuffer[0] = 0x07+4*number;  // LEDn_ON_H
  TxBuffer[1] = 0x00;
  HAL_I2C_Master_Transmit(&hi2c1, 0x80, (uint8_t*) &TxBuffer, 2, 100);

  TxBuffer[0] = 0x06+4*number;  // LEDn_ON_L
  TxBuffer[1] = 0x00;
  HAL_I2C_Master_Transmit(&hi2c1, 0x80, (uint8_t*) &TxBuffer, 2, 100);

  TxBuffer[0] = 0x09+4*number;  // LEDn_OFF_H
  TxBuffer[1] = RegBrightnessValue>>8;
  HAL_I2C_Master_Transmit(&hi2c1, 0x80, (uint8_t*) &TxBuffer, 2, 100);

  TxBuffer[0] = 0x08+4*number;  // LEDn_OFF_L
  TxBuffer[1] = (uint8_t)RegBrightnessValue;
  HAL_I2C_Master_Transmit(&hi2c1, 0x80, (uint8_t*) &TxBuffer, 2, 100);
}

void PCA9685_SetLedAll(uint16_t brightness) //brightness =0...100;
{
  if (brightness>100||brightness<0) {brightness=0;}
  uint16_t RegBrightnessValue=(uint16_t)(4096-(uint16_t)(4096*brightness/100));

  TxBuffer[0] = 0xFB;  // LEDn_ON_H
  TxBuffer[1] = 0x00;
  HAL_I2C_Master_Transmit(&hi2c1, 0x80, (uint8_t*) &TxBuffer, 2, 100);

  TxBuffer[0] = 0xFA;  // LEDn_ON_L
  TxBuffer[1] = 0x00;
  HAL_I2C_Master_Transmit(&hi2c1, 0x80, (uint8_t*) &TxBuffer, 2, 100);

  TxBuffer[0] = 0xFD;  // LEDn_OFF_H
  TxBuffer[1] = RegBrightnessValue>>8;
  HAL_I2C_Master_Transmit(&hi2c1, 0x80, (uint8_t*) &TxBuffer, 2, 100);

  TxBuffer[0] = 0xFC;  // LEDn_OFF_L
  TxBuffer[1] = (uint8_t)RegBrightnessValue;
  HAL_I2C_Master_Transmit(&hi2c1, 0x80, (uint8_t*) &TxBuffer, 2, 100);
}

void PCA9685_SetLedAllAlt(uint16_t brightness) //brightness = 0...11;
{
  if (brightness>11||brightness<0) {brightness=0;}
  uint16_t RegBrightnessValue=(4096-(4096>>(11-brightness)));

  TxBuffer[0] = 0xFB;  // LEDn_ON_H
  TxBuffer[1] = 0x00;
  HAL_I2C_Master_Transmit(&hi2c1, 0x80, (uint8_t*) &TxBuffer, 2, 100);

  TxBuffer[0] = 0xFA;  // LEDn_ON_L
  TxBuffer[1] = 0x00;
  HAL_I2C_Master_Transmit(&hi2c1, 0x80, (uint8_t*) &TxBuffer, 2, 100);

  TxBuffer[0] = 0xFD;  // LEDn_OFF_H
  TxBuffer[1] = RegBrightnessValue>>8;
  HAL_I2C_Master_Transmit(&hi2c1, 0x80, (uint8_t*) &TxBuffer, 2, 100);

  TxBuffer[0] = 0xFC;  // LEDn_OFF_L
  TxBuffer[1] = (uint8_t)RegBrightnessValue;
  HAL_I2C_Master_Transmit(&hi2c1, 0x80, (uint8_t*) &TxBuffer, 2, 100);
}

void PCA9685_SetFrequency(uint32_t frequency) //frequency = 24...1526
{
	uint32_t RegValue=(uint32_t)(CLKFREQ/(4096*frequency))-1;

	TxBuffer[0] = 0xFE;
	TxBuffer[1] = (uint8_t)RegValue;
	HAL_I2C_Master_Transmit(&hi2c1, 0x80, (uint8_t*) &TxBuffer, 2, 100);
}

void PollUart(void)
{
	HAL_UART_Receive_DMA(&huart3, (uint8_t *)UartReceiveBuffer, COMMANDLENGTH-1);
}

void HandleUartData(void)
{
if (ReceiveDataIsComplete==1)
  {
    UartReceiveBuffer[strcspn((char*)UartReceiveBuffer, "\r")] = '\0'; // Here we delete the symbol '\r'
    UartReceiveBuffer[strcspn((char*)UartReceiveBuffer, "\n")] = '\0'; // Here we delete the symbol '\n'
/*---------------------------------Here we break the buffer into two different words-------------------------*/
	char* Command[2];
	uint32_t number = 0;
	char* pvCommand = strtok((char*)UartReceiveBuffer, " ");
	while (pvCommand!=NULL&&number<2)
	{
	  Command[number++] = pvCommand;
	  pvCommand = strtok(NULL, " ");
	}
/*---------Now we have the command in Command[0] and its argument in Command[1]------------------------------*/

/*---------------------Here is the console command handler --------------------------------------------------*/
//ENBL xx; xx=00...15 or 16 ---------------------------------------------------------------------------------
    if (number==2 && strcmp(Command[0], "ENBL")==0)
    {
    	if (strcmp(Command[1], "16")!=0) //We neednt "atoi" to convert number to number
        {
          uint32_t value = atoi(Command[1]);
          if (value<16)
          {
            PCA9685_SetLedAlt(value, 11);
            HAL_UART_Transmit(&huart3, (uint8_t *)"LED is enabled\r\n", 16, 10);
          }
        }
    	else
    	{
    		PCA9685_SetLedAllAlt(11);
            HAL_UART_Transmit(&huart3, (uint8_t *)"ALL LEDs are enabled\r\n", 22, 10);
    	}
    }

//DSBL xx; xx=00...15 or 16 -------------------------------------------------------------------------------
    else if (number==2 && strcmp(Command[0], "DSBL")==0)
    {
      if (strcmp(Command[1], "16")!=0)//We neednt "atoi" to convert number to number
      {
        uint32_t value = atoi(Command[1]);
        if (value<16)
        {
          PCA9685_SetLedAlt(value, 0);
          HAL_UART_Transmit(&huart3, (uint8_t *)"LED is disabled\r\n", 17, 10);
        }
      }
      else
      {
    	  PCA9685_SetLedAllAlt(0);
          HAL_UART_Transmit(&huart3, (uint8_t *)"ALL LEDs are disabled\r\n", 23, 10);
      }
    }

//FREQ xx; xx=24...1526 ----------------------------------------------------------------------------
    else if (number==2 && strcmp(Command[0], "FREQ")==0)
      {
        uint32_t value = atoi(Command[1]);
        if (value<=1526 || value>=24)
        {
    	  PCA9685_SetFrequency(value);
    	  HAL_UART_Transmit(&huart3, (uint8_t *)"Frequency is changed\r\n", 22, 10);
        }
        else
        {
    	   HAL_UART_Transmit(&huart3, (uint8_t *)"The value must be between 24...1526\r\n", 37, 10);
        }
      }

//DTCL xx; xx=00...11 ----------------------------------------------------------------------------
    else if (number==2 && strcmp(Command[0], "FREQ")==0)
    {
    	uint32_t value = atoi(Command[1]);
    	if (value<=99 || value>=0)
    	{
    		PCA9685_SetLedAll(value);
    		HAL_UART_Transmit(&huart3, (uint8_t *)"Frequency is changed\r\n", 22, 10);
    	}
    	else
    	{
    		HAL_UART_Transmit(&huart3, (uint8_t *)"The value must be between 00...99\r\n", 35, 10);
    	}
    }

  ClearUartRxBuffer();
  ReceiveDataIsComplete=0;
  }
  PollUart();
  HAL_Delay(100); //we need this delay for correct working of this function
}

void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
{
	/*
  if (huart == &huart3)
  {
	  ReceiveDataHalfIsComplete=1;
  }
  */
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	ReceiveDataIsComplete=1;


	/*  //this code is for interrupts only
  if (huart == &huart3)
  {
    if (ReceiveDataIsComplete==0)
    {
      UartReceiveBuffer[UartReceiveBufferIndex] = huart->Instance->DR;
      UartReceiveBufferIndex++;
      if (UartReceiveBufferIndex>=COMMANDLENGTH)
        {
          UartReceiveBufferIndex = 0;
        }
      if (UartReceiveBuffer[UartReceiveBufferIndex-1]=='\n' || UartReceiveBuffer[UartReceiveBufferIndex-1]=='\r')
        {
        	ReceiveDataIsComplete=1;
        	UartReceiveBufferIndex = 0;
        }
      HAL_UART_Receive_IT(&huart3, &UartReceiveBuffer[UartReceiveBufferIndex], 1);
    }
  }
  */

}


