/**
   MouseClick
   
   Envia un click momentáneo a la computadora en la ubicación del cursor. Esto
   es lo mismo que presionar y soltar el botón del mouse.
   
   mouse_click() presiona por default el botón izquierdo del mouse.
   
   Sintaxis
   mouse_click();
   mouse_click(button);
   
   Parametros:
   button: el botón del mouse a presionar
      + MOUSE_LEFT (default)
      + MOUSE_RIGHT
      + MOUSE_MIDDLE
      
   Para mayor información, favor de consultar el archivo Mouse_Library.c.
   
   Este ejemplo está basado en la librería Arduino MouseKeyboard
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
