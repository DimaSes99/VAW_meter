/* 
 * File:   UART.h
 * Author: dima_ses
 *
 * Created on March 18, 2019, 7:03 PM
 */

#ifndef UART_H
#define	UART_H
#include "main.h"

#define RX_BUFF_SIZE 30

void UART_init(uint32_t baudrate);  //инициализация
void UART_transmitByte(uint8_t data); //отправка байта
void UART_print(char data[]);   //отправка строки
void UART_println(char data[]); //отправка строки с переходом на новую строку
void UART_printInt(int64_t num);    //отправка целого
void UART_printUint(uint64_t num);    //отправка целого беззнакового
uint8_t UART_receive(void); ////прочесть байт
void UART_clearBuff(void); //очистить буфер приема
uint8_t UART_checkRxFlag(void); //проверка флага окончания приема, при чтении сбрасывается
#endif	/* UART_H */

