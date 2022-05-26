#ifndef __UART_H__
#define __UART_H__
#include "queue.h"



class Uart
{
public:
    Uart(unsigned long baud);
    ~Uart();

    void put(const char c);
    void puts(const char *s);
    char get();
    void udre_handler();
private:
    static const unsigned long freq = 16e6;
    Fifo<16 , unsigned char> tx_fifo;
};

#endif /* __UART_H__ */
