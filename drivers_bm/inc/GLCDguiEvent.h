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

#ifndef GLCDGUIEVENT_H_
#define GLCDGUIEVENT_H_

enum GLCDgui_EnumEvents
{
	GLCD_CLICK = 0,
	GLCD_DOUBLECLICK = 1,
	GLCD_SCROLL_LEFTTORIGHT = 2,
	GLCD_SCROLL_RIGHTTOLEFT = 3,
	GLCD_DRAG = 4,
	GLCD_DROP = 5,
	GLCD_NOEVENT = 6
};
typedef enum GLCDgui_EnumEvents GLCDgui_EEvents;

struct GLCDgui_TypeEvent
{
	uint16_t xCoordinate;
	uint16_t yCoordinate;
	GLCDgui_EEvents eventType;
};
typedef struct GLCDgui_TypeEvent GLCDgui_TEvent;

#endif /* GLCDGUIEVENT_H_ */
