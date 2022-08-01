#include <G-PiC Lite!.c>

void main() {
   
   while (true){
      output_high(PIN_B0);
      delay_ms(500);
      output_low(PIN_B0);
      delay_ms(500);      
   }
}
