/* Copyright 2016, XXXXXXXXX  
 * All rights reserved.
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

/** \brief Blinking Bare Metal driver led
 **
 **
 **
 **/
/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal LED Driver
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

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif
#include "led.h"

/*==================[macros and definitions]=================================*/
#define PAQUETE2 2
#define PUERTO0 0
#define PUERTO1 1
#define PUERTO5 5
#define PIN1 10
#define PIN2 11
#define PIN3 12
#define PIN4 0
#define PIN5 1
#define PIN6 2
#define LED1 1<<14
#define LED2 1<<11
#define LED3 1<<12
#define LEDR 1<<0
#define LEDG 1<<1
#define LEDB 1<<2
#define Bit_LED1 14
#define Bit_LED2 11
#define Bit_LED3 12
#define Bit_LEDR 0
#define Bit_LEDG 1
#define Bit_LEDB 2
#define encendido 255
#define apagado 0
/*==================[internal data declaration]==============================*/
/*==================[internal functions declaration]=========================*/
/*==================[internal data definition]===============================*/
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
void ini_puerto(void)
{
 Chip_GPIO_Init(LPC_GPIO_PORT);
 Chip_SCU_PinMux(PAQUETE2,PIN1,MD_PUP,FUNC0);
 Chip_SCU_PinMux(PAQUETE2,PIN2,MD_PUP,FUNC0);
 Chip_SCU_PinMux(PAQUETE2,PIN3,MD_PUP,FUNC0);
 Chip_SCU_PinMux(PAQUETE2,PIN4,MD_PUP,FUNC4);
 Chip_SCU_PinMux(PAQUETE2,PIN5,MD_PUP,FUNC4);
 Chip_SCU_PinMux(PAQUETE2,PIN6,MD_PUP,FUNC4);
 Chip_GPIO_SetDir(LPC_GPIO_PORT,PUERTO0,LED1,TRUE);
 Chip_GPIO_SetDir(LPC_GPIO_PORT,PUERTO1,LED2,TRUE);
 Chip_GPIO_SetDir(LPC_GPIO_PORT,PUERTO1,LED3,TRUE);
 Chip_GPIO_SetDir(LPC_GPIO_PORT,PUERTO5,LEDR,TRUE);
 Chip_GPIO_SetDir(LPC_GPIO_PORT,PUERTO5,LEDG,TRUE);
 Chip_GPIO_SetDir(LPC_GPIO_PORT,PUERTO5,LEDB,TRUE);
}

void encenderL123(void)
{
 Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PUERTO0,Bit_LED1);
 Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PUERTO1,Bit_LED2);
 Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PUERTO1,Bit_LED3);
}

void encender(uint8_t Led)
{
 if(Led==rojo)
  Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PUERTO0,Bit_LED1);
 if(Led==amarillo)
  Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PUERTO1,Bit_LED2);
 if(Led==verde)
  Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PUERTO1,Bit_LED3);
 if(Led==rojoRGB)
  Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PUERTO5,Bit_LEDR);
 if(Led==verdeRGB)
  Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PUERTO5,Bit_LEDG);
 if(Led==azulRGB)
  Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PUERTO5,Bit_LEDB);
}

void RGB(str_LedRGB * LedRGB)
{
 if(LedRGB->azul==encendido)
 {
  Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PUERTO5,Bit_LEDB);
 }
 if(LedRGB->azul==apagado)
 {
  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PUERTO5,Bit_LEDB);
 }
 if(LedRGB->rojo==encendido)
 {
  Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PUERTO5,Bit_LEDR);
 }
 if(LedRGB->rojo==apagado)
 {
  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PUERTO5,Bit_LEDR);
 }
 if(LedRGB->verde==encendido)
 {
  Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PUERTO5,Bit_LEDG);
 }
 if(LedRGB->verde==apagado)
 {
  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PUERTO5,Bit_LEDG);
 }
 else
  return 0;
}

void apagarL123(void)
{
 Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PUERTO0,Bit_LED1);
 Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PUERTO1,Bit_LED2);
 Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PUERTO1,Bit_LED3);
}

void apagar(uint8_t Led)
{
 if(Led==rojo)
  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PUERTO0,Bit_LED1);
 if(Led==amarillo)
  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PUERTO1,Bit_LED2);
 if(Led==verde)
  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PUERTO1,Bit_LED3);
 if(Led==rojoRGB)
  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PUERTO5,Bit_LEDR);
 if(Led==verdeRGB)
  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PUERTO5,Bit_LEDG);
 if(Led==azulRGB)
  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PUERTO5,Bit_LEDB);
}

void toggle(uint8_t Led)
{
 if(Led==rojo)
  Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,PUERTO0,Bit_LED1);
 if(Led==amarillo)
  Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,PUERTO1,Bit_LED2);
 if(Led==verde)
  Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,PUERTO1,Bit_LED3);
}
/*==================[end of file]============================================*/

