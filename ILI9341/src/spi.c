/*
 * spi.c
 *
 *  Created on: 29/03/2016
 *      Author: Matias Leandro Ferraro
 */
#include <stdint.h>
#include "spi.h"
//================================================[SPI Management]========================================================

void Board_SSP_Init(void)
{
	Chip_SCU_PinMuxSet(0xF, 4, (SCU_PINIO_FAST | SCU_MODE_FUNC0));  /* PF.4 => SCK1 */
	Chip_SCU_PinMuxSet(0x1, 4, (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC5)); /* P1.4 => MOSI1 */
    Chip_SCU_PinMuxSet(0x1, 3, (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC5)); /* P1.3 => MISO1 */
}

void Board_SSP_config(uint8_t bits, uint8_t clockMode, uint32_t bitrate)
{
	uint32_t bitsConfig;
	uint32_t clockModeConfig;
	switch(bits)
	{
		case 4: bitsConfig  =SSP_BITS_4;break;
		case 8: bitsConfig  =SSP_BITS_8;break;
		case 16: bitsConfig =SSP_BITS_16;break;
	}
	switch(clockMode)
	{
		case 0: clockModeConfig = SSP_CLOCK_CPHA0_CPOL0;break;
		case 1: clockModeConfig = SSP_CLOCK_CPHA1_CPOL0;break;
		case 2: clockModeConfig = SSP_CLOCK_CPHA0_CPOL1;break;
		case 3: clockModeConfig = SSP_CLOCK_CPHA1_CPOL1;break;
	}
        Chip_SSP_Init(LPC_SSP1);
        Chip_SSP_SetFormat(LPC_SSP1, bitsConfig, SSP_FRAMEFORMAT_SPI, clockModeConfig);
        Chip_SSP_SetBitRate(LPC_SSP1, bitrate);
        Chip_SSP_Enable(LPC_SSP1);

}
void write_spi_XXh(uint32_t LPC_SSP_n, uint32_t XXh)
{
	Chip_SSP_Enable(LPC_SSP);
	Chip_SSP_WriteFrames_Blocking(LPC_SSP_n,&XXh, 1);
}
//===========================================================================================================================
