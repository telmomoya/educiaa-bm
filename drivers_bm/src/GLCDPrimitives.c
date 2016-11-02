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

#include "GLCDPrimitives.h"

#include <stdint.h>

#include "GLCDColor.h"
#include "GLCDLowLevel.h"

// ***************
// Private Methods
// ***************
// MODIFICAR ESTA HARDCODEADO
void SetPage(uint8_t x, uint8_t page, uint8_t val)
{
	if ((page<0)||(page>7)||(x<0)||(x>127))
		return;

	GLCDLowLevel_VideoRAM[x][page]=val;
}

// ******************
// Graphic Primitives
// ******************

/* --------------------------------------------------------------------------------------
 * Name: GLCDPrimitives_ClearScreen
 * Function: Borra la pantalla
 * Args: color=[WHITE/BLACK]
 * Status: OK
 * Comments:
 * Revisions:
 * 	1) Initial Code
 * --------------------------------------------------------------------------------------
 * */
void GLCDPrimitives_ClearScreen(uint32_t color)
{
	uint8_t i,j;
	for (i = 0; i < GLCDLowLevel_DISPLAY_WIDTH; i++)
	{
		for (j = 0; j < GLCDLowLevel_DISPLAY_HEIGHT_PAGES; j++)
		{
			if ( color == BLACK)
				GLCDLowLevel_VideoRAM[i][j] = 0x00;
			else
				GLCDLowLevel_VideoRAM[i][j] = 0xFF;
		}
	}
}

/* --------------------------------------------------------------------------------------
 * Name: GLCDPrimitives_DrawBitmap
 * Function: Copia un bitmap de alguna posicion
 * 			de la RAM a la memoria de video
 * Args: color=[WHITE/BLACK]
 * Status: OK
 * Comments:
 * Revisions:
 * 	1) Initial Code
 * --------------------------------------------------------------------------------------
 * */
void GLCDPrimitives_DrawBitmap(const uint8_t * bitmap, uint8_t x, uint8_t y, uint8_t color)
{
	uint8_t width, height;
	uint8_t i, j;

	width = *(bitmap++);
	height = *(bitmap++);

	for(j = 0; j < height / 8; j++)
	{
		for(i = 0; i < width; i++)
		{
			uint8_t displayData = *(bitmap++);
			if(color == BLACK)
				SetPage (i+x,j+y/GLCDLowLevel_DISPLAY_PAGE_SIZE,displayData);
			else
				SetPage (i+x,j+y/GLCDLowLevel_DISPLAY_PAGE_SIZE,~displayData);
		}
	}
}


/* --------------------------------------------------------------------------------------
 * Name: GLCDPrimitives_SetDot
 * Function: Pinta un pixel en las coordenadas correspondientes
 * Args: color=[WHITE/BLACK]
 * Status: OK
 * Comments:
 * Revisions:
 * 	1) Initial Code
 * --------------------------------------------------------------------------------------
 * */
// MODIFICAR ESTA HARDCODEADO
void GLCDPrimitives_SetDot(uint8_t x, uint8_t y, uint8_t color)
{
	if ((y<0)||(y>63)||(x<0)||(x>127))
		return;

	if (y!=0)
	{
		if (color==WHITE)
			GLCDLowLevel_VideoRAM[x][y/8] &= ~(1<<y%8);
		else
			GLCDLowLevel_VideoRAM[x][y/8] |= (1<<y%8);
	}
	else
	{
		if (color == WHITE)
			GLCDLowLevel_VideoRAM[x][0] &= ~(1<<0);
		else
			GLCDLowLevel_VideoRAM[x][0] |= (1<<0);
	}
}

/* --------------------------------------------------------------------------------------
 * Name: GLCDPrimitives_DrawLine
 * Function: Dibuja lineas, puede ser en cualquier angulo.
 * Args: color=[WHITE/BLACK]
 * Status: OK
 * Comments:
 * Revisions:
 * 	1) Initial Code
 * --------------------------------------------------------------------------------------
 * */
void GLCDPrimitives_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color)
{
	uint8_t length, i, y, yAlt, xTmp, yTmp;
	int16_t m;
	//
	// vertical line
	//
	if(x1 == x2) {
		// x1|y1 must be the upper point
		if(y1 > y2) {
			yTmp = y1;
			y1 = y2;
			y2 = yTmp;
		}
		GLCDPrimitives_DrawVertLine(x1, y1, y2-y1, color);

	//
	// horizontal line
	//
	} else if(y1 == y2) {
		// x1|y1 must be the left point
		if(x1 > x2) {
			xTmp = x1;
			x1 = x2;
			x2 = xTmp;
		}
		GLCDPrimitives_DrawHoriLine(x1, y1, x2-x1, color);

	//
	// angled line :)
	//
	} else {
		// angle >= 45�
		if((y2-y1) >= (x2-x1) || (y1-y2) >= (x2-x1)) {
			// x1 must be smaller than x2
			if(x1 > x2) {
				xTmp = x1;
				yTmp = y1;
				x1 = x2;
				y1 = y2;
				x2 = xTmp;
				y2 = yTmp;
			}

			length = x2-x1;		// not really the length :)
			m = ((y2-y1)*200)/length;
			yAlt = y1;

			for(i=0; i<=length; i++) {
				y = ((m*i)/200)+y1;

				if((m*i)%200 >= 100)
					y++;
				else if((m*i)%200 <= -100)
					y--;

				GLCDPrimitives_DrawLine(x1+i, yAlt, x1+i, y, color);

				if(length <= (y2-y1) && y1 < y2)
					yAlt = y+1;
				else if(length <= (y1-y2) && y1 > y2)
					yAlt = y-1;
				else
					yAlt = y;
			}

		// angle < 45�
		} else {
			// y1 must be smaller than y2
			if(y1 > y2) {
				xTmp = x1;
				yTmp = y1;
				x1 = x2;
				y1 = y2;
				x2 = xTmp;
				y2 = yTmp;
			}

			length = y2-y1;
			m = ((x2-x1)*200)/length;
			yAlt = x1;

			for(i=0; i<=length; i++) {
				y = ((m*i)/200)+x1;

				if((m*i)%200 >= 100)
					y++;
				else if((m*i)%200 <= -100)
					y--;

				GLCDPrimitives_DrawLine(yAlt, y1+i, y, y1+i, color);
				if(length <= (x2-x1) && x1 < x2)
					yAlt = y+1;
				else if(length <= (x1-x2) && x1 > x2)
					yAlt = y-1;
				else
					yAlt = y;
			}
		}
	}
}

/* --------------------------------------------------------------------------------------
 * Name: GLCDPrimitives_DrawRect
 * Function: Dibuja un rectangulo
 * Args: color=[WHITE/BLACK]
 * Status: OK
 * Comments:
 * Revisions:
 * 	1) Initial Code
 * --------------------------------------------------------------------------------------
 * */
void GLCDPrimitives_DrawRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color)
{
	GLCDPrimitives_DrawHoriLine(x, y, width, color);				// top
	GLCDPrimitives_DrawHoriLine(x, y+height, width, color);		// bottom
	GLCDPrimitives_DrawVertLine(x, y, height, color);			// left
	GLCDPrimitives_DrawVertLine(x+width, y, height, color);		// right
}

/* --------------------------------------------------------------------------------------
 * Name: GLCDPrimitives_DrawRoundRect
 * Function: Dibuja un rectangulo con bordes redondeados
 * Args: color=[WHITE/BLACK]
 * Status: OK
 * Comments:
 * Revisions:
 * 	1) Initial Code
 * --------------------------------------------------------------------------------------
 * */
void GLCDPrimitives_DrawRoundRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t radius, uint8_t color)
{
  	int16_t tSwitch, x1 = 0, y1 = radius;
  	tSwitch = 3 - 2 * radius;

  	if (width<height){
  		if (radius>(width/2))
  			return ;
  	}else{
  		if (radius>(height/2))
  		  	return ;
  	}

	while (x1 <= y1) {
	    GLCDPrimitives_SetDot(x+radius - x1, y+radius - y1, color);
	    GLCDPrimitives_SetDot(x+radius - y1, y+radius - x1, color);

	    GLCDPrimitives_SetDot(x+width-radius + x1, y+radius - y1, color);
	    GLCDPrimitives_SetDot(x+width-radius + y1, y+radius - x1, color);

	    GLCDPrimitives_SetDot(x+width-radius + x1, y+height-radius + y1, color);
	    GLCDPrimitives_SetDot(x+width-radius + y1, y+height-radius + x1, color);

	    GLCDPrimitives_SetDot(x+radius - x1, y+height-radius + y1, color);
	    GLCDPrimitives_SetDot(x+radius - y1, y+height-radius + x1, color);

	    if (tSwitch < 0) {
	    	tSwitch += (4 * x1 + 6);
	    } else {
	    	tSwitch += (4 * (x1 - y1) + 10);
	    	y1--;
	    }
	    x1++;
	}

	GLCDPrimitives_DrawHoriLine(x+radius, y, width-(2*radius), color);			// top
	GLCDPrimitives_DrawHoriLine(x+radius, y+height, width-(2*radius), color);	// bottom
	GLCDPrimitives_DrawVertLine(x, y+radius, height-(2*radius), color);			// left
	GLCDPrimitives_DrawVertLine(x+width, y+radius, height-(2*radius), color);	// right
}

/* --------------------------------------------------------------------------------------
 * Name: GLCDPrimitives_FillRect
 * Function: Dibuja un rectangulo relleno de color
 * Args: color=[WHITE/BLACK]
 * Status: OK
 * Comments: También se la utiliza para pintar lineas
 * Revisions:
 * 	1) Initial Code
 * --------------------------------------------------------------------------------------
 * */
void GLCDPrimitives_FillRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color)
{
	uint8_t mask, pageOffset, h, i;
	height++;

	pageOffset = y%8;
	y -= pageOffset;
	mask = 0xFF;

	if(height < 8-pageOffset) {
		mask >>= (8-height);
		h = height;
	} else {
		h = 8-pageOffset;
	}
	mask <<= pageOffset;

	for(i=0; i<=width; i++) {
		if(color == BLACK) {
			GLCDLowLevel_VideoRAM[x+i][y/8] |= mask;
		} else {
			GLCDLowLevel_VideoRAM[x+i][y/8] &= ~mask;
		}
	}

	while(h+8 <= height) {
		h += 8;
		y += 8;

		for(i=0; i<=width; i++) {
			if(color == BLACK) {
				//VideoRAM[x+i][y/8] |= color;
				GLCDLowLevel_VideoRAM[x+i][y/8]  = 0xFF;
			} else {
				//VideoRAM[x+i][y/8] &= ~color;
				GLCDLowLevel_VideoRAM[x+i][y/8]  = 0x00;
			}
		}
	}

	if(h < height) {
		mask = ~(0xFF << (height-h));
		y = y + 8;
		for(i=0; i<=width; i++) {
			if(color == BLACK) {
				GLCDLowLevel_VideoRAM[x+i][y/8] |= mask;
			} else {
				GLCDLowLevel_VideoRAM[x+i][y/8] &= ~mask;
			}
		}
	}
}

