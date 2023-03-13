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
//#define round(X) X=((((X)*10)%10)>4)?((X)+1):(X)

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart3;
uint8_t  PCA9685_WriteAddr= 0x80;
uint8_t TxBuffer[8];
uint8_t UartReceiveBuffer[COMMANDLENGTH]={0};
uint32_t UartReceiveBufferIndex=0;
uint32_t ReceiveDataIsComplete=0;
uint32_t ReceiveDataHalfIsComplete=0;

uint8_t Round(float X)
{
	X=(uint8_t)(((uint32_t)((X)*10)%10)>4)?((X)+1):(X);
	return X;
}

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

void PCA9685_Restart()
{
	uint8_t RxBuffer[1]; // Buffer for reading PCA9685 register
	HAL_I2C_Master_Transmit(&hi2c1, 0x80, 0x00, 1, 100); //read MODE1
	HAL_I2C_Master_Receive(&hi2c1, 0x81, RxBuffer, 1, 100); //read MODE1. For making restart.
	PCA9685_SleepMode(OFF);
	HAL_Delay(1);
	TxBuffer[0] = 0x00; //adress MODE1
	TxBuffer[1] = 0x80; // bit (7) RESTART = 1
	HAL_I2C_Master_Transmit(&hi2c1, 0x80, (uint8_t*) &TxBuffer, 2, 100); //write 1 to RESTART bit in MODE1
}

void PCA9685_Start(void)
{
  PCA9685_LedStateWhenDisabled(OFF);
  PCA9685_SleepMode(OFF); //Normal Mode
  PCA9685_Enable(ON);
}

void PCA9685_SetLed(led_t number, uint16_t brightness) //number=0...15, brightness =0...100 (inverted);
{
  if (number>15||number<0) {number=0;}
  if (brightness>100||brightness<0) {brightness=0;}
  uint16_t RegBrightnessValue=(uint16_t)(4096*brightness/100-1);

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

void PCA9685_SetLedAlt(led_t number, uint16_t brightness) //number=0...15, brightness = 0...11 (inverted);
{
  if (number>15||number<0) {number=0;}
  if (brightness>11||brightness<0) {brightness=0;}
  uint16_t RegBrightnessValue=(4095>>(11-brightness));

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

void PCA9685_SetLedAll(uint16_t brightness) //brightness =0...100 (inverted);
{
  if (brightness>100||brightness<0) {brightness=0;}
  uint16_t RegBrightnessValue=(uint16_t)(4096*brightness/100-1);

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

void PCA9685_SetLedAllAlt(uint16_t brightness) //brightness = 0...11 (inverted);
{
  if (brightness>11||brightness<0) {brightness=0;}
  uint16_t RegBrightnessValue=(4095>>(11-brightness));

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
	PCA9685_SleepMode(ON);
	uint8_t RegValue=Round(25000000/(4096*frequency))-1;
	TxBuffer[0] = 0xFE;
	TxBuffer[1] = RegValue;
	HAL_I2C_Master_Transmit(&hi2c1, 0x80, (uint8_t*) &TxBuffer, 2, 100); //set FREQUENCY value
	PCA9685_Restart();
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
          uint32_t argument = atoi(Command[1]);
          if (argument<16)
          {
            PCA9685_SetLedAlt(argument, 0);
            HAL_UART_Transmit(&huart3, (uint8_t *)"LED is enabled\r\n", 16, 10);
          }
        }
    	else
    	{
    		PCA9685_Enable(ON);
            HAL_UART_Transmit(&huart3, (uint8_t *)"ALL LEDs are enabled\r\n", 22, 10);
    	}
    }

//DSBL xx; xx=00...15 or 16 -------------------------------------------------------------------------------
    else if (number==2 && strcmp(Command[0], "DSBL")==0)
    {
      if (strcmp(Command[1], "16")!=0)//We neednt "atoi" to convert number to number
      {
        uint32_t argument = atoi(Command[1]);
        if (argument<16)
        {
          PCA9685_SetLedAlt(argument, 11);
          HAL_UART_Transmit(&huart3, (uint8_t *)"LED is disabled\r\n", 17, 10);
        }
      }
      else
      {
    	  PCA9685_Enable(OFF);;
          HAL_UART_Transmit(&huart3, (uint8_t *)"ALL LEDs are disabled\r\n", 23, 10);
      }
    }

//FR xxxx; xxxx=0024...1526 ----------------------------------------------------------------------------
    else if (number==2 && strcmp(Command[0], "FR")==0)
      {
        uint32_t argument = (uint32_t)atoi(Command[1]);
        if (argument<=1526 && argument>=24)
        {
    	  PCA9685_SetFrequency(argument);
    	  HAL_UART_Transmit(&huart3, (uint8_t *)"Frequency is changed\r\n", 22, 10);
        }
        else
        {
    	   HAL_UART_Transmit(&huart3, (uint8_t *)"The value must be between 0024...1526\r\n", 39, 10);
        }
      }

//DTCL xx; xx=00...99, Duty Cycle will be 01...100 --------------------------------------------------
    else if (number==2 && strcmp(Command[0], "DTCL")==0)
    {
    	uint32_t argument = (uint32_t)atoi(Command[1]);
    	if (argument<=99 && argument>=0)
    	{
    		PCA9685_SetLedAll(argument+1);
    		HAL_UART_Transmit(&huart3, (uint8_t *)"The Duty Cycle is changed\r\n", 27, 10);
    	}
    	else
    	{
    		HAL_UART_Transmit(&huart3, (uint8_t *)"The value must be between 00...99\r\n", 35, 10);
    	}
    }

//SLEEP x; x=0 (SLEEP OFF) or 1 (SLEEP ON);---------------------------------------------------------------------------------------
    else if (number==2 && strcmp(Command[0], "SLEEP")==0)
    {
    	uint32_t argument = (uint32_t)atoi(Command[1]);
    	if (argument==1)
    	{
    	  PCA9685_SleepMode(ON);
    	  HAL_UART_Transmit(&huart3, (uint8_t *)"PCA9685 is in the SLEEP Mode\r\n", 30, 10);
    	}
    	else if (argument==0)
    	{
    		PCA9685_Restart();
      	    HAL_UART_Transmit(&huart3, (uint8_t *)"PCA9685 is NOT in the SLEEP Mode\r\n", 34, 10);
    	}
    	else
    	{
      	    HAL_UART_Transmit(&huart3, (uint8_t *)"The correct argument is 1 or 0 only\r\n", 37, 10);
    	}
    }
    else
    {
    	HAL_UART_Transmit(&huart3, (uint8_t *)"Commands: ENBL NN, DSBL NN, FR NNNN, DTCL NN, SLEEP N\r\n", 55, 10);
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


