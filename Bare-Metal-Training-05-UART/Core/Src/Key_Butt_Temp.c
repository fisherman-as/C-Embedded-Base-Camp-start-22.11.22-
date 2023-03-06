/*
 * UartComm.c
 *
 *  Created on: Mar 5, 2023
 *      Author: AS
 */
#include <Key_Butt_Temp.h>

extern UART_HandleTypeDef huart3;
BUTTONFLAG ButtonState={0};
BUTTONFLAG* pvButtonState=&ButtonState;
volatile uint32_t JitterCounter=0;

void PollUart(void)
{
	uint8_t ReceiveBuffer[1]={0};
    HAL_StatusTypeDef status;
    status = HAL_UART_Receive(&huart3, ReceiveBuffer, 1, 10);

    if (status == HAL_OK)
      {
        switch (ReceiveBuffer[0])
          {
            case 'R':
            case 'r':
              HAL_GPIO_TogglePin(RED_GPIO_Port, RED_Pin);
              HAL_UART_Transmit(&huart3, (uint8_t *)"RED is switched\r\n", 17, 10);
              if (HAL_GPIO_ReadPin(RED_GPIO_Port, RED_Pin)==GPIO_PIN_SET)
                {HAL_UART_Transmit(&huart3, (uint8_t *)"RED is ON\r\n", 11, 10);}
              else {HAL_UART_Transmit(&huart3, (uint8_t *)"RED is OFF\r\n", 12, 10);}
              break;
            case 'G':
            case 'g':
              HAL_GPIO_TogglePin(GREEN_GPIO_Port, GREEN_Pin);
              HAL_UART_Transmit(&huart3, (uint8_t *)"GREEN is switched\r\n", 19, 10);
              if (HAL_GPIO_ReadPin(GREEN_GPIO_Port, GREEN_Pin)==GPIO_PIN_SET)
                {HAL_UART_Transmit(&huart3, (uint8_t *)"GREEN is ON\r\n", 13, 10);}
              else {HAL_UART_Transmit(&huart3, (uint8_t *)"GREEN is OFF\r\n", 14, 10);}
              break;
            case 'B':
            case 'b':
              HAL_GPIO_TogglePin(BLUE_GPIO_Port, BLUE_Pin);
              HAL_UART_Transmit(&huart3, (uint8_t *)"BLUE is switched\r\n", 18, 10);
              if (HAL_GPIO_ReadPin(BLUE_GPIO_Port, BLUE_Pin)==GPIO_PIN_SET)
                {HAL_UART_Transmit(&huart3, (uint8_t *)"BLUE is ON\r\n", 12, 10);}
              else {HAL_UART_Transmit(&huart3, (uint8_t *)"BLUE is OFF\r\n", 13, 10);}
              break;
            case 'O':
            case 'o':
              HAL_GPIO_TogglePin(ORANGE_GPIO_Port, ORANGE_Pin);
              HAL_UART_Transmit(&huart3, (uint8_t *)"ORANGE is switched\r\n", 20, 10);
              if (HAL_GPIO_ReadPin(ORANGE_GPIO_Port, ORANGE_Pin)==GPIO_PIN_SET)
                {HAL_UART_Transmit(&huart3, (uint8_t *)"ORANGE is ON\r\n", 14, 10);}
              else {HAL_UART_Transmit(&huart3, (uint8_t *)"ORANGE is OFF\r\n", 15, 10);}
              break;
            case '\r':
            case '\n':
           	 break;
            default:
              HAL_UART_Transmit(&huart3, (uint8_t *)"Unknown command, you should use R, G, B, O, r, g, b, o only\r\n", 61, 10);
              break;
	  			}
	  		}
    //else if (status==HAL_ERROR||status==HAL_BUSY||status==HAL_TIMEOUT)
      //{HAL_UART_Transmit(&huart3, (uint8_t *)"Something went wrong during receiving\r\n", 39, 10);}
}

void ButtonsAntiJitter(void)
{
	pvButtonState->ButtonsPollIsDenied=1;
	pvButtonState->JitterIsBlocking=1;
}


void PollButtons(void)
{
	static uint32_t TimeCounter=0;
	if (TimeCounter+100<HAL_GetTick()) //poll buttons every ~100ms
	{
		if (pvButtonState->ButtonsPollIsDenied==1)
		{
			pvButtonState->JitterIsBlocking=1;
			if (JitterCounter>200)
			  {
				pvButtonState->ButtonsPollIsDenied=0;
				JitterCounter=0;
				pvButtonState->JitterIsBlocking=0;
			  }
			else {}
		}
		else
		{
		  if (HAL_GPIO_ReadPin(SWT1_GPIO_Port, SWT1_Pin)==GPIO_PIN_RESET)
		    {pvButtonState->SWT1=1;}
		  if (HAL_GPIO_ReadPin(SWT3_GPIO_Port, SWT3_Pin)==GPIO_PIN_RESET)
		    {pvButtonState->SWT3=1;}
		  if (HAL_GPIO_ReadPin(SWT4_GPIO_Port, SWT4_Pin)==GPIO_PIN_RESET)
		    {pvButtonState->SWT4=1;}
		  if (HAL_GPIO_ReadPin(SWT5_GPIO_Port, SWT5_Pin)==GPIO_PIN_RESET)
		    {pvButtonState->SWT5=1;}
		}
		TimeCounter=HAL_GetTick();
	}

	if (pvButtonState->SWT1==1) {ButtonsAntiJitter();HAL_GPIO_TogglePin(BLUE_GPIO_Port, BLUE_Pin); pvButtonState->SWT1=0;}
	if (pvButtonState->SWT3==1) {ButtonsAntiJitter();HAL_GPIO_TogglePin(ORANGE_GPIO_Port, ORANGE_Pin); pvButtonState->SWT3=0;}
	if (pvButtonState->SWT4==1) {ButtonsAntiJitter();HAL_GPIO_TogglePin(RED_GPIO_Port, RED_Pin); pvButtonState->SWT4=0;}
	if (pvButtonState->SWT5==1) {ButtonsAntiJitter();HAL_GPIO_TogglePin(GREEN_GPIO_Port, GREEN_Pin); pvButtonState->SWT5=0;}
}





