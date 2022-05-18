#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
   
Timer * Timer::_singleton = 0;

Timer::Timer(){
    
    if (_singleton == 0){
        /* erro */
    }
    _singleton = this;

    microseconds = 0;
    TCCR0B = (1 << CS01);
    //WGM01 = 1;
    TCCR0A = (1 << WGM01);
    OCR0A = 99;
    TIMSK0 = (1 << OCIE0A);
}

// fint = fclk/[2 x div x (1+cmp)]
// "div" can be 1,8,64,256,1024
// cmp = ftimer/fint = fclk/(div x fint)
// fint = 10khz
// div set by 8 
// cmp = 99 p 8mhz 199 p 16mhz
// Tint = 100x10-6


Timer::~Timer(){
    TCCR0A = 0;
    TCCR0B = 0;
}


Microseconds Timer::micros(){
    return microseconds
}

void Timer::handleIsr(){
    microseconds += 100;

}

ISR(TIMER0_COMPA_vect){
    Timer::singleton()->handleIsr();
}