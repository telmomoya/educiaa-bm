/*
   ********************* Authors *********************
   ***** Laboratorio de Sistemas Embebidos (LSE) *****
   *****    http://laboratorios.fi.uba.ar/lse    *****
   ******************* 20/12/2011 ********************
     Ezequiel EspÃ³sito <ezequiel.esposito@gmail.com>
         Alan Kharsansky <akharsa@gmail.com>
       Federico Roasio <federoasio@gmail.com>
     Daniel Schermuk <daniel.schermuk@gmail.com>
   ***************************************************
*/

#include "GLCDLowLevel.h"

#include <stdint.h>

#include "MicroInterface.h"

// ******************
// Private Attributes
// ******************
int _delayCounter; // Used for EN_DELAY Macro

// ***************
// Private Methods
// ***************
static void SendData (byte _dataval, byte _chipval, byte _dival)
{
	// Enable chip
	if (_chipval==0)
		MicroInterface_Bit_WriteHigh (5, 16); //CS1
	else if (_chipval==1)
		MicroInterface_Bit_WriteHigh (3, 5); //CS2

	// Set write mode
	if (_dival==0)
		MicroInterface_Bit_WriteLow (0, 11); // DI
	else if (_dival==1)
		MicroInterface_Bit_WriteHigh (0, 11); // DI

	EN_DELAY ();
	MicroInterface_Byte_WriteData (_dataval);

	// Clock data
	MicroInterface_Bit_WriteHigh (5, 13); //EN
	EN_DELAY ();
	MicroInterface_Bit_WriteLow (5, 13); //EN

	// Disable chip
	MicroInterface_Bit_WriteLow (LCD_CSEL1_PORT, CSEL1); //CS1
	MicroInterface_Bit_WriteLow (LCD_CSEL2_PORT, CSEL2); //CS2
}

void GLCDLowLevel_Init(uint8_t invert)
{
	MicroInterface_Init();

	// Start LCD control lines in 0
	MicroInterface_Bit_WriteLow (0, D_I);
	MicroInterface_Bit_WriteLow (5, R_W);
	MicroInterface_Bit_WriteLow (5, EN);
	MicroInterface_Bit_WriteLow (LCD_CSEL1_PORT, CSEL1);
	MicroInterface_Bit_WriteLow (LCD_CSEL2_PORT, CSEL2);

	SendData (LCD_ON|1,0,0); // Chip1 display on
	SendData (LCD_ON|1,1,0); // Chip2 display on

	SendData (LCD_DISP_START,0,0); // Set Z address to 0, chip1
	SendData (LCD_DISP_START,1,0); // Set Z address to 0, chip2

	uint8_t i,j;
	for (i=0;i<GLCDLowLevel_DISPLAY_WIDTH;i++)
	{
		for (j=0;j<GLCDLowLevel_DISPLAY_HEIGHT_PAGES;j++)
		{
			GLCDLowLevel_VideoRAM[i][j] = 0x00;
		}
	}
	GLCDLowLevel_SwapBuffer();
}

void GLCDLowLevel_SwapBuffer(){
	SendData(LCD_SET_ADD|0,0,0);
	SendData(LCD_SET_ADD|0,1,0);
	uint8_t i,j;
	for(j=0;j<GLCDLowLevel_DISPLAY_HEIGHT_PAGES;j++){//scan 8 vertical rows of 8bits each
		SendData(LCD_SET_PAGE|j,0,0);
		SendData(LCD_SET_PAGE|j,1,0);
		for( i=0;i<GLCDLowLevel_DISPLAY_WIDTH/2;i++){//scan 64 horizontal to both chips
			SendData(GLCDLowLevel_VideoRAM[i][j],0,1);
			SendData(GLCDLowLevel_VideoRAM[i+GLCDLowLevel_DISPLAY_WIDTH/2][j],1,1);
		}
	}
}
