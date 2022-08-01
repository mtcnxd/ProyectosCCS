#include <G-PiC Lite!.c>
#use i2c (master, sda=PIN_B0, scl=PIN_B1, slow)

int tecla = 1;                       //Dato a transmitir
   
/***************************** Envío I2C **************************************/
    
void envio_I2C ()
{
   output_high(PIN_A3);
   i2c_start ();           // Se inicia la comunicación por I2C
   i2c_write (0xa0);       // Se asigna la dirección del esclavo
   i2c_write (tecla);      // Se envia la información a traves del canal
   i2c_stop ();            // Se finaliza la transmision
   delay_ms(100);
   output_low(PIN_A3);
}

/*************************** FUNCIÓN PRINCIPAL ********************************/
void main()
{
   
   while (true)
   {
      
      envio_I2C ();        //Se envía el dato a traves de la funcion
      delay_ms (1000) ;
   }
}

