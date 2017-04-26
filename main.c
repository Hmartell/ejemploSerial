#define uC18f4620
#include <18F4620.h>
#fuses XT, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT//,BORV28
#fuses NOPBADEN, MCLR, STVREN, NOLVP, NODEBUG, 
#use delay(clock=16000000)


void main (void){
	setup_oscillator(OSC_16MHZ | OSC_NORMAL   );
	set_tris_D(0x00);
	while(1){
		output_toggle(PIN_D0);
		delay_ms(1);
	}
}		