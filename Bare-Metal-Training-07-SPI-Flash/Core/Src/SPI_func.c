/*
 * SPI_func.c
 *
 *  Created on: Mar 14, 2023
 *      Author: yabanzhialek
 */
#include "SPI_func.h"


#define SST25VF016B_READ        0x03
#define SPI_TIMEOUT             1000
#define SST25VF016B_PAGE_SIZE   4096
#define SST25VF016B_NUM_PAGES   20//512
#define SPI_TIMEOUT             1000

extern SPI_HandleTypeDef hspi1;

/*----------------------------Simple instructions-----------------------------------------------*/

void EnableChip(STATE state)
{
  if (state==ON)
	  {HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);}
  else
	  {HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);}
}

void Read25(uint32_t ReadAdress, uint8_t* pvReceiveArray, uint16_t Size) //tested
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

void ByteProgram(uint32_t WriteAdress, uint8_t* pvWriteArray, uint16_t Size) //NEEDS TO BE TESTED AND CORRECTED
{
  WriteEnable();
  uint8_t TransmitArray[4]={0};
  TransmitArray[0] = 0x02;
  TransmitArray[1] = (uint8_t)((WriteAdress&0xFF0000)>>16);
  TransmitArray[2] = (uint8_t)((WriteAdress&0x00FF00)>>8);
  TransmitArray[3] = (uint8_t)((WriteAdress&0x0000FF));
  EnableChip(ON);
  HAL_SPI_Transmit(&hspi1, TransmitArray, 4, 100);
  HAL_SPI_Transmit(&hspi1, pvWriteArray, Size, 100);
  EnableChip(OFF);
  WriteDisable();
}

void Erase4(uint32_t WriteAdress)
{
  uint8_t TransmitArray[4]={0};
  TransmitArray[0] = 0x20;
  TransmitArray[1] = (uint8_t)((WriteAdress&0xFF0000)>>16);
  TransmitArray[2] = (uint8_t)((WriteAdress&0x00FF00)>>8);
  TransmitArray[3] = (uint8_t)((WriteAdress&0x0000FF));
  EnableChip(ON);
  HAL_SPI_Transmit(&hspi1, TransmitArray, 4, 100);
  /*read Status register and wait for the end of erasing*/
  TransmitArray[0] = 0x05; //read Status register
  uint8_t ReceiveArray[1]={0};
  do {HAL_SPI_TransmitReceive(&hspi1, TransmitArray, ReceiveArray, 1, 100);}
  while((ReceiveArray[0]&0x01)==1); //while BUSY==1...; wait for erase finish
  EnableChip(OFF);
}

void Erase32(uint32_t WriteAdress)
{
  uint8_t TransmitArray[4]={0};
  TransmitArray[0] = 0x52;
  TransmitArray[1] = (uint8_t)((WriteAdress&0xFF0000)>>16);
  TransmitArray[2] = (uint8_t)((WriteAdress&0x00FF00)>>8);
  TransmitArray[3] = (uint8_t)((WriteAdress&0x0000FF));
  EnableChip(ON);
  HAL_SPI_Transmit(&hspi1, TransmitArray, 4, 100);
  /*read Status register and wait for the end of erasing*/
  TransmitArray[0] = 0x05; //read Status register
  uint8_t ReceiveArray[1]={0};
  do {HAL_SPI_TransmitReceive(&hspi1, TransmitArray, ReceiveArray, 1, 100);}
  while((ReceiveArray[0]&0x01)==1); //while BUSY==1...; wait for erase finish
  EnableChip(OFF);
}

void Erase64(uint32_t WriteAdress)
{
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
  do
  {
	  ReceiveArray[0]=0;
	  ReceiveArray[1]=0;
	  HAL_SPI_TransmitReceive(&hspi1, TransmitArray, ReceiveArray, 2, 100);
  }
  while((ReceiveArray[1]&0x01)==1); //while BUSY==1...; wait for erase finish
  EnableChip(OFF);
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
  /*read Status register and wait for the end of erasing*/
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

void ReadStatusRegister(uint8_t* ReceiveArray) //tested
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
  //EnableChip(ON);
  uint8_t TransmitArray[1]={0x04};
  HAL_SPI_Transmit(&hspi1, TransmitArray, 1, 100);
  EnableChip(OFF);
}

void WriteStatusRegister(uint8_t NewStateOfStatusRegister) //tested, with 0x00
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

/*------------------------------Complicated and jointed instructions---------------------------------------------*/

void WriteEnableBP(void) //for enabling BP0-BP2
{

}




/*
void WriteBytes100(uint32_t WriteAdress, uint8_t* pvWriteArray)
{

  ByteProgram();

}
*/
/*
void ByteProgram(uint32_t WriteAdress, uint8_t* pvWriteArray, uint16_t Size) //NEEDS TO BE TESTED AND CORRECTED
{
  uint8_t TransmitArray[4]={0};
  TransmitArray[0] = 0x02;
  TransmitArray[1] = (uint8_t)((WriteAdress&0xFF0000)>>16);
  TransmitArray[2] = (uint8_t)((WriteAdress&0x00FF00)>>8);
  TransmitArray[3] = (uint8_t)((WriteAdress&0x0000FF));
  EnableChip(ON);
  HAL_SPI_Transmit(&hspi1, TransmitArray, 4, 100);
  HAL_SPI_Transmit(&hspi1, pvWriteArray, Size, 100);
  EnableChip(OFF);
}
*/









void ReadSPI_16(uint8_t* pvRxData, uint16_t Size) //the function for reading the first 80 bytes in 16 blocks of memory
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



















/*
void read_data(uint32_t address, uint8_t *data, uint32_t size)
{

	    TransmitArray[0] = SST25VF016B_READ;
    TransmitArray[1] = (address >> 16) & 0xFF;
    TransmitArray[2] = (address >> 8) & 0xFF;
    TransmitArray[3] = address & 0xFF;
	//HAL_SPI_TransmitReceive(&hspi1, TransmitArray, ReceiveArray, 8, 100);


    HAL_StatusTypeDef status;
    uint8_t cmd[4];
    // Send READ command and address
    cmd[0] = SST25VF016B_READ;
    cmd[1] = (address >> 16) & 0xFF;
    cmd[2] = (address >> 8) & 0xFF;
    cmd[3] = address & 0xFF;
    status = HAL_SPI_Transmit(&hspi1, cmd, 4, SPI_TIMEOUT);
    // Read data from chip
    status = HAL_SPI_Receive(&hspi1, data, size, SPI_TIMEOUT);

}

uint8_t data[SST25VF016B_PAGE_SIZE * SST25VF016B_NUM_PAGES];

void read_all_pages()
{
    for (uint32_t i = 0; i < SST25VF016B_NUM_PAGES; i++) {
        uint32_t address = i * SST25VF016B_PAGE_SIZE;
        read_data(address, &data[address], SST25VF016B_PAGE_SIZE);
    }
}
*/


