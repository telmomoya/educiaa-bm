/* Copyright 2016, 
 * Federico Pinna
 * fpinna@unsl.edu.ar
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

/** \brief Bare Metal driver for RIT timer in the EDU-CIAA board.
 **
 **/

/*
 * Initials     Name
 * ---------------------------
 *  FP          Federico Pinna
 *  EF			Eduardo Filomena
 *  JMR			Juan Manuel Reta
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20160807 v0.2 initial version by Eduardo Filomena 
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
#include "timer.h"


/*==================[macros and definitions]=================================*/




/*==================[internal data declaration]==============================*/

void (*pIsrTimer)();
void (*pIsrTimer0)();

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

void timerInit(uint32_t time_ms,void *pfunc){

	pIsrTimer=pfunc;
	Chip_RIT_Init(LPC_RITIMER);
	Chip_RIT_SetTimerInterval(LPC_RITIMER,time_ms);
	NVIC_EnableIRQ(RITIMER_IRQn);
}

 void ISR_RIT(){
	Chip_RIT_ClearInt(LPC_RITIMER);
	pIsrTimer();
}

 void ISR_Timer0(){
	if (Chip_TIMER_MatchPending(LPC_TIMER0, 0)) {
	 		Chip_TIMER_ClearMatch(LPC_TIMER0, 0);
	 }
	pIsrTimer0();
}

void timer0Init(uint32_t time_us,void *pfunc){
    pIsrTimer0=pfunc;
	Chip_TIMER_Init(LPC_TIMER0);
	//falta convertit time_ms en el match num
	uint32_t FrecuenciaClk = Chip_Clock_GetBaseClocktHz (CLK_BASE_MX); // Leo la vellocidad del micro en khz
	uint32_t MatchCount= time_us*(FrecuenciaClk/1000000);
	
	Chip_TIMER_SetMatch(LPC_TIMER0, 0, MatchCount);
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER0, 0);
	Chip_TIMER_MatchEnableInt(LPC_TIMER0, 0);
	Chip_TIMER_Enable(LPC_TIMER0);
	NVIC_EnableIRQ(TIMER0_IRQn);

}
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




/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

