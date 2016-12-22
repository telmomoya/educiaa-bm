/*=====================================================================
  ASpectrum Emulator. This is our contribution to the Spectrum World.
  We're trying to release our simple, useable and portable Spectrum
  emulator, always thinking in the GNU/Linux community.

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

 Copyright (c) 2000 Santiago Romero Iglesias
 Email: sromero@escomposlinux.org
 ======================================================================*/

#include "vector.h"
#include "main.h"
#include "z80.h"
#include "mem.h"
#include "graphics.h"


tipo_emuopt emuopt = {"\0","\0","\0",GS_INACTIVE, 0,'n',{'o', 'p', 'q', 'a', ' '} };

// hardware definitions for spectrum 48K
tipo_hwopt hwopt = { 0xFF, 24, 128, 24, 48, 224, 16, 48, 192, 48, 8,
  224, 64, 192, 56, 24, 128, 72, SPECMDL_48K };

int v_res = 240;
int v_border = 24;


// generic wrapper
extern volatile char *gkey;

/* Some global variables used in the emulator */
Z80Regs spectrumZ80;
volatile int last_fps, frame_counter;
volatile int target_cycle;

/*----------------------------------------------------------------*/
int debug = 0, main_tecla, hay_tecla, scanl = 0, quit_thread = 0;

void ExitEmulator (void);
void CreateVideoTables (void);
void UpdateKeyboard (void);
void target_incrementor (void);
void count_frames (void);



extern tipo_mem mem;

int skip=0;

int
Z80Initialization (void)
{
	init_spectrum();
	spectrumZ80.RAM=mem.p; // por compatibilidad
  
// COMMENT: Is this needed? -> CreateVideoTables();
  Z80Reset (&spectrumZ80, 69888);
  Z80FlagTables ();
  return 1;
}


/*----------------------------------------------------------------
 Main function. It inits all the emulator stuff and executes it.
----------------------------------------------------------------*/
//int main (int argc, char *argv[])
int main (void)

{
  int target_tstate, current_tstate;
  char b[1024];
  char value;
  int offs = 0, poke, option;
  int c, tecla = 0;
  static int f_flash = 1, f_flash2 = 0;

  Z80Initialization ();

  load_sna(&spectrumZ80);

  init_UART_FTDI_EDUCIAA();									/* Inicialización UART_FTDI y */

  ClearScreen (7);
  hay_tecla = main_tecla = 0;
  init_keyboard();


  while (1)									// main emulator loop
    {
	  f_flash2++;
	  if (f_flash2 >= 32)
	    f_flash2 = 0;
	  f_flash = (f_flash2 < 16 ? 0 : 1);

// Emulo un frame completo y después lo dibujo completo
// Lo único "raro" es que cambia el valor del Port FF mientras se dibuja el borde de la pantalla
// Entonces pone Port FF como corresponde y ejecuta tantos ciclos del Z80 como correspondan.

	      // no visible upper border
	      target_tstate =
          (hwopt.ts_line * (hwopt.line_upbo + hwopt.line_poin)) -
          hwopt.ts_lebo;
	      current_tstate = spectrumZ80.IPeriod - spectrumZ80.ICount;
	      hwopt.port_ff &= 0xF0;
	      Z80Run (&spectrumZ80, target_tstate - current_tstate);	// Ciclos de Z80

	      // Now run the emulator for all the real screen (192 lines)
	      for (scanl = 0; scanl < 192; scanl++)
		{
		  // left border
		  target_tstate += hwopt.ts_lebo;
		  current_tstate = spectrumZ80.IPeriod - spectrumZ80.ICount;
		  hwopt.port_ff &= 0xF0;
		  Z80Run (&spectrumZ80, target_tstate - current_tstate);

		  // Screen
		  target_tstate += hwopt.ts_grap;
		  current_tstate = spectrumZ80.IPeriod - spectrumZ80.ICount;
		  hwopt.port_ff |= 0x0F;
		  Z80Run (&spectrumZ80, target_tstate - current_tstate);

		  // right border 
		  target_tstate += (hwopt.ts_ribo + hwopt.ts_hore);
		  current_tstate = spectrumZ80.IPeriod - spectrumZ80.ICount;
		  hwopt.port_ff &= 0xF0;
		  Z80Run (&spectrumZ80, target_tstate - current_tstate);
	    }

	      // visible bottom border
	      hwopt.port_ff &= 0xF0;
	      Z80Run (&spectrumZ80, spectrumZ80.ICount);

	      /////////////////////////////
	      //MUESTRO UN FRAME COMPLETO//
	      /////////////////////////////

	      skip++;
	      if (skip==2)					// Puedo saltar frames para más velocidad
	      {
	    	  skip=1;
	    	  DisplayScreenDiff (&spectrumZ80);
	      }




	  target_cycle--;
	  frame_counter++;
	  UpdateKeyboard ();
      tecla = 0;

    }				// main emulator loop
}
