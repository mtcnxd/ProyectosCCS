#include <18F14K50.h>
#device adc=10
#fuses HS,NOWDT,NOLVP,NODEBUG,NOBROWNOUT,PLLEN,CPUDIV1,PUT,NOMCLR
#use delay(clock=48000000)

#define TriacShot PIN_B7

int16 Intensidad;

void main() 
{
   delay_ms(1000);
   output_low(TriacShot);
   
   set_adc_channel( 4 );
   setup_adc_ports( sAN4 );
   setup_adc( ADC_CLOCK_INTERNAL );
   delay_us(1000);
      
   while(true) {
      Intensidad = read_adc();
      delay_ms(1);

      if (Intensidad <= 512){
         output_high(TriacShot);
      } else {
         output_low(TriacShot);
      }
   }
}
