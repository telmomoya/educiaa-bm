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

#ifndef _TEXT_H_
#define _TEXT_H_

#include <stdint.h>


#define MAX_TEXT_LENGHT 20

// *********************
// Structures Definition
// *********************
struct typeText
{
	char windowName[10];
	char name[10];
	uint16_t xPos;
	uint16_t yPos;
	char fontName[15];
	uint8_t fontColor;
	char text[MAX_TEXT_LENGHT];
};
typedef struct typeText TText;

// *******
// Methods
// *******
void GUI_Text_Create (TText* pText, char* _windowName, char* _name, uint16_t _xPos, uint16_t _yPos,
					    char* _fontName, uint8_t _fontColor, char* _text);

void GUI_Text_Draw ( TText* pText );

#endif /* TEXT_H_ */
