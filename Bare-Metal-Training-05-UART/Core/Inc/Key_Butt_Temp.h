/*
 * UartComm.h
 *
 *  Created on: Mar 5, 2023
 *      Author: AS
 */

#ifndef INC_UARTCOMM_H_
#define INC_UARTCOMM_H_

#include "main.h"

typedef enum {GREEN, ORANGE, RED, BLUE}COLOR;

typedef struct
	{
	  uint32_t SWT1:1;
	  //uint32_t SWT2:1;
	  uint32_t SWT3:1;
	  uint32_t SWT4:1;
	  uint32_t SWT5:1;
	  uint32_t ButtonsPollIsDenied:1;
	  uint32_t JitterIsBlocking:1;
	}BUTTONFLAG;

void PollUart(void);
void ButtonsAntiJitter(void);
void PollButtons(void);
void HandleExtTempChannel(void);

#endif /* INC_UARTCOMM_H_ */
