#include <16F870.h>
#fuses NOWDT, NOPROTECT, XT, NOLVP
#use delay(clock=4000000)

void main () {
  while (true){
    output_high(PIN_B0);
    delay_ms(500);
    output_low(PIN_B0);
    delay_ms(500);
  }
}
