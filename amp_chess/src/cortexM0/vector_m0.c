/* Copyright 2015, Mariano Cerdeiro
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief Vector Interrupt tables
 **
 ** This file contains the vector interrupt tables
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Vector Vector interrupt tables
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "umax.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
/** \brief Handler for NMI */
void NMI_Handler(void);

/** \brief Handler for HardFault */
void HardFault_Handler(void);

/** \brief Handler for SVC */
static void SVC_Handler(void);

/** \brief Handler for NoHandler */
static void ISR_NoHandler(void);


/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
#ifndef CPU
#error CPU shall be defined.
#endif

/** \brief LPC4337 Interrupt vector */
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
   /* System ISRs */
   &_vStackTop,                    /* The initial stack pointer  */
   ResetISR,                       /* The reset handler          */
   NMI_Handler,                    /* The NMI handler            */
   HardFault_Handler,              /* The hard fault handler     */
   0,                              /* The MPU fault handler      */
   0,                              /* The bus fault handler      */
   0,                              /* The usage fault handler    */
   0,                              /* Reserved                   */
   0,                              /* Reserved                   */
   0,                              /* Reserved                   */
   0,                              /* Reserved                   */
   SVC_Handler,                    /* SVCall handler             */
   0,                              /* Debug monitor handler      */
   0,                              /* Reserved                   */
   0,                 /* The PendSV handler         */
   0,                              /* The SysTick handler        */
   /*** User Interrupts ***/
   ISR_NoHandler, /* 0x10 0x00000040 - No Handler set for ISR RTC (IRQ 0) */
   ISR_NoHandler, /* 0x11 0x00000044 ISR for M4CORE (IRQ 1) Category 2 */
   ISR_NoHandler, /* 0x12 0x00000048 - No Handler set for ISR DMA (IRQ 2) */
   ISR_NoHandler, /* 0x13 0x0000004C - No Handler set for ISR RES1 (IRQ 3) */
   ISR_NoHandler, /* 0x14 0x00000050 - No Handler set for ISR FLASH_EEPROM_ATIMER (IRQ 4) */
   ISR_NoHandler, /* 0x15 0x00000054 - No Handler set for ISR ETH (IRQ 5) */
   ISR_NoHandler, /* 0x16 0x00000058 - No Handler set for ISR SDIO (IRQ 6) */
   ISR_NoHandler, /* 0x17 0x0000005C - No Handler set for ISR LCD (IRQ 7) */
   ISR_NoHandler, /* 0x18 0x00000060 - No Handler set for ISR USB0 (IRQ 8) */
   ISR_NoHandler, /* 0x19 0x00000064 - No Handler set for ISR USB1 (IRQ 9) */
   ISR_NoHandler, /* 0x1a 0x00000068 - No Handler set for ISR SCT (IRQ 10) */
   ISR_NoHandler, /*RIT_IRQHandler*/
   ISR_NoHandler, /* 0x1c 0x00000070 - No Handler set for ISR TIMER0 (IRQ 12) */
   ISR_NoHandler, /* 0x1d 0x00000074 - No Handler set for ISR GINT1 (IRQ 13) */
   ISR_NoHandler, /* 0x1e 0x00000078 - No Handler set for ISR PIN_INT4 (IRQ 14) */
   ISR_NoHandler, /* 0x1f 0x0000007C - No Handler set for ISR TIMER3 (IRQ 15) */
   ISR_NoHandler, /* 0x20 0x00000080 - No Handler set for ISR MCPWM (IRQ 16) */
   ISR_NoHandler, /* 0x21 0x00000084 - No Handler set for ISR ADC0 (IRQ 17) */
   ISR_NoHandler, /* 0x22 0x00000088 - No Handler set for ISR I2C0_I2C1 (IRQ 18) */
   ISR_NoHandler, /* 0x23 0x0000008C - No Handler set for ISR SGPIO (IRQ 19) */
   ISR_NoHandler, /* 0x24 0x00000090 - No Handler set for ISR SPI_DAC (IRQ 20) */
   ISR_NoHandler, /* 0x25 0x00000094 - No Handler set for ISR ADC1 (IRQ 21) */
   ISR_NoHandler, /* 0x26 0x00000098 - No Handler set for ISR SSP0_SSP1 (IRQ 22) */
   ISR_NoHandler, /* 0x27 0x0000009C - No Handler set for ISR EVENTROUTER (IRQ 23) */
   ISR_NoHandler, /* 0x28 0x000000A0 - No Handler set for ISR UART0 (IRQ 24) */
   ISR_NoHandler, /* 0x29 0x000000A4 - No Handler set for ISR UART1 (IRQ 25) */
   ISR_NoHandler, /* 0x2a 0x000000A8 - No Handler set for ISR UART2_CCAN1 (IRQ 26) */
   ISR_NoHandler, /* 0x2b 0x000000AC - No Handler set for ISR UART3 (IRQ 27) */
   ISR_NoHandler, /* 0x2c 0x000000B0 - No Handler set for ISR I2S0_I2S1_QEI (IRQ 28) */
   ISR_NoHandler, /* 0x2d 0x000000B4 - No Handler set for ISR CCAN_0 (IRQ 29) */
   ISR_NoHandler, /* 0x2e 0x000000B8 - No Handler set for ISR ADCHS (IRQ 30) */
   ISR_NoHandler, /* 0x2f 0x000000BC - No Handler set for ISR M0SUB (IRQ 31) */
};

/*==================[internal functions definition]==========================*/
/* Default exception handlers. */

__attribute__ ((section(".after_vectors")))
void NMI_Handler(void) {
    while (1) {
    }
}


__attribute__ ((section(".after_vectors")))
void HardFault_Handler(void) {
    while (1) {
    }
}

__attribute__ ((section(".after_vectors")))
static void SVC_Handler(void) {
   while (1) {
    }
}


__attribute__ ((section(".after_vectors")))
static void ISR_NoHandler(void) {
   while (1) {
    }
}



/*==================[external functions definition]==========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

