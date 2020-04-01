/* 
 * File:   ADS1115.h
 * Author: sesdi
 *
 * Created on 11 февраля 2020 г., 19:36
 */

#ifndef ADS1115_H
#define	ADS1115_H
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
#define ALLERT_GPIO PD2
#define ALLERT_PIN  PIND
#define ALLERT_DDR  DDRD
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//TWI адрес
#define ADS_WRITE_ADDRESS 0b10010000
#define ADS_READ_ADDRESS  0b10010001
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//Значения для address pointer
#define ADS_CONV_REG_ADDR  0b00000000
#define ADS_CONF_REG_ADDR  0b00000001
#define ADS_LOTHR_REG_ADDR 0b00000010
#define ADS_HITHR_REG_ADDR 0b00000011
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//параметры для config register
#define START_S_CONV (0x0001<<15)
//Мультиплексор
#define MUX_0_1      (0x0000<<12)
#define MUX_0_3      (0x0001<<12)
#define MUX_1_3      (0x0002<<12)
#define MUX_2_3      (0x0003<<12)
#define MUX_0_GND    (0x0004<<12)
#define MUX_1_GND    (0x0005<<12)
#define MUX_2_GND    (0x0006<<12)
#define MUX_3_GND    (0x0007<<12)
//Усилитель
#define PGA_6144     (0x0000<<9)
#define PGA_4096     (0x0001<<9)
#define PGA_2048     (0x0002<<9)
#define PGA_1024     (0x0003<<9)
#define PGA_512      (0x0004<<9)
#define PGA_256      (0x0005<<9)
//Режим работы
#define CONTINUOUS_CONV_MODE (0x0000<<8)
#define SINGLE_SHOT_MODE     (0x0001<<8)
//Скорость преобразований
#define DATA_RATE_8   (0x0000<<5)
#define DATA_RATE_16  (0x0001<<5)
#define DATA_RATE_32  (0x0002<<5)
#define DATA_RATE_64  (0x0003<<5)
#define DATA_RATE_128 (0x0004<<5)
#define DATA_RATE_250 (0x0005<<5)
#define DATA_RATE_475 (0x0006<<5)
#define DATA_RATE_860 (0x0007<<5)

#define COMP_MODE_TRADIT (0x0000<<4)
#define COMP_MODE_WINDOW (0x0001<<4)

#define COMP_POL_L (0x0000<<3)
#define COMP_POL_H (0x0001<<3)

#define COMP_LAT_NONL (0x0000<<2)
#define COMP_LAT_L    (0x0001<<2)

#define COMP_QUE_1CONV (0x0000<<0)
#define COMP_QUE_2CONV (0x0001<<0)
#define COMP_QUE_4CONV (0x0002<<0)
#define COMP_DISABLE   (0x0003<<0)

/*
 0 - check OS bit to wait end of conversion
 1 - check ALLERT pin to wait end of conversion
 */
#define USE_ALERT_PIN 0

#include "main.h"
uint8_t ADS_init(uint16_t confReg); //инициализация АЦП
uint16_t ADS_readReg(uint8_t regAddress);   //читает регистр по адресу
void ADS_writeReg(uint8_t regAddress, uint16_t regValue);   //пишет данные по адресу
void ADS_setMUX(uint16_t mux);  //установка мультеплексора
void ADS_startSingleConv(void); //начать одиночное преобразование
int16_t ADS_readConvReg(void);  //прочесть результат преобразования
uint8_t ADS_convReady(void);    //проверяет готовность преобразования
int16_t ADS_readSingle(uint16_t mux);
#endif	/* ADS1115_H */

