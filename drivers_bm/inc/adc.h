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


#ifndef ADC_H
#define ADC_H

/** \brief AD Converter Bare Metal driver for the peripheral in the EDU-CIAA Board.
 **
 ** This is a driver to control the peripheral Analog to Digital Converter.
 **
 **/

/** \addtogroup EDU-CIAA_Course
 ** @{ */
/** \addtogroup Sources_LDM Leandro D. Medus Sources
 ** @{ */
/** \addtogroup Baremetal_App Bare Metal application source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *	LM			Leandro Medus
 *  EF			Eduardo Filomena
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20160610 v0.1 initials initial version leo
 */

/*==================[inclusions]=============================================*/
#include "stdint.h"
#include "chip.h"

/*==================[macros]=================================================*/


/*==================[typedef]================================================*/


/*==================[external data declaration]==============================*/
#define  CH1 ADC_CH1
#define  CH2 ADC_CH2
#define  CH3 ADC_CH3

/*==================[external functions declaration]=========================*/
/** \brief Initialization function to control adc 0 channel 0 in the EDU-CIAA BOARD 
 ** 
 ** \return TRUE if no error
 **/
uint8_t init_ADC_EDUCIAA(void);

/** \brief reads adc0 channel 1 value pooling method (blocking)
 ** \return ADC value (10 bits)
 **/
uint16_t read_ADC_value_pooling(void);

void ADC_Sel(ADC_CHANNEL_T C);
/** \brief adc0 channel 1 start of convertion
 ** 
 **/
void ADC_Start(void);

/** \brief reads adc0 channel 1 converted value (non blocking)
 ** \return ADC value (10 bits)
 **/
uint16_t read_ADC_value(void);

/** \brief enable adc0 channel 1 end of convertion interrupt 
 ** 
 ** \param[in] adress of adc0 ISR (Interrupt Servide Routine)
 **
 **/
void enable_ADC_IRQ(void *pfunc);


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef ADC_H */

