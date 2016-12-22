#ifndef _MAIN_H
#define _MAIN_H 1

#include "ili9341.h"
#include "adc.h"
#include "uart.h"


#define GS_HAYMOUSE 0x01
#define GS_GUNSTICK 0x02
#define GS_INACTIVE 0x04
typedefstruct {
	char romfile[1];
	char snapfile[1];
	char tapefile[1];
	unsigned int gunstick;
	char * raton_bmp;
	char joytype;
	char joy1key[5];
} tipo_emuopt ;

enum models_enum { SPECMDL_16K=1, SPECMDL_48K, SPECMDL_INVES, SPECMDL_128K, SPECMDL_PLUS2, 
       SPECMDL_PLUS3, SPECMDL_48KIF1, SPECMDL_48KTRANSTAPE };
enum inttypes_enum { NORMAL=1, INVES }; 

typedef struct {
  int port_ff;			// 0xff = emulate the port,  0x00 alwais 0xFF
  int ts_lebo;			// left border t states
  int ts_grap;			// graphic zone t states
  int ts_ribo;			// right border t states
  int ts_hore;			// horizontal retrace t states
  int ts_line;			// to speed the calc, the sum of 4 abobe
  int line_poin;		// lines in retraze post interrup
  int line_upbo;		// lines of upper border
  int line_grap;		// lines of graphic zone = 192
  int line_bobo;		// lines of bottom border
  int line_retr;		// lines of the retrace
  int TSTATES_PER_LINE;
  int TOP_BORDER_LINES;
  int SCANLINES;
  int BOTTOM_BORDER_LINES;
  int tstate_border_left;
  int tstate_graphic_zone;
  int tstate_border_right;
  int hw_model;
  int int_type;
  int videopage;
  int BANKM;
  int BANK678;
 } tipo_hwopt ;
 
int emuMain (int argc, char *argv[]);
int Z80Initialization (void);

/* Esto permite suprimir CASI TODOS los mensajes en aquellos sistemas que
no dispongan de STDOUT o esta corrompa la pantalla como en MacOS o MS-Dos

simplemente utilizar ASprintf en lugar de printf
*/

#ifdef ENABLE_LOGS
#define ASprintf printf
#else
void ASprintf (char *, ...);
#endif

#endif	/* main.h */  
