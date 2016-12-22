/*
Distribuido GPL (C) 2003 Alvaro Alea.
*/
#ifndef MEM_H
#define MEM_H

//#define word unsigned int // definidos en z80.h
//#define byte unsigned short int 

// EL MAPA DE MEMORIA QUEDA:
// ROM de spectrum 16kb en array constante spectrum_rom[] en MFlashA512
// Ram de pantalla del spectrum (6kb+768b, de 4000-5aff) accedo con ScreenArea(), en RamLoc40 a partir de 0x10080000
// Resto de la ram del Spectrum (41kb+256b, de 5b00 a ffff) en RAM_SPECTRUM() distribuidos así:
// Los primeros 32kb en RamAHB32 a partir de 0x20000000 y continuan los 11kb+256b restantes en RamAHB16
// Además hay un array (6kb+768b) en la ram del core como framebuffer que se compara con ScreenArea()
// para dibujar solamente las diferencias

#define RAM_SPECTRUM(offset)  (*((volatile byte *) 0x20000000+offset))	//RamAHB32 y sigue en RamAHB16
#define ScreenArea(offset)  (*((volatile byte *) 0x10080000+offset))	//Inicio de RamLoc40
#define LastScreenArea(offset)  (*((volatile byte *) 0x10081b00+offset))//offset de 1b00 en RamLoc40


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
