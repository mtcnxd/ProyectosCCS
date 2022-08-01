/**
   MousePress

   Envia la presión de una botón a la computadora conectada. Una presión es
   equivalente a hacer un click y sostener continuamente el botón del mouse.
   Una presión es cancelada mediante mouse_release();
   
   Antes de utilizar mouse_press(), es necesario iniciar la comunicación
   mediante KeyboardMouse_begin().
   
   mouse_press() presiona por default el botón izquierdo.
   
   Sintaxis
   mouse_press();
   mouse_press(button);
   
   Parametros
   button: el botón del mouse a presionar
      + MOUSE_LEFT (default)
      + MOUSE_RIGHT
      + MOUSE_MIDDLE
   
   Para mayor información, favor de consultar el archivo Mouse_Library.c.
   
   Este ejemplo está basado en la librería Arduino MouseKeyboard
      + http://arduino.cc/en/Reference/MouseKeyboard   
*/
#include <G-PiC Lite!.c>
#include <G-PiC KeyboardMouse.c>

#define pressPin     Pin_A4   // Switch utilizado para presionar el botón
#define releasePin   Pin_A3   // Switch utilizado para libera el botón

void main() {
   KeyboardMouse_begin();              // Inicia la comunicación
   
   while(true) {
      if(digitalRead(pressPin) == 0) {
         mouse_press();                // Presiona el botón izquierdo del mouse
         delay_ms(500);
      }
      
      if(digitalRead(releasePin) == 0) {
         mouse_release();              // Libera los botones del mouse
         delay_ms(500);
      }
   }
}
