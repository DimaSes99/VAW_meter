#include "ADS1115.h"

uint8_t ADS_init(uint16_t confReg) { //записывает 2 байта в конфигурационный регистр
    TWI_init(2, 0);
    ADS_writeReg(ADS_CONF_REG_ADDR, confReg | COMP_QUE_1CONV);
    ADS_writeReg(ADS_HITHR_REG_ADDR, ADS_readReg(ADS_HITHR_REG_ADDR) | 0x0001 << 15);
    ADS_writeReg(ADS_LOTHR_REG_ADDR, ADS_readReg(ADS_LOTHR_REG_ADDR)&~(0x0001 << 15));
#if USE_ALERT_PIN==1
    ALLERT_DDR &= ~(1 << ALLERT_GPIO);
#endif
    return 1;
}

uint16_t ADS_readReg(uint8_t regAddress) {
    TWI_sendStart();
    TWI_sendByte(ADS_WRITE_ADDRESS);
    TWI_sendByte(regAddress);
    TWI_sendStart();
    TWI_sendByte(ADS_READ_ADDRESS);
    uint8_t MSB = TWI_readByte();
    uint8_t LSB = TWI_readLastByte();
    TWI_sendStop();
    return (uint16_t) (MSB << 8) | (LSB);
}

void ADS_writeReg(uint8_t regAddress, uint16_t regValue) {
    uint8_t MSB = (regValue & 0xFF00) >> 8;
    uint8_t LSB = (regValue & 0x00FF);
    TWI_sendStart();
    TWI_sendByte(ADS_WRITE_ADDRESS);
    TWI_sendByte(regAddress);
    TWI_sendByte(MSB);
    TWI_sendByte(LSB);
    TWI_sendStop();
}

void ADS_setMUX(uint16_t mux) {
    if ((mux == MUX_0_1) || (mux == MUX_0_3) || (mux == MUX_1_3) || (mux == MUX_2_3) ||
            (mux == MUX_0_GND) || (mux == MUX_1_GND) || (mux == MUX_2_GND) || (mux == MUX_3_GND)) {
        uint16_t confReg = ADS_readReg(ADS_CONF_REG_ADDR); //прочесть регистр
        confReg = confReg&~(0x0007 << 12); //сбросить биты мультиплексора
        ADS_writeReg(ADS_CONF_REG_ADDR, confReg | mux); //записать обновленные данные
    } else {
        //оставить все как есть
    }
}

void ADS_startSingleConv(void) {
    uint16_t confReg = ADS_readReg(ADS_CONF_REG_ADDR); //прочесть регистр
    confReg = confReg | START_S_CONV;
    ADS_writeReg(ADS_CONF_REG_ADDR, confReg);
}

int16_t ADS_readConvReg(void) {
    return ((int16_t) ADS_readReg(ADS_CONV_REG_ADDR));
}

uint8_t ADS_convReady(void) {
#if USE_ALERT_PIN==1
    if ((ALLERT_PIN & (1 << ALLERT_GPIO)) != 0) {
        return 0;
    } else {
        return 1;
    }
#else
    if ((ADS_readReg(ADS_CONF_REG_ADDR) & START_S_CONV) == 0) {
        return 0;
    } else {
        return 1;
    }
#endif
}

int16_t ADS_readSingle(uint16_t mux){
    ADS_setMUX(mux);
    ADS_startSingleConv();
    while(ADS_convReady()==0);
    return ADS_readConvReg();
}