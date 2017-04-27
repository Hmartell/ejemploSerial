#ifndef RS485_DRIVER_H
#define RS485_DRIVER_H

#define RX_232        PIN_C7
#define TX_232        PIN_C6
#use RS232(BAUD=9600, XMIT=TX_232, RCV=RX_232, BITS=8,PARITY=N, STOP=1)

#define BUFFER_SERIAL_SIZE 100
char bufferRecepcionRda[BUFFER_SERIAL_SIZE];
byte indiceBufferRecepcionRda=0;
byte serial0=0;
#bit banderaNuevoCaracter = serial0.0

void isr_rda(void);
byte hayNuevoCaracter(void);
signed int buscaFinTrama(void);
void imprimeBuffer(void);
void imprimeTrama(void);

#endif