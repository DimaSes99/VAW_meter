/* 
 * File:   timer.h
 * Author: sesdi
 *
 * Created on 31 марта 2020 г., 12:00
 */

#ifndef TIMER_H
#define	TIMER_H

#include "main.h"

typedef enum{
    NO_CLK, DIV_1, DIV_8, DIV_64, DIV_256, DIV_1024, EXT_CLK_FALLING_EDGE, EXT_CLK_RISING_EDGE
}timer_prescaler_t;   //prescaler values

void timer0_init(timer_prescaler_t prsc, uint8_t tcntInitVal);   //timer 0 init funclion
void timer0_initOneMsPeriod(void);  //overflow interupt every 1 ms
void timer0_initTwoMsPeriod(void);  //overflow interupt every 2 ms
void timer0_initFiveMsPeriod(void);  //overflow interupt every 5 ms

uint64_t getUptime(void);

#endif	/* TIMER_H */

