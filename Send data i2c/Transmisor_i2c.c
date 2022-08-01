#include <G-PiC Lite!.c>
#use i2c (master, sda=PIN_B0, scl=PIN_B1, slow)
#include <usb_cdc.h>

int tecla;                       //Dato a transmitir
   
/***************************** Envío I2C **************************************/
    
void envio_I2C (int tecla)
{
   output_high(PIN_A3);
   i2c_start ();           // Se inicia la comunicación por I2C
   i2c_write (0x04);       // Se asigna la dirección del esclavo
   i2c_write (tecla);      // Se envia la información a traves del canal
   i2c_stop ();            // Se finaliza la transmision
   delay_ms(50);
   output_low(PIN_A3);
}

/*************************** FUNCIÓN PRINCIPAL ********************************/
void main()
{
   usb_init();
   
   while (true)
   {
      tecla = usb_cdc_getc();
      envio_I2C (tecla);        //Se envía el dato a traves de la funcion
      printf (usb_cdc_putc, "Valor obtenido: %i\n\r", tecla);
      delay_ms (100) ;
   }
}

