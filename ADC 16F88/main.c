#include <16F88.h>
#fuses INTRC, NOWDT, NOLVP, NOCPD, NOWRT, NODEBUG, NOPROTECT, NOFCMEN, NOIESO, NOMCLR, NOBROWNOUT, CCPB3
#use delay(clock=4000000) 
#include <lcd.c>

void main(){
   lcd_init();

   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(sAN0);
   setup_vref(FALSE);
   
   set_adc_channel(0);
   delay_ms (1);
   
   while (true) {   
      printf (lcd_putc,"\f\nADC = %i", read_adc());
      delay_ms (100);
   }
}
