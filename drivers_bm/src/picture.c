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

#include "picture.h"

#include "GLCDColor.h"
#include "GLCDFonts.h"
#include "GLCDLowLevel.h"
#include "GLCDPrimitives.h"

void GUI_Picture_Create (TPicture* pPicture, char* _windowName, char* _name,
						 uint16_t _xPos, uint16_t _yPos, uint16_t _width,
						 uint16_t _height, const uint8_t* _bitmap, uint8_t _color)
{
	strcpy (pPicture->windowName, _windowName);
	strcpy (pPicture->name, _name);

	pPicture->xPos = _xPos;
	pPicture->yPos = _yPos;
	pPicture->width = _width;
	pPicture->height = _height;
	pPicture->color = _color;
	pPicture->bitmap = _bitmap;
}

void GUI_Picture_Draw ( TPicture* pPicture )
{
    // Draw de bitmap
    GLCDPrimitives_DrawBitmap (pPicture->bitmap, pPicture->xPos, pPicture->yPos, pPicture->color);
}
