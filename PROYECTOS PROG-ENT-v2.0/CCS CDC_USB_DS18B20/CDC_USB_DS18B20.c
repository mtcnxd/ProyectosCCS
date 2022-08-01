//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////  Adquisición de temperatura de Sensor DS18B20                    
////  con Entrenador PIC18F4550 y LABVIEW
////
//// PINES SENSOR DS18B20
////1.GND  (Tierra)
////2.DQ   (Salida-conectarle una resistencia de Pull-Up de 4.7k        
////3.VDD  (3v a 5v)                                                   
//////////////////////////////////////////////////////////////////////////            
//////////////////////////////////////////////////////////////////////////

/*CONFIGURACION PIC*/

#include "18f4550.h"

#use delay(clock=48000000)                //FREC DE OSC DEL MICROCONTROLADOR

#build(reset=0x02000,interrupt=0x02008)   //REMAPEO DE VECTORES PARA RESPETAR AREA DE BOOTLOADER
#org 0x0000,0x1FFF {}

//--------------------------------------------------------------------------------------------------------------------

#define DS1820_PIN  PIN_B3                //Se define pin 3 del Puerto B como entrada digital para leer datos del sensor DS18B20

#include<1wire.c>                         //Se eincluyen las librerias correspondientes para el manejo del protocolo 1WIRE
#include<ds1820.c>                        //Se incluyela librería del driver para el manejo del sensor DS18B20

#include "usb_cdc.h"                      //Se incluye libreria para trabajar con conexion USB en el microcontrolador

void main() {                             //Programa principal

float temperatura;                        //Se declara variable tipo flotante para giardar el datop de temperatura leido del sensor DS18B20
char recibe;                              //Variable que recibe caracter desde la computadora a traves del puerto COM emulado

   usb_cdc_init();                        //Configuramos al puerto virtual COM
   usb_init();                            //Inicializamos el stack USB
   while(!usb_cdc_connected()) {}         //Espera a detectar una transmisión de la PC (Set_Line_Coding)
       

    do{
          usb_task();
          if (usb_enumerated()){        // Espera a que el dispositivo sea enumerado por el host.
           
//------------------ colocar codigo de usuario--------------------------------


                  recibe=usb_cdc_getc();    //Recibe un caracter desde la computadora
                                             
                  
                  if(recibe=='@')            //si recibe una "@" lee el dato de temparatura del sensor DS18B20
                  {                      
//-------------- LECTURA SENSOR TEMPERATURA ------------------------
                     temperatura = ds1820_read();
                     printf(usb_cdc_putc,"%3.1f", temperatura);
                  }

//----------------------------------------------------------------------------
             }
       }while (TRUE); // bucle infinito.
     
}


