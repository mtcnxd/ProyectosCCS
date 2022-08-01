/*CONFIGURACION PIC*/

#include "18f4550.h"


#use delay(clock=48000000)

#build(reset=0x02000,interrupt=0x02008)
#org 0x0000,0x1FFF {}

//-------------------------------------------------------------------------------

#define LED PIN_B1

void main(void)
{


set_tris_b(0b11111101);


output_low(LED);

do{

output_toggle(LED);
delay_ms(500);

}while(true);

}

