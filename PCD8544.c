#include "PCD8544.h"

#define FUNCTION_SET (1<<5)
    #define ACTIVE_MODE 0
    #define POWER_DOWN_MODE (1<<3)

    #define HORIZONTAL_ADDRESING 0
    #define VERTICAL_ADDRESING (1<<1)

    #define BASIC_INSTRUCTION 0
    #define EXTENDED_INSTRUCTION (1<<0)

#define DISPLAY_CONTROL (1<<3)
    #define DISPLAY_BLANK 0
    #define NORMAL_MODE (1<<2)
    #define ALL_SEGMENTS_ON (1<<0)
    #define INVERSE_MODE ((1<<0)|(1<<2))

#define SET_Y_ADDRESS (1<<6)
#define SET_X_ADDRESS (1<<7)

#define TEMPERATURE_CONTROL (1<<2)
#define BIAS_SYSTEM (1<<4)
#define SET_VOP (1<<7)

static const char ASCII_5x8[][5] ={
    {0x00, 0x00, 0x00, 0x00, 0x00} // 20  
    ,
    {0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
    ,
    {0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
    ,
    {0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
    ,
    {0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
    ,
    {0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
    ,
    {0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
    ,
    {0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
    ,
    {0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
    ,
    {0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
    ,
    {0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
    ,
    {0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
    ,
    {0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
    ,
    {0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
    ,
    {0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
    ,
    {0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
    ,
    {0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
    ,
    {0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
    ,
    {0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
    ,
    {0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
    ,
    {0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
    ,
    {0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
    ,
    {0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
    ,
    {0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
    ,
    {0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
    ,
    {0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
    ,
    {0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
    ,
    {0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
    ,
    {0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
    ,
    {0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
    ,
    {0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
    ,
    {0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
    ,
    {0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
    ,
    {0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
    ,
    {0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
    ,
    {0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
    ,
    {0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
    ,
    {0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
    ,
    {0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
    ,
    {0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
    ,
    {0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
    ,
    {0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
    ,
    {0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
    ,
    {0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
    ,
    {0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
    ,
    {0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
    ,
    {0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
    ,
    {0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
    ,
    {0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
    ,
    {0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
    ,
    {0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
    ,
    {0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
    ,
    {0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
    ,
    {0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
    ,
    {0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
    ,
    {0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
    ,
    {0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
    ,
    {0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
    ,
    {0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
    ,
    {0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
    ,
    {0x02, 0x04, 0x08, 0x10, 0x20} // 5c ?
    ,
    {0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
    ,
    {0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
    ,
    {0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
    ,
    {0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
    ,
    {0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
    ,
    {0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
    ,
    {0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
    ,
    {0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
    ,
    {0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
    ,
    {0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
    ,
    {0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
    ,
    {0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
    ,
    {0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
    ,
    {0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j 
    ,
    {0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
    ,
    {0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
    ,
    {0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
    ,
    {0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
    ,
    {0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
    ,
    {0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
    ,
    {0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
    ,
    {0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
    ,
    {0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
    ,
    {0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
    ,
    {0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
    ,
    {0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
    ,
    {0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
    ,
    {0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
    ,
    {0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
    ,
    {0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
    ,
    {0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
    ,
    {0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
    ,
    {0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
    ,
    {0x10, 0x08, 0x08, 0x10, 0x08} // 7e ?
    ,
    {0x78, 0x46, 0x41, 0x46, 0x78} // 7f ?
};

void PCD_sendCommand(uint8_t byte) {
    CE_PORT &= ~(1 << CE_GPIO); //enable chip
    DC_PORT &= ~(1 << DC_GPIO); //command 
    SPI_Send_byte(byte);
    CE_PORT |= (1 << CE_GPIO); //disable chip
}

void PCD_sendData(uint8_t byte) {
    CE_PORT &= ~(1 << CE_GPIO); //enable chip
    DC_PORT |= (1 << DC_GPIO); //data
    SPI_Send_byte(byte);
    CE_PORT |= (1 << CE_GPIO); //disable chip
}

void PCD_Clrscr() {
    for (uint32_t i = 0; i < 504; i++) {
        PCD_sendData(0x00);
    }
}

void PCD_init() {
    SPI_Init();

    CE_DDR |= (1 << CE_GPIO); // init pins as output
    DC_DDR |= (1 << DC_GPIO);
    RST_DDR |= (1 << RST_GPIO);

    LIGHT_DDR |= (1 << LIGHT_GPIO);
    /*timer 1 settings:
     *Fast PWM 8 bit on OC1B
     *No prescaler 
     */
    TCCR1A |= (1<<COM1B1)|(1<<COM1B0)|(1<<WGM10); 
    TCCR1B |= (1<<WGM12)|(1<<CS10);
    OCR1B = 0;

    CE_PORT |= (1 << CE_GPIO); // rst & ce active LOW
    RST_PORT |= (1 << RST_GPIO);

    RST_PORT &= ~(1 << RST_GPIO); //reset chip 
    RST_PORT |= (1 << RST_GPIO);
    
    PCD_sendCommand(FUNCTION_SET|BASIC_INSTRUCTION);
    PCD_sendCommand(DISPLAY_CONTROL|NORMAL_MODE);
    PCD_sendCommand(FUNCTION_SET|EXTENDED_INSTRUCTION|HORIZONTAL_ADDRESING); 
    PCD_sendCommand(TEMPERATURE_CONTROL|0);
    PCD_sendCommand(BIAS_SYSTEM|3);
    PCD_sendCommand(SET_VOP|75);
    //PCD_Clrscr();
}

void PCD_reinit(){
    RST_PORT &= ~(1 << RST_GPIO); //reset chip 
    RST_PORT |= (1 << RST_GPIO);

    PCD_sendCommand(FUNCTION_SET|BASIC_INSTRUCTION);
    PCD_sendCommand(DISPLAY_CONTROL|NORMAL_MODE);
    PCD_sendCommand(FUNCTION_SET|EXTENDED_INSTRUCTION|HORIZONTAL_ADDRESING); 
    PCD_sendCommand(TEMPERATURE_CONTROL|0);
    PCD_sendCommand(BIAS_SYSTEM|3);
    PCD_sendCommand(SET_VOP|75);
}

void PCD_setBacklightLevel(uint8_t level){
    OCR1B = level;
}

uint8_t PCD_readBacklightLevel(void){
    return OCR1B;
}

void PCD_setRAMpos(uint8_t x, uint8_t y) {
    PCD_sendCommand(FUNCTION_SET|BASIC_INSTRUCTION); 
    if ((x >= 0 && x <= 83) && (y >= 0 && y <= 5)) {
        PCD_sendCommand(SET_X_ADDRESS | x);
        PCD_sendCommand(SET_Y_ADDRESS | y);
    }
}

void PCD_printChar(char c) {
    for (int i = 0; i < 5; i++) {
        PCD_sendData(ASCII_5x8[c - 32][i]);
    }
    PCD_sendData(0x00); //extra space after symbol
}

void PCD_printChar_10x16(char symbol, uint8_t x, uint8_t y) {
    uint16_t output[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (uint8_t i = 0; i < 5; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            if ((ASCII_5x8[symbol - 32][i] & (1 << j)) != 0) {
                output[2 * i] |= (1 << (2 * j)) | (1 << (2 * j + 1));
                output[2 * i + 1] |= output[2 * i];
            }
        }
    }
    for (uint8_t i = 0; i < 10; i++) {
        uint8_t upHalf = output[i] & 0b0000000011111111;
        uint8_t downHalf = output[i] >> 8;
        PCD_setRAMpos(i + x * 11, 2 * y);
        PCD_sendData(upHalf);
        PCD_setRAMpos(i + x * 11, 2 * y + 1);
        PCD_sendData(downHalf);
    }
}
void PCD_print_10x16(char string[], uint8_t x, uint8_t y){
    uint8_t i = 0;
    while (string[i] != 0x00) {
        PCD_printChar_10x16(string[i], i, y);
        i++;
    }
}

void PCD_print(char string[]) {
    uint8_t i = 0;
    while (string[i] != 0x00) {
        PCD_printChar(string[i]);
        i++;
    }
}

void PCD_setCursor(uint8_t x, uint8_t y) {
    if ((x >= 0 && x * 5 <= 80) && (y >= 0 && y <= 5)) {
        PCD_setRAMpos(x * 5, y);
    }
}

void PCD_printInt(int32_t num) {
    char numString [11]; //масив символов
    if (num == 0) {
        PCD_printChar('0');
        return;
    }
    if (num < 0) { //если отрицательное число
        PCD_printChar('-'); //первый знак "-"
        num *= -1; //делаем число положительным и обрабатываем как обычно
    }
    for (uint8_t i = 0; i < sizeof (numString) - 1; i++) {
        numString[i] = 0;
    }
    int32_t div = 1;
    uint8_t counter = 10; //заполняем массив с конца
    while (num / div != 0) { //раскладываем число на цифры 
        numString[counter] = ((num / div) % 10) + '0';
        div *= 10;
        counter--;
    }
    /*Так как заполнение масива происходит с конца, то число в массиве
    смещено в конец (256 = 000...00256). Чтобы не выводить лишние нули
    сместим все влево
     */
    uint8_t notZero = 0;
    while (numString[notZero] == 0) { //найти первый не 0
        notZero++;
    }
    for (uint8_t i = 0; i < sizeof (numString) - notZero; i++) { //смещаем  
        numString[i] = numString[i + notZero];
        numString[i + notZero] = 0;
    }
    PCD_print(numString); //выводим
}