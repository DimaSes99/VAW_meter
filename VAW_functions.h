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
#define FILTER_COEF 0.5
#endif

#define VOLTAGE_MUX MUX_2_GND
#define CURRENT_MUX MUX_3_GND

int16_t getCurrent(void);   //returns current in mA
int32_t getVoltage(void);   //returns voltage in mV
#ifdef USE_MEDIAN_FILTER
void sortArray(int16_t array[], uint8_t size);  
int16_t getMedian(int16_t array[], uint8_t size);
#endif
#ifdef USE_RUNNING_AVG_FILTER
typedef enum{
VOLTAGE_AVG, CURRENT_AVG}running_avg_t;
float getRunningAvg(int16_t unfilteredVal, running_avg_t type); //running average filter
#endif

#endif	/* VAW_FUNCTIONS_H */

