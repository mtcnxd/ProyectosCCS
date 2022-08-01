/*
   Led fading
   Controla la intensidad de brillo de un led mediante una salida PWM. El led
   de la G-PIC Lite ! enciende al brillo m�ximo y se atenua hasta apagarse, 
   una y otra vez.
   
   Los pines de salida PWM pueden ser configurados en la libreria 
   < analogWrite.c > .
   Este ejempo puede ser usado y modificado para cualquier aplicaci�n que 
   requiera PWM.
*/
#include <G-PIC Lite!.c>

int8 duty = 0;                   //Declara una variable para el ciclo de trabajo
void main() {                     //Inicia el programa principal
   while (true) {
      analogWrite (29, duty); //Habilita la salida PWM con un valor de 0 a 100
      duty += 3;             //duty = duty + 10;
      
      if (duty > 100) duty = 0;  //Si duty es mayor que 100, duty se vuelve 0
      
      delay_ms (100);            //Espera 100ms
   }
}

