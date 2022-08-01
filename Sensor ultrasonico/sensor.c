#include <G-PiC Lite!.c>
#include <usb_cdc.h>
#define trig PIN_B1
#define echo PIN_B0

int16 cms = 0;

int16 distancia (){
   int16 contador = 0;
   output_high (trig) ;
   delay_us (50) ;
   output_low (trig) ;

   while (input(echo)==0);
   while (input(echo)==1){
      contador++;
      delay_us(58);
   }
   delay_us(50);
   return (contador);
}

void main ()
{
   usb_init ();
   
   while (true)
   {
      cms = distancia();
      if (cms > 2000){
         printf (usb_cdc_putc, "Estas a mas de 2M de distancia\n\r");
      } else {
         printf (usb_cdc_putc, "Distancia: %Lu cms\n\r", cms);
      }
      
      delay_ms (500) ;
   }
}

