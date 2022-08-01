/**
   KeyboardCloseWindow
  
   Implementa el macro Alt + F4 para mandar el comando Cerrar.
   
   Se requiere que el idioma del teclado sea:

   INGL�S (Estados Unidos - Internacional).
   
   --
   Created: 02 ene 2013
   By:      Ing. Ayrton Estrella Alcocer
            G-PiC Electronics
*/

#include <G-PiC Lite!.c>
#include <G-PiC KeyboardMouse.c>

void main() {
   KeyboardMouse_begin();                      // Inicializa el teclado USB
   
   while(true) {
      if(digitalRead(Pin_A4) == 0) {      // Si la entrada del Pin_A4 es 0
         keyboard_close_window();         // Env�a el comando Alt + F4
                                          // Luego libera las teclas presionadas
         delay_ms(1000);
      }
   }
}
