#include "TWI.h"
//#include "UART.h"
#include<sys/../util/twi.h>

uint8_t err = 0;

void TWI_errorHandler(void){
    char hexStr [6] = "ABCDEF";
    char outStr [2];
    if((TWSR & 0xF8)%16 < 10){
        outStr[1] = ((TWSR & 0xF8)%16) + '0';
    } else {
        outStr[1] = hexStr[((TWSR & 0xF8)%16)-10];
    }
    if((TWSR & 0xF8)/16 < 10){
        outStr[0] = ((TWSR & 0xF8)/16) + '0';
    } else {
        outStr[0] = hexStr[((TWSR & 0xF8)/16)-10];
    }
    //UART_Transmit_string("Ther is an error! Code: 0x");
    //UART_Transmit_string(outStr);   //код ошибки в hex
    //UART_Transmit_byte('\n');
    err++;
}
void TWI_init(uint8_t twbr, uint8_t twps){
    TWBR = twbr; 
    if(twps<4){TWSR |= twps;}
}
void TWI_sendByte(uint8_t byte){
    if(!err){
        TWDR = byte;
        TWCR = (1<<TWINT) | (1<<TWEN);
        while (!(TWCR & (1<<TWINT)));
        if(((TWSR & 0xF8)!=TW_MT_DATA_ACK) && //data transmitted
           ((TWSR & 0xF8)!=TW_MR_SLA_ACK)  && //SLA+R transmitted
           (((TWSR & 0xF8)!=TW_MT_SLA_ACK)))  //SLA+W transmitted
        {TWI_errorHandler();}   
    }
}
void TWI_sendStart(void){
    if(!err){
        TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
        while(!(TWCR & (1<<TWINT)));
        if(((TWSR & 0xF8)!=TW_START) && ((TWSR & 0xF8)!=TW_REP_START)){TWI_errorHandler();}
    }
}
void TWI_sendStop(void){
    if(!err){
        TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
        
    }
}
uint8_t TWI_readByte(void){
    if(!err){
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);//включим прием данных
        while(!(TWCR & (1<<TWINT)));//подождем пока установится TWIN
        if((TWSR & 0xF8)!=TW_MR_DATA_ACK){TWI_errorHandler();}
    }
    return TWDR;
}
uint8_t TWI_readLastByte(void){
    if(!err){
        TWCR = (1<<TWINT)|(1<<TWEN);//включим прием данных
        while(!(TWCR & (1<<TWINT)));//подождем пока установится TWIN
        if((TWSR & 0xF8)!=TW_MR_DATA_NACK	){TWI_errorHandler();}
    }
    return TWDR;
}