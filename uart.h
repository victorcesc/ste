#ifndef __UART_H__
#define __UART_H__
#include <avr/io.h>




class Uart
{
public:
    Uart(unsigned long baud){
        //UBRR0H = (unsigned char)(baud >> 8);
        //UBRR0 = freq/16/baud;//???
        UBRR0 = 51;//PARA 9600 8MHZ
        //UBRR0L = (unsigned char)baud;
        /* Enable receiver and transmitter */
        UCSR0B |= (1<<3);
        /* Set frame format: 8data, 2stop bit */
        UCSR0C |= (3<<1);
    }
    ~Uart();

    void put(const char c){
        while(!(UCSR0A  & (UDRE0)))
        UDR0 = c;
    }
    char get();

private:
    static const unsigned long freq = 8e6;
    
};

#endif /* __UART_H__ */
