#include<avr/interrupt.h>
#include<avr/io.h>
#include<util/delay.h>

volatile int modo = 0;

ISR(INT0_vect){
	modo |= 1;
}


int main(){
  // GREEN YELLOW RED 1 é saida
  DDRB |= ((1 << 3)|(1 << 2)|(1 << 1)); // xxxx_111x
  
  // BUTTON 0 é entrada
  DDRD &= ~(1 << 0); // xxxx_XXX0
  
  
  PORTB &= ~((1 << 3)|(1 << 2)|(1 << 1)); // SET - 0
  PORTD |= (1 << 0); // PULL-UP
  
  EICRA |= (0X3); // mudança em qualque borda 01 |   subida 11
  EIMSK |= (1 << 0); // PCINT0 activate
  
  sei();
  
  while(1){
    int red_time = 600;

    
    
     PORTB |= (1 << 3); // verde  
     PORTB &= ~((1 << 1) | (1 << 2)); // amarelo e vermelho
     _delay_ms(500);
    
    PORTB |= (1 << 2); // amarelo
    PORTB &= ~((1 << 1) | (1 << 3));
     _delay_ms(200);
    
    PORTB |= (1 << 1); // vermelho
    PORTB &= ~((1 << 3) | (1 << 2));
    if (modo){
      red_time = 12000;
      modo = 0;
    }
     _delay_ms(red_time); 
  }
  return 0;
}