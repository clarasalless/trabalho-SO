#include "bootloader.h"

void bootloaderInit()
{
	int App = 0;
	BootloaderMode bootloaderMode = JumpMode;

	if(HAL_GPIO_ReadPin(Blue_Button_GPIO_Port, Blue_Button_Pin) == GPIO_PIN_RESET)
		App = App1;
	else
		App = App2;

	if(bootloaderMode == JumpMode)
	{
		if(App == App1)
		{
			//Check if the application is there
			uint8_t emptyCellCount = 0;
			for(uint8_t i=0; i<10; i++)
			{
				if(readWord(APP1_START + (i*4)) == -1)
					emptyCellCount++;
			}

			if(emptyCellCount != 10)
				jumpToApp(APP1_START);
			else
				errorBlink();
		}
		else
		{
			//Check if the application is there
			uint8_t emptyCellCount = 0;
			for(uint8_t i=0; i<10; i++)
			{
				if(readWord(APP2_START + (i*4)) == -1)
					emptyCellCount++;
			}

			if(emptyCellCount != 10)
				jumpToApp(APP2_START);
			else
				errorBlink();
		}
	}
}


uint32_t readWord(uint32_t address)
{
	uint32_t read_data;
	read_data = *(uint32_t*)(address);
	return read_data;
}

void jumpToApp(const uint32_t address)
{
	const JumpStruct* vector_p = (JumpStruct*)address;

	deinitEverything();
	SCB->VTOR = address;  // address é o endereço base da aplicação FreeRTOS
	// Atualiza o main stack pointer e faz o jump para a função
    asm("msr msp, %0; bx %1;" : : "r"(vector_p->stack_addr), "r"(vector_p->func_p));


}

void deinitEverything()
{
	//-- reset peripherals to guarantee flawless start of user application
	HAL_GPIO_DeInit(LED_Green_GPIO_Port, LED_Green_Pin);
	  __HAL_RCC_GPIOC_CLK_DISABLE();
	  __HAL_RCC_GPIOD_CLK_DISABLE();
	  __HAL_RCC_GPIOB_CLK_DISABLE();
	  __HAL_RCC_GPIOA_CLK_DISABLE();
	HAL_RCC_DeInit();
	HAL_DeInit();
	SysTick->CTRL = 0;
	SysTick->LOAD = 0;
	SysTick->VAL = 0;
}

uint8_t string_compare(char array1[], char array2[], uint16_t length)
{
	 uint8_t comVAR=0, i;
	 for(i=0;i<length;i++)
	   	{
	   		  if(array1[i]==array2[i])
	   	  		  comVAR++;
	   	  	  else comVAR=0;
	   	}
	 if (comVAR==length)
		 	return 1;
	 else 	return 0;
}

void errorBlink()
{
	HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, GPIO_PIN_SET);
	while(1)
	{
		HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, GPIO_PIN_RESET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, GPIO_PIN_SET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, GPIO_PIN_RESET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, GPIO_PIN_SET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, GPIO_PIN_RESET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, GPIO_PIN_SET);
		HAL_Delay(500);

		HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, GPIO_PIN_RESET);
		HAL_Delay(800);
		HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, GPIO_PIN_SET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, GPIO_PIN_RESET);
		HAL_Delay(800);
		HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, GPIO_PIN_SET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, GPIO_PIN_RESET);
		HAL_Delay(800);
		HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, GPIO_PIN_SET);
		HAL_Delay(500);

		HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, GPIO_PIN_RESET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, GPIO_PIN_SET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, GPIO_PIN_RESET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, GPIO_PIN_SET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, GPIO_PIN_RESET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, GPIO_PIN_SET);
		HAL_Delay(3000);
	}
}
