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

#include "GLCDFonts.h"

static volatile lcdCoord	__GLCD_Coord;
static const uint8_t 		* Font;
static uint8_t  			FontColor;


//===========================================================================================================
//												Fonts
//===========================================================================================================

/* --------------------------------------------------------------------------------------
 * Name: FontRead
 * Function:
 * Args: color=[WHITE/BLACK]
 * Status: REVISION
 * Comments: Static, this is a private function
 * Revisions:
 * 	1) Initial Code
 * TODO: Replace with a MACRO
 * --------------------------------------------------------------------------------------
 * */

uint8_t FontRead(const uint8_t* ptr) {  // note this is a static function
	//return pgm_read_byte(ptr);
	return *ptr;
}

/* --------------------------------------------------------------------------------------
 * Name: GLCD_SelectFont
 * Function:
 * Args: color=[WHITE/BLACK]
 * Status: REVISION
 * Comments: PASARLA A UN MACRO
 * Revisions:
 * 	1) Initial Code
 * --------------------------------------------------------------------------------------
 * */

void GLCD_SelectFont(const uint8_t* font,uint8_t color) {
	Font = font;
	FontColor = color;
}

/* --------------------------------------------------------------------------------------
 * Name: GLCD_PrintNumber
 * Function:
 * Args: color=[WHITE/BLACK]
 * Status: REVISION
 * Comments:
 * Revisions:
 * 	1) Initial Code
 * --------------------------------------------------------------------------------------
 * */

void GLCD_PrintNumber(long n){
   byte buf[10];  // prints up to 10 digits
   byte i=0;
   if(n==0)
	   GLCD_PutChar('0');
   else{
	 if(n < 0){
        GLCD_PutChar('-');
		n = -n;
	 }
     while(n>0 && i <= 10){
	   buf[i++] = n % 10;  // n % base
	   n /= 10;   // n/= base
	 }
	 for(; i >0; i--)
		 GLCD_PutChar((char) (buf[i-1] < 10 ? '0' + buf[i-1] : 'A' + buf[i-1] - 10));
   }
}

/* --------------------------------------------------------------------------------------
 * Name: GLCD_PutChar
 * Function:
 * Args: color=[WHITE/BLACK]
 * Status: OK
 * Comments:
 * Revisions:
 * 	1) Initial Code
 * --------------------------------------------------------------------------------------
 * */
int GLCD_PutChar(char c) {
	uint8_t width = 0;
	uint8_t height = FontRead(Font+FONT_HEIGHT);
	uint8_t bytes = (height+7)/GLCDLowLevel_DISPLAY_PAGE_SIZE; // Sumando 7, hago que para fuentes de altura menor a 8 siempre use un byte
	                                                           // y en el caso de tener una fuente que supere los 8bits de altura, ya paso a
	                                                           // usar 2bytes, y así.

	uint8_t firstChar = FontRead(Font+FONT_FIRST_CHAR);
	uint8_t charCount = FontRead(Font+FONT_CHAR_COUNT);

	uint16_t index = 0; // Va a apuntar al primer elemento de la tabla de caracteres del archivo de la fuente seleccionada
	// Tanto x como y, van a determinar el punto en la GLCD_VideoRAM donde vaya a cargar los elementos que después representen el
	// char que recibió esta función.
	uint8_t x = __GLCD_Coord.x;
	uint8_t y = __GLCD_Coord.y/GLCDLowLevel_DISPLAY_PAGE_SIZE;

	if(c < firstChar || c >= (firstChar+charCount)) {
		return 1;
	}

	c-= firstChar; // desplazo el valor de c para que sea relativo a la posición de la tabla dentro del archivo de la fuente

	if( FontRead(Font+FONT_LENGTH) == 0 && FontRead(Font+FONT_LENGTH+1) == 0) {
    // zero length is flag indicating fixed width font (array does not contain width data entries)
	   width = FontRead(Font+FONT_FIXED_WIDTH); // El ancho de la fuente es el que aparece dentro del archivo, en la posición FONT_FIXED_WIDTH
	   index = c*bytes*width+FONT_WIDTH_TABLE; // Cada caracter en la tabla tiene "width" valores para representarlo. Entonces, para pasar de un carac
	   	   	   	   	   	   	   	   	   	   	   // ter a otro, necesito desplazarme "width" lugares dentro del archivo. por eso el "c*width".
	   	   	   	   	   	   	   	   	   	   	   // Por otra parte, bytes es 1, pero si fuese más, la tabla de caracteres cambiaría y por eso la multip.
	   	   	   	   	   	   	   	   	   	   	   // A tod o ese producto le sumo FONT_WIDTH_TABLE, que es en realidad donde inicia la tabla de caracteres.
	   	   	   	   	   	   	   	   	   	  // Los términos utilizados, al igual que el producto por "byte" no son aplicables a este caso. a este archivo.
	}
	else{
	// variable width font, read width data, to get the index
		uint8_t i;
	   for(i=0; i<c; i++) {
		 index += FontRead(Font+FONT_WIDTH_TABLE+i);
	   }
	   index = index*bytes+charCount+FONT_WIDTH_TABLE;
	   width = FontRead(Font+FONT_WIDTH_TABLE+c);
    }

	// Draw the character
	uint8_t i;
	uint8_t j;

	for( i=0; i<bytes; i++) {
		uint8_t page = i*width; //Uso page para el caso en que el archivo de la fuente tenga width variable
		for(j=0; j<width; j++) {
			uint8_t data = FontRead(Font+index+page+j); //Cargo el valor al que apunta index, dentro del archivo de la fuente

			if(height > 8 && height < (i+1)*8) { //Para casos en los que trabajo con fuentes de altura mayor a un byte, hago otras asignaciones a data.
											//Pero to do esto es en archivos que serían distintos al que estamos trabajando.
				data >>= (i+1)*8-height;
			}

			if(FontColor == BLACK) { //Cargo en el buffer de video el valor que cargué en data.
				GLCDLowLevel_VideoRAM[x+j][y+i]|=data;
				//__GLCD_WriteData(data);
			} else {
				GLCDLowLevel_VideoRAM[x+j][y+i]&=~data;
				//__GLCD_WriteData(~data);
			}
		} //El for se repite hasta que haya cargado una cantidad "width" de valores en la VideoRAM. Esto se corresponde con el hecho de que el valor
		//de width es la cantidad de columnas que voy a ocupar en la pantalla. cada columna, para una altura menor a 8 elementos, es un byte.


		// agrego una columna de elementos vacíos a la derecha del char cargado, correspondiendo al espacio entre caracteres.
		if(FontColor == BLACK) {
			GLCDLowLevel_VideoRAM[x+j+1][y+i] = WHITE;
		} else {
			GLCDLowLevel_VideoRAM[x+j+1][y+i] = BLACK;
		}
	}
	__GLCD_Coord.x += width + 1; //desplazo la coordenada sobre la que estoy trabajando en width+1, equivalente a un caracter.
	return 0;
}


/* --------------------------------------------------------------------------------------
 * Name: GLCD_Puts
 * Function: Escribo un string en la GLCD_VideoRAM
 * Args: color=[WHITE/BLACK]
 * Status: OK
 * Comments:
 * Revisions:
 * 	1) Initial Code
 * --------------------------------------------------------------------------------------
 * */
void GLCD_Puts(char* str) {
	int x = __GLCD_Coord.x;
	int y = __GLCD_Coord.y;

	while(*str != 0) {
		if(*str == '\n') { //Si el caracter al que estoy apuntando es un fin de linea..
			__GLCD_Coord.x =  x;
			__GLCD_Coord.y =  y + (FontRead(Font+FONT_HEIGHT)+1); //aumento mi coordenada en y en una cantidad igual a la altura de la fuente + 1 (espacio vacío)
		} else {
			GLCD_PutChar(*str); //Cargo en la GLCD_VideoRAM el caracter al que apunta
		}
		str++; //Me muevo al siguiente caracter
	}
}


/* --------------------------------------------------------------------------------------
 * Name: GLCD_FreePuts
 * Function:
 * Args: color=[WHITE/BLACK]
 * Status: OK
 * Comments:
 * Revisions:
 * 	1) Initial Code
 * --------------------------------------------------------------------------------------
 * */
void GLCD_FreePuts(char* str) {
	int x = __GLCD_Coord.x;
	int y = __GLCD_Coord.y;

	while(*str != 0) {
		if(*str == '\n') {
			__GLCD_Coord.x =  x;
			__GLCD_Coord.y =  y + (FontRead(Font+FONT_HEIGHT)+1);
		} else {
			GLCD_FreePutChar(*str);
		}
		str++;
	}
}


/* --------------------------------------------------------------------------------------
 * Name: GLCD_FreePutChar
 * Function: Escribo un caracter a una altura distinta a la "estándard".
 * Args: color=[WHITE/BLACK]
 * Status: OK
 * Comments:
 * Revisions:
 * 	1) Initial Code
 * --------------------------------------------------------------------------------------
 * */
int GLCD_FreePutChar(char c) {
	// Leo los datos del font
	uint8_t width = 0;
	uint8_t height = FontRead(Font+FONT_HEIGHT);
	uint8_t bytes = (height+7)/GLCDLowLevel_DISPLAY_PAGE_SIZE;

	uint8_t firstChar = FontRead(Font+FONT_FIRST_CHAR);
	uint8_t charCount = FontRead(Font+FONT_CHAR_COUNT);

	uint16_t index = 0;
	uint8_t x = __GLCD_Coord.x, y = __GLCD_Coord.y/GLCDLowLevel_DISPLAY_PAGE_SIZE;

	// Chequea si el caracter es válido
	if(c < firstChar || c >= (firstChar+charCount)) {
		return 1;
	}

	// Index c en la tabla de caracteres, ya no vale más el ascii
	c-= firstChar;

	if( FontRead(Font+FONT_LENGTH) == 0 && FontRead(Font+FONT_LENGTH+1) == 0) {
    // zero length is flag indicating fixed width font (array does not contain width data entries)
	   width = FontRead(Font+FONT_FIXED_WIDTH);
	   index = c*bytes*width+FONT_WIDTH_TABLE;
	}
	else{
	// variable width font, read width data, to get the index
		uint8_t i;
	   for(i=0; i<c; i++) {
		 index += FontRead(Font+FONT_WIDTH_TABLE+i);
	   }
	   index = index*bytes+charCount+FONT_WIDTH_TABLE;
	   width = FontRead(Font+FONT_WIDTH_TABLE+c);
    }

	// Draw the character
	uint8_t i;
	uint8_t j;
	uint8_t k;

	for( i=0; i<bytes; i++) {
		uint8_t page = i*width;
		for(j=0; j<width; j++) {
			uint8_t data = FontRead(Font+index+page+j);
			uint8_t auxdata = data;
// Parece que me permite escribir 'entre páginas'. El valor que quede en "data" va en una página y en "auxdata" en la pag siguiente.
// Desplaza ambos valores para que construyan entre ambos la línea del caracter deseado.
			data <<= (__GLCD_Coord.y)%GLCDLowLevel_DISPLAY_PAGE_SIZE;

			auxdata >>= 8-(__GLCD_Coord.y)%GLCDLowLevel_DISPLAY_PAGE_SIZE;

			if(height > 8 && height < (i+1)*8) {
				data >>= (i+1)*8-height;
			}

			if(FontColor == BLACK) {
				GLCDLowLevel_VideoRAM[x+j][y+i]|=data;
			} else {
				GLCDLowLevel_VideoRAM[x+j][y+i]&=~data;
			}

			if(height > 8 && height < (i+1)*8) {
				auxdata >>= (i+1)*8-height;
			}

			if(FontColor == BLACK) {
				GLCDLowLevel_VideoRAM[x+j][y+i+1]|=auxdata;
			} else {
				GLCDLowLevel_VideoRAM[x+j][y+i+1]&=~auxdata;
			}

		}
		//Agrega el caracter vacío desplazado al igual que el texto (respecto de una página común del LCD).
		uint8_t auxdata,data;
		data = auxdata =  0xFF;
		data <<= (__GLCD_Coord.y)%GLCDLowLevel_DISPLAY_PAGE_SIZE;
		auxdata >>= 8-(__GLCD_Coord.y)%GLCDLowLevel_DISPLAY_PAGE_SIZE;

		// 1px gap between chars
		if(FontColor == BLACK) {
			GLCDLowLevel_VideoRAM[x+j+1][y+i] &=~ data;
		} else {
			GLCDLowLevel_VideoRAM[x+j+1][y+i] |= data;
		}


		// 1px gap between chars
		if(FontColor == BLACK) {
			GLCDLowLevel_VideoRAM[x+j+1][y+i+1] &=~ auxdata;
		} else {
			GLCDLowLevel_VideoRAM[x+j+1][y+i+1] |= auxdata;
		}
	}
	__GLCD_Coord.x += width + 1; //Paso al siguiente caracter en x.
	return 0;
}


/* --------------------------------------------------------------------------------------
 * Name: GLCD_CharWidth
 * Function:
 * Args: color=[WHITE/BLACK]
 * Status: REVISION
 * Comments:
 * Revisions:
 * 	1) Initial Code
 * --------------------------------------------------------------------------------------
 * */
uint8_t GLCD_CharWidth(char c) {
	uint8_t width = 0;
	uint8_t firstChar = FontRead(Font+FONT_FIRST_CHAR);
	uint8_t charCount = FontRead(Font+FONT_CHAR_COUNT);

	// read width data
	if(c >= firstChar && c < (firstChar+charCount)) {
		c -= firstChar;
		width = FontRead(Font+FONT_WIDTH_TABLE+c)+1;
	}

	return width;
}

/* --------------------------------------------------------------------------------------
 * Name: GLCD_StringWidth
 * Function:
 * Args: color=[WHITE/BLACK]
 * Status: REVISION
 * Comments:
 * Revisions:
 * 	1) Initial Code
 * --------------------------------------------------------------------------------------
 * */
uint16_t GLCD_StringWidth(char* str) {
	uint16_t width = 0;

	while(*str != 0) {
		width += GLCD_CharWidth(*str++);
	}

	return width;
}

/* --------------------------------------------------------------------------------------
 * Name: GLCD_CursorTo
 * Function:
 * Args:
 * Status: OK
 * Comments:
 * Revisions:
 * 	1) Initial Code
 * --------------------------------------------------------------------------------------
 * */

void GLCD_CursorTo( uint8_t x, uint8_t y){
	// 0 based __GLCD_Coordinates for fixed width fonts (i.e. systemFont5x7)
	__GLCD_Coord.x =  x * (FontRead(Font+FONT_FIXED_WIDTH)+1);
	__GLCD_Coord.y =  y * (FontRead(Font+FONT_HEIGHT)+1);
}


/* --------------------------------------------------------------------------------------
 * Name: GLCD_CursorFreeTo
 * Function:
 * Args:
 * Status: OK
 * Comments:
 * Revisions:
 * 	1) Initial Code
 * --------------------------------------------------------------------------------------
 * */

void GLCD_CursorFreeTo( uint8_t x, uint8_t y){
	// 0 based __GLCD_Coordinates for fixed width fonts (i.e. systemFont5x7)
	__GLCD_Coord.x =  x;
	__GLCD_Coord.y =  y;
}
