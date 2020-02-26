#include "UART.h"
char rxBuff[RX_BUFF_SIZE];   //буфер приема
uint8_t rxFlag = 0; //если 1, то прием окончен и данные готовы
ISR(USART_RXC_vect){    //обработка прерываний на прием
    static uint8_t rxIndex = 0; //для заполнения массива
    rxFlag = 0; //прием не окончен, ожидаем еще 
    if (rxIndex == 0) UART_clearBuff();    //очистить буффер перед приемом новых данных
    char incomingChar = UART_receive();
    if (incomingChar != 0x0a){  
        rxBuff[rxIndex] = incomingChar;
        rxIndex++;
    } else {    //если обнаружен конец строки(LF line end)
        rxBuff[rxIndex] = incomingChar; //запись LF в буфер
        rxIndex = 0;
        rxFlag = 1;//прием окончен
    }
}

void UART_init(uint32_t baudrate){
 UBRRH = (unsigned char) (baudrate>>8);     //запись значения в регистр
 UBRRL = (unsigned char) (baudrate);
 
 UCSRA |= (0<<U2X); //удвоение скорости обмена
 UCSRB |= (1<<RXEN)|(1<<TXEN); //разрешить прием и передачу 
 UCSRB |= (1<<RXCIE); //разрешить прерывание по завершению приема
 UCSRC |= (1<<URSEL)|(1<<USBS)|(1<<UCSZ0)|(1<<UCSZ1); //8 бит, 2 стоп бита, без контроля четности
 
 UART_clearBuff();
 sei();
}

void UART_transmitByte(uint8_t data){//отправка байта
    while(!(UCSRA & (1<<UDRE)));//подождать конец передачи данных
    UDR = data; //отправить данные
}

void UART_print(char data[]){//отправка строки
    uint8_t i = 0;
    while(data[i] != 0x00){
        UART_transmitByte(data[i]);
        i++;
    }
}

void UART_println(char data[]){
    UART_print(data);
    UART_transmitByte(0x0D);    //CR
    UART_transmitByte(0x0A);    //LF
}

void UART_printInt(int64_t num){//отправка целого
    char numString [20]; //масив символов для отправки
    if (num == 0){
        UART_transmitByte('0');
        return;
    }
    if (num < 0){   //если отрицательное число
        UART_transmitByte('-');    //первый знак "-"
        num *= -1;  //делаем число положительным и обрабатываем как обычно
    }
    for(uint8_t i = 0; i < sizeof(numString) - 1; i++){ //
        numString[i] = 0;
    }
    int64_t div = 1;
    uint8_t counter = 19;   //заполняем массив с конца
    while ((num / div != 0)&&(counter!=0) ){ //раскладываем число на цифры 
        numString[counter] = ((num / div) % 10) + '0';
        div *= 10;
        counter--;
    }
    /*Так как заполнение масива происходит с конца, то число в массиве
     смещено в конец (256 = 000...00256). Чтобы не выводить лишние нули
     сместим все влево
     */
    uint8_t notZero = 0;
    while(numString[notZero] == 0){   //найти первый не 0
        notZero++;
    }
    for(uint8_t i = 0; i < sizeof(numString) - notZero; i++){   //смещаем   
        numString[i] = numString[i + notZero];
        numString[i + notZero] = 0;
    }
    UART_print(numString);  //выводим
}

void UART_printUint(uint64_t num){//отправка целого
    char numString [21]; //масив символов для отправки
    if (num == 0){
        UART_transmitByte('0');
        return;
    }
    for(uint8_t i = 0; i < sizeof(numString) - 1; i++){ //
        numString[i] = 0;
    }
    uint64_t div = 1;
    uint8_t counter = 20;   //заполняем массив с конца
    while ((num / div != 0)&&(counter!=0) ){ //раскладываем число на цифры 
        numString[counter] = ((num / div) % 10) + '0';
        div *= 10;
        counter--;
    }
    /*Так как заполнение масива происходит с конца, то число в массиве
     смещено в конец (256 = 000...00256). Чтобы не выводить лишние нули
     сместим все влево
     */
    uint8_t notZero = 0;
    while(numString[notZero] == 0){   //найти первый не 0
        notZero++;
    }
    for(uint8_t i = 0; i < sizeof(numString) - notZero; i++){   //смещаем   
        numString[i] = numString[i + notZero];
        numString[i + notZero] = 0;
    }
    UART_print(numString);  //выводим
}

uint8_t UART_receive(void){//прочесть байт
    while(!(UCSRA &(1<<RXC)));
    return UDR;
}

void UART_clearBuff(){//очистить буфер приема
    for(int i = 0; i < sizeof(rxBuff) - 1; i++){
        rxBuff[i] = 0;  //заполнить нулями
    }
}

uint8_t UART_checkRxFlag(void){//проверка флага окончания приема
    if (rxFlag == 1){   //если данные готовы
        rxFlag = 0; //сбросить флаг
        return 1;
    } else {
        return 0;  
    }
}