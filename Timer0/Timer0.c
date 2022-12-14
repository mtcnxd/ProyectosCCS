#include <18F2550.h>
#device adc = 10
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL2,CPUDIV1,VREGEN,NOPBADEN
#use delay (clock = 48000000)
#include <lcd.c>

int contador = 0 ;

#INT_TIMER0
void interrupt_timer0() {
   set_timer0(0);                   // Reinicia el contador del Timer0
   output_toggle(Pin_C1);           // Genera un toggle en el Pin_C1
   contador ++ ;
   
   if (contador == 60) {
      output_toggle(PIN_C2);
      contador = 0;
   }
}

void main(void) {
   lcd_init();

   setup_adc( ADC_CLOCK_INTERNAL );
   setup_adc_ports( AN0 );
   set_adc_channel( 0 );
   delay_us( 10 );
   
   setup_timer_0(T0_INTERNAL | T0_DIV_32);  // T0_DIV_4 indica un Prescaler = 4
   set_timer0(-995);                            // En esta funci?n ponemos el valor de CuentaInicial
   
   enable_interrupts(GLOBAL);       // Habilita interrupciones globales
   enable_interrupts(INT_TIMER0);   // Habilita interrupci? espec?fica   

while (TRUE) {
      lcd_gotoxy(1,1);
      printf(lcd_putc, "\fA/D value = %Lu", read_adc());
      lcd_gotoxy(1,2);
      printf(lcd_putc, "Timer0 val = %i", contador);
      delay_ms(500);
   }
}

