#include <avr/interrupt.h>
#include <stdio.h>
#include "gpio_pin.h"
#include "queue.h"
#include "uart.h"
#include "adc.h"
// LED - PB5 - Arduino 13
// BTN - PD2 - Arduino 2

//to compile : avr-gcc -mmcu=atmega328p file -o output

Uart uart(9600);
//port b 0x24 0x23 0x25
AdcChannel adc0(0);


void setup() {
  uart.puts("Setup\n");
}   // 0xfc = 1111 1100


void delay1000(){
  unsigned long x = 0x7ffff;
  while(x--);  
} 

void readAdc0(){
  int val = adc0.get();
  char buffer[10];
  sprintf(buffer,"%d\n", val);
  uart.puts(buffer);
}
// the loop function runs over and over again forever
void loop() {    
    readAdc0();
    delay1000();
}




int main(void){
  //setup();
  while(true)
  {
      loop();
  }

}