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

void EnableChip(STATE state);													//
void Read25(uint32_t ReadAdress, uint8_t* pvReceiveArray, uint16_t Size);		//tested
void ByteProgram(uint32_t WriteAdress, uint8_t* pvWriteArray, uint16_t Size);	//
void Erase4(uint32_t WriteAdress);												//
void Erase32(uint32_t WriteAdress);												//
void Erase64(uint32_t WriteAdress);												//
void EraseChip(void);															//
void ReadStatusRegister(uint8_t* ReceiveArray);									//tested
void WriteEnable(void);															//tested
void WriteDisable(void);														//
void WriteStatusRegister(uint8_t NewStateOfStatusRegister);						//tested, with 0x00




void ReadSPI_16(uint8_t* pvRxData, uint16_t Size);

void read_data(uint32_t address, uint8_t *data, uint32_t size);
void read_all_pages();

#endif /* INC_SPI_FUNC_H_ */
