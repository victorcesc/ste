#include <avr/interrupt.h>
// LED - PB5 - Arduino 13
// BTN - PD2 - Arduino 2

//to compile : avr-gcc -mmcu=atmega328p file -o output


//olhar na imagem do datasheet
int led_pin = 5;// pinb5 = port13 arduino
int bot_pin = 2;// pind2 = port2 arduino
volatile int bot = 0 ; // sempre ser buscada em memoria, nunca ser permanentemente salva no registrador


//port b 0x24 0x23 0x25
unsigned char *ddrb = (unsigned char *) 0x24;//0x24 endereco de memoria
unsigned char *pinb = (unsigned char *) 0x23;
unsigned char *portb = (unsigned char *) 0x25;

//port d - 0x29 0x2a 0x2b
unsigned char *ddrd = (unsigned char *) 0x29;//0x24 endereco de memoria
unsigned char *pind = (unsigned char *) 0x2a;
unsigned char *portd = (unsigned char *) 0x2b;

//interrupc

unsigned char *eicra = (unsigned char *) 0x69;
unsigned char *eimsk = (unsigned char *) 0x3d;


void setup() {

    *ddrb = ((*ddrb) | ( 1 << led_pin ));  // 0010 0000 correspondente ao shift de 5 no led 
    *ddrd = ((*ddrd) & ~( 1 << bot_pin ));  // 1111 1011 correspondente ao shift de 2 do botao
    *eicra = ( (*eicra) & 0xf0 | 0x03 ); // (*eicra) & 0xf0 == 1111 0000 
    // zera os quatro da direita e escreve 1111 nos da esq, apos isso faz um | com os dados a serem atribuidos
    *eimsk = ( (*eimsk) & 0xfc | 0x01 );
    sei();
}   // 0xfc = 1111 1100

//ISR(ADC_vect) // nome na tabela do libc
ISR(INT0_vect){
  bot = !bot;
}


void delay1000(){
  unsigned long x = 0x7ffff;
  while(x--);  
} 

void ledOn(){
    *portb = *portb | (1 << led_pin);//mantem os bits da porta e apenas altera o especifico - vale pra todos ^
}


void ledOff(){
    *portb = *portb & ~(1 << led_pin);
}

bool botao(){
  // ler o valor do botao pind
  //  return ( (*pind) & (1 << bot_pin) ) > 0;
  return bot;
  // return botao esta on ou off?
}




// the loop function runs over and over again forever
void loop() {
    botao() ? ledOn() : ledOff();   // turn the LED on (HIGH is the voltage level)
}


int main(void){
  setup();
  while(true)
  {
      loop();
  }

}