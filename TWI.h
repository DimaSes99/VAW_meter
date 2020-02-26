/* 
 * File:   TWI.h
 * Author: sesdi
 *
 * Created on 12 января 2020 г., 16:51
 */

#ifndef TWI_H
#define	TWI_H

#include "main.h"
void TWI_errorHandler(void);
void TWI_init(uint8_t twbr, uint8_t twps);
void TWI_sendByte(uint8_t);
void TWI_sendStart(void);
void TWI_sendStop(void);
uint8_t TWI_readByte(void);
uint8_t TWI_readLastByte(void);
#endif	/* TWI_H */

