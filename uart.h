#ifndef __UART_H__
#define __UART_H__




class Uart
{
public:
    Uart(unsigned long baud);
    ~Uart();

    void put(const char c);
    void puts(const char *s);
    char get();

private:
    static const unsigned long freq = 16e6;
    
};

#endif /* __UART_H__ */
