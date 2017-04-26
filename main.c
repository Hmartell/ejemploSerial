#define uC18f4620
#include <18F4620.h>
#fuses XT, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, MCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)

#define infoDebug

#define RX_232        PIN_C7
#define TX_232        PIN_C6
#use RS232(BAUD=9600, XMIT=TX_232, RCV=RX_232, BITS=8,PARITY=N, STOP=1)

#use fast_io(c)

#define BUFFER_SIZE 100
char bufferRecepcionRda[BUFFER_SIZE];
byte indiceBufferRecepcionRda=0;
byte banderas0;
#bit banderaNuevoCaracter = banderas0.0

#int_rda
void isr_rda(){
   while(kbhit()){
     bufferRecepcionRda[indiceBufferRecepcionRda]=getc();
     indiceBufferRecepcionRda++;
     if(indiceBufferRecepcionRda >= BUFFER_SIZE){
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
   }
}

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