
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_hal.h"
#include "usb_device.h"

/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h" // Plik bedacy interfejsem uzytkownika do kontrolera USB
#include "komendy_at/komendy_at.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim14;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint8_t DataToSend[40]; // Tablica zawierajaca dane do wyslania
uint8_t MessageCounter = 0; // Licznik wyslanych wiadomosci
uint8_t MessageLength = 0; // Zawiera dlugosc wysylanej wiadomosci

uint8_t ReceivedData[40]; // Tablica przechowujaca odebrane dane
uint8_t ReceivedDataFlag = 0; // Flaga informujaca o odebraniu danych

enum stany_silownika {
	silownik_stop, silownik_gora, silownik_dol
};

volatile enum stany_silownika stan_silownika = silownik_stop;
volatile uint8_t stan_silownika_flag = 0;
volatile uint8_t przycisk_flag = 0;

volatile uint8_t pc_on, rz_on, przycisk_on, pc_pwr;
volatile uint8_t tryb = 0; // 0 - normalny, 1 - serwisowy
volatile uint8_t flag_zmiana_trybu;

volatile uint8_t flag_1Hz;
volatile uint8_t flag_2Hz;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM14_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
#define PC_ON ( HAL_GPIO_ReadPin(PC_LED_GPIO_Port, PC_LED_Pin) )
#define RZUTNIK_ON ( HAL_GPIO_ReadPin(RZUTNIK_VUSB_GPIO_Port, RZUTNIK_VUSB_Pin|RZUTNIK_DM_Pin|RZUTNIK_DP_Pin) )
#define PRZYCISK_DOWN ( HAL_GPIO_ReadPin(PRZYCISK_GPIO_Port, PRZYCISK_Pin) == 0)
#define PWR_ON ( HAL_GPIO_WritePin(PC_PWR_GPIO_Port, PC_PWR_Pin, GPIO_PIN_RESET) )
#define PWR_OFF ( HAL_GPIO_WritePin(PC_PWR_GPIO_Port, PC_PWR_Pin, GPIO_PIN_SET) )
#define RED_ON ( HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET) )
#define RED_OFF ( HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET) )
#define RED_TOG ( HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin) )
#define GREEN_ON ( HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET) )
#define GREEN_OFF ( HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET) )
#define GREEN_TOG ( HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin) )
#define BLUE_ON ( HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET) )
#define BLUE_OFF ( HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET) )
#define BLUE_TOG ( HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin) )
#define USB_PWR_ON ( HAL_GPIO_WritePin(USB_PWR_GPIO_Port, USB_PWR_Pin, GPIO_PIN_RESET) )
#define USB_PWR_OFF ( HAL_GPIO_WritePin(USB_PWR_GPIO_Port, USB_PWR_Pin, GPIO_PIN_SET) )

void inline SILOWNIK_STOP() {
	HAL_GPIO_WritePin(M_IN1_GPIO_Port, M_IN1_Pin | M_IN2_Pin, GPIO_PIN_RESET);
}
void inline SILOWNIK_GORA() {
	HAL_GPIO_WritePin(M_IN1_GPIO_Port, M_IN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(M_IN1_GPIO_Port, M_IN2_Pin, GPIO_PIN_SET);
}
void inline SILOWNIK_DOL() {
	HAL_GPIO_WritePin(M_IN1_GPIO_Port, M_IN2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(M_IN1_GPIO_Port, M_IN1_Pin, GPIO_PIN_SET);
}

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	if(htim->Instance == TIM14)	// 20 Hz
//	{
//		if(PRZYCISK_DOWN)
//		{
//			RED_TOG;
//			BLUE_TOG;
//			GREEN_TOG;
//		}
//	}
//}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM14)	// 40 Hz
	{
		const uint8_t licznik_2Hz_max = 20 - 1;
		static uint8_t licznik_2Hz = licznik_2Hz_max;
		const uint8_t licznik_1Hz_max = 2 - 1;
		static uint8_t licznik_1Hz = licznik_1Hz_max;

		if (licznik_2Hz)
			licznik_2Hz--;
		else {
			licznik_2Hz = licznik_2Hz_max;
			flag_2Hz = 1;
			if (licznik_1Hz)
				licznik_1Hz--;
			else {
				licznik_1Hz = licznik_1Hz_max;
				flag_1Hz = 1;
			}
		}

		// Parametry obslugi sygnalow i przycisku
		const uint8_t reakcja_na_sygnal_czas = 120;	// reakcja na sygnal, gdy utrzyma sie dluzej niz zadana liczba dziesi�tych cz�ci sekund (40 Hz)
		const uint8_t reakcja_na_przycisk_czas = 2;	// reakcja na przycisk, musi byc wcisniety dluzej niz 0,05 s.
		const uint8_t pc_pwr_czas = 20;	// wcisniecie przycisku PWR po zadanym czasie (40 Hz)
		const uint8_t tryb_czas_na_wcisniecia = 40;	// czas w ktorym trzeba wcisnac przycisk n razy
		const uint8_t tryb_ilosc_wcisniec_zmiana = 3;// po ilu wcisnieciach zmieni sie tryb na serwisowy

		static uint8_t pc_on_s, pc_off_s;// zliczanie sekund wlaczenia\wylaczenia PC i jego stan
		static uint8_t rz_on_s, rz_off_s;// zliczanie sekund wlaczenia\wylaczenia rzutnika i jego stan
		static uint8_t przycisk_on_s;// zliczanie sekund wcisniecia przycisku i jego stan

		// ---------- Licznik najblizszego czasu ----------
		static uint8_t licznik = 0;
		if (licznik)
			licznik--;
		// ----- reakcja na przycisk - filtracja i zliczanie wci�ni�� -----
		static uint8_t wcisniecia = 0;
		if (PRZYCISK_DOWN) {

			if (przycisk_on_s < 255)
				przycisk_on_s++; // licznik czasu wcisniecia przycisku
			if (przycisk_on_s >= reakcja_na_przycisk_czas) // reakcja na wcisniecie przycisku, gdy wcisniety dluzej niz
					{
				przycisk_on = 1;	// Ustaw stan przycisku na 1 - wcisniety
				if (!licznik) {
					if (tryb) // Obs�uga silnika w trybie serwisowym
					{
						if (wcisniecia == 1) // silownik w d�
								{
							if (stan_silownika == silownik_stop)
								stan_silownika = silownik_dol;
							else
								stan_silownika = silownik_stop;
							stan_silownika_flag = 1;
						} else if (wcisniecia == 2) // silownik w gore
								{
							if (stan_silownika == silownik_stop)
								stan_silownika = silownik_gora;
							else
								stan_silownika = silownik_stop;
							stan_silownika_flag = 1;
						}
						// 1 d�
						// 2 g�ra
						// gdy si� porusza, 1 lub 2 wy��cza ruch
					}

					wcisniecia = 0; // Gdy licznik doliczyl do zera wyzeruj wcisniecia
				}
				if (!wcisniecia)
					licznik = tryb_czas_na_wcisniecia; // Po pierwszym wcisnieciu przycisku wyzeruj licznik - zliczaj wcisniecia z ostatnich 1,5 s
				if (przycisk_on_s == reakcja_na_przycisk_czas) // Licz wcisniecia tylko w ustalonym czasie reakcji na przycisk
						{
					wcisniecia++;
					if (wcisniecia == tryb_ilosc_wcisniec_zmiana) // Zmiana trybu po osiagnieciu ustalonej liczby wcisniec
							{
						flag_zmiana_trybu = 1; // zmiana trybu serwisowy/normalny
						wcisniecia = 0; // wyzeruj ilosc wcisniec i licznik (kolejne 3 wcisniecia liczone beda od nowa)
						licznik = 0;
						// Zatrzymaj ruch silownika
						stan_silownika = silownik_stop;
						stan_silownika_flag = 1;
					} // Zmiana trybu
				} // Licz wcisniecia

				// Ustaw flage pc_pwr po zadanym czasie wcisniecia przycisku
				if (przycisk_on_s >= pc_pwr_czas)
					pc_pwr = 1;
				else
					pc_pwr = 0;
			} // Reakcja na wcisniety przycisk
		} // PRZYCISK_DOWN
		else // Przycisk nie wcisniety
		{
			przycisk_on = 0;
			przycisk_on_s = 0;
			pc_pwr = 0;
		}

		// ---------- reakcja na sygnal od PC i rzutnika ----------
		if (PC_ON) { // PC wlaczony
			if (pc_on_s < reakcja_na_sygnal_czas)
				pc_on_s++;
			else
				pc_on = 1;
			pc_off_s = 0;
		} else { // PC wylaczony
			if (pc_off_s < reakcja_na_sygnal_czas)
				pc_off_s++;
			else
				pc_on = 0;
			pc_on_s = 0;
		}
		if (RZUTNIK_ON) { // rzutnik wlaczony
			if (rz_on_s < reakcja_na_sygnal_czas)
				rz_on_s++;
			else
				rz_on = 1;
			rz_off_s = 0;
		} else { // rzutnik wylaczony
			if (rz_off_s < reakcja_na_sygnal_czas)
				rz_off_s++;
			else
				rz_on = 0;
			rz_on_s = 0;
		}
	} // TIM14
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
  MX_TIM14_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim14);
	// Testowe mrugranie diod
	for (int i = 0; i < 10; i++) {
		RED_TOG;
		GREEN_TOG;
		BLUE_TOG;
		HAL_Delay(250);
	}

	RED_ON;
	//GREEN_ON;
	//BLUE_ON;
//	while (1) {
//		if (flag_1Hz) {
//			flag_1Hz = 0;
//
//			++MessageCounter;
//			MessageLength = sprintf(DataToSend, "Wiadomosc nr %d\n\r",
//					MessageCounter);
//			CDC_Transmit_FS(DataToSend, MessageLength);
//			BLUE_TOG;
//		}
//		// Przycisk wcisniety dluzej niz 1s
//		if (pc_pwr) {
//			PWR_ON;
//			GREEN_ON;
//
//		} else {
//			PWR_OFF;
//			GREEN_OFF;
//		}
//	}

//    while(1)
//    {
////		if(PRZYCISK_DOWN)
////		{
////		  GREEN_ON;
////		  BLUE_OFF;
////		  HAL_GPIO_WritePin(BOOT0_GPIO_Port, BOOT0_Pin, GPIO_PIN_SET);
////		  HAL_Delay(1000);
////		  NVIC_SystemReset();
////		}
////		  else
////		  {
////			  GREEN_TOG;
////			  BLUE_ON;
////			  HAL_Delay(100);
////		  }
//
//		// Odeslanie odebranych danych przez USB
//		if (ReceivedDataFlag == 1) {
//			ReceivedDataFlag = 0;
//			parse_uart_data(ReceivedData);
//		}
//    }

	const uint8_t liczba_prob_wylaczenia = 5;
	const uint8_t czas_na_wylaczenie = 60; //s
	const uint8_t czas_na_wlaczenie = 10; //s
	const uint8_t czas_wylaczanie_twarde = 10; //s
	const uint8_t czas_praca_silownika_max = 30; //s
	uint8_t czas_praca_silownika = 0;
	uint8_t flag_praca_silownika = 0;
	uint8_t flag_czekaj = 0;
	uint8_t flag_wylaczanie = 0;
	uint8_t flag_wylaczanie_twarde = 0;
	uint8_t flag_wlaczanie = 0;
	uint8_t licznik_prob = 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	uint8_t pc_pwr_poprzedni = 0;
//	while (1) {
//		if (pc_pwr && !pc_pwr_poprzedni) {
//			pc_pwr_poprzedni = 1;
//			++MessageCounter;
//			MessageLength = sprintf(DataToSend, "Wiadomosc nr %d\n\r",
//					MessageCounter);
//			CDC_Transmit_FS(DataToSend, MessageLength);
//		} else
//			pc_pwr_poprzedni = 0;
//		BLUE_TOG;
//	}

	while (1) {
		// Odeslanie odebranych danych przez USB
		if (ReceivedDataFlag == 1) {
			ReceivedDataFlag = 0;
			parse_uart_data(ReceivedData);
		}

		//watchdog
		if (flag_zmiana_trybu) // Zmiana trybu
		{
			flag_zmiana_trybu = 0;
			tryb ^= 1;
		}

		// silownik
		if (stan_silownika_flag) {
			stan_silownika_flag = 0;
			if (stan_silownika == silownik_gora) {
				SILOWNIK_GORA();
				czas_praca_silownika = czas_praca_silownika_max;
				flag_praca_silownika = 1;
			} else if (stan_silownika == silownik_dol) {
				SILOWNIK_DOL();
				czas_praca_silownika = czas_praca_silownika_max;
				flag_praca_silownika = 1;
			} else {
				SILOWNIK_STOP();
				czas_praca_silownika = 0;
				flag_praca_silownika = 0;
			}

		}

		// oczekiwanie
		if (flag_1Hz) {
			flag_1Hz = 0;
			if (flag_czekaj)
				flag_czekaj--;

			if (flag_praca_silownika) // czasowa praca silownika
			{
				if (czas_praca_silownika)
					czas_praca_silownika--;
				else {
					SILOWNIK_STOP();
					flag_praca_silownika = 0;
					stan_silownika = silownik_stop;
				}
			}
		}

		// Przycisk wcisniety dluzej niz 1s
		if (pc_pwr || flag_wylaczanie_twarde) {
			PWR_ON;
		} else if (!flag_wylaczanie_twarde)
			PWR_OFF;

		if (tryb) // serwisowy
		{
			// W trybie serwisowym wej�cia nie maj� wp�ywu na w��czanie/wy��czanie komputera
			if (flag_2Hz) {
				flag_2Hz = 0;
				RED_TOG;
				if (stan_silownika == silownik_stop) {
					if (PC_ON) {
						GREEN_TOG;
						USB_PWR_ON;
					} else {
						GREEN_OFF;
						USB_PWR_OFF;
					}

					if (RZUTNIK_ON)
						BLUE_TOG;
					else
						BLUE_OFF;
				} else if (stan_silownika == silownik_gora) {
					GREEN_OFF;
					BLUE_TOG;
				} else if (stan_silownika == silownik_dol) {
					BLUE_OFF;
					GREEN_TOG;
				}
			}

		} // serwisowy
		else // normalny
		{
			if (flag_2Hz) // Mruganie diod podczas wlaczania / wylaczania PC
			{
				flag_2Hz = 0;
				if (flag_wlaczanie)
					BLUE_TOG;
				if (flag_wylaczanie)
					GREEN_TOG;
				if (flag_wylaczanie_twarde) {
					// Mruganie przy twardym wylaczaniu ma byc wolniejsze
					static uint8_t opoznienie = 0;
					if (opoznienie)
						opoznienie--;
					else {
						opoznienie = 3;
						GREEN_TOG;
					}
				}
			}
			// Diody informuj�ce
			RED_ON;
			if (PC_ON) {
				if (!(flag_wylaczanie || flag_wylaczanie_twarde))
					GREEN_ON;
			} else
				GREEN_OFF;
			if (RZUTNIK_ON) {
				if (!flag_wlaczanie)
					BLUE_ON;
			} else
				BLUE_OFF;

			// ----- Obsluga stanow -----
			if ((pc_on && rz_on) || !(pc_on || rz_on)) //wszystko jest w��czone / wy��czone - OK
					{
				licznik_prob = 0;
				flag_czekaj = 0;
				flag_wylaczanie = 0;
				flag_wylaczanie_twarde = 0;
				flag_wlaczanie = 0;
				PWR_OFF;
				if (pc_on)
					USB_PWR_ON;
				else
					USB_PWR_OFF;
			} else if (pc_on && !rz_on) //PC w��czony, rzutnik wy��czony - wy��cz PC
					{
				if (!flag_czekaj) // czekaj minut� po wci�ni�ciu
				{
					if (licznik_prob < 255)
						licznik_prob++;
					if (licznik_prob <= liczba_prob_wylaczenia) // wylacz normalnie
							{
						flag_wylaczanie = 1;
						PWR_ON;
						HAL_Delay(500);
						PWR_OFF;

						USB_PWR_OFF;
						// czekaj minut�
						flag_czekaj = czas_na_wylaczenie;
					} else // wylaczanie twarde
					{
						flag_wylaczanie_twarde = 1;
						flag_czekaj = czas_wylaczanie_twarde;
						//PWR_ON;
					}
				}
			} else if (!pc_on && rz_on) // Rzutnik w��czony, PC wy��czony - w��cz PC
					{
				if (!flag_czekaj) // czekaj 10s po wci�ni�ciu
				{
					flag_wlaczanie = 1;
					PWR_ON;
					HAL_Delay(500);
					PWR_OFF;

					USB_PWR_ON;
					// czekaj 10s
					flag_czekaj = czas_na_wlaczenie;
				}
			}
		} // normalny
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV4;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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

/* TIM14 init function */
static void MX_TIM14_Init(void)
{

  htim14.Instance = TIM14;
  htim14.Init.Prescaler = 5;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = 50000;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

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
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, M_IN1_Pin|M_IN2_Pin|LED_GREEN_Pin|LED_BLUE_Pin 
                          |LED_RED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PWR_GPIO_Port, USB_PWR_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(PC_PWR_GPIO_Port, PC_PWR_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BOOT0_GPIO_Port, BOOT0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : M_IMP_Pin */
  GPIO_InitStruct.Pin = M_IMP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(M_IMP_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : M_IN1_Pin M_IN2_Pin LED_GREEN_Pin LED_BLUE_Pin 
                           LED_RED_Pin */
  GPIO_InitStruct.Pin = M_IN1_Pin|M_IN2_Pin|LED_GREEN_Pin|LED_BLUE_Pin 
                          |LED_RED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PRZYCISK_Pin */
  GPIO_InitStruct.Pin = PRZYCISK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(PRZYCISK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PWR_Pin */
  GPIO_InitStruct.Pin = USB_PWR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PWR_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PC_LED_Pin */
  GPIO_InitStruct.Pin = PC_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(PC_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PC_PWR_Pin */
  GPIO_InitStruct.Pin = PC_PWR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PC_PWR_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RZUTNIK_DP_Pin RZUTNIK_DM_Pin RZUTNIK_VUSB_Pin */
  GPIO_InitStruct.Pin = RZUTNIK_DP_Pin|RZUTNIK_DM_Pin|RZUTNIK_VUSB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOT0_Pin */
  GPIO_InitStruct.Pin = BOOT0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BOOT0_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
	while (1) {
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
