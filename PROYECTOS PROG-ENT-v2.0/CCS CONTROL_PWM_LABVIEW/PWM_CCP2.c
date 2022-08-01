/*CONFIGURACION PIC*/

#include "18f4550.h"
#use delay(clock=48000000) //FREC DE OSC DEL MICRO

#build(reset=0x01000,interrupt=0x01008)
#org 0x0000,0x0FFF {}

//--------------------------------------------------------------------------------------------------------------------

#include "usb_cdc.h"   //Incluye libreria para COM Virtual USB_CDC

void main()
{
  unsigned int8 valor_pwm; //variable para ajustar valos de PWM en CCP2 PIN_B3
  byte P1, P2, P3;     // variables para recibir valores de ajuste de PWM desde LabView
  
  setup_ccp2(CCP_PWM);                               //Se configura el Modulo CCP2(PIN_B3) en modo PWM
  setup_timer_2(T2_DIV_BY_16,255,16);                //Configuracion Frecuencia de Osc


 usb_cdc_init();                       // Configuramos al puerto virtual.
  usb_init();                          // Inicializamos el stack USB. 
  while(!usb_cdc_connected()) {} // espera a detectar una transmisión de la PC (Set_Line_Coding).
  do{usb_task();
    if (usb_enumerated()){       // Espera a que el dispositivo sea enumerado por el host.
 
//#################### Recepción de parametros para ajuste de PWM ################################
            
     P1=usb_cdc_getc();       //Recibe desde LabView por USB_CDC (COMx) valor de las centenas en ascii
     P2=usb_cdc_getc();       //Recibe desde LabView por USB_CDC (COMx) valor de las decenas en ascii
     P3=usb_cdc_getc();       //Recibe desde LabView por USB_CDC (COMx) valor de las unidades en ascii
     P1=((P1-48)*100);        //Se resta 48 para convertir de ascii recibido a tipo int y se multiplica por 100 para posición de centenas
     P2=((P2-48)*10);         //Se resta 48 para convertir de ascii recibido a tipo int y se multiplica por 10 para posición de decenas
     P3=(P3-48);              //Se resta 48 para convertir de ascii recibido a tipo int para posición de unididades
     
     valor_pwm=((P1+P2+P3)*2.55);  //valor de factor de ajuste de PWM 
     set_pwm2_duty(valor_pwm);   //Ajuste del ciclo de trabajo de PWM en salida de PIN_B3
     
             }
       }while (TRUE); //Bucle infinito
}
