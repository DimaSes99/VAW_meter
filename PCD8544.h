/* 
 * File:   PCD8544.h
 * Author: dima_ses
 *
 * Created on August 28, 2019, 11:18 PM
 */

#ifndef PCD8544_H
#define	PCD8544_H
#include "main.h"

#define RST PB7
#define CE PB0
#define DC PB1

void PCD_sendCommand(uint8_t);
void PCD_sendData(uint8_t);
void PCD_init();
void PCD_Clrscr();
void PCD_setRAMpos(uint8_t x, uint8_t y);
void PCD_printChar(char);
void PCD_print(char[]);
void PCD_setCursor(uint8_t x, uint8_t y);
void PCD_printInt(int32_t);
#endif	/* PCD8544_H */

