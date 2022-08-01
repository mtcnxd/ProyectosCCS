/*CONFIGURACION PIC*/

#include "18f4550.h"
#device adc=8

#use delay(clock=48000000) //FREC DE OSC DEL MICRO

#build(reset=0x02000,interrupt=0x02008)
#org 0x0000,0x1FFF {}

//--------------------------------------------------------------------------------------------------------------------

#include "usb_cdc.h"

void main() {

char envia,recibe;


   usb_cdc_init();                   // Configuramos al puerto virtual.
   usb_init();                      // Inicializamos el stack USB.
   while(!usb_cdc_connected()) {}    // espera a detectar una transmisión de la PC (Set_Line_Coding)
       

    do{
          usb_task();
          if (usb_enumerated()){        // Espera a que el dispositivo sea enumerado por el host.
           
//------------------ colocar codigo de usuario--------------------------------


                  recibe=usb_cdc_getc();    //Recibe un caracter desde el puerto com_cdc en windows
    
                  envia=recibe+1;               //incrementa una posición al caracter recibido  
                  
                  printf(usb_cdc_putc,"%c",envia);  //envia el siguiente caracter del recibido hacia windows

   
//----------------------------------------------------------------------------
             }
       }while (TRUE); // bucle infinito.
     
}
















/*#include <usb_cdc.h>

#rom int 0xf00000={1,2,3,4}

void main() {
   BYTE i, j, address, value;

   usb_cdc_init();
   usb_init();
   while(!usb_cdc_connected()) {}

   do {
      usb_task();
      if (usb_enumerated()) {
         printf(usb_cdc_putc, "\r\n\nEEPROM:\r\n");              // Display contents of the first 64
         for(i=0; i<=3; ++i) {                     // bytes of the data EEPROM in hex
            for(j=0; j<=15; ++j) {
               printf(usb_cdc_putc, "%2x ", read_eeprom( i*16+j ) );
            }
            printf(usb_cdc_putc, "\n\r");
         }
         printf(usb_cdc_putc, "\r\nLocation to change: ");
         address = gethex_usb();
         printf(usb_cdc_putc, "\r\nNew value: ");
         value = gethex_usb();

         write_eeprom( address, value );
      }
   } while (TRUE);
} */
//--------------------------------------------------------------------------------------------------------------------
