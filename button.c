#include "button.h"

uint16_t btnPressCountCycles = 0;   
uint8_t btnState = 0;   
uint8_t prevBtnState = 0;   
uint8_t btnPressCount = 0;     
uint8_t readyToReadFlag = 1;    
void Btn_init(){
    BUTTON_DDR &= ~(1<<BUTTON_GPIO);
    BUTTON_PORT |= (1<<BUTTON_GPIO); //pullup 
}
uint8_t Read_btn(void){
    return ((BUTTON_PIN & (1<<BUTTON_GPIO)) == 0);
}
uint8_t Btn_press(void){
    if((readyToReadFlag == 1) && (btnPressCount == 1) ){
        btnPressCount = 0; 
        return 1;
    } else {
        return 0;
    }
}
uint8_t Btn_release(void){
    if(btnState == 0 && prevBtnState == 1){
        return 1;
    } else {
        return 0;
    }    
}
uint8_t Btn_hold(void){
    if(btnPressCountCycles >= 100){    
        return 1;
    } else {
        return 0;
    }
}
uint8_t Btn_double_press(void){
        if((readyToReadFlag == 1) && (btnPressCount == 2) ){
        btnPressCount = 0; 
        return 1;
    } else {
        return 0;
    }
}
void Reset_btn_press_count(void){
    if(readyToReadFlag == 1){
        btnPressCount = 0;
    }
}
void Btn_handler(void){
    static uint8_t clickTimeoutTimer = 0; 
    prevBtnState = btnState;   
    btnState = Read_btn();  
    if(btnState == 1 && prevBtnState == 1){ 
        btnPressCountCycles++; 
    } 
    if(Btn_release() && btnPressCountCycles < 50){    
        if (clickTimeoutTimer < 25){ 
            btnPressCount++;    
            clickTimeoutTimer = 0;
            readyToReadFlag = 0;  
        }
        btnPressCountCycles = 0;  
    }
    if(Btn_release()){btnPressCountCycles = 0;}   
    if(clickTimeoutTimer >= 25){
        readyToReadFlag = 1;
        clickTimeoutTimer = 0;
    }
    if(readyToReadFlag == 0){clickTimeoutTimer++;}
}

