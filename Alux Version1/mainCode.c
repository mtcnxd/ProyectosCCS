#include <18F2455.h>
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL2,CPUDIV1,VREGEN,NOPBADEN
#use delay(clock=48000000)
#use RS232(BAUD=9600, BITS=8, PARITY=N, XMIT=PIN_C6, RCV=PIN_C7)

#define LOADER_SIZE 0x1000    //4096 Bytes.
#build(reset=LOADER_SIZE, interrupt=LOADER_SIZE+0x08)
#org 0, (LOADER_SIZE-1) {}

#include <lcd.c>

#define ledTest PIN_C0;
int8 Data;

void main(){
   lcd_init();
   printf(LCD_PUTC,"\fEsperando Data");
   delay_ms(1000); 

   while(true){
      if(kbhit()){
         Data = getc();
            
         if(Data == 'G' || Data == 0){
            printf(LCD_PUTC,"\fGuardando");
            //output_high(ledTest);
            delay_ms(50);
               
         } else if (Data == 'L' || Data == 1){
            printf(LCD_PUTC,"\fLeyendo");
            //output_low(ledTest);
            delay_ms(50);
               
         }            
      }
   }
}
