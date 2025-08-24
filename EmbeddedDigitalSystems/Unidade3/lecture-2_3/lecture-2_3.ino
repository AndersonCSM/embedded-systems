#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

ISR(PCINT0_vect){
  PORTB ^= (1 <<1);
  _delay_ms(100);
}

int main(){
  
  cli();
  
  DDRB |= (1 << 1); // SAIDA
  DDRB &= ~(1 << 0); // ENTRADA
  
  PORTB &= ~(1 << 1); // output low
  PORTB |= (1 << 0); // input pull-up
  
  PCICR |= (1 << 0); // PCIE0 habilitado
  PCMSK0 |= (1 << 0); // PCINT0 (1 << PCINT0)
  
  sei();
  while(1){;;}
  return 0;
}