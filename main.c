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
    PCD_init();
    ADS_init(PGA_256|DATA_RATE_16|SINGLE_SHOT_MODE);
    while (1) {
        int16_t current = getCurrent();
        int16_t voltage =  getVoltage() - (current/100);
        PCD_setCursor(0, 0);
        PCD_print("U=");
        PCD_printInt(voltage);
        PCD_print("   ");
        
        PCD_setCursor(0, 1);
        PCD_print("I=");
        PCD_printInt(current);
        PCD_print("   ");
        
    }
    return 0;
}

