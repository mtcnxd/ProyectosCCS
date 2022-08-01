#include <G-PiC Lite!.c>
#include <DS1621.c>
#include <usb_cdc.h>

void main(void)
{
  usb_init();
  init_temp();
  float Temp, Centi;
  delay_ms(500);
  
do
  {
      Temp = read_full_temp();
      printf(usb_cdc_putc,"Temperatura: %f C\n\r", Temp);
      delay_ms(1000);
      
  } while (true);
}
