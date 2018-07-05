/*
 * komendy_at.c  
 *
 *  Created on: 13-03-2012
 *      Author: Miros³aw Kardaœ
 *  Implementacja na STM32 18.05.2018
 *  Autor: Marek Piotrowski
 */
#include "komendy_at.h"
#include <string.h>

#define AT_CNT 	4	// iloæ poleceñ AT

enum stany_silownika {
	silownik_stop, silownik_gora, silownik_dol
};
extern volatile enum stany_silownika stan_silownika;
extern volatile uint8_t stan_silownika_flag;

//----------- tablica z poleceniami AT i wskaŸnikami funkcji do ich obs³ugi --------------------
const TATCMD polecenia_at[AT_CNT] = {
// { at_cmd } , { wskaŸnik do funkcji obs³ugi at },
		{ "AT", at_service },
		{"ATI", 	ati_service},
		{"AT+PASEK", at_pasek_service},
		{"AT+SILOWNIK", at_silownik_service}
//		{"AT+RST", 	at_rst_service},
//		{"AT+IR", 	at_ir_service},
//		{"AT+LED", 	at_led_service},
//		{"AT+LCD", 	at_lcd_service}
		};

//----------------- funkcja do analizowania danych odebranych z UART ------------------------------
void parse_uart_data(char * pBuf) {
	int8_t (*_at_srv)(uint8_t inout, char * data);

	char * cmd_wsk;
	char * reszta;
	uint8_t i = 0, len;

	if (strpbrk(pBuf, "=?")) {
		// obs³uga poleceñ AT we/wy + parametry

		if (strpbrk(pBuf, "?")) {
			// zapytania do uk³adu w postaci: AT+CMD?

			cmd_wsk = strtok_r(pBuf, "?", &reszta);
			len = strlen(cmd_wsk);
			for (i = 0; i < AT_CNT; i++) {
				//if (len	&& 0 == strncasecmp_P(cmd_wsk,polecenia_at[i].polecenie_at, len)) strncasecmp
				if (len	&& 0 == strncasecmp(cmd_wsk,polecenia_at[i].polecenie_at, len))
				{
//					MessageLength = sprintf(DataToSend, "1\r\n");
//					CDC_Transmit_FS(DataToSend, MessageLength);
					//if (pgm_read_word(polecenia_at[i].polecenie_at))
					if (polecenia_at[i].polecenie_at)
					{ // <--- UWAGA! w tekœcie ksi¹¿ki zabrak³o pgm_read_word()
						//_at_srv = (void *) pgm_read_word(&polecenia_at[i].at_service);
						_at_srv = polecenia_at[i].at_service;
						if (_at_srv) {
							if (_at_srv(0, reszta) < 0) {
								//uart_puts("ERROR\r\n");
								MessageLength = sprintf(DataToSend, "ERROR\r\n");
								CDC_Transmit_FS(DataToSend, MessageLength);
							}
						}
					}
					//uart_puts("\r\n");
					MessageLength = sprintf(DataToSend, "\r\n");
					CDC_Transmit_FS(DataToSend, MessageLength);
					break;
				}
			}

		} else {
			// ustawienia uk³adu w postaci: AT+CMD=parametry

			cmd_wsk = strtok_r(pBuf, "=", &reszta);
			len = strlen(cmd_wsk);
			for (i = 0; i < AT_CNT; i++) {
				//if (len	&& 0 == strncasecmp_P(cmd_wsk, polecenia_at[i].polecenie_at, len))
				if (len	&& 0 == strncasecmp(cmd_wsk,polecenia_at[i].polecenie_at, len))
				{
//					MessageLength = sprintf(DataToSend, "2\r\n");
//					CDC_Transmit_FS(DataToSend, MessageLength);
					//if (pgm_read_word(polecenia_at[i].polecenie_at))
					if (polecenia_at[i].polecenie_at)
					{ // <--- UWAGA! w tekœcie ksi¹¿ki zabrak³o pgm_read_word()
						//_at_srv = (void *) pgm_read_word(&polecenia_at[i].at_service);
						_at_srv = polecenia_at[i].at_service;
						if (_at_srv && !_at_srv(1, reszta))
						{
							//uart_puts("OK\r\n");
							MessageLength = sprintf(DataToSend, "OK\r\n");
							CDC_Transmit_FS(DataToSend, MessageLength);
						}

						else
						{
							//uart_puts("ERROR\r\n");
							MessageLength = sprintf(DataToSend, "ERROR\r\n");
							CDC_Transmit_FS(DataToSend, MessageLength);
						}
					}
					break;
				}
			}
		}

	} else {
		// obs³uga poleceñ AT bez parametrów

		if (0 == pBuf[0])
		{
			//uart_puts("\r\n");	// reakcja na znak CR lub CRLF z terminala
			MessageLength = sprintf(DataToSend, "\r\n");
			CDC_Transmit_FS(DataToSend, MessageLength);
//			MessageLength = sprintf(DataToSend, "3\r\n");
//			CDC_Transmit_FS(DataToSend, MessageLength);
		}

		else {
			for (i = 0; i < AT_CNT; i++) {
				//if (0 == strncasecmp_P(pBuf, polecenia_at[i].polecenie_at, strlen(pBuf)))
				if (0 == strncasecmp(pBuf, polecenia_at[i].polecenie_at, strlen(pBuf)))
				{
//					MessageLength = sprintf(DataToSend, "4\r\n");
//					CDC_Transmit_FS(DataToSend, MessageLength);
					//if (pgm_read_word(polecenia_at[i].polecenie_at))
					if (polecenia_at[i].polecenie_at)
					{ // <--- UWAGA! w tekœcie ksi¹¿ki zabrak³o pgm_read_word()
						//_at_srv = (void *) pgm_read_word(&polecenia_at[i].at_service);
						_at_srv = polecenia_at[i].at_service;
						if (_at_srv)
							_at_srv(2, 0);
					}
					break;
				}
			}
		}
	}

	if ( AT_CNT == i)
	{
		//uart_puts("ERROR\r\n");
		MessageLength = sprintf(DataToSend, "ERROR\r\n");
		CDC_Transmit_FS(DataToSend, MessageLength);
//		MessageLength = sprintf(DataToSend, "5\r\n");
//		CDC_Transmit_FS(DataToSend, MessageLength);
	}

}

//----------------- obs³uga poszczególnych komend AT ----------------------------------
int8_t at_service(uint8_t inout, char * params) {
	//uart_puts("OK\r\n");
	MessageLength = sprintf(DataToSend, "OK\r\n");
	CDC_Transmit_FS(DataToSend, MessageLength);
	return 0;
}

int8_t ati_service(uint8_t inout, char * params) {
	//uart_puts("ATNEL AT Commands tester v1.04\r\n");
	MessageLength = sprintf(DataToSend, "STM32 AT Commands tester\r\n");
	CDC_Transmit_FS(DataToSend, MessageLength);
	return 0;
}

int8_t at_pasek_service(uint8_t inout, char * params) {
	//uart_puts("OK\r\n");
	MessageLength = sprintf(DataToSend, "Twoj tata to grubasek\r\n");
	CDC_Transmit_FS(DataToSend, MessageLength);
	return 0;
}

int8_t at_silownik_service(uint8_t inout, char * params) {

	if( inout < 2 ) {
		if( 1 == inout ) {
			if( params[0] < '0' || params[0] > '2' ) return -1;
			if( '1' == params[0] )
			{
				//LED_ON;
				stan_silownika = silownik_gora;
				stan_silownika_flag = 1;

			}
			else if( '2' == params[0] )
			{
				//LED_OFF;
				stan_silownika = silownik_dol;
				stan_silownika_flag = 1;
			}
			else
			{
				//LED_OFF;
				stan_silownika = silownik_stop;
				stan_silownika_flag = 1;
			}
		}

//		uart_puts("+LED: ");
//		if( LED_PIN & LED ) uart_putint(1,10);
//		else uart_putint(0,10);
//		uart_puts("\r\n");

		if(stan_silownika == silownik_gora) MessageLength = sprintf(DataToSend, "+SILOWNIK: gora\r\n");
		else if(stan_silownika == silownik_dol) MessageLength = sprintf(DataToSend, "+SILOWNIK: dol\r\n");
		else MessageLength = sprintf(DataToSend, "+SILOWNIK: stop\r\n");
		CDC_Transmit_FS(DataToSend, MessageLength);
	} else if( 2 == inout ) {
		//uart_puts("AT+SILOWNIK = (0-2)\r\n");
		MessageLength = sprintf(DataToSend, "AT+SILOWNIK = (0-2)\r\n");
		CDC_Transmit_FS(DataToSend, MessageLength);
	}
	return 0;
}


//
//int8_t at_rst_service(uint8_t inout, char * params) {
//
//	uart_puts("za 1.5s - restart\r\n");
//	lcd_cls();
//	lcd_str("za 1.5s restart");
//	_delay_ms(1500);
//
//	//****** RESET UK£ADU NA POTRZEBY BOOTLOADERA (MkBootloader) ***********
//	cli();			// wy³¹cz przerwania
//	wdt_enable(0);  // ustaw watch-dog
//	while(1);		// czekaj na RESET
//
//	return 0;
//}
//
//int8_t at_ir_service(uint8_t inout, char * params) {
//	if( 1 == inout ) {
//		if( '1' == params[0] ) ir_enable=1;
//		else ir_enable=0;
//		uart_puts("+IR: ");
//		uart_putint(ir_enable,10);
//		uart_puts("\r\n");
//	} else if( !inout ) {
//		uart_puts("+IR: ");
//		uart_putint(ir_enable,10);
//		uart_puts("\r\n");
//	} else if( 2 == inout ) {
//		uart_puts("AT+IR = (0-1)\r\n");
//	}
//	return 0;
//}
//
//int8_t at_led_service(uint8_t inout, char * params) {
//
//	if( inout < 2 ) {
//		if( 1 == inout ) {
//			if( params[0] < '0' || params[0] > '1' ) return -1;
//			if( '1' == params[0] ) LED_ON;
//			else LED_OFF;
//		}
//		uart_puts("+LED: ");
//		if( LED_PIN & LED ) uart_putint(1,10);
//		else uart_putint(0,10);
//		uart_puts("\r\n");
//	} else if( 2 == inout ) {
//		uart_puts("AT+LED = (0-1)\r\n");
//	}
//	return 0;
//
//}
//
//
//int8_t at_lcd_service( uint8_t inout, char * params ) {
//	uint8_t y,x;
//	char * wsk;
//
//	if( 1 == inout ) {
//		// sprawdzamy czy s¹ parametry, jeli nie to b³¹d
//		if(!strlen(params)) return -1;
//		// wy³uskujemy pierwszy parametr do przecinka
//		wsk = strtok(params, ",");
//		// sprawdzamy czy s¹ parametry, jeli nie to b³¹d
//		if(!strlen(wsk)) return -1;
//		// zamieniamy liczbê ASCII na wartoœæ dziesiêtn¹
//		y=atoi(wsk);
//		// jeœli Y  nie mieœci siê w zakresie od 0 do 3 to b³¹d
//		if( !(y>=0 && y<4) ) return -1;
//		// wy³uskujemy drugi parametr do przecinka
//		wsk = strtok(NULL, ",");
//		// sprawdzamy czy s¹ parametry, jeli nie to b³¹d
//		if(!strlen(wsk)) return -1;
//		// zamieniamy liczbê ASCII na wartoœæ dziesiêtn¹
//		x=atoi(wsk);
//		// jeœli X  nie mieœci siê w zakresie od 0 do 39 to b³¹d
//		if( !(x>=0 && y<40) ) return -1;
//		// wy³uskujemy trzeci parametr do przecinka lub do koñca ³añcucha
//		wsk = strtok(NULL, ",");
//		// sprawdzamy czy s¹ parametry, jeli nie to b³¹d
//		if(!strlen(wsk)) return -1;
//		// ustawiamy kursor w zadanym miejscu y,x
//		lcd_locate(y,x);
//		// wyœwietlamy tekst
//		lcd_str( wsk );
//
//
//	} else if( 2 == inout ) {
//		uart_puts("AT+LCD = (0-3), (0-39),(TEXT)\r\n");
//	} else {
//		if( !inout ) return -1;
//	}
//
//	return 0;
//
//}

