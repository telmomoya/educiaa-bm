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

#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <stdint.h>

// *********************
// Structures Definition
// *********************
struct Button
{
	const char windowName[10];
	const char name[10];
	uint16_t height;
	uint16_t width;
	uint16_t xPos;
	uint16_t yPos;
	uint8_t color;
	const char fontName[15];
	uint8_t fontColor;
	char text[16];
//	void (*OnClickHandler) (void* voidPointerParams);
};
typedef struct Button TButton;

// *******
// Methods
// *******
void GUI_Button_Create (TButton* pButton, char* _windowName, char* _name, uint16_t _height, uint16_t _width,
						uint16_t _xPos,	uint16_t _yPos, uint8_t _color, char* _fontName, uint8_t _fontColor,
						char* _text);

void GUI_Button_Draw ( TButton* pButton );

#endif
