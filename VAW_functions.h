/* 
 * File:   VAW_functions.h
 * Author: sesdi
 *
 * Created on 16 февраля 2020 г., 21:25
 */

#ifndef VAW_FUNCTIONS_H
#define	VAW_FUNCTIONS_H

#include "main.h"

//#define USE_MEDIAN_FILTER
#define USE_RUNNING_AVG_FILTER

#ifdef USE_MEDIAN_FILTER
#define SAMPLES 3
#endif

#ifdef USE_RUNNING_AVG_FILTER
#define FILTER_COEF 0.4
#endif

#define VOLTAGE_MUX MUX_2_GND
#define CURRENT_MUX MUX_3_GND

int16_t getCurrent(void);
int32_t getVoltage(void);
void sortArray(int16_t array[], uint8_t size);
#ifdef USE_MEDIAN_FILTER
int16_t getMedian(int16_t array[], uint8_t size);
#endif
#ifdef USE_RUNNING_AVG_FILTER
float getRunningAvgV(int16_t unfilteredVal);
float getRunningAvgC(int16_t unfilteredVal);
#endif

#endif	/* VAW_FUNCTIONS_H */

