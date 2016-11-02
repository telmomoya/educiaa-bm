/* Copyright 2016, XXXX
 *
 *  * All rights reserved.
 *
 * This file is part of CIAA Firmware.
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

/** \brief Blinking Bare Metal example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "adc_uart.h"       /* <= own header */
/*==================[macros and definitions]=================================*/
#define PERIOD			150000
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
#define UMBRAL_INICIAL 1000
/*==================[external data definition]===============================*/
/*==================[internal functions definition]==========================*/
/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */

uint16_t umbral = UMBRAL_INICIAL;
uint16_t retardo;

void LeeDatoAnalogico()
{
	if (retardo!=0) retardo--;
	InvierteLed(LED_AMARILLO);
	uint16_t lectura;
	lectura = read_ADC_value();
	if (lectura>umbral)
	{
		EncenderLed(LED_ROJO);
		ApagarLed(LED_VERDE);
	}
	else
	{
		EncenderLed(LED_VERDE);
		ApagarLed(LED_ROJO);
	}

//	sendString_UART_USB_EDUCIAA("OK", 2);

//	sendString_UART_USB_EDUCIAA(Itoa(lectura,10), 10);
//	writeByte_UART_USB_EDUCIAA(9);
//	writeByte_UART_USB_EDUCIAA(9);
//	writeByte_UART_USB_EDUCIAA(9);


	sendString_UART_USB_EDUCIAA(Itoa(umbral,10), 10);
	writeByte_UART_USB_EDUCIAA(13);
	writeByte_UART_USB_EDUCIAA(10);
}

int main(void)
{
   /* inicializaciones */
	uint8_t tecla;
   
   /*acá va mi programa principal */
   
	init_UART_FTDI_EDUCIAA();
	InitLeds();
	Init_Switches();
	init_ADC_EDUCIAA();
	ADC_Sel(CH1);
	timer0Init(PERIOD, &ADC_Start);
	enable_ADC_IRQ(&LeeDatoAnalogico);

    while(1){
    tecla = Read_Switches();

    if (tecla==TEC4){
    		umbral=umbral+10;
    		if (umbral>1023)
    		{
    			umbral=1023;
//    			InvierteLed(LED_AMARILLO);
    		}
		}

    if (tecla==TEC3){
    	umbral=umbral-10;
    		if (umbral<1)
    		{
    			umbral=0;
//				InvierteLed(LED_AMARILLO);
    		}
    	}

retardo = 2;
while (retardo);

    };

	return 0;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

