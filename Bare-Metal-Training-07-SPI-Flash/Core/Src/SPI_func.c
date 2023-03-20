/*
 * SPI_func.c
 *
 *  Created on: Mar 14, 2023
 *      Author: yabanzhialek
 */
#include "SPI_func.h"
#include <string.h>

extern SPI_HandleTypeDef hspi1;

/*----------------------------Simple instructions-----------------------------------------------*/

void EnableChip(STATE state)
{
  if (state==ON)
	  {HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);}
  else
	  {HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);}
}

void Read25(uint32_t ReadAdress, uint8_t* pvReceiveArray, uint16_t Size)
{
  uint8_t TransmitArray[4]={0};
  TransmitArray[0] = 0x03;
  TransmitArray[1] = (uint8_t)((ReadAdress&0xFF0000)>>16);
  TransmitArray[2] = (uint8_t)((ReadAdress&0x00FF00)>>8);
  TransmitArray[3] = (uint8_t)((ReadAdress&0x0000FF));

  EnableChip(ON);
  HAL_SPI_TransmitReceive(&hspi1, TransmitArray, pvReceiveArray, Size+4, 100);
  EnableChip(OFF);
}

void ByteProgram(uint32_t WriteAdress, uint8_t* pvWriteArray)
{
  EnableChip(OFF);
	  /*
	   * WE NEED TO ALLOW WRITING USING THE NEXT COMMENTED INSTRUCTION HERE, OR BEFORE THIS FUNCTION
	   * 1. UNCOMMENT THE NEXT INSTRUCTION, OR...
	   * 2. PUT NE NEXT COMMENTED INSTRUCTION BEFORE THIS FUNCTION EVERYWHERE YOU ARE USING IT
	  */
  //WriteStatusRegister(0x00); //reset write protection bits BP0-3, and BPL
  WriteEnable();
  uint8_t TransmitArray[4]={0};
  TransmitArray[0] = 0x02;
  TransmitArray[1] = (uint8_t)((WriteAdress&0xFF0000)>>16);
  TransmitArray[2] = (uint8_t)((WriteAdress&0x00FF00)>>8);
  TransmitArray[3] = (uint8_t)((WriteAdress&0x0000FF));
  EnableChip(ON);
  HAL_SPI_Transmit(&hspi1, TransmitArray, 4, 100);
  HAL_SPI_Transmit(&hspi1, pvWriteArray, 1, 100);
  EnableChip(OFF);
  WriteDisable();
}
void EBSY(void)
{
  uint8_t TransmitArray[1]={0};
  TransmitArray[0] = 0x70; //EBSY
  EnableChip(ON);
  HAL_SPI_Transmit(&hspi1, TransmitArray, 1, 100);
  EnableChip(OFF);
}

void DBSY(void)
{
  uint8_t TransmitArray[1]={0};
  TransmitArray[0] = 0x80; //DBSY
  EnableChip(ON);
  HAL_SPI_Transmit(&hspi1, TransmitArray, 1, 100);
  EnableChip(OFF);
}

void RDSR(void)  /*read Status register and wait for the end of writing*/
{
  uint8_t TransmitArray[1]={0};
  TransmitArray[0] = 0x05; //read Status register
  uint8_t ReceiveArray[2]={0};
  EnableChip(OFF);
  EnableChip(ON);
  do
  {
	  ReceiveArray[0]=0;
	  ReceiveArray[1]=0;
	  HAL_SPI_TransmitReceive(&hspi1, TransmitArray, ReceiveArray, 2, 100);
  }
  while((ReceiveArray[1]&0x01)==1); //while BUSY==1...; wait for erase finish
  EnableChip(OFF);
}

void WordProgramAAI_HW(uint32_t WriteAdress, uint8_t* pvWriteArray, uint16_t Size)
{
  EnableChip(OFF);
  	  /*
  	   * WE NEED TO ALLOW WRITING USING THE NEXT COMMENTED INSTRUCTION HERE, OR BEFORE THIS FUNCTION
  	   * 1. UNCOMMENT THE NEXT INSTRUCTION, OR...
  	   * 2. PUT NE NEXT COMMENTED INSTRUCTION BEFORE THIS FUNCTION EVERYWHERE YOU ARE USING IT
  	  */
  //WriteStatusRegister(0x00); //reset write protection bits BP0-3, and BPL
  uint8_t TransmitArray[6]={0};
  EBSY();
  WriteEnable();
  /*--- AD + ADRESS + DATA ---*/
  TransmitArray[0] = 0xAD;
  TransmitArray[1] = (uint8_t)((WriteAdress&0xFF0000)>>16);
  TransmitArray[2] = (uint8_t)((WriteAdress&0x00FF00)>>8);
  TransmitArray[3] = (uint8_t)((WriteAdress&0x0000FF));
  TransmitArray[4] = pvWriteArray[0];
  TransmitArray[5] = pvWriteArray[1];
  EnableChip(ON);
  HAL_SPI_Transmit(&hspi1, TransmitArray, 6, 100);
  EnableChip(OFF);
  uint32_t i=2;
  while (i<Size)
  {
	  TransmitArray[1] = pvWriteArray[i];
	  i++;
	  if (i<Size) {TransmitArray[2] = pvWriteArray[i];}
	  else        {TransmitArray[2] = 0xFF;}
	  i++;
	  EnableChip(ON);
	  HAL_SPI_Transmit(&hspi1, TransmitArray, 3, 100);
	  EnableChip(OFF);
  }
  WriteDisable();
  DBSY();
  RDSR();
}

void Erase4(uint32_t WriteAdress)
{
  EnableChip(OFF);
  WriteStatusRegister(0x00); //reset write protection bits BP0-3, and BPL
  WriteEnable();
  uint8_t TransmitArray[4]={0};
  TransmitArray[0] = 0x20;
  TransmitArray[1] = (uint8_t)((WriteAdress&0xFF0000)>>16);
  TransmitArray[2] = (uint8_t)((WriteAdress&0x00FF00)>>8);
  TransmitArray[3] = (uint8_t)((WriteAdress&0x0000FF));
  EnableChip(ON);
  HAL_SPI_Transmit(&hspi1, TransmitArray, 4, 100);
  /*read Status register and wait for the end of erasing*/
  TransmitArray[0] = 0x05; //read Status register
  uint8_t ReceiveArray[2]={0};
  EnableChip(ON);
  do
  {
	  ReceiveArray[0]=0;
	  ReceiveArray[1]=0;
	  HAL_SPI_TransmitReceive(&hspi1, TransmitArray, ReceiveArray, 2, 100);
  }
  while((ReceiveArray[1]&0x01)==1); //while BUSY==1...; wait for erase finish
  EnableChip(OFF);
  WriteDisable();
}

void Erase32(uint32_t WriteAdress)
{
  EnableChip(OFF);
  WriteStatusRegister(0x00); //reset write protection bits BP0-3, and BPL
  WriteEnable();
  uint8_t TransmitArray[4]={0};
  TransmitArray[0] = 0x52;
  TransmitArray[1] = (uint8_t)((WriteAdress&0xFF0000)>>16);
  TransmitArray[2] = (uint8_t)((WriteAdress&0x00FF00)>>8);
  TransmitArray[3] = (uint8_t)((WriteAdress&0x0000FF));
  EnableChip(ON);
  HAL_SPI_Transmit(&hspi1, TransmitArray, 4, 100);
  /*read Status register and wait for the end of erasing*/
  TransmitArray[0] = 0x05; //read Status register
  uint8_t ReceiveArray[2]={0};
  EnableChip(ON);
  do
  {
	  ReceiveArray[0]=0;
	  ReceiveArray[1]=0;
	  HAL_SPI_TransmitReceive(&hspi1, TransmitArray, ReceiveArray, 2, 100);
  }
  while((ReceiveArray[1]&0x01)==1); //while BUSY==1...; wait for erase finish
  EnableChip(OFF);
  WriteDisable();
}

void Erase64(uint32_t WriteAdress)
{
  EnableChip(OFF);
  WriteStatusRegister(0x00); //reset write protection bits BP0-3, and BPL
  WriteEnable();
  uint8_t TransmitArray[4]={0};
  TransmitArray[0] = 0xD8;
  TransmitArray[1] = (uint8_t)((WriteAdress&0xFF0000)>>16);
  TransmitArray[2] = (uint8_t)((WriteAdress&0x00FF00)>>8);
  TransmitArray[3] = (uint8_t)((WriteAdress&0x0000FF));
  EnableChip(ON);
  HAL_SPI_Transmit(&hspi1, TransmitArray, 4, 100);
  EnableChip(OFF);
  EnableChip(ON);
  /*read Status register and wait for the end of erasing*/
  TransmitArray[0] = 0x05; //read Status register
  uint8_t ReceiveArray[2]={0};
  EnableChip(ON);
  do
  {
	  ReceiveArray[0]=0;
	  ReceiveArray[1]=0;
	  HAL_SPI_TransmitReceive(&hspi1, TransmitArray, ReceiveArray, 2, 100);
  }
  while((ReceiveArray[1]&0x01)==1); //while BUSY==1...; wait for erase finish
  EnableChip(OFF);
  WriteDisable();
}

void EraseChip(void)
{
  EnableChip(OFF);
  WriteStatusRegister(0x00); //reset write protection bits BP0-3, and BPL
  WriteEnable();
  uint8_t TransmitArray[2]={0};
  TransmitArray[0]=0x60;
  TransmitArray[1]=0x00;
  EnableChip(ON);
  HAL_SPI_Transmit(&hspi1, TransmitArray, 1, 1000);
  EnableChip(OFF);
  /*read Status register and wait for the end of erasing*/
  TransmitArray[0] = 0x05; //read Status register
  uint8_t ReceiveArray[2]={0};
  EnableChip(ON);
  do
  {
	  ReceiveArray[0]=0;
	  ReceiveArray[1]=0;
	  HAL_SPI_TransmitReceive(&hspi1, TransmitArray, ReceiveArray, 2, 100);
  }
  while((ReceiveArray[1]&0x01)==1); //while BUSY==1...; wait for erase finish
  EnableChip(OFF);
  WriteDisable();
}

void ReadStatusRegister(uint8_t* ReceiveArray)
{
  EnableChip(ON);
  uint8_t TransmitArray[2]={0};
  TransmitArray[0]=0x05;
  TransmitArray[1]=0;
  HAL_SPI_TransmitReceive(&hspi1, TransmitArray, ReceiveArray, 2, 100);
  EnableChip(OFF);
}

void WriteEnable(void) //tested
{
  EnableChip(ON);
  uint8_t TransmitArray[1]={0x06};
  HAL_SPI_Transmit(&hspi1, TransmitArray, 1, 1000);
  EnableChip(OFF);
}

void WriteDisable(void)
{
  EnableChip(ON);
  uint8_t TransmitArray[1]={0x04};
  HAL_SPI_Transmit(&hspi1, TransmitArray, 1, 100);
  EnableChip(OFF);
}

void WriteStatusRegister(uint8_t NewStateOfStatusRegister)
{
  EnableChip(ON);
  uint8_t TransmitArray[2]={0};
  TransmitArray[0]=0x50;
  HAL_SPI_Transmit(&hspi1, TransmitArray, 1, 100); //enable write status register
  EnableChip(OFF);
  uint32_t i=8;
  while (i-->0) {} //delay
  EnableChip(ON);
  TransmitArray[0]=0x01;
  TransmitArray[1]=NewStateOfStatusRegister;
  HAL_SPI_Transmit(&hspi1, TransmitArray, 2, 100); //write a new state to the status register
  EnableChip(OFF);
}

/*------------------------------The end of the simple instructions---------------------------------------------*/

/*------------------------------Functions for my homework---------------------------------------------*/



void ReadSPI_20(uint8_t* pvRxData, uint16_t Size) //the function for reading the first <Size> bytes in 20 blocks of memory
{
  uint8_t TransmitArray[80]={0};
  for (uint32_t i=0; i<20;i++)
  {
	  TransmitArray[0] = 0x03;
	  TransmitArray[1] = (uint8_t)(i>>4);
	  TransmitArray[2] = (uint8_t)(i<<4);
	  TransmitArray[3] = 0x00;

	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
	  HAL_SPI_TransmitReceive(&hspi1, TransmitArray, pvRxData, Size, 100);
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
  }
}

void WriteMyTextToFlash(uint8_t* pvWriteArray)
{
	/*-------Here we break pvWriteArray into 20 different strings and write each string into the flash--------------*/
	uint8_t* String[20];
	uint32_t number = 0;
	uint8_t* pvString = (uint8_t*)strtok((char*)pvWriteArray, "\r"); //cut the string (up to the symbol '\r' without itself)
	while (pvString!=NULL&&number<20)
	{
	  String[number] = pvString;
	  pvString = (uint8_t*)strtok(NULL, "\r"); //cut the next string (up to the symbol '\r' without itself)
	  /*---Write String into the flash---*/
	  uint32_t WriteAdress=0;
	  WriteAdress|=number<<12; //address of the page to write (0x0XX000, XX = 00h-13h)
	  WordProgramAAI_HW(WriteAdress, String[number], strlen(String[number])); //write a string into the flash
	  number++;
	}
}

