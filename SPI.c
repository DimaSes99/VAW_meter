#include "SPI.h"

void SPI_Init(){
    DDRB |= (1<<PB3) | (1<<PB5) | (1<<PB2);    // mosi & sck & ss as output
    SPCR |= (1<<SPE) | (1<<MSTR);
    
}

void SPI_Send_byte(uint8_t data){
    SPCR |= (1<<SPE);
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
    SPCR &= ~(1<<SPE);
}