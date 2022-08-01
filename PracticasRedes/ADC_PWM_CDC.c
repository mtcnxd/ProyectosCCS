#include <G-PiC Lite!.c>

float retardo;

#INT_EXT
void interrupt_ext0() {
   retardo = analogRead(0);
   retardo = (retardo/1024) * 8;
  
   delay_ms(retardo);  
   output_high(PIN_D2);   
   delay_ms(1);
   output_low(PIN_D2);
}

void main(void) {
   enable_interrupts( GLOBAL );
   enable_interrupts( INT_EXT );

   while (true) {
      // Se trabaja solo con interrupcion del B0.
   }
}
