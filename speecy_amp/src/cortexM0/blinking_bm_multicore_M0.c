/* Copyright 2014, 2015 Mariano Cerdeiro
 * Copyright 2014, Pablo Ridolfi
 * Copyright 2014, Juan Cecconi
 * Copyright 2014, Gustavo Muro
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

/** \brief Bare Metal example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */
extern void NMI_Handler(void);						// Parece que estas funciones tienen que ser visibles desde la aplicacion, como estan en vector_m0.c
extern void HardFault_Handler(void);				// puse estos extern aqui y en vector_m0.c quite los static.
/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/


//////////////#include "vector.h"



#include "vga.h"       /* <= own header */
#include "itoa.h"

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */
#define CIAA_MULTICORE_IPC_MAILBOX1_ADDR  (*((volatile unsigned long *) 0x2000B000))
#define CIAA_MULTICORE_IPC_MAILBOX2_ADDR  (*((volatile unsigned long *) 0x2000B004))
#define CIAA_MULTICORE_CORE_1_IMAGE ((uint8_t *)0x1B000000)


/* User interface routines */
void myputchar(char c) {
   CIAA_MULTICORE_IPC_MAILBOX1_ADDR = c;
  while (CIAA_MULTICORE_IPC_MAILBOX1_ADDR!=0);

}

void myputs(const char *s) {
  while(*s) myputchar(*s++);
}

char mygetchar(void) {
	  unsigned long mailbox_in;
      while (CIAA_MULTICORE_IPC_MAILBOX2_ADDR==0);			/*espera mientras mailbox2 es 0*/
      mailbox_in=CIAA_MULTICORE_IPC_MAILBOX2_ADDR;          /*tomo el valor                */
      CIAA_MULTICORE_IPC_MAILBOX2_ADDR=0;                   /*pongo mailbox2 a 0           */
      return mailbox_in;
}

/////////////////////////////////////////////////////////////////////////////////////////////
#define MATCH	204			// Para acomodar el timer0 al clk

#define TRANSFER_SRC_ADDR   0x20000000			// Inicio de RamAHB32, origen de DMA
#define TRANSFER_DST_ADDR   0x400F610C			// GPIO a RGB, destino (no incrementable) de DMA
#define SRC_DIR(offset)  (*((volatile uint8_t *) TRANSFER_SRC_ADDR+offset))

// Variables globales
uint16_t usegundos;			// Cuenta usegundos, la incrementa la ISR del timer0

void DMA_IRQHandler(void){	// No se usa
}


void VGAcycle()	// ISR del timer0, cada 2us
{
	usegundos++;
}


int main(void)
{

/* inicializacion perifericos: puertos, timer y DMA*/
Chip_GPIO_Init(LPC_GPIO_PORT);
Chip_SCU_PinMux(HSYNC_MUX_GROUP,HSYNC_MUX_PIN,MD_PLN,FUNC4);			/* mapea HSYNC como GPIO, sin pull up ni pull down*/
Chip_SCU_PinMux(VSYNC_MUX_GROUP,VSYNC_MUX_PIN,MD_PLN,FUNC4);			/* mapea VSYNC como GPIO, sin pull up ni pull down*/
Chip_SCU_PinMux(RED_MUX_GROUP,RED_MUX_PIN,MD_PLN,FUNC0);				/* mapea RED como GPIO, sin pull up ni pull down*/
Chip_SCU_PinMux(GREEN_MUX_GROUP,GREEN_MUX_PIN,MD_PLN,FUNC0);			/* mapea GREEN como GPIO, sin pull up ni pull down*/
Chip_SCU_PinMux(BLUE_MUX_GROUP,BLUE_MUX_PIN,MD_PLN,FUNC0);				/* mapea BLUE como GPIO, sin pull up ni pull down*/
Chip_GPIO_SetDir(LPC_GPIO_PORT, HSYNC_GPIO_PORT,1<<HSYNC_GPIO_PIN,OUTPUT_DIR);		/* HSYNC como salida*/
Chip_GPIO_SetDir(LPC_GPIO_PORT, VSYNC_GPIO_PORT,1<<VSYNC_GPIO_PIN,OUTPUT_DIR);		/* VSYNC como salida*/
Chip_GPIO_SetDir(LPC_GPIO_PORT, RED_GPIO_PORT,1<<RED_GPIO_PIN,OUTPUT_DIR);			/* RED como salida*/
Chip_GPIO_SetDir(LPC_GPIO_PORT, GREEN_GPIO_PORT,1<<GREEN_GPIO_PIN,OUTPUT_DIR);		/* GREEN como salida*/
Chip_GPIO_SetDir(LPC_GPIO_PORT, BLUE_GPIO_PORT,1<<BLUE_GPIO_PIN,OUTPUT_DIR);		/* BLUE como salida*/

timer0Init_VGA(MATCH, &VGAcycle);		// Paso el match para timer0: 2us

// Inicializar DMA para GPIO
uint8_t dma_ch_gpio;  					// There are 8 DMA channels available
Chip_GPDMA_Init(LPC_GPDMA);
dma_ch_gpio = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, GPDMA_CONN_MEMORY);



// Inicio generación video
		uint16_t linea;					// Nro de linea en el frame
		HSYNC_HI;						//Estado inicial, syncs off, rgb off
		VSYNC_HI;
		RGB_LOW;

while(1)						//Loop de Frames de Video
 {
	//Nuevo Frame, sincronismo vertical
	usegundos=0;
	VSYNC_LOW;							// En este momento doy el pulso de vsync (activo a nivel bajo)
	while(usegundos< 64*(204/MATCH));	// que dura 64us
	VSYNC_HI;			 				// Termina pulso vsync
	while(usegundos<1020*(204/MATCH));	// Borde superior no visible: 1020us
	HSYNC_LOW;							// En este momento doy el pulso de hsync (activo a nivel bajo)
	for (linea=0; linea<525; linea++)	//Visibles desde la 33 a la 480
		{
		// Linea de Video, sincronismo horizontal
		usegundos=0;
		while(usegundos<2*(204/MATCH));			// que dura 4us
		HSYNC_HI;								// Termina pulso hsync
		while(usegundos<4*(204/MATCH));			// Portico Trasero 2us

//		CIAA_MULTICORE_IPC_MAILBOX1_ADDR=1;		// Reservo el recurso, para que M4 no escriba
		if ((linea>159)&(linea<352))
	{
	// Saco video, duración máxima: 25.42us



	Chip_GPDMA_Transfer(LPC_GPDMA, dma_ch_gpio,TRANSFER_SRC_ADDR+(linea-160)*256,TRANSFER_DST_ADDR,GPDMA_TRANSFERTYPE_VGA_CONTROLLER_DMA,1024);
	}

		//Apago_video				//
		while(usegundos<20*(204/MATCH));		// Fin de video pixels
		RGB_LOW;


		while(usegundos<31*(204/MATCH));		// Portico Delantero: 0.79us
		HSYNC_LOW;					// En este momento doy el pulso de hsync (activo a nivel bajo)
		// Fin línea de Video
		}
	CIAA_MULTICORE_IPC_MAILBOX1_ADDR=0;			// Libero el recurso, "supongo" que DMA terminó

	while(usegundos<333*(204/MATCH));			// Espero 300us hasta que termina el ciclo vertical
 	 }
}
