#include <16f886.h>
#device adc = 10;
#fuses INTRC_IO, NOWDT, NOPUT, NOBROWNOUT, NOPROTECT, NOIESO, NOFCMEN, NOLVP, NODEBUG, NOWRT, NOMCLR
#use delay(Internal = 8MHz)
#include <SevenSegment.h>

void main () 
{

   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(sAN0);
   setup_vref(FALSE);
   
   set_adc_channel(0);
   delay_ms (5);
   
   while (true)
   {  
      for (int i=0; i<=9; i++)
      {
         DigitaNumero(i, 0x20);
         delay_ms (2000);
      }
   }
}

