/*
Distribuido GPL (C) 2003 Alvaro Alea.
*/
#ifndef MEM_H
#define MEM_H

//#define word unsigned int // definidos en z80.h
//#define byte unsigned short int 

// EL MAPA DE MEMORIA QUEDA:
// ROM de spectrum 16kb en array constante spectrum_rom[] en MFlashA512
// 8Kb de Ram baja del Spectrum (incluye la pantalla: 6kb+768b, de 4000-5aff)
// en un aray en RAM que maneja M4, o sea RamLoc32
// Lo mismo con otro array LastScreenArea(6kb+768b) que tiene una copia del fram anterior
// para que el render sólo dibuje las diferencias y sea usable con la pantalla que es SPI
// Resto de la ram del Spectrum en RamLoc40 y así totalizan los 48kb
// A partir de 0x20000000 están los 32kb de RamAHB32 y continuan los 16kb de RamAHB16
// los uso a todos para un frame de video VGA (la resolución que tengo es 192x256=48kb)
// Acceden con SRC_DIR() M4 para escritura y M0 para lectura.

#define RAM_SPECTRUM(offset)  (*((volatile byte *) 0x10080000+offset))	//RamAHB32 y sigue en RamAHB16
#define LastScreenArea(offset)  (*((volatile byte *) 0x10081b00+offset))//offset de 1b00 en RamLoc40

byte ScreenArea[0x2000];		// Memoria de pantalla del Spectrum
byte LastScreenArea[0x1b00];


typedef struct   //estructura de memoria
{
   byte *p;  // pointer to memory poll
   int mp;    // bitmap for page bits in z80 mem
   int md;    // bitmap for dir bits in z80 mem
   int np;    // number of pages of memory 
   int ro[16];  // map of pages for read  (map ar alwais a offset for *p) 
   int wo[16];  // map of pages for write
   int sro[16]; // map of system memory pages for read (to remember when perife-
   int swo[16]; // map of system memory pages for write         -rical is paged)
   int vn;    // number of video pages
   int vo[2];  // map of video memory
   int roo;   // offset to dummy page for readonly emulation
   	      //   Precalculated data
   int mr;    // times left rotations for page ( number of zero of mp)
   int sp;    // size of pages (hFFFF / mp)
} tipo_mem;

#define RO_PAGE 1
#define RW_PAGE 0
#define SYSTEM_PAGE 0
#define NOSYS_PAGE 1

byte readmem(word dir);
void writemem(word dir, byte data);
byte readvmem(word offset, int page);

void pagein(int size, int bloq, int page, int ro, int issystem);
void pageout(int size, int bloq, int page);

int init_spectrum();
int end_spectrum(void);
int reset_spectrum(void);

int init_48k();

#endif  // #ifdef MEM_H
