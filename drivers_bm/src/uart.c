/* Copyright 2016, 
 * Leandro D. Medus
 * lmedus@bioingenieria.edu.ar
 * Eduardo Filomena
 * efilomena@bioingenieria.edu.ar
 * Juan Manuel Reta
 * jmrera@bioingenieria.edu.ar
 * Facultad de Ingeniería
 * Universidad Nacional de Entre Ríos
 * Argentina
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief Bare Metal driver for uart in the EDU-CIAA board.
 **
 **/

/*
 * Initials     Name
 * ---------------------------
 *	LM			Leandro Medus
 *  EF			Eduardo Filomena
 *  JMR			Juan Manuel Reta
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20160422 v0.1 initials initial version leo
 * 20160807 v0.2 modifications and improvements made by Eduardo Filomena 
 */

/*==================[inclusions]=============================================*/
#include "uart.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief ADC Initialization method  */
uint8_t init_UART_FTDI_EDUCIAA(void)
{

	/* UART2 (USB-UART) */
	
	Chip_UART_Init(LPC_USART2);
	Chip_UART_SetBaud(LPC_USART2, 115200);

	Chip_UART_SetupFIFOS(LPC_USART2, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0);

	Chip_UART_TXEnable(LPC_USART2);

Chip_SCU_PinMux(7, 1, MD_PDN, FUNC6);              /* P7_1: UART2_TXD */
	Chip_SCU_PinMux(7, 2, MD_PLN|MD_EZI|MD_ZI, FUNC6); /* P7_2: UART2_RXD */

	return TRUE;
}

uint8_t init_UART_RS485_EDUCIAA(void)
{

	/** \details
	 * This function initialize the ADC peripheral in the EDU-CIAA board,
	 * with the correct parameters with LPCOpen library. It uses CH1
	 *
	 * \param none
	 *
	 * \return uint8_t: TBD (to support errors in the init function)
	 * */

	/*UART initialization*/

	/* UART0 (RS485/Profibus) */
	Chip_UART_Init(LPC_USART0);
	Chip_UART_SetBaud(LPC_USART0, 115200);

	Chip_UART_SetupFIFOS(LPC_USART0, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0);

	Chip_UART_TXEnable(LPC_USART0);

	Chip_SCU_PinMux(9, 5, MD_PDN, FUNC7);              /* P9_5: UART0_TXD */
	Chip_SCU_PinMux(9, 6, MD_PLN|MD_EZI|MD_ZI, FUNC7); /* P9_6: UART0_RXD */
    
	Chip_UART_SetRS485Flags(LPC_USART0, UART_RS485CTRL_DCTRL_EN | UART_RS485CTRL_OINV_1);

	Chip_SCU_PinMux(6, 2, MD_PDN, FUNC2);              /* P6_2: UART0_DIR */

	return TRUE;
}

uint8_t init_UART_RS232_EDUCIAA(void)
{


	Chip_UART_Init(LPC_USART3);
	Chip_UART_SetBaud(LPC_USART3, 19200);

	Chip_UART_SetupFIFOS(LPC_USART3, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0);

	Chip_UART_TXEnable(LPC_USART3);

	Chip_SCU_PinMux(2, 3, MD_PDN, FUNC2);              /* P2_3: UART3_TXD */
	Chip_SCU_PinMux(2, 4, MD_PLN|MD_EZI|MD_ZI, FUNC2); /* P2_4: UART3_RXD */

	return TRUE;
}

uint8_t readByte_UART_USB_EDUCIAA()
{
	return Chip_UART_ReadByte(LPC_USART2);
}
uint8_t readByte_UART_RS232_EDUCIAA(){
	return Chip_UART_ReadByte(LPC_USART3);

}

void writeByte_UART_USB_EDUCIAA(uint8_t dato)
{
	Chip_UART_SendByte(LPC_USART2,dato);
}
void writeByte_UART_RS232_EDUCIAA(uint8_t dato)
{
	Chip_UART_SendByte(LPC_USART3,dato);
}



uint32_t readStatus_UART_USB_EDUCIAA()
{
	return (Chip_UART_ReadLineStatus((LPC_USART_T *)LPC_USART2) & UART_LSR_THRE);
}
uint32_t readStatus_UART_RS232_EDUCIAA()
{
	return (Chip_UART_ReadLineStatus((LPC_USART_T *)LPC_USART3) & UART_LSR_THRE);
}

void sendString_UART_USB_EDUCIAA(char message[], uint8_t size)
{
	uint8_t msjIndex = 0;
	uint64_t i;

	/* sending byte by byte*/
	while(( readStatus_UART_USB_EDUCIAA() != 0) && (msjIndex < size) && (message[msjIndex]!=0))
	{
		Chip_UART_SendByte((LPC_USART_T *)LPC_USART2, message[msjIndex]);

		/*delay*/
		for (i=0;i<50000;i++)
		{
			asm  ("nop");
		}
		msjIndex++;
	}

}
void sendString_UART_RS232_EDUCIAA(char message[], uint8_t size)
{
	uint8_t msjIndex = 0;
	uint64_t i;

	/* sending byte by byte*/
	while(( readStatus_UART_RS232_EDUCIAA() != 0) && (msjIndex < size))
	{
		Chip_UART_SendByte(LPC_USART3, message[msjIndex]);

		/*delay*/
		for (i=0;i<50000;i++)
		{
			asm  ("nop");
		}
		msjIndex++;
	}

}

void intToString(int16_t value, uint8_t* pBuf, uint32_t len, uint32_t base)
{
	/**
	 * \details
	 * Conversion method to obtain a character or a string from a float to send
	 * throw UART peripheral.
	 * */
    static const char* pAscii = "0123456789abcdefghijklmnopqrstuvwxyz";
    int pos = 0;
    int tmpValue = value;

    /*  the buffer must not be null and at least have a length of 2 to handle one */
    /*  digit and null-terminator */
    if (pBuf == NULL || len < 2)
    {
        return;
    }

    /* a valid base cannot be less than 2 or larger than 36 */
    /* a base value of 2 means binary representation. A value of 1 would mean only zeros */
    /*  a base larger than 36 can only be used if a larger alphabet were used. */
    if (base < 2 || base > 36)
    {
        return;
    }

    /* negative value */
    if (value < 0)
    {
        tmpValue = -tmpValue;
        value    = -value;
        pBuf[pos++] = '-';
    }

    /* calculate the required length of the buffer */
    do {
        pos++;
        tmpValue /= base;
    } while(tmpValue > 0);


    if (pos > len)
    {
    	/* the len parameter is invalid. */
        return;
    }

    pBuf[pos] = '\0';

    do {
        pBuf[--pos] = pAscii[value % base];
        value /= base;
    } while(value > 0);

    return;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
