// main.cpp - aula 1
#include <stdio.h>

// LED - PB5 - Arduino 13
// BTN - PD2 - Arduino 2

//to compile : avr-gcc -mmcu=atmega328p file -o output

int led_pin = 5;

unsigned char *ddrb = (unsigned char *) 0x24;//0x24 endereco de memoria
unsigned char *pinb = (unsigned char *) 0x23;
unsigned char *portb = (unsigned char *) 0x25;


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
//   pinMode(LED_BUILTIN, OUTPUT);
    *ddrb = ~( 1 << led_pin );  // 1101 1111
   
}

void delay1000(){
  unsigned long x = 0x7ffff;
  while(x--);  
} 

void ledOn(){
    *portb = (1 << led_pin);
}


void ledOff(){
    *portb = ~(1 << led_pin);
}



// the loop function runs over and over again forever
void loop() {
  ledOn();   // turn the LED on (HIGH is the voltage level)
//  delay(1000);
  delay1000();// wait for a second
  ledOff();    // turn the LED off by making the voltage LOW
  delay1000();
//  delay(1000);                       // wait for a second
}


int main(void){
  setup();
  while(true)
  {
      loop();
  }

}