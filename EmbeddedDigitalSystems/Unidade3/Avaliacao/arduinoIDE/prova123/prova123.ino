volatile int count, somar, decrementar = 0;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 500; // 500 ms debounce

ISR(INT0_vect) {
  if (PIND & (1 << PD2)) {  // Confirma borda de subida
    somar = 1;
  }
}

ISR(INT1_vect) {
   if (PIND & (1 << PD3)) { // Confirma borda de subida
    decrementar = 1;
  }
}

//ISR( TIMER0_OVF_vect ){
  //count++; 
//}

uint8_t conversor(uint8_t bin)
{
  return bin ^ (bin >> 1);
}

void setup()
{
  Serial.begin(115200); // serial

  DDRB |= 0x3F;                   // PB0–PB5 como saída
  DDRC |= 0x03;                   // PD0 e PD1 como saída
  DDRD &= ~((1 << 2) | (1 << 3)); // PD2 e PD3 como entrada

  PORTB &= ~(0x3F);  
  PORTC &= ~(0x3);  
  PORTD |= (1 << 2) | (1 << 3);   // Pull-up em PD2 e PD3

  EICRA = ((1 << ISC01) | (1 << ISC00)|(1 << ISC11) | (1 << ISC10));  // (EICRA XXXX_1111) // mudança em borda de subida 0B = 11
  EIMSK |= ((1 << INT0) | (1 << INT1)); // INT0 e INT1  activate

  //TCCR0A = 0b00000000; // TC0 (normal operating)
  //TCCR0B = 0b00000010; // TC0 with prescaler 8. Overflow every 128us = 256/(16Mhz/8)
  //TIMSK0 = 0b00000001; // Enabling interrupt TC0 escreve 1 quando tem interrupção

  sei(); // habilita interrupções globais
}

void loop()
{
  unsigned long now = millis(); // tentando resolver debounce

  if (somar && (now - lastDebounceTime > debounceDelay)) { // tentando resolver debounce
    count++;
    somar = 0;
    lastDebounceTime = now;
  }
  
  if (decrementar && (now - lastDebounceTime > debounceDelay)) { // tentando resolver debounce
    count--;
    decrementar = 0;
    lastDebounceTime = now;
  }
  
  uint8_t gray = conversor(count);

  PORTB = (gray & 0x3F);                          // bits 0–5 para PB0–PB5
  PORTC = (PORTC & ~0x03) | ((gray >> 6) & 0x03); // bits 6–7 para PD0–PD1

  Serial.print("Contador: ");
  Serial.print(count);
  Serial.print(" - Gray: ");
  Serial.println(gray);

  if (somar){
    count ++;
    somar = 0;
    }
  else if (decrementar){
    count --;
    decrementar = 0;
    } else {
      count++;
      _delay_ms(1000);

    }
  
}
