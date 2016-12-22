/*=====================================================================
  graphics.c -> This file includes all the graphical functions
                for the ASpectrum emulator.

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

 Copyright (c) 2000 Santiago Romero Iglesias.
 Email: sromero@escomposlinux.org
 ======================================================================*/
#include "z80.h"
#include "graphics.h"
#include "mem.h"
#include "vga.h"

#define ScreenVGA(offset)  (*((volatile char *) 0x20000000+offset))	//Inicio de RamAHB32
extern byte ScreenArea[0x2000];			// Primeros 8kb de la RAM del Spectrum, incluyen la memoria de pantalla

void
DisplayScreenDiff ()
{
// Paleta con colores del spectrum a los pines RGB
	static int paletaVGA[16] = {						//Faltan los brillos!!!
	0,															// BLACK
	1<<BLUE_GPIO_PIN,											// BLUE
	1<<RED_GPIO_PIN,											// RED
	(1<<RED_GPIO_PIN)|(1<<BLUE_GPIO_PIN),						// MAGENTA
	(1<<GREEN_GPIO_PIN),										// GREEN
	(1<<BLUE_GPIO_PIN)|(1<<GREEN_GPIO_PIN),						// CYAN
	(1<<RED_GPIO_PIN)|(1<<GREEN_GPIO_PIN),						// YELLOW
	(1<<BLUE_GPIO_PIN)|(1<<RED_GPIO_PIN)|(1<<GREEN_GPIO_PIN),	// GRAY
	0,															// BLACK
	1<<BLUE_GPIO_PIN,											// BLUE2
	1<<RED_GPIO_PIN,											// RED2
	(1<<RED_GPIO_PIN)|(1<<BLUE_GPIO_PIN),						// MAGENTA2
	(1<<GREEN_GPIO_PIN),										// GREEN2
	(1<<BLUE_GPIO_PIN)|(1<<GREEN_GPIO_PIN),						// CYAN2
	(1<<RED_GPIO_PIN)|(1<<GREEN_GPIO_PIN),						// YELLOW2
	(1<<BLUE_GPIO_PIN)|(1<<RED_GPIO_PIN)|(1<<GREEN_GPIO_PIN),	// WHITE
	};


	int pixeles,atributos,last_pixeles,last_atributos,tinta,papel,dir_p,dir_a,y,x,offset=0;

		for (y=0;y<192;y++)
		 {
		  dir_p = ((y & 0xC0) << 5) + ((y & 0x07) << 8) + ((y & 0x38) << 2);
		  dir_a = 0x1800 + (32 * (y >> 3));

		  for (x = 0; x < 32; x++)
		    {
			    pixeles=  ScreenArea[dir_p];
			    atributos=ScreenArea[dir_a];
			    last_pixeles=LastScreenArea[dir_p];
			    last_atributos=LastScreenArea[dir_a];

	    if ((last_pixeles!=pixeles)|(last_atributos!=atributos))	// Sólo escribo diferencias!
	    {

		      if ((atributos & 0x80) == 0)
			{
			  tinta = (atributos & 0x07) + ((atributos & 0x40) >> 3);
			  papel = (atributos & 0x78) >> 3;
			}
		      else
			{
			  papel = (atributos & 0x07) + ((atributos & 0x40) >> 3);
			  tinta = (atributos & 0x78) >> 3;
			}
//			  while (*((volatile unsigned long *) 0x2000F000));

		      ScreenVGA(offset++)=((pixeles & 0x80) ? paletaVGA[tinta] : paletaVGA[papel]);
		      ScreenVGA(offset++)=((pixeles & 0x40) ? paletaVGA[tinta] : paletaVGA[papel]);
		      ScreenVGA(offset++)=((pixeles & 0x20) ? paletaVGA[tinta] : paletaVGA[papel]);
		      ScreenVGA(offset++)=((pixeles & 0x10) ? paletaVGA[tinta] : paletaVGA[papel]);
		      ScreenVGA(offset++)=((pixeles & 0x08) ? paletaVGA[tinta] : paletaVGA[papel]);
		      ScreenVGA(offset++)=((pixeles & 0x04) ? paletaVGA[tinta] : paletaVGA[papel]);
		      ScreenVGA(offset++)=((pixeles & 0x02) ? paletaVGA[tinta] : paletaVGA[papel]);
		      ScreenVGA(offset++)=((pixeles & 0x01) ? paletaVGA[tinta] : paletaVGA[papel]);
  		LastScreenArea[dir_p]=pixeles;
  		if ((y&7)==7)LastScreenArea[dir_a]=atributos;
  		}
	    else offset+=8;
		  dir_p++;
		  dir_a++;

		    }
		  ScreenVGA(offset-1)=0;
	 }
}
