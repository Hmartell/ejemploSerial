#define uC18f4620
#include <18F4620.h>
#fuses XT, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, MCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)

#define RX_232        PIN_C7
#define TX_232        PIN_C6
#use RS232(BAUD=9600, XMIT=TX_232, RCV=RX_232, BITS=8,PARITY=N, STOP=1)

#use fast_io(c)
char caracterRecibido;
byte banderas0;
#bit banderaNuevoCaracter = banderas0.0

#int_rda
void isr_rda(){
   while(kbhit()){
     caracterRecibido=getc();
     banderaNuevoCaracter=1;
   }
}   
void main (void){
   setup_oscillator(OSC_16MHZ | OSC_NORMAL   );
   set_tris_c(0x80);
   banderaNuevoCaracter=0;
   clear_interrupt(INT_RDA);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   printf("Hola Mundo\n");
   while(1){
      if(banderaNuevoCaracter==1){
         banderaNuevoCaracter=0;
         putc(caracterRecibido+1);
      }
   }
}		