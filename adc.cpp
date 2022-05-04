#include "adc.h"
#include <avr/io.h>



AdcChannel::AdcChannel(int ch) : channel(ch){
    ADMUX = (1 << REFS0) | (0x0f  & channel);
    ADCSRA  = (1<< ADEN);
}

int AdcChannel::get(){
    
    ADMUX = (ADMUX & 0Xf0) | (0x0f & channel);
    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC));
    
    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC));    
    return ADC;

}