/*CONFIGURACION PIC*/

#include "18f4550.h"
#use delay(clock=48000000) //FREC DE OSC DEL MICRO
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)   //Comunicación serial a 9600bps, 1 bit de paro, sin paridad
#zero_ram

#build(reset=0x02000,interrupt=0x02008)
#org 0x0000,0x1FFF {}

//--------------------------------------------------------------------------------------------------------------------

#include "usb_cdc.h"

void main() {

byte envia,recibe;


   usb_cdc_init();                   // Configuramos al puerto virtual.
   usb_init();                      // Inicializamos el stack USB.
   while(!usb_cdc_connected()) {}    // espera a detectar comunicación de la PC
       

    do{
          usb_task();
          if (usb_enumerated()){        // Espera a que el dispositivo sea enumerado por Windows
           
//------------------ colocar codigo de usuario--------------------------------


                  recibe=getc();    //Recibe información del módulo ultrasonido RS232                      
                  printf(usb_cdc_putc,"%X",recibe);  //Envia información hacia la computadora por puerto emulado COM(RS232)
                  
                  //recibe=usb_cdc_getc();    //Recibe un caracter desde el puerto com_cdc en windows
                  
                  //printf("%c",recibe);

//----------------------------------------------------------------------------
             }
       }while (TRUE); // bucle infinito.
     
}



