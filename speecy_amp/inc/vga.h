/* Copyright 2016, XXXXXXX
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

#define BLINKING_BM_H
/** \brief Bare Metal example header file
 **
 ** This is a mini example of the CIAA Firmware
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example header file
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


/*==================[macros]=================================================*/
#define lpc4337            1
#define mk60fx512vlq15     2



/* Ports definitions */
#define HSYNC_MUX_GROUP     6		//HSYNC = GPIO3: Pin34 // cable naranja // Vga Pin 13
#define HSYNC_MUX_PIN       7		//FUNC=4
#define HSYNC_GPIO_PORT     5
#define HSYNC_GPIO_PIN      15

#define VSYNC_MUX_GROUP     6		//VSYNC = GPIO4: Pin33 // cable rojo  // Vga Pin 14
#define VSYNC_MUX_PIN       8		//FUNC=4
#define VSYNC_GPIO_PORT     5
#define VSYNC_GPIO_PIN      16

#define RED_MUX_GROUP     6 		//RED = GPIO5: Pin36 // cable amarillo //Vga Pin 1
#define RED_MUX_PIN       9			//FUNC=0
#define RED_GPIO_PORT     3
#define RED_GPIO_PIN      5

#define GREEN_MUX_GROUP     6 		//GREEN = GPIO5: Pin35 // cable xxxxxxxxx //Vga Pin 2
#define GREEN_MUX_PIN       10		//FUNC=0
#define GREEN_GPIO_PORT     3
#define GREEN_GPIO_PIN      6

#define BLUE_MUX_GROUP     6 		//BLUE = GPIO5: Pin38 // cable xxxxxxxxxx //Vga Pin 3
#define BLUE_MUX_PIN       11		//FUNC=0
#define BLUE_GPIO_PORT     3
#define BLUE_GPIO_PIN      7



#define OUTPUT_DIR	1
#define INPUT_DIR   0


/* Pin definitions */
#define HSYNC_HI			Chip_GPIO_SetValue(LPC_GPIO_PORT, HSYNC_GPIO_PORT,1<<HSYNC_GPIO_PIN)
#define HSYNC_LOW			Chip_GPIO_ClearValue(LPC_GPIO_PORT, HSYNC_GPIO_PORT,1<<HSYNC_GPIO_PIN)
#define VSYNC_HI			Chip_GPIO_SetValue(LPC_GPIO_PORT, VSYNC_GPIO_PORT,1<<VSYNC_GPIO_PIN)
#define VSYNC_LOW			Chip_GPIO_ClearValue(LPC_GPIO_PORT, VSYNC_GPIO_PORT,1<<VSYNC_GPIO_PIN)
#define RED_HI				Chip_GPIO_SetValue(LPC_GPIO_PORT, RED_GPIO_PORT,1<<RED_GPIO_PIN)
#define RED_LOW				Chip_GPIO_ClearValue(LPC_GPIO_PORT, RED_GPIO_PORT,1<<RED_GPIO_PIN)
#define GREEN_HI			Chip_GPIO_SetValue(LPC_GPIO_PORT, GREEN_GPIO_PORT,1<<GREEN_GPIO_PIN)
#define GREEN_LOW			Chip_GPIO_ClearValue(LPC_GPIO_PORT, GREEN_GPIO_PORT,1<<GREEN_GPIO_PIN)
#define BLUE_HI				Chip_GPIO_SetValue(LPC_GPIO_PORT, BLUE_GPIO_PORT,1<<BLUE_GPIO_PIN)
#define BLUE_LOW			Chip_GPIO_ClearValue(LPC_GPIO_PORT, BLUE_GPIO_PORT,1<<BLUE_GPIO_PIN)
#define RGB_LOW				Chip_GPIO_ClearValue(LPC_GPIO_PORT, RED_GPIO_PORT,1<<RED_GPIO_PIN|1<<GREEN_GPIO_PIN|1<<BLUE_GPIO_PIN)

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/** \brief Reset ISR
 **
 ** ResetISR is defined in cr_startup_lpc43xx.c
 **
 ** \remark the definition is in
 **         externals/drivers/cortexM4/lpc43xx/src/cr_startup_lpc43xx.c
 **/
extern void ResetISR(void);

/** \brief Stack Top address
 **
 ** External declaration for the pointer to the stack top from the Linker Script
 **
 ** \remark only a declaration is needed, there is no definition, the address
 **         is set in the linker script:
 **         externals/base/cortexM4/lpc43xx/linker/ciaa_lpc4337.ld.
 **/
extern void _vStackTop(void);



void RIT_IRQHandler(void);



/*==================[external functions declaration]=========================*/


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

