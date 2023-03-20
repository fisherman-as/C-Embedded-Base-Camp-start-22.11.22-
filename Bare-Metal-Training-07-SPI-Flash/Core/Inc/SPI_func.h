/*
 * SPI_func.h
 *
 *  Created on: Mar 14, 2023
 *      Author: yabanzhialek
 */

#ifndef INC_SPI_FUNC_H_
#define INC_SPI_FUNC_H_
#include "main.h"

typedef enum {OFF, ON}STATE;

void EnableChip(STATE state);								//
void Read25(uint32_t ReadAdress,
		uint8_t* pvReceiveArray, uint16_t Size);			//tested
void ByteProgram(uint32_t WriteAdress,
		uint8_t* pvWriteArray);								//tested //writes 1 byte only
void EBSY(void);
void DBSY(void);
void RDSR(void);
void WordProgramAAI_HW(uint32_t WriteAdress,
		uint8_t* pvWriteArray, uint16_t Size); 				//tested
void Erase4(uint32_t WriteAdress);							//+
void Erase32(uint32_t WriteAdress);							//+
void Erase64(uint32_t WriteAdress);							//+
void EraseChip(void);										//tested
void ReadStatusRegister(uint8_t* ReceiveArray);				//tested
void WriteEnable(void);										//tested
void WriteDisable(void);									//
void WriteStatusRegister(uint8_t NewStateOfStatusRegister);	//tested, with 0x00
void ReadSPI_20(uint16_t rows, uint16_t cols, uint8_t (*pvRxData)[]);			//tested
void WriteMyTextToFlash(const uint8_t* pvWriteArray);

#endif /* INC_SPI_FUNC_H_ */
