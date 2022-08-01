/**
   MousePress

   Envia la presi�n de una bot�n a la computadora conectada. Una presi�n es
   equivalente a hacer un click y sostener continuamente el bot�n del mouse.
   Una presi�n es cancelada mediante mouse_release();
   
   Antes de utilizar mouse_press(), es necesario iniciar la comunicaci�n
   mediante KeyboardMouse_begin().
   
   mouse_press() presiona por default el bot�n izquierdo.
   
   Sintaxis
   mouse_press();
   mouse_press(button);
   
   Parametros
   button: el bot�n del mouse a presionar
      + MOUSE_LEFT (default)
      + MOUSE_RIGHT
      + MOUSE_MIDDLE
   
   Para mayor informaci�n, favor de consultar el archivo Mouse_Library.c.
   
   Este ejemplo est� basado en la librer�a Arduino MouseKeyboard
      + http://arduino.cc/en/Reference/MouseKeyboard   
*/
#include <G-PiC Lite!.c>
#include <G-PiC KeyboardMouse.c>

#define pressPin     Pin_A4   // Switch utilizado para presionar el bot�n
#define releasePin   Pin_A3   // Switch utilizado para libera el bot�n

void main() {
   KeyboardMouse_begin();              // Inicia la comunicaci�n
   
   while(true) {
      if(digitalRead(pressPin) == 0) {
         mouse_press();                // Presiona el bot�n izquierdo del mouse
         delay_ms(500);
      }
      
      if(digitalRead(releasePin) == 0) {
         mouse_release();              // Libera los botones del mouse
         delay_ms(500);
      }
   }
}
