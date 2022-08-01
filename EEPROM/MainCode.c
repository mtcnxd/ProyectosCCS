#include <18F2550.h>
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL2,CPUDIV1,VREGEN,NOPBADEN  
#use delay(clock=48000000) 

#define LOADER_SIZE 0x1000       //4096 Bytes.
#build(reset=LOADER_SIZE, interrupt=LOADER_SIZE+0x08)
#org 0, (LOADER_SIZE-1) {}

#use rs232(UART1, baud=9600, DISABLE_INTS, errors)

#include <lcd.c>

int info = 0;

void write_data_eeprom (int addr,  int data){
   output_high(PIN_C2);
   write_eeprom(addr, data);
   delay_ms(100);
   output_low(PIN_C2);
}

int read_data_eeprom(int addr){
   info = read_eeprom(addr);
   return info;
}

void main() {
   lcd_init();
   printf(lcd_putc("LOADING..."));
   delay_ms(1000);

   while (true) {
      if (!input(PIN_A1)){
         write_data_eeprom(0x00, 25);
      }
      read_data_eeprom(0x00);
      printf(lcd_putc, "\f\nDATA: %d", info);
      delay_ms(20);
   }
}

