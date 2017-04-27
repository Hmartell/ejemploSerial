#define uC18f4620
#include <18F4620.h>
#fuses XT, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, MCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)
#use fast_io(c)

#define infoDebug

void configuracion(void){
   setup_oscillator(OSC_16MHZ | OSC_NORMAL   );
   set_tris_c(0x80);
   clear_interrupt(INT_RDA);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
}