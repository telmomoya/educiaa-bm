#include "ehbasic.h"
#include "uart.h"
extern void step6502();
extern void exec6502(uint32_t);
uint8_t read6502(uint16_t);
void write6502(uint16_t,uint8_t);
void reset6502();
void nmi6502();
void irq6502();

