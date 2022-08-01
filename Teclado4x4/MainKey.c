#include <G-PiC Lite!.c>
#include <kbd_lib.c>
#include <usb_cdc.h>

kbd_init();

void main (){

   usb_init();
   
   do {
      char tecla = kbd_getc();

      if (tecla !=0) {
         printf(usb_cdc_putc, "Tecla: %c \n\r", tecla);
      }  
      
   } while (true);
}
