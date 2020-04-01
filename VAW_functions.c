#include "VAW_functions.h"


float const voltageCalK[5] = {0.838, 0.840, 0.840, 0.838, 0.839};
float const voltageCalB[5] = {7, -8.619, -6.698, 16.240, -8.595};

float const currentCalK[6] = {1.135, 1.142, 1.136, 1.139, 1.131, 1.105};
float const currentCalB[6] = {13.618, 13.087, 14.221, 12.886, 20.086, 134.374};

int16_t getCurrent(void) {
#ifdef USE_MEDIAN_FILTER
    int16_t currentArr[SAMPLES];
    for (uint8_t i = 0; i < SAMPLES; i++) {
        currentArr[i] = ADS_readSingle(CURRENT_MUX);
    }
    float valFiltered = (float) getMedian(currentArr, SAMPLES); //медиана
#endif
#ifdef USE_RUNNING_AVG_FILTER
    float valFiltered = (float) getRunningAvgC(ADS_readSingle(CURRENT_MUX)); //медиана
#endif
    float current;
    if (valFiltered <= 77) {
        current = valFiltered * currentCalK[0] + currentCalB[0];
    } else if (valFiltered > 77 && valFiltered <= 204) {
        current = valFiltered * currentCalK[1] + currentCalB[1];
    } else if (valFiltered > 204 && valFiltered <= 439) {
        current = valFiltered * currentCalK[2] + currentCalB[2];
    } else if (valFiltered > 439 && valFiltered <= 870) {
        current = valFiltered * currentCalK[3] + currentCalB[3];
    } else if (valFiltered > 870 && valFiltered <= 4429) {
        current = valFiltered * currentCalK[4] + currentCalB[4];
    } else {
        current = valFiltered * currentCalK[5] + currentCalB[5];
    }
    return (int16_t) (current);
}

int32_t getVoltage(void) {
#ifdef USE_MEDIAN_FILTER
    int16_t voltageArr[SAMPLES];
    for (uint8_t i = 0; i < SAMPLES; i++) {
        voltageArr[i] = ADS_readSingle(VOLTAGE_MUX);
    }
    float valFiltered = (float) getMedian(voltageArr, SAMPLES); //медиана
#endif
#ifdef USE_RUNNING_AVG_FILTER
    ADS_startSingleConv();
    while (ADS_convReady() == 0); //дождаться конца преобразования
    float valFiltered = (float) getRunningAvgV(ADS_readSingle(VOLTAGE_MUX)); //медиана
#endif
    float voltage;
    if (valFiltered <= 6004) { //преобразование и интерполяция
        voltage = valFiltered * voltageCalK[0] + voltageCalB[0];
    } else if (valFiltered > 6004 && valFiltered <= 11937) {
        voltage = valFiltered * voltageCalK[1] + voltageCalB[1];
    } else if (valFiltered > 11937 && valFiltered <= 17970) {
        voltage = valFiltered * voltageCalK[2] + voltageCalB[2];
    } else if (valFiltered > 17970 && valFiltered <= 23875) {
        voltage = valFiltered * voltageCalK[3] + voltageCalB[3];
    } else {
        voltage = valFiltered * voltageCalK[4] + voltageCalB[4];
    }
    return (int16_t) (voltage);
}

void sortArray(int16_t array[], uint8_t size) {
    for (uint8_t i = 0; i < size - 1; i++) {
        for (uint8_t j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int16_t temp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = temp;
            }
        }
    }
}
#ifdef USE_MEDIAN_FILTER

int16_t getMedian(int16_t array[], uint8_t size) {
    if (SAMPLES % 2 == 0) { //четное количество элементов
        return ((int32_t) array[(SAMPLES / 2) - 1]+(int32_t) array[SAMPLES / 2]) / 2;
    } else { //нечетное количество элементов
        return array[(SAMPLES - 1) / 2];
    }
}
#endif
#ifdef USE_RUNNING_AVG_FILTER
float getRunningAvgV(int16_t unfilteredVal) {
    static float filteredVal = 0;
    filteredVal += (unfilteredVal - filteredVal)*FILTER_COEF;
    return filteredVal;
}

float getRunningAvgC(int16_t unfilteredVal) {
    static float filteredVal = 0;
    filteredVal += (unfilteredVal - filteredVal)*FILTER_COEF;
    return filteredVal;
}
#endif