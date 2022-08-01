/////////////////////////////////////////////////////////////////////////
////                            DAQ.c                                ////
////                                                                 ////
//// Este ejemplo muestra como desarrollar un sencillo dispositivo   ////
//// USB con el PIC18F2550 (para la serie 18Fxx5x)                   ////
//// los drivers que se requiere para éste dispositivo son los que   ////
//// proporciona Microchip en su pagina web, y se basan en protocolo ////
//// USB_ENABLE_BULK su XTAL es de 12Mhz.                            ////
////                                                                 ////
////                                                                 ////
//// Cuando el dispositivo sea conectado al PC, saldrá el asistente  ////
//// para la instalación del driver. Se instala el driver            ////
//// que nos proporciona Microchip.                                  ////
////                                                                 ////
//// Al aplicar energia al PIC se enciende el LED en RB6 y  hasta    ////
//// que el dispositivo halla sido configurado por la PC via puerto  ////
//// USB se encende el Led en RB7. El PIC muestra el dato que le     ////
//// envia la PC en el vector [0] e inmediatamente el PIC le         ////
//// responde con el valor del puerto A almacenado en el vector [1]. ////
//// Sólo si la PC le envia un dato al PIC éste enviará el dato del  ////
//// puerto A                                                        ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
//// Realizado con el compilador CCS PCWH 3.227                      ////
//// Este programa fue desarrollado para estimular el uso del        ////
//// puerto USB y desarrollar tarjetas de adquisición económicas     ////
//// por Ing. Gabriel Pool y Ing. Julio Lugo para proyecto de        ////
//// materia Sensores y Actuadores impartida por el profesor         ////
//// M.C. Pedro Nájera.                                              ////
////                                                                 ////
//// Actualizado en Julio de 2009 para uso en  Matlab                ////
//// por Ing. Gabriel Pool para proyecto de la materia Diseño        ////
//// Mecatrónico impartida por el profesor Dr. Alejo Mosso Vazquez   ////
//// (Universidad Modelo en Mérida, Yucatán, México)                 ////
//// Apoyado por Centro de Investigación Científica de Yucatán AC    ////
//// Depto de Instrumentación ( www.cicy.mx)                         ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////

// Por favor, complete los 4 pasos siguientes ...
// Paso 1:
// Cambie la siguiente instrucción de acuerdo al PIC que utilice PIC18F2455/2550/4455/4550
#include <18F2455.h>
//#device ADC=10                             //Descomente ésta opción en caso de usar el ADC a 10bits
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL3,CPUDIV1,VREGEN,MCLR,NOPBADEN
// Paso 2: Ajuste el fusible del PLL de acuerdo al Xtal que utilice
// No olvide que PLL1 = Para un Xtal de 4Mhz
//               PLL2 = Para un Xtal de 8Mhz
//               PLL3 = Para un Xtal de 12Mhz
//               PLL4 = Para un Xtal de 20Mhz , etc.
#use delay(clock=48000000)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)

/////////////////////////////////////////////////////////////////////////////
//
// CCS Library dynamic defines.  For dynamic configuration of the CCS Library
// for your application several defines need to be made.  See the comments
// at usb.h for more information
//
/////////////////////////////////////////////////////////////////////////////

#define USB_HID_DEVICE     FALSE              //deshabilitamos el uso de las directivas HID
#define USB_EP1_TX_ENABLE  USB_ENABLE_BULK    //turn on EP1(EndPoint1) for IN bulk/interrupt transfers
#define USB_EP1_RX_ENABLE  USB_ENABLE_BULK    //turn on EP1(EndPoint1) for OUT bulk/interrupt transfers
#define USB_EP1_TX_SIZE    64                 //size to allocate for the tx endpoint 1 buffer
#define USB_EP1_RX_SIZE    64                 //size to allocate for the rx endpoint 1 buffer

/////////////////////////////////////////////////////////////////////////////
// Lo siguiente no es indispensable:
// If you are using a USB connection sense pin, define it here.  If you are
// not using connection sense, comment out this line.  Without connection
// sense you will not know if the device gets disconnected.
//       (connection sense should look like this:
//                             100k
//            VBUS-----+----/\/\/\/\/\----- (I/O PIN ON PIC)
//                     |
//                     +----/\/\/\/\/\-----GND
//                             100k
//        (where VBUS is pin1 of the USB connector)
//
/////////////////////////////////////////////////////////////////////////////
//#define USB_CON_SENSE_PIN PIN_B2  //CCS 18F4550 development kit has optional conection sense pin

/////////////////////////////////////////////////////////////////////////////
//
// Include the CCS USB Libraries.  See the comments at the top of these
// files for more information
//
/////////////////////////////////////////////////////////////////////////////

#include <pic18_usb.h>              //Microchip PIC18Fxx5x Hardware layer for CCS's PIC USB driver
#include <usb_desc_scope.h>         //descriptors del Pic USB
#include <usb.c>                    //handles usb setup tokens and get descriptor reports

/////////////////////////////////////////////////////////////////////////////
/* 
Paso 3: Abra el archivo C:\Archivos de programa\PICC\Drivers\usb_desc_scope.h
        ( donde se instaló el compilador de CCS ) que es el descriptor del USB
        ubicado en su PC, avance hasta la sección start device descriptors
        (aprox en la linea 132) y reemplace los valores del vendor id,
        el product id y el device release number como sigue ( puede copiar
        las tres líneas siguiente y pegar en el archivo del descriptor <<usb_desc_scope.h>> ) :
               
         0xD8,0x04,           //vendor id (0x04D8 is Microchip)
         0x0B,0x00,           //product id
         0x01,0x00,           //device release number

ESTO ES IMPORTANTE HACERLO CORRECTAMENTE DE LO CONTRARIO, EL DISPOSITIVO NO SERA RECONOCIDO POR EL DRIVER.
*/
/////////////////////////////////////////////////////////////////////////////


#define  LEDV    PIN_B6
#define  LEDR    PIN_B7
#define  LED_ON  output_high
#define  LED_OFF output_low

// Direcciones de memoria válidas para PIC18F2455/2550/4455/4550 (no olvide que son la misma familia)
// Esto es con el fin de poder escribir directamente en ellos sin usar instrucciones como intermediarios.
#BYTE TRISA  = 0x0F92                           // Registro de control de E/S del puerto A
#BYTE TRISB  = 0x0F93                           // Registro de control de E/S del puerto B
#BYTE PORTA  = 0x0F80                           // Registro del puerto A
#BYTE PORTB  = 0x0F81                           // Registro del puerto B
#BYTE ADCON1  = 0x0FC1                          // Registro de control del ADC
#BYTE CMCON   = 0x0FB4                          // Registro del modulo comparador

int8 dato[64];

void main(void) {

   LED_ON(LEDV);                                //encendemos led en RB6 para indicar presencia de energia
   LED_OFF(LEDR);

   usb_init();                                  // inicializamos el USB
   usb_task();                                  // habilita periferico usb e interrupciones
   usb_wait_for_enumeration();                  // esperamos hasta que el PicUSB sea configurado por el host

   LED_OFF(LEDV);
   LED_ON(LEDR);                                // encendemos led en RB7 al establecer contacto con la PC

   TRISA  = 0x0FF;                              // Se declara el puerto A como entradas (instrucción opcional)
   TRISB  = 0x00;                               // Se declara el puerto B como salidas (instrucción opcional)
   ADCON1 = 0x0F;                               // Se configura al ADC para entradas digitales (apagar el ADC)
   CMCON  = 0x07;                               // Se configuran los comparadores para entradas digitales (apagar los comparadores)

   while (TRUE)
   {
      if(usb_enumerated())                      // si el Pic está configurado via USB
      {
         if (usb_kbhit(1))                      // si el endpoint de salida contiene datos del host
         {
            usb_get_packet(1, dato, 64);        // cojemos el paquete de tamaño 8bytes del EP1 y almacenamos en dato
            portb = dato[0];                    // Se muestra al byte completo en el puerto B
            dato[1] = porta;                    // Se lee el puerto A y se almacena en el vector
            usb_put_packet(1, dato, 64, USB_DTS_TOGGLE); //y enviamos el mismo paquete de tamaño 64bytes del EP1 al PC
         }
       }
    }
}

//Paso 4: Compile y grabe en el PIC
