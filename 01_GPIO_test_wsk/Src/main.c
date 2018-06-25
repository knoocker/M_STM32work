
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_hal.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
#define LEDn 8

typedef enum
{
  LED3 = 0,
  LED4 = 1,
  LED5 = 2,
  LED6 = 3,
  LED7 = 4,
  LED8 = 5,
  LED9 = 6,
  LED10 = 7
} Led_TypeDef;

uint16_t GPIO_PIN[LEDn] = {LED_3_RED_Pin, LED_4_BLUE_Pin, LED_5_ORANGE_Pin, LED_6_GREEN_Pin,
		LED_7_GREEN_Pin, LED_8_ORANGE_Pin, LED_9_BLUE_Pin, LED_10_RED_Pin};

GPIO_TypeDef* GPIO_PORT[LEDn] = {LED_3_RED_GPIO_Port, LED_4_BLUE_GPIO_Port, LED_5_ORANGE_GPIO_Port,
                                 LED_6_GREEN_GPIO_Port, LED_7_GREEN_GPIO_Port, LED_8_ORANGE_GPIO_Port,
                                 LED_9_BLUE_GPIO_Port, LED_10_RED_GPIO_Port };
uint8_t LED_SEQ[LEDn] = {LED3, LED5, LED7, LED9, LED10, LED8, LED6, LED4};
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* USER CODE BEGIN PFP */
void STM_EVAL_LEDOn(Led_TypeDef Led);
void STM_EVAL_LEDOff(Led_TypeDef Led);
void STM_EVAL_LEDToggle(Led_TypeDef Led);
/* Private function prototypes -----------------------------------------------*/

//----------- tablica z poleceniami AT i wska�nikami funkcji do ich obs�ugi --------------------
void at_service(uint8_t inout, char * params);
void ati_service(uint8_t inout, char * params);


typedef struct {
	char polecenie_at[8];
	int8_t (* at_service)(uint8_t inout, char * params);
} TATCMD;

#define AT_CNT 	2	// ilo� polece� AT
const TATCMD polecenia_at[AT_CNT] = {
// { at_cmd } , { wska�nik do funkcji obs�ugi at },
		{ "AT", at_service },
		{"ATI", 	ati_service}
//		{"AT+RST", 	at_rst_service},
//		{"AT+IR", 	at_ir_service},
//		{"AT+LED", 	at_led_service},
//		{"AT+LCD", 	at_lcd_service}
		};

void funkcja(uint8_t inout, char * params)
{
	static uint8_t indeks = 0;
	static uint8_t zapal = 1;



	if (0 == strncasecmp("ATI",polecenia_at[1].polecenie_at, 3))
	{
		if(zapal) HAL_GPIO_WritePin(GPIO_PORT[LED_SEQ[indeks]], GPIO_PIN[LED_SEQ[indeks]], GPIO_PIN_SET);
					else HAL_GPIO_WritePin(GPIO_PORT[LED_SEQ[indeks]], GPIO_PIN[LED_SEQ[indeks]], GPIO_PIN_RESET);

			if(++indeks >= LEDn)
			{
				indeks = 0;
				if(zapal) zapal = 0;
				else zapal = 1;
			}
	}




}
void at_service(uint8_t inout, char * params)
{

}
void ati_service(uint8_t inout, char * params)
{

}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){


//	if(HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin) == GPIO_PIN_SET)
//	{
//	  HAL_GPIO_WritePin(LED_6_GREEN_GPIO_Port, LED_6_GREEN_Pin, GPIO_PIN_SET);
//	}
//	else
//	{
//	  HAL_GPIO_WritePin(LED_6_GREEN_GPIO_Port, LED_6_GREEN_Pin, GPIO_PIN_RESET);;
//	}

	//HAL_GPIO_WritePin(LED_6_GREEN_GPIO_Port, LED_6_GREEN_Pin, HAL_GPIO_ReadPin(BUTTON_USER_GPIO_Port, BUTTON_USER_Pin));

	if(GPIO_Pin == BUTTON_Pin){
		void (*_at_srv)(uint8_t inout, char * data);
		//_at_srv = (void *) pgm_read_word(&polecenia_at[i].at_service);
		_at_srv = funkcja;
		//funkcja();
		_at_srv(2,0);
	}
}
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  //Uzupe�nianie komend CTRL+SPACJA
  //HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_SET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	Project > Clean
//	Project > C/C++ Index > Rebuild
//	Project > C/C++ Index > Freshen All Files

//	  if(HAL_GPIO_ReadPin(BUTTON_USER_GPIO_Port, BUTTON_USER_Pin) == GPIO_PIN_SET)
//	  {
//		  HAL_GPIO_WritePin(LED_6_GREEN_GPIO_Port, LED_6_GREEN_Pin, GPIO_PIN_SET);
//	  }
//	  else
//	  {
//		  HAL_GPIO_WritePin(LED_6_GREEN_GPIO_Port, LED_6_GREEN_Pin, GPIO_PIN_RESET);;
//	  }

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, LED_4_BLUE_Pin|LED_3_RED_Pin|LED_5_ORANGE_Pin|LED_7_GREEN_Pin 
                          |LED_9_BLUE_Pin|LED_10_RED_Pin|LED_8_ORANGE_Pin|LED_6_GREEN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : BUTTON_Pin */
  GPIO_InitStruct.Pin = BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BUTTON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_4_BLUE_Pin LED_3_RED_Pin LED_5_ORANGE_Pin LED_7_GREEN_Pin 
                           LED_9_BLUE_Pin LED_10_RED_Pin LED_8_ORANGE_Pin LED_6_GREEN_Pin */
  GPIO_InitStruct.Pin = LED_4_BLUE_Pin|LED_3_RED_Pin|LED_5_ORANGE_Pin|LED_7_GREEN_Pin 
                          |LED_9_BLUE_Pin|LED_10_RED_Pin|LED_8_ORANGE_Pin|LED_6_GREEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

}

/* USER CODE BEGIN 4 */
void STM_EVAL_LEDOn(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BSRR = GPIO_PIN[Led];
}

void STM_EVAL_LEDOff(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BRR = GPIO_PIN[Led];
}

void STM_EVAL_LEDToggle(Led_TypeDef Led)
{
  GPIO_PORT[Led]->ODR ^= GPIO_PIN[Led];
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/