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

#ifndef _GLCD_FONTS_H_
#define _GLCD_FONTS_H_

#include <stdint.h>

#include "GLCDLowLevel.h"
#include "GLCDPrimitives.h"

typedef struct {
	uint8_t x;
	uint8_t y;
	uint8_t page;
} lcdCoord;

// Font Indices
#define FONT_LENGTH			0
#define FONT_FIXED_WIDTH	2
#define FONT_HEIGHT			3
#define FONT_FIRST_CHAR		4
#define FONT_CHAR_COUNT		5
#define FONT_WIDTH_TABLE	6

void GLCD_SelectFont(const uint8_t * font, uint8_t color); // defualt arguments added, callback now last arg
int GLCD_PutChar(char c);
void GLCD_Puts(char* str);
int GLCD_FreePutChar(char c);
void GLCD_FreePuts(char* str);
void GLCD_PrintNumber(long n);
uint8_t GLCD_CharWidth(char c);
uint16_t GLCD_StringWidth(char* str);
void GLCD_CursorTo( uint8_t x, uint8_t y); // 0 based coordinates for fixed width fonts (i.e. systemFont5x7)
void GLCD_CursorFreeTo( uint8_t x, uint8_t y);

#define GLCD_ClearSysTextLine(_line) GLCD_FillRect(0, (_line*8), (DISPLAY_WIDTH-1), ((_line*8)+ 7), WHITE )

#endif
