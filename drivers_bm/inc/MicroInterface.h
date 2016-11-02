/*
   ********************* Authors *********************
   ***** Laboratorio de Sistemas Embebidos (LSE) *****
   *****    http://laboratorios.fi.uba.ar/lse    *****
   ******************* 20/12/2011 ********************
     Ezequiel Espósito <ezequiel.esposito@gmail.com>
         Alan Kharsansky <akharsa@gmail.com>
       Federico Roasio <federoasio@gmail.com>
     Daniel Schermuk <daniel.schermuk@gmail.com>
   ***************************************************
*/

// ********************************
// Microcontroller Interface (Head)
// ********************************

#ifndef _MICROINTERFACE_H_
#define _MICROINTERFACE_H_

#include <stdint.h>

// ********************************
// LPC pins assigned to LCD WG12864
// ********************************
#define LCD_CSEL2_PORT		3
#define CSEL2				5		// CS2 P0.22

#define LCD_CSEL1_PORT		5
#define CSEL1				16		// CS1 P2.13

//#define LCD_CMD_PORT		0
#define D_I					11		// D/I Bit
#define R_W					14		// R/W Bit
#define EN					13		// EN Bit

//#define LCD_DATA_PORT		0
#define D0					12
#define D1					6
#define D2					5
#define D3					4
#define D4					0
#define D5					3
#define D6					4
#define D7					15

#define true 1
#define false 0


// ******************************
// LPC digital I/O pins Functions
// ******************************
inline void MicroInterface_Init ();
inline void MicroInterface_Bit_WriteLow (uint8_t port, uint8_t pin);
inline void MicroInterface_Bit_WriteHigh (uint8_t port, uint8_t pin);
inline void MicroInterface_Byte_WriteData (uint8_t buf);

// ******
// Macros
// ******
#define EN_DELAY() for (_delayCounter=0; _delayCounter<10; _delayCounter++);

#endif
