#include <G-PiC Lite!.c>
#include <Nokia3310.c>
#include <usb_cdc.h>

void main (){

   nokia_init();
   usb_init();

   while (true) {   
      nokia_gotoxy(0,1);
      printf(nokia_putc,"PROBANDO");      
      printf(usb_cdc_putc,"PROBANDO");        
      delay_ms(1000);
   }
}
