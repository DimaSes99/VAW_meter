#include "VAW_functions.h"

int16_t voltageCalDots[5] = {-46, 5757, 11404, 17128, 22862};
float const voltageCalK[5] = {0.838, 0.839, 0.839, 0.839, 0.838};
float const voltageCalB[5] = {38.541, 31.707, 36.897, 32.075, 62.870};

int16_t currentCalDots[7] = {-48, -4, 45, 394, 828, 1702, 4350};
float const currentCalK[7] = {1.159, 1.122, 1.146, 1.145, 1.141, 1.137, 1.122};
float const currentCalB[7] = {55.636, 55.490, 54.424, 54.806, 58.474, 65.325, 128.009};

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
    if (valFiltered < currentCalDots[0]) {
        current = 0;
    } else if (valFiltered >= currentCalDots[0] && valFiltered < currentCalDots[1]) {
        current = valFiltered * currentCalK[0] + currentCalB[0];
    } else if (valFiltered >= currentCalDots[1] && valFiltered < currentCalDots[2]) {
        current = valFiltered * currentCalK[1] + currentCalB[1];
    } else if (valFiltered >= currentCalDots[2] && valFiltered < currentCalDots[3]) {
        current = valFiltered * currentCalK[2] + currentCalB[2];
    } else if (valFiltered >= currentCalDots[3] && valFiltered < currentCalDots[4]) {
        current = valFiltered * currentCalK[3] + currentCalB[3];
    } else if (valFiltered >= currentCalDots[4] && valFiltered < currentCalDots[5]) {
        current = valFiltered * currentCalK[4] + currentCalB[4];
    } else if (valFiltered >= currentCalDots[5] && valFiltered < currentCalDots[6]) {
        current = valFiltered * currentCalK[5] + currentCalB[5];
    } else {
        current = valFiltered * currentCalK[6] + currentCalB[6];
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
    float valFiltered = (float) getRunningAvgV(ADS_readSingle(VOLTAGE_MUX)); //медиана
#endif
    float voltage;
    if (valFiltered < voltageCalDots[0]) { //преобразование и интерполяция
        voltage = 0;
    } else if (valFiltered >= voltageCalDots[0] && valFiltered < voltageCalDots[1]) {
        voltage = valFiltered * voltageCalK[0] + voltageCalB[0];
    } else if (valFiltered >= voltageCalDots[1] && valFiltered < voltageCalDots[2]) {
        voltage = valFiltered * voltageCalK[1] + voltageCalB[1];
    } else if (valFiltered >= voltageCalDots[2] && valFiltered < voltageCalDots[3]) {
        voltage = valFiltered * voltageCalK[2] + voltageCalB[2];
    } else if (valFiltered >= voltageCalDots[3] && valFiltered < voltageCalDots[4])  {
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