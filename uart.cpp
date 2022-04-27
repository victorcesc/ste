#include "uart.h"



Uart::Uart(unsigned long baud)
{
    UBRR0L = freq/16/baud;
}

Uart::~Uart()
{
}

void Uart::put(const char c)
{

}

char Uart::get()
{

}
