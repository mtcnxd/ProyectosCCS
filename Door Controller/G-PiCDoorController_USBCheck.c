#include <18F14K50.h>
#fuses HS,NOWDT,NOLVP,NODEBUG,NOBROWNOUT,PLLEN,CPUDIV1,PUT,NOMCLR
#use delay(clock=48000000)
//#include "D:\Documents\Electronics\CCS\G-PiC Door Controller\usb\usb_cdc.h"
#include "D:\Electronica\CCS\Door Controller\usb\usb_cdc.h"

//#define Timer0
//#include <Timers.c>
#define usbAvailable() usb_cdc_kbhit()
#define usbRead()      usb_cdc_getc()
#define usbWrite       usb_cdc_putc
#define Rele1 PIN_C6
#define Rele2 PIN_C7

int8 cdcByte; // counter;
//int1 usbChecking = false;

void usbInit()
{
   usb_init();
   usb_wait_for_enumeration();
}

/*
void checkUSB()
{
   int8 checkByte, timeout;
   usbWrite('A');
   
   while(usbAvailable() == false)
   {
      timeout ++;
      delay_ms(20);
      if(timeout >= 500)   reset_cpu();
   }
   
   timeout = 0;
   checkByte = usbRead();
   
   if(!(checkByte == 'A')) reset_cpu();
}

void interruptTimer0()
{
   counter ++;
   if(counter == 20)
   {
      counter = 0;
      usbChecking = true;
   }   
}

*/

void main()
{
   delay_ms(1000);
   output_low(Rele1);
   output_low(Rele2);   
   
   usbInit();
   //setupTimer(0, 1000);
   
   while(true)
   {
         if(usbAvailable() == true)
         {
            cdcByte = usbRead();
   
            if(cdcByte == 1 || cdcByte == '1')  
            {
               output_high(Rele1);
               output_high(Rele2);
            } 
            else if (cdcByte == 0 || cdcByte == '0')  {
               output_low(Rele1);
               output_low(Rele2);
            }            
         }
   }
}


