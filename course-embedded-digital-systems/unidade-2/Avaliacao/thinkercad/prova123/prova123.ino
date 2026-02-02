#define F_CPU 16000000UL // Defining clock

#include <avr/io.h>     // Including library avr
#include <util/delay.h> // Including library delay
#include <avr/interrupt.h>

volatile uint8_t count = 0; // só conta até 255 [255- 0] achei que dava para converter em binário mais fácil e printar bonitinho
volatile int add, sub;

ISR(INT0_vect)
{
  count++;
}

ISR(INT1_vect)
{
  if (count>0){
    count--;
  }
  
}

//ISR( TIMER0_OVF_vect ){
  //count++; 
//}

uint8_t conversor(uint8_t bin)
{
  bin ^= (bin >> 1);
  return bin;
}

int main(void)
{
  Serial.begin(115200);
  
  DDRB |= (0X3F);                 // set output PB all // OB = xx11_1111 -> DEC = 63 -> OX = 3f
  DDRC |= (0X3);                  // set output PC0, PC1 11 // OB = xxxx_xx11 -> DEC = 3 -> 0X = 3
  DDRD &= ~((1 << 2) | (1 << 3)); // set input PD2 e PD3

  PORTB &= ~(0x3F);               // set low
  PORTC &= ~(0x3);               // set low
  PORTD |= ((1 << 2) | (1 << 3)); // Set pull-up PD2 e PD3

  EICRA |= ((1 << ISC01) | (1 << ISC00) | (1 << ISC11) | (1 << ISC10));
  // EICRA |= (0x15);                      // mudança em borda de subida 0000_1111
  EIMSK |= ((1 << INT0) | (1 << INT1)); // INT0 e INT1  activate
	
  // TCCR0A = 0b00000000; // TC0 (normal operating)
  // TCCR0B = 0b00000010; // TC0 with prescaler 8. Overflow every 128us = 256/(16Mhz/8)
  // TIMSK0 = 0b00000001; // Enabling interrupt TC0 escreve 1 quando tem interrupção
  
  sei();

  // Infinity loop
  while (1)
  {
    uint8_t gray = conversor(count);

    // Saída para PB0–PB5 (bits 0–5 do~p Gray)
    PORTB = (gray & 0x3F); // xxxx_xxxx & 0011_1111 = 00xx_xxxx

    // Saída para PC0 e PC1 (bits 6 e 7 do Gray)
    PORTC = (PORTC & ~0x03) | ((gray >> 6) & 0x03);
    // ~0000_0011 = 1111_1100
    // xxxx_xxxx & 1111_1100 = xxxx_xx00
    // abxx_xxxx >> 6 = xxxx_xxab
    // xxxx_xxab & 0000_0011 = 0000_00ab

    // count++;
    Serial.print("Contador: ");
  	Serial.print(count);
  	Serial.print(" - Gray: ");
  	Serial.println(gray);
    
	
    if (add)
    {
      count++;
      add = 0;
    }
    else if (sub)
    {
      count--;
      sub = 0;
    } else {
      count++;
      _delay_ms(1000);
    }

    
  }

  return 0;
}
