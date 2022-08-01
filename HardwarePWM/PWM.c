#include <18F2550.h>
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL2,CPUDIV1,VREGEN,NOPBADEN
#use delay(clock=48000000)
#include <lcd.c>


int16 duty = 0;                 // Variable para guardar el ciclo de trabajo

void main()
{
lcd_init();
   setup_ccp1(CCP_PWM);
   setup_timer_2(T2_DIV_BY_4, 255, 1);
   
   while(true)
   {
      duty = duty + 2;
      printf(lcd_putc,"\f\nDUTY: %Lu", duty);
      set_pwm1_duty(duty);
      delay_ms(300);
      
      if (duty > 255) duty=0;
   }
}

