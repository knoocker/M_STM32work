/*
 * komendy_at.h  
 *
 *  Created on: 13-03-2012
 *      Author: Miros³aw Kardaœ
 *  Implementacja na STM32 18.05.2018
 *  Autor: Marek Piotrowski
 */

#ifndef KOMENDY_AT_H_
#define KOMENDY_AT_H_
#include "stm32f0xx_hal.h"

// definicja typu strukturalnego
typedef struct {
	char polecenie_at[16];
	int8_t (* at_service)(uint8_t inout, char * params);
} TATCMD;


// deklaracje zmiennych zewnêtrznych
extern const TATCMD polecenia_at[];
extern uint8_t ir_enable;

extern uint8_t DataToSend[40]; // Tablica zawierajaca dane do wyslania
extern uint8_t MessageLength; // Zawiera dlugosc wysylanej wiadomosci


// deklaracje funkcji
void parse_uart_data( char * pBuf );

int8_t at_service(uint8_t inout, char * params);
int8_t ati_service(uint8_t inout, char * params);
int8_t at_rst_service(uint8_t inout, char * params);
int8_t at_ir_service(uint8_t inout, char * params);
int8_t at_led_service(uint8_t inout, char * params);
int8_t at_lcd_service( uint8_t inout, char * params );

int8_t at_pasek_service(uint8_t inout, char * params);

#endif /* KOMENDY_AT_H_ */
