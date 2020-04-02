/* 
 * File:   PCD8544.h
 * Author: dima_ses
 *
 * Created on August 28, 2019, 11:18 PM
 */

#ifndef PCD8544_H
#define	PCD8544_H
#include "main.h"

#define RST_GPIO PD7
#define RST_DDR DDRD
#define RST_PORT PORTD

#define CE_GPIO PB0
#define CE_DDR DDRB
#define CE_PORT PORTB

#define DC_GPIO PB1
#define DC_DDR DDRB
#define DC_PORT PORTB

#define LIGHT_GPIO PB2
#define LIGHT_DDR DDRB
#define LIGHT_PORT PORTB

void PCD_sendCommand(uint8_t);
void PCD_sendData(uint8_t);
void PCD_init();
void PCD_reinit();
void PCD_Clrscr();
void PCD_setRAMpos(uint8_t x, uint8_t y);
void PCD_printChar(char);
void PCD_printChar_10x16(char symbol, uint8_t x, uint8_t y);
void PCD_print_10x16(char string[], uint8_t x, uint8_t y);
void PCD_print(char[]);
void PCD_setCursor(uint8_t x, uint8_t y);
void PCD_printInt(int32_t);
#endif	/* PCD8544_H */

