#include "uart.h"
#include <avr/io.h>




Uart::Uart(unsigned long baud)
{
        UBRR0 = freq/16/baud;//???
        //UBRR0 = 51;//PARA 9600 8MHZ
        //UBRR0L = (unsigned char)baud;
        /* Enable receiver and transmitter */
        UCSR0B = (1 << TXEN0);
        /* Set frame format: 8data, 2stop bit */
        UCSR0C = (3 << UCSZ00);
}

Uart::~Uart()
{
}

void Uart::put(const char c)
{
    tx_fifo.enqueue(c);

    // while(!(UCSR0A  & (1 << UDRE0))); 
    // UDR0 = c;
}


void Uart::udre_handler(){
    if(tx_fifo.length() > 0){
        UDR0 = tx_fifo.dequeue();
    }else{

        //desligar interrupcao udre
    }
}

ISR(USART_UDRE_vect){
    UCSR0A = (1 << UDRE0);
}

void Uart::puts(const char *s){
    do{
        put(*s);
    }while(*(++s));
}


char Uart::get()
{

}
