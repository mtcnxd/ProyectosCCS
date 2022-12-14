/**
   MouseMove
   
   Mueve el cursor en una computadora conectada. El movimiento en pantalla
   siempre es relativo a la posici?n actual del cursor.
   
   Sintaxis
   mouse_move(deltaX, deltaY);
   mouse_move(deltaX, deltaY, deltaWheel);
   
   Parametros
   deltaX:  incremento/decremento en la posici?n en X, un valor positivo mover?
            el cursor hacia la derecha, un valor negativo lo mover? hacia la 
            izquierda.
   deltaY:  incremento/decremento en la posici?n en Y, un valor positivo mover?
            el cursor hacia arriba, un valor negativo lo mover? hacia abajo.
   deltaWheel (opcional):  incremento/decremento en la posici?n de la rueda del
                           mouse. un valor positivo mover? el cursor hacia 
                           arriba, un valor negativo lo mover? hacia abajo.
                           Este valor es 0 en caso de no ser especificado.
                           
   Devuelve
   -
   
   Hardware
   Pin_A0      Switch con resistencia pull-up que conecte a GND
   Pin_A1      Switch con resistencia pull-up que conecte a GND  
   Pin_A2      Switch con resistencia pull-up que conecte a GND
   Pin_A3      Switch con resistencia pull-up que conecte a GND
   
   Para mayor informaci?n, favor de consultar el archivo Mouse_Library.c.
   
   Este ejemplo est? basado en la librer?a Arduino MouseKeyboard
      + http://arduino.cc/en/Reference/MouseKeyboard 
      
   --
   Created: 15 feb 2013
   By:      Ing. Ayrton Estrella Alcocer
            G-PiC Electronics
*/
#include <G-PiC Lite!.c>
#include <G-PiC KeyboardMouse.c>

// Define los pines en los cuales se conectar?n los switches para mover el cursor
#define moveUp    Pin_A0
#define moveDown  Pin_A1
#define moveRight Pin_A2
#define moveLeft  Pin_A3

int16 ejeX;
int16 ejeY;

void main() {   
   KeyboardMouse_begin();              // Inicia la comunicaci?n
   
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0_TO_AN1);
   //set_adc_channel(0);   
   
   while(true) {
      set_adc_channel(0);
      ejeX = read_adc();
      set_adc_channel(1);
      ejeY = read_adc();      
      
      mouse_move(ejeY,0);
      mouse_move(0,ejeX);      

      /*
      if(digitalRead(moveUp) == 0) {
         mouse_move(0, 1);             // Mueve el cursor hacia arriba
      }
      else if(digitalRead(moveDown) == 0) {
         mouse_move(0, -1);            // Mueve el cursor hacia abajo
      }
      else if(digitalRead(moveRight) == 0) {
         mouse_move(1, 0);             // Mueve el cursor hacia la derecha
      } 
      else if(digitalRead(moveLeft) == 0) {
         mouse_move(-1, 0);            // Mueve el cursor hacia la izquierda
      }
      */
   }
}
