#include <G-PIC Lite!.c>
#include <lcd.c>
#include <usb_cdc.h>

char Option;

void main () {
   lcd_init();
   usb_init();   
   printf (lcd_putc,"\fProbando...");   
   
   while (true){     
      if ( usb_enumerated() ){
         if ( usb_cdc_kbhit() ){
            Option = get_string_usb();
            printf( usb_cdc_putc,"%c",Option );
            lcd_gotoxy(0,2);
            printf( lcd_putc,"\f%c", Option );
         }
      }
   }
}
