/*==================[inclusions]=============================================*/
#include "billete.h"
#include "stdint.h"
#include "button.h"
#include "Bitmaps.h"
#include "GLCDColor.h"
#include "GLCDFonts.h"
#include "GLCDgui.h"
#include "GLCDguiEvent.h"
#include "GLCDLowLevel.h"
#include "GLCDPrimitives.h"
#include "led.h"
#include "MicroInterface.h"
#include "picture.h"
#include "switch.h"
#include "SysFont3x5.h"
#include "SystemFont5x7.h"
#include "text.h"
#include "window.h"
#include "GLCDColor.h"
#include "string.h"
#include "uart.h"
#include "itoa.h"
/*==================[macros and definitions]=================================*/

#define PERIOD 3000000
enum EFFECT {NO_EFFECT, MOV_ICON, MOV_LINE1, MOV_LINE2, MOV_LINE3};

#define X_POS_ICON   5
#define Y_POS_LINE_1   20
#define Y_POS_LINE_2   30
#define Y_POS_LINE_3   38
#define X_POS_LINE_4   30
#define Y_POS_LINE_4   46
#define X_POS_LINE_5   30
#define Y_POS_LINE_5   54

#define Y_MIN_ICON   30
#define Y_MAX_ICON  60

#define X_MIN_LINE1  20
#define X_MAX_LINE1  40
#define X_MIN_LINE2  30
#define X_MAX_LINE2  60
#define X_MIN_LINE3  30
#define X_MAX_LINE3  60


#define READER_BAUDS	9600

// Mensajes del BV20 para las  denominaciones cargadas
#define C1	2
#define C2	5
#define C3	10
#define C4	20
#define C5	50
#define C6	100

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/


/*==================[internal data definition]===============================*/
char Login[10] = "Login";
char text[10] = " ";
uint8_t* color = BLACK;

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

void init_Screen()
{
	uint8_t y_pos_icon, x_pos_line1,x_pos_line2,x_pos_line3;
//	uint8_t tec;
//	uint32_t i;
	GUI_StartLibrary ();

	y_pos_icon = Y_MIN_ICON;
	x_pos_line1 = X_MIN_LINE1;
	x_pos_line2 = X_MIN_LINE2;
	x_pos_line3 = X_MIN_LINE3;

	GUI_Window_Create (Login, color, text );
	GUI_Window_AddText (Login, "row1", 20, 20, "SystemFont5x7", WHITE, "INTRODUZCA");
	GUI_Window_AddText (Login, "row2", 30, 30, "SystemFont5x7", WHITE, "BILLETES DE");
	GUI_Window_AddText (Login, "row3", 30, 38, "SystemFont5x7", WHITE, "$2 $5 $10 $20");
	GUI_Window_AddText (Login, "row4", 30, 46, "SystemFont5x7", WHITE, "$50 o $100");
	GUI_Window_AddText (Login, "row5", 30, 54, "SystemFont5x7", WHITE, "HASTA TOTALIZAR $100");
	GUI_Window_Draw (Login);
	}


uint8_t LeerBillete()
	{
	uint8_t denominacion[] = {0,C1,C2,C3,C4,C5,C6};
	uint8_t dato = 0;
	while (1)
		{
		dato = readByte_UART_RS232_EDUCIAA();

		if (dato!=0)
			{
			if (dato==120)
				{
/*
				sendString_UART_USB_EDUCIAA("Bussy", 7);
				writeByte_UART_USB_EDUCIAA(0xa);
				writeByte_UART_USB_EDUCIAA(0xd);
*/
				}

			if (dato==121)
				{
/*
				sendString_UART_USB_EDUCIAA("Ready", 5);
				writeByte_UART_USB_EDUCIAA(0xa);
				writeByte_UART_USB_EDUCIAA(0xd);
*/
				}

			if (dato==20)
				{
				sendString_UART_USB_EDUCIAA("No reconocido", 13);
				writeByte_UART_USB_EDUCIAA(0xa);
				writeByte_UART_USB_EDUCIAA(0xd);
				}

			if (dato==50)
				{
				sendString_UART_USB_EDUCIAA("Falso", 13);
				writeByte_UART_USB_EDUCIAA(0xa);
				writeByte_UART_USB_EDUCIAA(0xd);
				}

			if (dato<17)
				{
				return (denominacion[dato]);
				}
			}

		}
}


int main(void)
{
init_Screen();
init_UART_FTDI_EDUCIAA();
init_UART_RS232_EDUCIAA(READER_BAUDS);
writeByte_UART_USB_EDUCIAA(0x2e);
writeByte_UART_USB_EDUCIAA(0xa);
writeByte_UART_USB_EDUCIAA(0xd);

uint8_t valor;
uint32_t total = 0;


while(1)
	{
	sendString_UART_USB_EDUCIAA("Esperando billete",18);
	writeByte_UART_USB_EDUCIAA(0x9);
	valor = LeerBillete();
	if (valor!=0)
		{
		total = total + valor;


		GUI_Window_Create (Login, color, text );
		GUI_Window_AddText (Login, "row1", 30, 20, "SystemFont5x7", WHITE, "TOMADO");
		GUI_Window_AddText (Login, "row2", 30, 30, "SystemFont5x7", WHITE, "BILLETE DE");
		GUI_Window_AddText (Login, "row3", 30, 38, "SystemFont5x7", WHITE, "$");
		GUI_Window_AddText (Login, "row3", 35, 38, "SystemFont5x7", WHITE, Itoa(valor,10));
		GUI_Window_AddText (Login, "row4", 30, 46, "SystemFont5x7", WHITE, "TOTAL");
		GUI_Window_AddText (Login, "row5", 30, 38, "SystemFont5x7", WHITE, "$");
		GUI_Window_AddText (Login, "row5", 35, 54, "SystemFont5x7", WHITE, Itoa(total,10));
		GUI_Window_Draw (Login);

//		GLCDPrimitives_ClearScreen(WHITE);

		sendString_UART_USB_EDUCIAA("Sumados $",9);
		sendString_UART_USB_EDUCIAA(Itoa(valor,10),3);
		writeByte_UART_USB_EDUCIAA(0x9);


		sendString_UART_USB_EDUCIAA("Total acumulado $",17);
		sendString_UART_USB_EDUCIAA(Itoa(total,10),3);
		writeByte_UART_USB_EDUCIAA(0xa);
		writeByte_UART_USB_EDUCIAA(0xd);
		}
	}
}
