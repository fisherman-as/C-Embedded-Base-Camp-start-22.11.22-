/*
 * UartComm.c
 *
 *  Created on: Mar 5, 2023
 *      Author: AS
 */
#include <Key_Butt_Temp.h>
#include <stdio.h>
//#include <string.h>

extern UART_HandleTypeDef huart3;
extern ADC_HandleTypeDef hadc1;
BUTTONFLAG ButtonState={0};
BUTTONFLAG* pvButtonState=&ButtonState;
volatile uint32_t JitterCounter=0;
uint16_t AdcData[1]={0};

void UartSendMessageTogglePin(COLOR color)
{
	switch (color)
	{
	case GREEN:
        HAL_GPIO_TogglePin(GREEN_GPIO_Port, GREEN_Pin);
        HAL_UART_Transmit(&huart3, (uint8_t *)"GREEN is switched\r\n", 19, 10);
        if (HAL_GPIO_ReadPin(GREEN_GPIO_Port, GREEN_Pin)==GPIO_PIN_SET)
          {HAL_UART_Transmit(&huart3, (uint8_t *)"GREEN is ON\r\n", 13, 10);}
        else {HAL_UART_Transmit(&huart3, (uint8_t *)"GREEN is OFF\r\n", 14, 10);}
        break;
	case ORANGE:
        HAL_GPIO_TogglePin(ORANGE_GPIO_Port, ORANGE_Pin);
        HAL_UART_Transmit(&huart3, (uint8_t *)"ORANGE is switched\r\n", 20, 10);
        if (HAL_GPIO_ReadPin(ORANGE_GPIO_Port, ORANGE_Pin)==GPIO_PIN_SET)
          {HAL_UART_Transmit(&huart3, (uint8_t *)"ORANGE is ON\r\n", 14, 10);}
        else {HAL_UART_Transmit(&huart3, (uint8_t *)"ORANGE is OFF\r\n", 15, 10);}
        break;
	case RED:
        HAL_GPIO_TogglePin(RED_GPIO_Port, RED_Pin);
        HAL_UART_Transmit(&huart3, (uint8_t *)"RED is switched\r\n", 17, 10);
        if (HAL_GPIO_ReadPin(RED_GPIO_Port, RED_Pin)==GPIO_PIN_SET)
          {HAL_UART_Transmit(&huart3, (uint8_t *)"RED is ON\r\n", 11, 10);}
        else {HAL_UART_Transmit(&huart3, (uint8_t *)"RED is OFF\r\n", 12, 10);}
        break;
	case BLUE:
        HAL_GPIO_TogglePin(BLUE_GPIO_Port, BLUE_Pin);
        HAL_UART_Transmit(&huart3, (uint8_t *)"BLUE is switched\r\n", 18, 10);
        if (HAL_GPIO_ReadPin(BLUE_GPIO_Port, BLUE_Pin)==GPIO_PIN_SET)
          {HAL_UART_Transmit(&huart3, (uint8_t *)"BLUE is ON\r\n", 12, 10);}
        else {HAL_UART_Transmit(&huart3, (uint8_t *)"BLUE is OFF\r\n", 13, 10);}
        break;
	default:
        HAL_UART_Transmit(&huart3, (uint8_t *)"Hey, programmer, you made a mistake!\r\n", 38, 10);
        break;
	}
}


void PollUart(void)
{
	uint8_t ReceiveBuffer[1]={0};
    HAL_StatusTypeDef status;
    status = HAL_UART_Receive(&huart3, ReceiveBuffer, 1, 1);
    if (status == HAL_OK)
      {
        switch (ReceiveBuffer[0])
          {
            case 'R':
            case 'r':
              UartSendMessageTogglePin(RED);
              break;
            case 'G':
            case 'g':
              UartSendMessageTogglePin(GREEN);
              break;
            case 'B':
            case 'b':
              UartSendMessageTogglePin(BLUE);
              break;
            case 'O':
            case 'o':
              UartSendMessageTogglePin(ORANGE);
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

    HAL_Delay(50);
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

	if (pvButtonState->SWT1==1) {ButtonsAntiJitter();UartSendMessageTogglePin(BLUE); pvButtonState->SWT1=0;}
	if (pvButtonState->SWT3==1) {ButtonsAntiJitter();UartSendMessageTogglePin(ORANGE); pvButtonState->SWT3=0;}
	if (pvButtonState->SWT4==1) {ButtonsAntiJitter();UartSendMessageTogglePin(RED); pvButtonState->SWT4=0;}
	if (pvButtonState->SWT5==1) {ButtonsAntiJitter();UartSendMessageTogglePin(GREEN); pvButtonState->SWT5=0;}
}


void HandleExtTempChannel()
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*) AdcData, 1);
	//HAL_ADC_PollForConversion(&hadc1, 100);
	//uint16_t ADCValue=HAL_ADC_GetValue(&hadc1);
	float Voltage=(float)(AdcData[0])*3.3/4096;
	uint32_t Temperature= (uint32_t)(101-50*Voltage);
	//uint8_t buffer[10];
	//sprintf(buffer, "%d", (uint16_t)Temperature);

	HAL_UART_Transmit(&huart3, (uint8_t *)buffer, strlen(buffer), 10);
	HAL_UART_Transmit(&huart3, (uint8_t *)"\r\n", 2, 10);
	HAL_Delay(1000);

}




//--------------------------------------------------------------------------------------------------------------------struct divmod10_t
struct divmod10_t
{
    uint32_t quot;
    uint8_t rem;
};
inline static divmod10_t divmodu10(uint32_t n)
{
    divmod10_t res;
// умножаем на 0.8
    res.quot = n >> 1;
    res.quot += res.quot >> 1;
    res.quot += res.quot >> 4;
    res.quot += res.quot >> 8;
    res.quot += res.quot >> 16;
    uint32_t qq = res.quot;
// делим на 8
    res.quot >>= 3;
// вычисляем остаток
    res.rem = uint8_t(n - ((res.quot << 1) + (qq & ~7ul)));
// корректируем остаток и частное
    if(res.rem > 9)
    {
        res.rem -= 10;
        res.quot++;
    }
    return res;
}

char * utoa_fast_div(uint32_t value, char *buffer)
{
    buffer += 11;
    *--buffer = 0;
    do
    {
        divmod10_t res = divmodu10(value);
        *--buffer = res.rem + '0';
        value = res.quot;
    }
    while (value != 0);
    return buffer;
}












