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
//mapear led?
int potMax = 0;
int potMin = 1023;

// void calibratePot(){
//   uart.puts("Calibrando...\n");
//   for(int i=0;i<1000;i++){
//   int pot = analogRead(A0);  
//   if(pot < potMin){
//       potMin = pot;
//   }
//   if(pot > potMax){
//       potMax = pot; 
//   }
  
//   delay(10);
//   }
//   uart.puts("Calibrado!!\n");
// }


int map_led = 255;
int Pmap(int pot){
    int range = (int) pot - potMin + 1;
    int teste = range/map_led;
    int result = pot/teste;
    if(result < 0) return 0;
    else if (result > map_led) return map_led;
    else return 0;        
}


void setup() {
  uart.puts("Setup\n");
  //calibratePot();
}   // 0xfc = 1111 1100


void delay1000(){
  unsigned long x = 0x7ffff;
  while(x--);  
} 

int mVcc = 5000;
void readAdc0(){
  int val = adc0.get();
  int out = val*((double)mVcc/1023);
  char buffer[10];
  sprintf(buffer,"milivolts  %d\n", out);
  //sprintf(buffer,"Digital : %d\n", val);
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