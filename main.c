/* 
 * File:   main.c
 * Author: sesdi
 *
 * Created on 16 февраля 2020 г., 20:45
 */

#include "main.h"



/*
 * 
 */

int main() {
    //timer0_initFiveMsPeriod();
    ADS_init(PGA_256|DATA_RATE_16|SINGLE_SHOT_MODE);
    PCD_init();        
    
    while (1) {
//        int16_t current = getCurrent();
//        int16_t voltage =  getVoltage() - (current/100);
//        char buff[7];
//        memset(buff, 0, sizeof(buff));
//        if(voltage < 10000){
//            sprintf(buff, "U=%d.%d", voltage/1000, voltage%1000);
//        } else {
//            sprintf(buff, "U=%d.%d", voltage/1000, (voltage%1000)/10);
//        }
//        PCD_print_10x16(buff, 0, 0);
//        memset(buff, 0, sizeof(buff));
//        if(current < 10000){
//            sprintf(buff, "U=%d.%d", current/1000, current%1000);
//        } else {
//            sprintf(buff, "U=%d.%d", current/1000, (current%1000)/10);
//        }
//        PCD_print_10x16(buff, 0, 1);        
        int16_t voltageRaw = ADS_readSingle(VOLTAGE_MUX);
        int16_t currentRaw = ADS_readSingle(CURRENT_MUX);
        int16_t voltageF = (int16_t)getRunningAvgV(voltageRaw);
        int16_t currentF = (int16_t)getRunningAvgC(currentRaw);
        PCD_setCursor(0, 0);
        PCD_print("U="); PCD_printInt(voltageF); PCD_print("   ");
        PCD_setCursor(0, 1);
        PCD_print("I="); PCD_printInt(currentF);PCD_print("   ");
    }
    return 0;
}
