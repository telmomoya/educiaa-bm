/*=====================================================================
  Graphics.h -> Header file for graphics.c

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
  
#ifndef GRAPHICS_H
#define GRAPHICS_H
void InitGraphics (void);
void DisplayScreen (Z80Regs * regs);
void DisplayScreenDiff (Z80Regs * regs);
void DisplayScanLine (int linea, Z80Regs * regs);
void displayscanline2 (int y, int f_flash, Z80Regs * regs);
void displayscanlineDiff (int y, int f_flash, Z80Regs * regs);
void displayborderscanline (int y);
void GFXprintf (int x, int y, char *sentence, char *font, char fg_color,
		  char bg_color, char incr);
int GFXgets (int x, int y, char *cadena, char *font, int fg_color,
	      int bg_color, int max);
void GFXprintf_tovideo (int x, int y, char *sentence, char *font,
			 char fg_color, char bg_color, char incr);

/* Speccy colours */ 
/*
static RGB colores[16] = {
  {   0/4,   0/4,   0/4},
  {   0/4,   0/4, 205/4},
  { 205/4,   0/4,   0/4},
  { 205/4,   0/4, 205/4},
  {   0/4, 205/4,   0/4},
  {   0/4, 205/4, 205/4},
  { 205/4, 205/4,   0/4},
  { 212/4, 212/4, 212/4},
  {   0/4,   0/4,   0/4},
  {   0/4,   0/4, 255/4},
  { 255/4,   0/4,   0/4},
  { 255/4,   0/4, 255/4},
  {   0/4, 255/4,   0/4},
  {   0/4, 255/4, 255/4},
  { 255/4, 255/4,   0/4},
  { 255/4, 255/4, 255/4}
};
*/ 

#define PutPixel(dst,x,y,color) (dst->line[y])[x]=colors[color]
#endif	/*  */
