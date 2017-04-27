#include "include/config.h"
#include "include/serial.c"
#define infoDebug



void main (void){
   setup_oscillator(OSC_16MHZ | OSC_NORMAL   );
   set_tris_c(0x80);
   banderaNuevoCaracter=0;
   clear_interrupt(INT_RDA);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   printf("Hola Mundo\r");
   while(1){
     if(buscaFinTrama()){
        imprimeTrama();
     }
   }
}		