/*
 * SPI_func.h
 *
 *  Created on: Mar 14, 2023
 *      Author: yabanzhialek
 */

#ifndef INC_SPI_FUNC_H_
#define INC_SPI_FUNC_H_
#include "main.h"

void read_data(uint32_t address, uint8_t *data, uint32_t size);
void read_all_pages();

#endif /* INC_SPI_FUNC_H_ */
