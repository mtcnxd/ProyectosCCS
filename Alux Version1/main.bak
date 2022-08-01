#include <18F2455.h>
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL2,CPUDIV1,VREGEN,NOPBADEN
#use delay(clock=48000000)

#define LOADER_SIZE 0x1000    //4096 Bytes.
#build(reset=LOADER_SIZE, interrupt=LOADER_SIZE+0x08)
#org 0, (LOADER_SIZE-1) {}

#define ledRed PIN_C0
#define ledGreen PIN_C1
#define ledBlue PIN_C2
#define ledRun PIN_B6

int minValue = 400;
int maxValue = 700;
int timerToggle = 0;
int objectDetect = 0;

#INT_EXT
void interrupt_ext0() {
   objectDetect = 1;
}

#INT_TIMER0
void interrupt_timer1() {
   set_timer0(0);                      // Reinicia el contador del Timer0
   if (timerToggle == 20){ 
      output_toggle(ledRun);
      timerToggle = 0;
   } else {
      timerToggle++;
   }
}

void main(){

   setup_adc( ADC_CLOCK_INTERNAL );
   setup_adc_ports( AN0 );
   set_adc_channel( 0 );
   delay_us( 10 );
   
   setup_timer_0(T0_INTERNAL | T0_DIV_4);   // T0_DIV_4 indica un Prescaler = 4
   set_timer0(0);                            // En esta función ponemos el valor de CuentaInicial
   
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER0);      // Habilita interrupció TIMER1
   enable_interrupts(INT_EXT);      // Habilita interrupció TIMER1

   while(true){
      
      if (objectDetect == 1){
         int sensorValue = read_adc();
         
         if (sensorValue > minValue && sensorValue < maxValue){
            output_high(ledGreen);
            output_low(ledBlue);
            output_low(ledRed);
            delay_ms(10);
         } else if (sensorValue < minValue){
            output_high(ledBlue);
            output_low(ledGreen);
            output_low(ledRed);
            delay_ms(10);
         } else if (sensorValue > maxValue){
            output_high(ledRed);
            output_low(ledBlue);
            output_low(ledGreen);
            delay_ms(10);
         }
      }
   }
}
