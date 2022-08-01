#include <16f886.h>
#device adc=10;
#fuses INTRC_IO, NOWDT, NOPUT, NOBROWNOUT, NOPROTECT, NOIESO, NOFCMEN, NOLVP, NODEBUG, NOWRT, NOMCLR
#use delay(Internal = 8MHz)
#include <SevenSegment.h>

int16 Lectura,Voltaje, SetPoint;
int16 Almacen1, Almacen2, Almacen3, Almacen0, Total;
int Decenas, Unidades ;

void inicio(){
   output_c(0x00);
   
   output_b(0x01);
   delay_ms(300);
   output_b(0x02);
   delay_ms(300);
   output_b(0x04);
   delay_ms(300);
   output_b(0x08);
   delay_ms(300);
   output_b(0x10);
   delay_ms(400);
   output_b(0x20);
   delay_ms(500);   
}

void main () 
{  
   inicio();
   
   while (true)
   {
      setup_adc(ADC_CLOCK_INTERNAL);
      setup_adc_ports(sAN0);
      setup_vref(FALSE);   
      set_adc_channel(0);
      delay_us(10);
      Lectura = read_adc();
      Voltaje = (((5.0 * Lectura) * 100) / 1023.0);
      setup_adc( ADC_OFF );
      
      // Algoritmo para la atenuacion de la señal
      Almacen3 = Voltaje;
      Almacen2 = Almacen3;
      Almacen1 = Almacen2;
      Almacen0 = Almacen1;
      Total = ((Almacen0 + Almacen1 + Almacen2 + Almacen3)/4);
   
      setup_adc(ADC_CLOCK_INTERNAL);
      setup_adc_ports(sAN1);
      setup_vref(FALSE);            
      set_adc_channel(1);
      delay_us(10);
      SetPoint = read_adc();
      SetPoint = (SetPoint * 99/1023);
      setup_adc( ADC_OFF );      
      
      if ( Total <= SetPoint )
      {
         output_low(PIN_A2);
      } else {
         output_high(PIN_A2);
      }      
      
      Decenas  = ((Total/10)%10);
      Unidades = (Total % 10);

      for (int i=0; i<=200; i++)
      {
         DigitaNumero ( Unidades, 0x20 );
         delay_ms (10);
         DigitaNumero ( Decenas, 0x10);
         delay_ms (10);
      }
   }
}
