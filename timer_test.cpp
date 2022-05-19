#include <avr/interrupt.h>
#include <stdio.h>
#include "gpio_pin.h"
#include "queue.h"
#include "uart.h"
#include "adc.h"
#include "timer.h"

Uart uart(9600);
//port b 0x24 0x23 0x25
Timer timer;



void setup() {
  uart.puts("Setup\n");
  //calibratePot();
}   // 0xfc = 1111 1100


void delay1000(){
  Microseconds d = 100000;
  Microseconds end = timer.micros() + d;
  while (timer.micros() < end);  
   
} 


int count = 0;
char buffer[32];
void loop() {
    sprintf(buffer,"%d\n",count++);
    uart.puts(buffer);
    //readAdc0();
    delay1000();
}




int main(void){
  //setup();
  while(true)
  {
      loop();
  }

}