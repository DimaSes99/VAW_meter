/* 
 * File:   VAW_functions.h
 * Author: sesdi
 *
 * Created on 16 февраля 2020 г., 21:25
 */

#ifndef VAW_FUNCTIONS_H
#define	VAW_FUNCTIONS_H

#include "main.h"

#define SAMPLES 10

int16_t getCurrent(void);
int32_t getVoltage(void);
void sortArray(int16_t array[], uint8_t size);
int16_t getMedian(int16_t array[], uint8_t size);
#endif	/* VAW_FUNCTIONS_H */

