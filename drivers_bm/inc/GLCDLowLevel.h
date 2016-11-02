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

// *****************************
// GLCD WG12864 Manager (Header)
// *****************************

#ifndef _GLCD_LOW_LEVEL_H_
#define _GLCD_LOW_LEVEL_H_

#include <stdint.h>

// ************
// LCD commandsGLCDLowLevel_DISPLAY_HEIGHT
// ************
#define LCD_ON								0x3F
#define LCD_OFF								0x3E
#define LCD_DISP_START						0xC0
#define LCD_SET_ADD							0x40
#define LCD_SET_PAGE						0xB8
#define LCD_BUSY_FLAG						0x80

// *************
// LCD constants
// *************
#define GLCDLowLevel_DISPLAY_WIDTH 			128
#define GLCDLowLevel_DISPLAY_HEIGHT			64
#define GLCDLowLevel_DISPLAY_PAGE_SIZE 		8
#define GLCDLowLevel_DISPLAY_HEIGHT_PAGES	GLCDLowLevel_DISPLAY_HEIGHT/GLCDLowLevel_DISPLAY_PAGE_SIZE
#define GLCDLowLevel_EN_DELAY_VALUE 		1

// Video Memory RAM
uint8_t	GLCDLowLevel_VideoRAM[GLCDLowLevel_DISPLAY_WIDTH][GLCDLowLevel_DISPLAY_HEIGHT_PAGES];

// *******************************
// Structures and Type Definitions
// *******************************
typedef uint8_t byte;

// ************************
// Low level GLCD Functions
// ************************
void GLCDLowLevel_Init (uint8_t invert);
void GLCDLowLevel_SwapBuffer ();

#endif
