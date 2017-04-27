#include "serial.h"
#ifndef RS485_DRIVER
#define RS485_DRIVER

#int_rda
void isr_rda(void){
   while(kbhit()){
     bufferRecepcionRda[indiceBufferRecepcionRda]=getc();
     indiceBufferRecepcionRda++;
     if(indiceBufferRecepcionRda >= BUFFER_SERIAL_SIZE){
        indiceBufferRecepcionRda--;
     }
     banderaNuevoCaracter=1;
   }
}   

byte hayNuevoCaracter(void){
   if(banderaNuevoCaracter==1){
      return 1;
   }
   return 0;
}

signed int buscaFinTrama(void){
   signed int indiceBusqueda=0;
   if(hayNuevoCaracter() == 0){
      return -1;
   }
   while(indiceBusqueda < (signed int)indiceBufferRecepcionRda){
      if(bufferRecepcionRda[indiceBusqueda] == 0x0D){
         return indiceBusqueda;
      }
      indiceBusqueda++;
   }
   return -1;
}
void imprimeBuffer(void){
   byte indiceImpresion=0;
   printf("Imprime Buffer Completo\r");
   while(indiceImpresion < indiceBufferRecepcionRda){
      printf("Buffer[%X] = %c =  0x%X\r",indiceImpresion, bufferRecepcionRda[indiceImpresion],bufferRecepcionRda[indiceImpresion]);
      indiceImpresion++;
   }
   printf("Fin Impresion Buffer Completo\r\r");
}
void imprimeTrama(void){
   int indiceImpresion=0;
   signed int finTrama;
   finTrama = buscaFinTrama();
   if( finTrama > -1){
#ifdef infoDebug
printf("Imprime Trama\r");
printf("Posición fin de trama = %u\r", finTrama);
printf("BufferSize = %X\r", indiceBufferRecepcionRda);
if(indiceBufferRecepcionRda > finTrama){
   imprimeBuffer();
}
#endif
      banderaNuevoCaracter=0;
      do{
         printf("Buffer[%X] = %c =  0x%X\r",indiceImpresion, bufferRecepcionRda[indiceImpresion],bufferRecepcionRda[indiceImpresion]);
         indiceImpresion++;
      }while((signed int)indiceImpresion < finTrama);
      indiceBufferRecepcionRda=0;
   }
}
#endif