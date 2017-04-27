#include "include/config.h"
#include "include/serial.c"

void main (void){
   configuracion();
   printf("Hola Mundo\r");
   while(1){
     if(buscaFinTrama()){
        imprimeTrama();
     }
   }
}		