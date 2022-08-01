/**
   KeyboardMessage
  
   Cuando el bot�n BOOT es presionado, realiza un cierre de sesi�n en el sistema
   operativo. Utiliza una combinaci�n de teclas para hacer esto.
   
   En Windows, CTRL+ALT+DEL seguido de ALT+l
   En Ubuntu,  CTRL+ALT+DEL, y ENTER
   En OSX,     CMD+SHIFT+q
   
   Este ejemplo solo ha sido probado en Windows 7. Si deseas probarlo en otro
   sistema operativo, puedes programar la presi�n de las teclas correspondientes
   para realizar la operaci�n deseada.
   
   Se requiere que el idioma del teclado sea:
   
   INGL�S (Estados Unidos - Internacional).
   
   
   --
   Created: 02 ene 2013
   By:      Ing. Ayrton Estrella Alcocer
            G-PiC Electronics
*/
#include <G-PiC Lite!.c>
#include <G-PiC KeyboardMouse.c>

#define buttonPin Pin_A4

void main() {
   KeyboardMouse_begin();
      
   while(true) {
      if(digitalRead(buttonPin) == 0) {
         keyboard_press(KEY_LEFT_CTRL);
         keyboard_press(KEY_LEFT_ALT);
         keyboard_press(KEY_DELETE);
         delay_ms(100);
         keyboard_releaseAll();
         delay_ms(2000);
         
         // Si tu idioma es espa�ol, cambia la 'l' por una 's'
         keyboard_press(KEY_LEFT_ALT);
         keyboard_press('l'); 
         keyboard_releaseAll();
         break;
         
         delay_ms(1000);
      }
   }
}
