/**
   MouseClick
   
   Envia un click moment�neo a la computadora en la ubicaci�n del cursor. Esto
   es lo mismo que presionar y soltar el bot�n del mouse.
   
   mouse_click() presiona por default el bot�n izquierdo del mouse.
   
   Sintaxis
   mouse_click();
   mouse_click(button);
   
   Parametros:
   button: el bot�n del mouse a presionar
      + MOUSE_LEFT (default)
      + MOUSE_RIGHT
      + MOUSE_MIDDLE
      
   Para mayor informaci�n, favor de consultar el archivo Mouse_Library.c.
   
   Este ejemplo est� basado en la librer�a Arduino MouseKeyboard
      +  http://arduino.cc/en/Reference/MouseKeyboard
*/
#include <G-PiC Lite!.c>
#include <G-PiC KeyboardMouse.c>

#define buttonPin Pin_A4

void main() {
   KeyboardMouse_begin();
   
   while(true) {
      if(digitalRead(buttonPin) == 0) {
         mouse_click();
         delay_ms(500);
      }
   }
}
