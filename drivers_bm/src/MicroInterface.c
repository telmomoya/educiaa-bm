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

#include "MicroInterface.h"

#include <stdint.h>
#include "chip.h"

uint32_t MaskedBuf;

//Mapeo de pines y seteo como salida
inline void MicroInterface_Init ()
{
	Chip_GPIO_Init(LPC_GPIO_PORT);

	// Mapeo pines de datos
	Chip_SCU_PinMux( 1, 3, MD_PUP, FUNC0); //D0 - SPI-MISO
	Chip_SCU_PinMux( 4, 6, MD_PUP, FUNC0); //D1 - LCD3
	Chip_SCU_PinMux( 4, 5, MD_PUP, FUNC0); //D2 - LCD2
	Chip_SCU_PinMux( 4, 4, MD_PUP, FUNC0); //D3 - LCD1
	Chip_SCU_PinMux( 6, 1, MD_PUP, FUNC0); //D4 - GPIO0
	Chip_SCU_PinMux( 6, 4, MD_PUP, FUNC0); //D5 - GPIO1
	Chip_SCU_PinMux( 6, 5, MD_PUP, FUNC0); //D6 - GPIO2
	Chip_SCU_PinMux( 6, 7, MD_PUP, FUNC4); //D7 - GPIO3

	//Mapeo pines de control
	Chip_SCU_PinMux( 1, 4, MD_PUP, FUNC0); //DI - SPI-MOSI
	Chip_SCU_PinMux( 4, 10, MD_PUP, FUNC4);  //R_W - LCD4
	Chip_SCU_PinMux( 4, 9, MD_PUP, FUNC4);  //EN - LCD_EN
	Chip_SCU_PinMux( 6, 8, MD_PUP, FUNC4);  //CS1 - GPIO4
	Chip_SCU_PinMux( 6, 9, MD_PUP, FUNC0);  //CS2 - GPIO5
	Chip_SCU_PinMux( 6, 10, MD_PUP, FUNC0); //RST - GPIO6 Activo por bajo, entonces lo dejo en alto.
	// Set as digital outputs LCD control lines

	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, 0, 11 ); //DI
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, 5, 14 ); //R_W
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, 5, 13 ); //EN
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, 5, 16 ); //CS1
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, 3, 5 ); //CS2
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, 3, 6 ); //RST
//	Chip_GPIO_SetPinDIROutput (LPC_GPIO_T,LCD_CMD_PORT, D_I);
//	Chip_G	PIO_SetPinDIROutput (LPC_GPIO_T,LCD_CMD_PORT,R_W);
//	Chip_GPIO_SetPinDIROutput (LPC_GPIO_T,LCD_CMD_PORT,EN);
//	Chip_GPIO_SetPinDIROutput (LPC_GPIO_T,LCD_CSEL1_PORT, CSEL1);
//	Chip_GPIO_SetPinDIROutput (LPC_GPIO_T,LCD_CSEL2_PORT, CSEL2);

	// Set as digital outputs LCD data lines

	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, 0, 10 ); //D0
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, 2, 6 ); //D1
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, 2, 5 ); //D2
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, 2, 4 ); //D3
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, 3, 0 ); //D4
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, 3, 3 ); //D5
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, 3, 4 ); //D6
	Chip_GPIO_SetPinDIROutput (LPC_GPIO_PORT, 5, 15 ); //D7
//	Chip_GPIO_SetPinDIROutput(LPC_GPIO_T, LCD_DATA_PORT,D0);
//	Chip_GPIO_SetPinDIROutput(LPC_GPIO_T, LCD_DATA_PORT,D1);
//	Chip_GPIO_SetPinDIROutput(LPC_GPIO_T, LCD_DATA_PORT,D2);
//	Chip_GPIO_SetPinDIROutput(LPC_GPIO_T, LCD_DATA_PORT,D3);
//	Chip_GPIO_SetPinDIROutput(LPC_GPIO_T, LCD_DATA_PORT,D4);
//	Chip_GPIO_SetPinDIROutput(LPC_GPIO_T, LCD_DATA_PORT,D5);
//	Chip_GPIO_SetPinDIROutput(LPC_GPIO_T, LCD_DATA_PORT,D6);
//	Chip_GPIO_SetPinDIROutput(LPC_GPIO_T, LCD_DATA_PORT,D7);

	Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 3, 6); //Dejo RST en alto.
}

inline void MicroInterface_Bit_WriteLow (uint8_t port, uint8_t pin)
{

	Chip_GPIO_SetPinState(LPC_GPIO_PORT, port, pin, false);
}

inline void MicroInterface_Bit_WriteHigh (uint8_t port, uint8_t pin)
{
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, port, pin, true);
}

inline void MicroInterface_Byte_WriteData (uint8_t buf)
{

	Chip_GPIO_SetPinState (LPC_GPIO_PORT, 0, 10, (buf>>0 & 0x01) ); //D0
	Chip_GPIO_SetPinState (LPC_GPIO_PORT, 2, 6,  (buf>>1 & 0x01) ); //D1
	Chip_GPIO_SetPinState (LPC_GPIO_PORT, 2, 5,  (buf>>2 & 0x01) ); //D2
	Chip_GPIO_SetPinState (LPC_GPIO_PORT, 2, 4,  (buf>>3 & 0x01) ); //D3
	Chip_GPIO_SetPinState (LPC_GPIO_PORT, 3, 0,  (buf>>4 & 0x01) ); //D4
	Chip_GPIO_SetPinState (LPC_GPIO_PORT, 3, 3,  (buf>>5 & 0x01) ); //D5
	Chip_GPIO_SetPinState (LPC_GPIO_PORT, 3, 4,  (buf>>6 & 0x01) ); //D6
	Chip_GPIO_SetPinState (LPC_GPIO_PORT, 5, 15, (buf>>7 & 0x01) ); //D7

//	Chip_GPIO_SetPinState (LPC_GPIO_PORT, 5, 12, (MaskedBuf>>0 & 0x01) ); //D0
//		Chip_GPIO_SetPinState (LPC_GPIO_PORT, 2, 6,  (MaskedBuf>>1 & 0x01) ); //D1
//		Chip_GPIO_SetPinState (LPC_GPIO_PORT, 2, 5,  (MaskedBuf>>2 & 0x01) ); //D2
//		Chip_GPIO_SetPinState (LPC_GPIO_PORT, 2, 4,  (MaskedBuf>>3 & 0x01) ); //D3
//		Chip_GPIO_SetPinState (LPC_GPIO_PORT, 3, 0,  (MaskedBuf>>4 & 0x01) ); //D4
//		Chip_GPIO_SetPinState (LPC_GPIO_PORT, 3, 3,  (MaskedBuf>>5 & 0x01) ); //D5
//		Chip_GPIO_SetPinState (LPC_GPIO_PORT, 3, 4,  (MaskedBuf>>6 & 0x01) ); //D6
//		Chip_GPIO_SetPinState (LPC_GPIO_PORT, 5, 15, (MaskedBuf>>7 & 0x01) ); //D7
//
	//Chip_GPIO_SetPortOutHigh(LPC_GPIO_T, LCD_DATA_PORT, MaskedBuf);
	//Chip_GPIO_SetPortOutLow(LPC_GPIO_T, LCD_DATA_PORT, buf);
}


