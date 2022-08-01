#include <18F2550.h>
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL2,CPUDIV1,VREGEN,NOPBADEN  
#use delay(clock=48000000) 

#define LOADER_SIZE 0x1000       //4096 Bytes.
#build(reset=LOADER_SIZE, interrupt=LOADER_SIZE+0x08)
#org 0, (LOADER_SIZE-1) {}
#use i2c (slave, sda=PIN_B0, scl=PIN_B1, slow, address=0x04)
#use rs232(UART1, baud=9600, DISABLE_INTS, errors)

void main() {

   int dato;
   int16 contador = 0;
   
   while (true) {
   
      // Recepción por comunicación I2C     
      if(i2c_poll()) {

         dato=i2c_read();
         if (dato == 1) {
            output_toggle(PIN_C1);
            contador ++;
            printf("Contador: %Lu   \r\f", contador);
         }
      }
   }
}
