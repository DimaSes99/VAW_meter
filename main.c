/* 
 * File:   main.c
 * Author: sesdi
 *
 * Created on 16 февраля 2020 г., 20:45
 */

#include "main.h"
#define DISPLAY_REINIT_PERIOD_MS 1000


/*
 * 
 */

int main() {
    timer0_initFiveMsPeriod();
    ADS_init(PGA_256|DATA_RATE_8|SINGLE_SHOT_MODE);
    PCD_init();  
    PCD_Clrscr();
    while (1) {
        static uint64_t counter = 0;
        if (getUptime() - counter >= DISPLAY_REINIT_PERIOD_MS){
            counter = getUptime();
            PCD_reinit();
        }
        int16_t current = getCurrent();
        int16_t voltage =  getVoltage() - (current/100);
        int32_t power = ((int32_t)voltage*(int32_t)current)/(int32_t)1000; 
        char buff[7];
        memset(buff, 0, sizeof(buff));
        if(voltage < 10){
            sprintf(buff, "U=0.00%d", voltage%1000);
        } else if(voltage < 100){
            sprintf(buff, "U=0.0%d", voltage%1000);
        } else if(voltage < 10000){
            sprintf(buff, "U=%d.%d", voltage/1000, voltage%1000);
        } else {
            sprintf(buff, "U=%d.%d", voltage/1000, (voltage%1000)/10);
        }
        PCD_print_10x16(buff, 0, 0);
        
        memset(buff, 0, sizeof(buff));
        if(current < 10){
            sprintf(buff, "I=0.00%d", current%1000);
        } else if(current < 100){
            sprintf(buff, "I=0.0%d", current%1000);
        } else if(current < 10000){
            sprintf(buff, "I=%d.%d", current/1000, current%1000);
        } else {
            sprintf(buff, "I=%d.%d", current/1000, (current%1000)/10);
        }
        PCD_print_10x16(buff, 0, 1);   
        
        memset(buff, 0, sizeof(buff));
        int16_t powerInt = power/1000;
        int16_t powerFract;
        if(power < 10){
            powerFract = power%1000;
            sprintf(buff, "P=0.00%d", powerFract);
        } else if(power < 100){
            powerFract = power%1000;
            sprintf(buff, "P=0.0%d", powerFract);
        } else if(power < 10000){
            powerFract = (power%1000);
            sprintf(buff, "P=%d.%d", powerInt, powerFract);
        } else if (power < 100000){
            powerFract = (power%1000)/10;
            sprintf(buff, "P=%d.%d", powerInt, powerFract);
        } else {
            powerFract = (power%1000)/100;
            sprintf(buff, "P=%d.%d", powerInt, powerFract);
        }
        PCD_print_10x16(buff, 0, 2);    
        
//        int16_t voltageRaw = ADS_readSingle(VOLTAGE_MUX);
//        int16_t currentRaw = ADS_readSingle(CURRENT_MUX);
//        int16_t voltageF = (int16_t)getRunningAvgV(voltageRaw);
//        int16_t currentF = (int16_t)getRunningAvgC(currentRaw);
//        PCD_setCursor(0, 0);
//        PCD_print("U="); PCD_printInt(voltageF); PCD_print("   ");
//        PCD_setCursor(0, 1);
//        PCD_print("I="); PCD_printInt(currentF);PCD_print("   ");
        
    }
    return 0;
}
