/* Copyright 2014, 2015 Mariano Cerdeiro
 * Copyright 2014, Pablo Ridolfi
 * Copyright 2014, Juan Cecconi
 * Copyright 2014, Gustavo Muro
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
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

/** \brief Bare Metal example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "umax.h"       /* <= own header */

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

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

/***************************************************************************/
/*               http://www.andreadrian.de/schach/avr_umax.c               */
/***************************************************************************/
/*                               micro-Max,                                */
/* A chess program smaller than 2KB (of non-blank source), by H.G. Muller  */
/* Port to Atmel ATMega644 and AVR GCC, by Andre Adrian                    */
/* Port to EDUCIAA ARM M4 Core, by Telmo Moya                              */
/***************************************************************************/
/* version 4.8 (1953 characters) features:                                 */
/* - recursive negamax search                                              */
/* - all-capture MVV/LVA quiescence search                                 */
/* - (internal) iterative deepening                                        */
/* - best-move-first 'sorting'                                             */
/* - a hash table storing score and best move                              */
/* - futility pruning                                                      */
/* - king safety through magnetic, frozen king in middle-game              */
/* - R=2 null-move pruning                                                 */
/* - keep hash and repetition-draw detection                               */
/* - better defense against passers through gradual promotion              */
/* - extend check evasions in inner nodes                                  */
/* - reduction of all non-Pawn, non-capture moves except hash move (LMR)   */
/* - full FIDE rules (expt under-promotion) and move-legality checking     */

/* 26nov2008 no hash table                                                 */
/* 29nov2008 all IO via myputchar(), mygetchar(), pseudo random generator  */

/* 29nov2016 avoid #define W while                                         */

//#define UNIX
#define EDUCIAA
#define VERBOSE
#define ENTERKEY	0x0d    		// Terminal Enter key
#define STRENGTH    5000			// Nivel de juego CPU (por profundidad y no por tiempo)
#define CIAA_MULTICORE_IPC_MAILBOX1_ADDR  (*((volatile unsigned long *) 0x20008000))
#define CIAA_MULTICORE_IPC_MAILBOX2_ADDR  (*((volatile unsigned long *) 0x20008004))
#define CIAA_MULTICORE_CORE_1_IMAGE ((uint8_t *)0x1B000000)

#ifdef UNIX
  #include <stdio.h>
  #include <time.h>
#endif


#define WHITE 16
#define BLACK  8

#define M 0x88
#define S 128
#define I 8000

long N, T;    		                                  /* N=evaluated positions+S, T=recursion limit */
short Q,O,K,R,k;					                  /* k=moving side */
char *p,c[5],Z;   									  /* p=pointer to c, c=user input, computer output, Z=recursion counter */

char L,
w[]={0,2,2,7,-1,8,12,23},		                      /* relative piece values    */
o[]={-16,-15,-17,0,1,16,0,1,16,15,17,0,14,18,31,33,0, /* step-vector lists */
     7,-1,11,6,8,3,6,           		              /* 1st dir. in o[] per piece*/
     6,3,5,7,4,5,3,6},                  		      /* initial piece setup      */
b[]={  												  /* board is left part, center-pts table is right part, and dummy */
  22, 19, 21, 23, 20, 21, 19, 22, 28, 21, 16, 13, 12, 13, 16, 21,
  18, 18, 18, 18, 18, 18, 18, 18, 22, 15, 10,  7,  6,  7, 10, 15,
   0,  0,  0,  0,  0,  0,  0,  0, 18, 11,  6,  3,  2,  3,  6, 11,
   0,  0,  0,  0,  0,  0,  0,  0, 16,  9,  4,  1,  0,  1,  4,  9,
   0,  0,  0,  0,  0,  0,  0,  0, 16,  9,  4,  1,  0,  1,  4,  9,
   0,  0,  0,  0,  0,  0,  0,  0, 18, 11,  6,  3,  2,  3,  6, 11,
   9,  9,  9,  9,  9,  9,  9,  9, 22, 15, 10,  7,  6,  7, 10, 15,
  14, 11, 13, 15, 12, 13, 11, 14, 28, 21, 16, 13, 12, 13, 16, 21, 0
};

char last_board[129];			// For tft update without blinks

volatile char breakpoint; /* for debugger */

/* IPC routines */
void ipcputchar(char c) {
CIAA_MULTICORE_IPC_MAILBOX2_ADDR = c;
while (CIAA_MULTICORE_IPC_MAILBOX2_ADDR!=0);		/* polling :( */
}
void ipcputs(const char *s) {
  while(*s) ipcputchar(*s++);
}

char mygetchar(void) {
#ifdef VERBOSE
#ifdef EDUCIAA
	unsigned long mailbox_in;
    while (CIAA_MULTICORE_IPC_MAILBOX1_ADDR==0);		  /*espera mientras mailbox1 es 0, polling :( */
    mailbox_in=CIAA_MULTICORE_IPC_MAILBOX1_ADDR;          /*tomo el valor                */
    CIAA_MULTICORE_IPC_MAILBOX1_ADDR=0;                   /*pongo mailbox1 a 0           */
    return mailbox_in;
	#else
	  return getchar();
	#endif
#else
  return ENTERKEY;                          	/* self play						*/
#endif
}

/* User interface routines */
void myputchar(char c) {
#ifdef UNIX
  putchar(c);
#endif
#ifdef EDUCIAA
  writeByte_UART_USB_EDUCIAA(c);
#endif
}

void myputs(const char *s) {
  while(*s) myputchar(*s++);
}

/* 16bit pseudo random generator */
#define MYRAND_MAX 65535

unsigned short r = 1;                       	/* pseudo random generator seed, hardcoded, but different for each core */

void mysrand(unsigned short r_) {
 r = r_;
}

unsigned short myrand(void) {
 return r=((r<<11)+(r<<7)+r)>>1;
}

short D(q,l,e,E,z,n)        	                /* recursive minimax search */
short q,l,e;  				                    /* (q,l)=window, e=current eval. score, */
unsigned char E,z,n;     						/* E=e.p. sqr.z=prev.dest, n=depth; return score */
{
 short m,v,i,P,V,s;
 unsigned char t,p,u,x,y,X,Y,H,B,j,d,h,F,G,C;
 signed char r;

#ifndef EDUCIAA
 if (++Z>30) {                                  /* stack underrun check */
  breakpoint=1;             					/* AVR Studio 4 Breakpoint for stack underrun */
  myputchar('u');
  --Z;return e;
 }
#endif

 q--;                                          /* adj. window: delay bonus */
 k^=24;                                        /* change sides             */
 d=Y=0;                                        /* start iter. from scratch */
 X=myrand()&~M;                                /* start at random field    */
 while(d++<n||d<3||                            /* iterative deepening loop */
   z&K==I&&(N<T&d<98||                         /* root: deepen upto time   */
   (K=X,L=Y&~M,d=3)))                          /* time's up: go do best    */
 {x=B=X;                                       /* start scan at prev. best */
  h=Y&S;                                       /* request try noncastl. 1st*/
  P=d<3?I:D(-l,1-l,-e,S,0,d-3);                /* Search null move         */
  m=-P<l|R>35?d>2?-I:e:-P;                     /* Prune or stand-pat       */
  ++N;                                         /* node count (for timing)  */
  do{u=b[x];                                   /* scan board looking for   */
   if(u&k)                                     /*  own piece (inefficient!)*/
   {r=p=u&7;                                   /* p = piece type (set r>0) */
    j=o[p+16];                                 /* first step vector f.piece*/
    while(r=p>2&r<0?-r:-o[++j])                /* loop over directions o[] */
    {A:                                        /* resume normal after best */
     y=x;F=G=S;                                /* (x,y)=move, (F,G)=castl.R*/
     do{                                       /* y traverses ray, or:     */
      H=y=h?Y^h:y+r;                           /* sneak in prev. best move */
      if(y&M)break;                            /* board edge hit           */
      m=E-S&b[E]&&y-E<2&E-y<2?I:m;             /* bad castling             */
      if(p<3&y==E)H^=16;                       /* shift capt.sqr. H if e.p.*/
      t=b[H];if(t&k|p<3&!(y-x&7)-!t)break;     /* capt. own, bad pawn mode */
      i=37*w[t&7]+(t&192);                     /* value of capt. piece t   */
      m=i<0?I:m;                               /* K capture                */
      if(m>=l&d>1)goto C;                      /* abort on fail high       */
      v=d-1?e:i-p;                             /* MVV/LVA scoring          */
      if(d-!t>1)                               /* remaining depth          */
      {v=p<6?b[x+8]-b[y+8]:0;                  /* center positional pts.   */
       b[G]=b[H]=b[x]=0;b[y]=u|32;             /* do move, set non-virgin  */
       if(!(G&M))b[F]=k+6,v+=50;               /* castling: put R & score  */
       v-=p-4|R>29?0:20;                       /* penalize mid-game K move */
       if(p<3)                                 /* pawns:                   */
       {v-=9*((x-2&M||b[x-2]-u)+               /* structure, undefended    */
              (x+2&M||b[x+2]-u)-1              /*        squares plus bias */
             +(b[x^16]==k+36))                 /* kling to non-virgin King */
             -(R>>2);                          /* end-game Pawn-push bonus */
        V=y+r+1&S?647-p:2*(u&y+16&32);         /* promotion or 6/7th bonus */
        b[y]+=V;i+=V;                          /* change piece, add score  */
       }
       v+=e+i;V=m>q?m:q;                       /* new eval and alpha       */
       C=d-1-(d>5&p>2&!t&!h);
       C=R>29|d<3|P-I?C:d;                     /* extend 1 ply if in check */
       do
        s=C>2|v>V?-D(-l,-V,-v,                 /* recursive eval. of reply */
                              F,0,C):v;        /* or fail low if futile    */
       while(s>q&++C<d);v=s;
       if(z&&K-I&&v+I&&x==K&y==L)              /* move pending & in root:  */
       {Q=-e-i;O=F;                            /*   exit if legal & found  */
        R+=i>>7;--Z;return l;                  /* captured non-P material  */
       }
       b[G]=k+6;b[F]=b[y]=0;b[x]=u;b[H]=t;     /* undo move,G can be dummy */
      }
      if(v>m)                                  /* new best, update max,best*/
       m=v,X=x,Y=y|S&F;                        /* mark double move with S  */
      if(h){h=0;goto A;}                       /* redo after doing old best*/
      if(x+r-y|u&32|                           /* not 1st step,moved before*/
         p>2&(p-4|j-7||                        /* no P & no lateral K move,*/
         b[G=x+3^r>>1&7]-k-6                   /* no virgin R in corner G, */
         ||b[G^1]|b[G^2])                      /* no 2 empty sq. next to R */
        )t+=p<5;                               /* fake capt. for nonsliding*/
      else F=y;                                /* enable e.p.              */
     }while(!t);                               /* if not capt. continue ray*/
  }}}while((x=x+9&~M)-B);                      /* next sqr. of board, wrap */
C:if(m>I-M|m<M-I)d=98;                         /* mate holds to any depth  */
  m=m+I|P==I?m:0;                              /* best loses K: (stale)mate*/
  if(z&&d>2)
   {*c='a'+(X&7);c[1]='8'-(X>>4);c[2]='a'+(Y&7);c[3]='8'-(Y>>4&7);c[4]=0;
    breakpoint=2;         					  /* AVR Studio 4 Breakpoint for moves, watch c[] */
#ifdef VERBOSE
//    printf("%2d ply, %9d searched, score=%6d by %c%c%c%c\n",d-1,N-S,m,
//     'a'+(X&7),'8'-(X>>4),'a'+(Y&7),'8'-(Y>>4&7)); /* uncomment for Kibitz */
#endif
  }
 }                                             /* encoded in X S,8 bits    */
 k^=24;                                        /* change sides back        */
 --Z;return m+=m<e;                            /* delayed-loss bonus       */
}

void print_board()
{
 short N=-1;
 myputs("\n\n\r");
 while(++N<121)
 {
  myputchar(N&8&&(N+7)?'\r':' ');           	/* Return & spacer for better viewing */
  myputchar(N&8&&(N+=7)?'\n':".?+nkbrq?*?NKBRQ"[b[N]&15]);
 }
}


void tft_board()
{
	uint8_t pieza;
	uint8_t color_pieza;
	uint8_t color_cuadro;
	uint8_t N=0;
	uint8_t linea=0;
	uint8_t columna=0;

	for (N=0;N<121;N++)
	{
		if (N&8&&(N+=7))
		{
		linea++;
		columna=0;
		}
		else
		{
		pieza = b[N]&7;
		color_pieza=(b[N]&15)>7;
		color_cuadro = (linea+columna)%2;
		if ((color_cuadro!=color_pieza))pieza=pieza+8;	// Si son diferente color usar caracter lleno y no vacío
		if (last_board[N]!=b[N])							// Sólo escribo si las piezas son diferentes
		        {
				if (color_cuadro==0)
					{
					TM_ILI9341_Putc(15+columna*28, 1+linea*28, 32+pieza, &TM_Font_28x28, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
					}
				else
					{
					TM_ILI9341_Putc(15+columna*28, 1+linea*28, 32+pieza, &TM_Font_28x28, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
					}
		        }
		columna++;
		}
	}

	for (N=0;N<121;N++){last_board[N]=b[N];}			// update last board

}


int main(void)
{
#ifdef EDUCIAA

	/* Start slave core */
	CIAA_MULTICORE_IPC_MAILBOX1_ADDR=0;
	CIAA_MULTICORE_IPC_MAILBOX2_ADDR=0;
	cr_start_m0(0, CIAA_MULTICORE_CORE_1_IMAGE);



	for (N=0;N<121;N++){last_board[N]=255;}			// initialize last board

	//Initialize ILI9341
	TM_ILI9341_Init();
	//Rotate LCD for 90 degrees
	TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_2);
	//FIll lcd with color
	TM_ILI9341_Fill(ILI9341_COLOR_ORANGE);

	uint8_t i;
	for (i=0;i<8;i++)TM_ILI9341_Putc(3, 10+i*28, '1'+i, &TM_Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
	for (i=0;i<8;i++)TM_ILI9341_Putc(25+i*28, 228 ,'a'+i, &TM_Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);


	 TM_ILI9341_Puts(245, 7, "M0", &TM_Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_ORANGE);
	 TM_ILI9341_Puts(273, 7, "Core", &TM_Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_ORANGE);


	 TM_ILI9341_Puts(245, 177, "M4", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
	 TM_ILI9341_Puts(273, 177, "Core", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);



	//Put string with black foreground color and blue background with 11x18px font
//	TM_ILI9341_Puts(5, 100, "EDUCIAA CHESS", &TM_Font_16x26, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE);
	//Put string with black foreground color and blue background with 11x18px font

 init_UART_FTDI_EDUCIAA();									/* Inicialización UART_FTDI y */
 myputs("\n\n\r");
 myputs("   EDUCIAA AMP Chess   \n\r");     						/* mensaje de bienvenida      */
 myputs("     Core vs. Core     \n\r");	     						/* mensaje de bienvenida      */
 myputs("M0 Negras  (minusculas)\n\r");	     						/* mensaje de bienvenida      */
 myputs("M4 Blancas (mayusculas)\n\r");	     						/* mensaje de bienvenida      */
 #endif



short temp;
k = WHITE;												/* Empiezan las blancas  */


tft_board();

while(temp>-I+1)
 {
 print_board();											/* Muestro el tablero*/
 tft_board();
 TM_ILI9341_Puts(260, 37, c, &TM_Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_ORANGE);


 myputs("M0 pensando: ");
 p=c;
 while((*p++=mygetchar())>ENTERKEY);                    /* Recibo movimiento de M0 (blancas)*/

 K=*c-16*c[1]+799,L=c[2]-16*c[3]+799;      		    	/* Aplico el movimiento recibido*/
 temp = D(-I,I,Q,O,1,3);

 myputs(c);												/* Muestro el movimiento recibido*/
 myputs("\n\r");

 print_board();											/* Muestro el tablero*/
 tft_board();
 TM_ILI9341_Puts(260, 200, c, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);

 myputs("M4 pensando: ");
 K=I;
 N=0;T=STRENGTH;                                        /* T=Computer Play strength       */
 temp = D(-I,I,Q,O,1,3);								/* Calculo mi movimiento          */

 myputs(c);												/* Muestro el movimiento calculado*/
 myputs("\n\r");

 ipcputs(c);											/* Mando mi movimiento a M0       */
 ipcputchar(ENTERKEY);                                  /* con un Enter al final          */
 }
myputs("FIN DE JUEGO: M4");
while(1);
}
