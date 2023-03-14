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

    uint8_t TransmitArray[4];
    // Send READ command and address


extern SPI_HandleTypeDef hspi1;

void read_data(uint32_t address, uint8_t *data, uint32_t size)
{

	    TransmitArray[0] = SST25VF016B_READ;
    TransmitArray[1] = (address >> 16) & 0xFF;
    TransmitArray[2] = (address >> 8) & 0xFF;
    TransmitArray[3] = address & 0xFF;
	//HAL_SPI_TransmitReceive(&hspi1, TransmitArray, ReceiveArray, 8, 100);

	/*
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
*/



}


uint8_t data[SST25VF016B_PAGE_SIZE * SST25VF016B_NUM_PAGES];

void read_all_pages()
{
    for (uint32_t i = 0; i < SST25VF016B_NUM_PAGES; i++) {
        uint32_t address = i * SST25VF016B_PAGE_SIZE;
        read_data(address, &data[address], SST25VF016B_PAGE_SIZE);
    }
}



