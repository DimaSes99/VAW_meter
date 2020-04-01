#include "timer_0.h"

volatile uint8_t timerInitValue = 0; // compare match vice versa
volatile uint64_t uptime = 0;

typedef enum {
    CUSTOM_PERIOD,
    ONE_MS = 1,
    TWO_MS = 2,
    FIVE_MS = 5
} timer_period_t;
volatile timer_period_t timer0_period; //timer period

void timer0_init(timer_prescaler_t prsc, uint8_t initVal) {
    
    TCCR0 |= (1 << CS00) | (1 << CS02); //set prescaler
    timerInitValue = initVal; //set initial value
    TIMSK |= (1<<TOIE0); // overflow interupt 
    TCNT0 = timerInitValue; // start counting from this value
    sei();
}

void timer0_initOneMsPeriod(void) {
    timer0_init(DIV_1024, 248);
    timer0_period = ONE_MS;
}

void timer0_initTwoMsPeriod(void) {
    timer0_init(DIV_1024, 241);
    timer0_period = TWO_MS;
}

void timer0_initFiveMsPeriod(void) {
    timer0_init(DIV_1024, 219);
    timer0_period = FIVE_MS;
}

uint64_t getUptime(void) {
    return uptime;
}

ISR(TIMER0_OVF_vect) {
    TCNT0 = timerInitValue; // start counting from this value
    if (timer0_period != CUSTOM_PERIOD) {
        uptime += timer0_period; 
    } else {
        //uptime do not work
    }
}