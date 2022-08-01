#include <G-PIC Lite!.c>
#include <usb_cdc.h>
// En la variable valor guardo el dato que se recibe por USB
int valor;

void main() {
   // Equivalente a Serial.begin(9600);
   usb_init();

   while(true) {
      // usb_enumerated = Serial.available()
      if (usb_enumerated()) {
         
         // usb_cdc_getc = Serial.read()
         if (valor = usb_cdc_getc()){
         
            switch(valor){
               case 1:
                  printf(usb_cdc_putc, "\n\rLED 1 encendido");
                  output_b(0x01);
               break;
               case 2:
                  printf(usb_cdc_putc, "\n\rLED 2 encendido");
                  output_b(0x04);
               break;
               case 3:
                  printf(usb_cdc_putc, "\n\rLED 3 encendido");
                  output_b(0x08);
               break;
               case 4:
                  printf(usb_cdc_putc, "\n\rLED 4 encendido");
                  output_b(0x10);
               break;
               case 5:
                  printf(usb_cdc_putc, "\n\rLED 5 encendido");
                  output_b(0x20);
               break;
            }
         }
      }
   }
}
