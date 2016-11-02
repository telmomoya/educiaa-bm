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

#ifndef _GLCD_PRIMITIVES_H_
#define _GLCD_PRIMITIVES_H_

#include <stdint.h>

#include "GLCDColor.h"

void GLCDPrimitives_ClearScreen (uint32_t color);
void GLCDPrimitives_DrawBitmap (const uint8_t * bitmap, uint8_t x, uint8_t y, uint8_t color);
void GLCDPrimitives_SetDot (uint8_t x, uint8_t y, uint8_t color);
void GLCDPrimitives_DrawLine (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color);
void GLCDPrimitives_DrawRect (uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color);
void GLCDPrimitives_DrawRoundRect (uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t radius, uint8_t color);
void GLCDPrimitives_FillRect (uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color);

// This are functions.
// For speed and code efficiency they are implemented with MACROS
#define GLCDPrimitives_DrawVertLine(x, y, length, color) GLCDPrimitives_FillRect(x, y, 0, length, color)
#define GLCDPrimitives_DrawHoriLine(x, y, length, color) GLCDPrimitives_FillRect(x, y, length, 0, color)
#define GLCDPrimitives_DrawCircle(xCenter, yCenter, radius, color) GLCDPrimitives_DrawRoundRect(xCenter-radius, yCenter-radius, 2*radius, 2*radius, radius, color)

#endif
