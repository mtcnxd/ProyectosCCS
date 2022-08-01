/**
   KeyboardMessage
  
   Cuando el botón BOOT es presionado, una cadena de caracteres es enviada a la 
   PC como entrada de teclado. Puedes usar tu editor de texto favorito para ver
   el resultado.

   keyboard_print()
   Envía la presión de teclas hacia la computadora conectada. keyboard_print()
   debe ser llamado después de haber inicializado mediante KeyboadMouse_begin().

   ADVERTENCIA: Al usar el comando keyboard_print(), la G-PiC Lite! toma el
   control de tu teclado! Asegúrate de tener el control antes de utilizar este
   comando. Se recomienda utilizar un push button para activar/desactivar 
   esta función.
   
   Sintaxis
   char text[] = "Texto a teclear!";
   keyboard_print(text);
   
   Parametros
   text: la cadena de caracteres que se desea teclear. Es necesario guardar
   esta cadena en una arreglo tipo char y luego pasar este arreglo como parámetro
   de la función keyboard_print().
   
   Devuelve
   -

   Se requiere que el idioma del teclado sea:
   
   INGLÉS (Estados Unidos - Internacional).
    
   --
   Created: 08 feb 2013
   By:      Ing. Ayrton Estrella Alcocer
            G-PiC Electronics
*/
#include <G-PiC Lite!.c>
#include <G-PiC KeyboardMouse.c>

#define buttonPin Pin_A4

void main() {
   int counter = 0;
   
   KeyboardMouse_begin();
      
   while(true) {
      if(digitalRead(buttonPin) == 0) {
         counter ++;
         
         // Crea una variable tipo arreglo (array) lo suficientemente
         // grande para almacenar todos los caracteres de la cadena.
         char text[50] = "Has presionado el boton ";
         keyboard_print(text);            // Imprime la cadena de caracteres
         
         // Convierte el valor de la variable a una cadena de caracteres y
         // guarda el resultado en la variable <text>. Para mayor información,
         // revisar el archivo de ayuda HELP.
         sprintf(text, "%u", counter);
         keyboard_print(text);            // Imprime el valor de counter
         
         text = " veces!";
         keyboard_println(text);          // Imprime la cadena de caracteres
         
         delay_ms(500);
      }
   }
}
