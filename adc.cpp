#include "adc.h"
#include <avr/io.h>



AdcChannel::AdcChannel() : channel(ch){
    ADMUX = 0x0f  & ch;
    ADCRSA  = (1<< ADEN);
}

int AdcChannel::get(){
    ADMUX = 0x0f & channel;
    ADCRSA  = (1<< ADEN) | (1 << ADSC);

    while (ADCRSA & (1 << ADSC));
    return ADC;

}