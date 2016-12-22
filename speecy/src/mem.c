/*
 * Distribuido GPL (C) 2003 Alvaro Alea.
 *
 * TODO:
 *
 * Meterlo en el codigo central. (parte DONE)
 * rutinas de paginacion para cada uno
 * Hacer un GUI para la selecion del HW 
 * Compatibilizar con snapshots / cintas
 * Reactivar el uso de Cartuchos Sinclair DONE
 * Hacer gui para el transpate
 */

#include <stdio.h>
#include <stdlib.h>
#include "z80.h"
#include "main.h"
#include "mem.h"
#include "spectrum.rom.h"


tipo_mem mem;

byte readmem(word dir){

		int valor;
		if (dir < 16384) valor = spectrum_rom[dir];
		else
			if (dir<0x5b00) valor = ScreenArea(dir-0x4000);
			else valor = RAM_SPECTRUM(dir-16384);

/*
		if ((dir>0x1538)&(dir<0x1555)){
//		if ((dir>65530)){
		  writeByte_UART_USB_EDUCIAA('R');
		  writeByte_UART_USB_EDUCIAA(' ');
		  sendString_UART_USB_EDUCIAA (Itoa(dir,10),8);
		  writeByte_UART_USB_EDUCIAA(' ');
		  sendString_UART_USB_EDUCIAA (Itoa(valor,10),8);
		  writeByte_UART_USB_EDUCIAA(valor);
		  writeByte_UART_USB_EDUCIAA(10);
		  writeByte_UART_USB_EDUCIAA(13);
		}
*/
	return valor;


/*
	int page;
	byte v;
	page= ( dir & mem.mp ) >> mem.mr ;
	v=*( mem.p + mem.ro[page] + (dir & mem.md)) ;
	return v;
*/
}

void writemem(word dir, byte data){

	if (dir >= 16384)
		{
		if (dir<0x5b00) ScreenArea(dir-0x4000)=data;
		else RAM_SPECTRUM(dir-16384) = data;

		}

/*
	if (dir>65530){
	  writeByte_UART_USB_EDUCIAA('W');
	  writeByte_UART_USB_EDUCIAA(' ');
	  sendString_UART_USB_EDUCIAA (Itoa(dir,10),8);
	  writeByte_UART_USB_EDUCIAA(' ');
	  sendString_UART_USB_EDUCIAA (Itoa(data,10),8);
	  writeByte_UART_USB_EDUCIAA(10);
	  writeByte_UART_USB_EDUCIAA(13);
	}
*/

/*
	int page;
	page= ( dir & mem.mp ) >> mem.mr ;
	*( mem.p + mem.wo[page] + (dir & mem.md))=data ;
*/
}

byte readvmem(word offset, int page){
	return *( mem.p + mem.vo[page] + offset) ;
}


/* por que estas rutinas y no paginar directamente sobre los arrais???
 * Supon la arquitectura del +2 y la del +2 con el pokeador automatico de MH
 * en el primero el tamaño de la pagina es de 16K mientras que en el segundo es de 2K
 * Con esto deberiamos poder aprobechar la rutina de paginacion del 128 en los dos casos
 * ya que esta rutina tiene en cuenta el tamaño de pagina con el que trabajamos y hace los
 * ajustes necesarios
 */
void pagein(int size, int block, int page, int ro, int issystem){
	int npag,cf,c,d;
	npag=size/mem.sp;
	d=block*npag;
	c=page*npag;
	cf=c+npag;
	for(;c<cf;c++,d+=mem.sp)
		if ( mem.ro[c]==mem.sro[c] ) { // no hay periferico
			if (issystem==SYSTEM_PAGE) {  		// y pagino systema
				mem.ro[c]=d;
				mem.sro[c]=d;
				mem.wo[c]=(ro==RW_PAGE?d:mem.roo);
				mem.swo[c]=(ro==RW_PAGE?d:mem.roo);
			  } else {    		// y meto periferico
				mem.ro[c]=d;
				mem.wo[c]=(ro==RW_PAGE?d:mem.roo);
			  }
		 } else {    		// si hay periferico
			  if (issystem==SYSTEM_PAGE) {  		// los cambios solo se notaran en el futuro.
				   mem.sro[c]=d;
				   mem.swo[c]=(ro==RW_PAGE?d:mem.roo);
			  } else {  		// y cambio de periferico.
				   mem.ro[c]=d;
				   mem.wo[c]=(ro==RW_PAGE?d:mem.roo);
			  }
		 }
        
}

void pageout(int size, int bloq, int page){
	int npag,c;
	npag=size/mem.sp;
	c=page*npag;
	mem.ro[c]=mem.sro[c];
	mem.wo[c]=mem.swo[c];
}

int init_spectrum(){
	init_48k();
	return 0;
}

extern tipo_hwopt hwopt;

/* This do aditional stuff for reset, like mute sound chip, o reset bank switch */
int reset_spectrum(void){
	return 0;
}


int end_spectrum(){
	return 0;
}

//Ejemplos de rutinas de inicializacion de 3 modelos de spectrum.

//extern int TSTATES_PER_LINE;
//extern int TOP_BORDER_LINES;
//extern int BOTTOM_BORDER_LINES, 
//extern int SCANLINES;

int init_48k(){
	int i;
	mem.md= 0x3FFF ;
	mem.mp= 0xC000 ;
	mem.mr= 14;
	mem.np=4;
	mem.sp=16*1024;
	i=0;
	mem.roo=4*mem.sp;
	mem.vn=1;

	mem.ro[0]=mem.sro[0]=0;
	mem.wo[0]=mem.swo[0]=mem.roo;
	mem.ro[1]=mem.sro[1]=mem.wo[1]=mem.swo[1]=mem.sp;
	mem.ro[2]=mem.sro[2]=mem.wo[2]=mem.swo[2]=2*mem.sp;
	mem.ro[3]=mem.sro[3]=mem.wo[3]=mem.swo[3]=3*mem.sp;
	mem.vo[0]=0x4000;

	// ULA config
	hwopt.port_ff=0xFF;			// 0xff = emulate the port,  0x00 alwais 0xFF
	hwopt.ts_lebo=24;			  // left border t states
	hwopt.ts_grap=128;			 // graphic zone t states
	hwopt.ts_ribo=24;			  // right border t states
	hwopt.ts_hore=48;			  // horizontal retrace t states
	hwopt.ts_line=224;			 // to speed the calc, the sum of 4 abobe
	hwopt.line_poin=16;		    // lines in retraze post interrup
	hwopt.line_upbo=48;		    // lines of upper border
	hwopt.line_grap=192;		   // lines of graphic zone = 192
	hwopt.line_bobo=48;		    // lines of bottom border
	hwopt.line_retr=8;		     // lines of the retrace
	hwopt.TSTATES_PER_LINE=224;
	hwopt.TOP_BORDER_LINES=64;
	hwopt.SCANLINES=192;
	hwopt.BOTTOM_BORDER_LINES=56;
	hwopt.tstate_border_left=24;
	hwopt.tstate_graphic_zone=128;
	hwopt.tstate_border_right=72;
	hwopt.hw_model=SPECMDL_48K;
	hwopt.int_type=NORMAL;
	hwopt.videopage=0;
	return 0;
	}
