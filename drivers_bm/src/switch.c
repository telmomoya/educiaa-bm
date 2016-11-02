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

/** \brief Bare Metal driver for switchs in the EDU-CIAA board.
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
 * 20160808 v0.3 modifications and improvements made by Juan Manuel Reta
 */

/*==================[inclusions]=============================================*/
#include "switch.h"

/*==================[macros and definitions]=================================*/
/* Mapeo de pines Pulsadores
 * P1_0  en GPIO 0[4], SW1
 * P1_1  en GPIO 0[8], SW2
 * P1_2  en GPIO 0[9], SW3
 * P1_6  en GPIO 1[9], SW4
 * */
#define SW1_MUX_GROUP 	1
#define SW1_MUX_PIN 	0
#define SW1_GPIO_PORT 	0
#define SW1_GPIO_PIN 	4

#define SW2_MUX_GROUP 	1
#define SW2_MUX_PIN 	1
#define SW2_GPIO_PORT 	0
#define SW2_GPIO_PIN 	8

#define SW3_MUX_GROUP 	1
#define SW3_MUX_PIN 	2
#define SW3_GPIO_PORT 	0
#define SW3_GPIO_PIN 	9

#define SW4_MUX_GROUP 	1
#define SW4_MUX_PIN 	6
#define SW4_GPIO_PORT 	1
#define SW4_GPIO_PIN 	9

#define OUTPUT_DIRECTION 1
#define INPUT_DIRECTION 0

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Initialize method for the basic push-buttons in the EDU-CIAA board */
uint8_t Init_Switches(void)
{
	/** \details
	 * This function initialize the four switches present in the EDU-CIAA board,
	 * with the correct parameters with LPCOpen methods.
	 *
	 * \param none
	 *
	 * \return uint8_t: the function return a 8 bits word, where the first four
	 * binaries positions represent each push-button.
	 * */

	/* Configuración del GPIO*/
	Chip_GPIO_Init(LPC_GPIO_PORT);

	/* Mapeo de pines Pulsadores */
	Chip_SCU_PinMux(SW1_MUX_GROUP,SW1_MUX_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0);
	Chip_SCU_PinMux(SW2_MUX_GROUP,SW2_MUX_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0);
	Chip_SCU_PinMux(SW3_MUX_GROUP,SW3_MUX_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0);
	Chip_SCU_PinMux(SW4_MUX_GROUP,SW4_MUX_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0);

	/* Configuración como entrada para los pulsadores */
	Chip_GPIO_SetDir(LPC_GPIO_PORT, SW1_GPIO_PORT,1<<SW1_GPIO_PIN,INPUT_DIRECTION);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, SW2_GPIO_PORT,1<<SW2_GPIO_PIN,INPUT_DIRECTION);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, SW3_GPIO_PORT,1<<SW3_GPIO_PIN,INPUT_DIRECTION);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, SW4_GPIO_PORT,1<<SW4_GPIO_PIN,INPUT_DIRECTION);

	return TRUE;
}

uint8_t Read_Switches(void)
{
	uint8_t switchPressed = 0;

	if (!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,SW1_GPIO_PORT,SW1_GPIO_PIN))
		switchPressed |= TEC1;
	else
		switchPressed &= ~TEC1;

	if (!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,SW2_GPIO_PORT,SW2_GPIO_PIN))
		switchPressed |= TEC2;
	else
		switchPressed &= ~TEC2;

	if (!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,SW3_GPIO_PORT,SW3_GPIO_PIN))
		switchPressed |= TEC3;
	else
		switchPressed &= ~TEC3;

	if (!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,SW4_GPIO_PORT,SW4_GPIO_PIN))
		switchPressed |= TEC4;
	else
		switchPressed &= ~TEC4;

	return switchPressed;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/


/*
 * Para los pulsadores
 * Chip_GPIO_ReadValue()
 * Chip_GPIO_ReadPortBit()
 * */
