/*CONFIGURACION PIC*/

#include "18f4550.h"
#device adc=8

#use delay(clock=48000000)
//#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)
//#zero_ram

#build(reset=0x02000,interrupt=0x02008)
#org 0x0000,0x1FFF {}

//-------------------------------------------------------------------------------

#include "usb_cdc.h"

#define LED1     PIN_B0
#define LED2     PIN_B4



void main(void)
{

byte  dato;                   // variable deonde se guardaran los comandos enviados por la pc
byte  voltaje;                //variable donde se guardara el valor de voltaje analogico leido por el PIC

set_tris_b(0b11101110);       //Configura puerto B  1= entrada  0= salida
set_tris_c(0b11111111);       //Configura puerto C  1= entrada  0= salida

         setup_adc_ports(AN0);         //configuracion indiuvidual de canales ADC
         setup_adc( ADC_CLOCK_INTERNAL );

  usb_cdc_init();                      // Configuramos al puerto virtual.
   usb_init();                         // Inicializamos el stack USB.
   while(!usb_cdc_connected()) {}      // espera a detectar una transmisión de la PC (Set_Line_Coding)
   
    usb_task();
    while (!usb_enumerated()){}        // Espera a que el dispositivo sea enumerado por el host.
                
                                 
//----------------------------rutina principal ----------------------------

  do{
                      dato=usb_cdc_getc();                     //espera a recibir un datos por el puerto cdc_usb
                                         
                      switch(dato) {                           // compara el dato para ejecutar accion
                  
                      case 'a': output_toggle(LED1);           //cambia de estado el puerto B0
                                break;
                                
                      case 'b': output_toggle(LED2);            //cambia de estado el puerto B4
                                break;
                                
                      case 'c': if(input(PIN_C2)==0)           //compara el estado del puerto C2, si esta en bajo
                                    {                          //envia caracter 1 hacia la pc por el puerto cdc_usb
                                     printf(usb_cdc_putc,"1");
                                    } 
                                 else                          //si esta en alto 
                                    {                          //envia caracter 2 hacia la pc por el puerto cdc_usb
                                     printf(usb_cdc_putc,"2");
                                    }
                                break;                                                                  
                                 
                      case 'd': set_adc_channel( 0 );                //conversion analogica por canal 0
                                delay_ms(100);                       //tiempo de espera para conversion de ADC
                                voltaje = read_adc();                //lee voltaje analogico en puerto A0
                                printf(usb_cdc_putc,"%c",voltaje);   //envia valor expresado en 1 byte del voltaje analogico
                                break;                               // hacia la pc por el puerto cdc_usb
                                }
                              
       }while (TRUE); // bucle infinito.

}

