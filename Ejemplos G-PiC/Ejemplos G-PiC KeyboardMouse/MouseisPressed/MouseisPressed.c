/**
   MouseisPressed
   
   Checa el estado actual del bot?n del mouse especificado y reporta si ?ste
   est? presionado.
   
   mouse_isPressed() verifica por default el bot?n izquierdo.
   
   Hardware
   Pin_A1   Push button con resistencia de pull-up
   Pin_A2   Push button con resistencia de pull-up
   
   Para mayor informaci?n, favor de consultar el archivo Mouse_Library.c.
   Este ejemplo est? basado en la librer?a Arduino MouseKeyboard
      +  http://arduino.cc/en/Reference/MouseKeyboard
*/
#include <G-PiC Lite!.c>
#include <G-PiC KeyboardMouse.c>

#define ledPin       Pin_A4   // LED que indica si que el bot?n est? presionado
#define pressPin     Pin_A1   // Switch utilizado para presionar el bot?n
#define releasePin   Pin_A2   // Switch utilizado para libera el bot?n

void main() {
   KeyboardMouse_begin();
   
   while(true) {
      if(digitalRead(pressPin) == 0) {
         mouse_press();                // Presiona el bot?n izquierdo del mouse
         delay_ms(100); 
      }
      
      if(digitalRead(releasePin) == 0) {
         mouse_release();              // Libera los botones del mouse
         delay_ms(100); 
      }
      
      // El LED del Pin_A4 se apaga si el bot?n est? presionado
      digitalWrite(ledPin, mouse_isPressed());
   }
}
