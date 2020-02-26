#include "VAW_functions.h"

float voltageCalK[5] = {0.838, 0.840, 0.840, 0.838, 0.839};
float voltageCalB[5] = {7, -8.619, -6.698, 16.240, -8.595};

float currentCalK[6] = {1.135, 1.142, 1.136, 1.139, 1.131, 1.105};
float currentCalB[6] = {13.618, 13.087, 14.221, 12.886, 20.086, 134.374};

int16_t getCurrent(void){
    int16_t currentArr[SAMPLES];
    ADS_setMUX(MUX_3_GND);
    for(uint8_t i = 0; i < SAMPLES; i++){
        ADS_startSingleConv();
        while(ADS_convReady()==0);  //дождаться конца преобразования
        currentArr[i]=ADS_readConvReg();
    }
    float median = (float)getMedian(currentArr, SAMPLES);   //медиана
    float current;
    if(median <= 77){
        current = median*currentCalK[0] + currentCalB[0];
    }else if(median>77 && median<=204){
        current = median*currentCalK[1] + currentCalB[1];
    }else if(median>204 && median<=439){
        current = median*currentCalK[2] + currentCalB[2];
    }else if(median>439 && median<=870){
        current = median*currentCalK[3] + currentCalB[3];
    }else if(median>870 && median<=4429){
        current = median*currentCalK[4] + currentCalB[4];
    }else{
        current = median*currentCalK[5] + currentCalB[5];
    }
    
    return (int16_t)(current);
}
int32_t getVoltage(void){
    int16_t voltageArr[SAMPLES];
    ADS_setMUX(MUX_2_GND);
    for(uint8_t i = 0; i < SAMPLES; i++){
        ADS_startSingleConv();
        while(ADS_convReady()==0);  //дождаться конца преобразования
        voltageArr[i]=ADS_readConvReg();
    }
    float median = (float)getMedian(voltageArr, SAMPLES);   //медиана
    float voltage;
    if(median <= 6004){    //преобразование и интерполяция
        voltage = median*voltageCalK[0] + voltageCalB[0];
    } else if(median>6004 && median<=11937){
        voltage = median*voltageCalK[1] + voltageCalB[1];
    } else if(median>11937 &&median<=17970){
        voltage = median*voltageCalK[2] + voltageCalB[2];
    } else if(median>17970 && median<=23875){
        voltage = median*voltageCalK[3] + voltageCalB[3];
    } else {
        voltage = median*voltageCalK[4] + voltageCalB[4];
    }
    return (int16_t)(voltage);
}
void sortArray(int16_t array[], uint8_t size){
    for(uint8_t i = 0; i < size-1; i++){
        for(uint8_t j = 0; j < size-i-1; j++){
            if(array[j]>array[j+1]){
                int16_t temp = array[j+1];
                array[j+1] = array[j];
                array[j] = temp;
            }
        }
    }
}
int16_t getMedian(int16_t array[], uint8_t size){
    if(SAMPLES%2 == 0){ //четное количество элементов
        return ((int32_t)array[(SAMPLES/2)-1]+(int32_t)array[SAMPLES/2])/2; 
    } else { //нечетное количество элементов
        return array[(SAMPLES-1)/2];
    }
}