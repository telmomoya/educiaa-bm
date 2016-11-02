/*
   ********************* Authors *********************
   ***** Laboratorio de Sistemas Embebidos (LSE) *****
   *****    http://laboratorios.fi.uba.ar/lse    *****
   ******************* 20/12/2011 ********************
     Ezequiel Espósito <ezequiel.esposito@gmail.com>
         Alan Kharsansky <akharsa@gmail.com>
       Federico Roasio <federoasio@gmail.com>
     Daniel Schermuk <daniel.schermuk@gmail.com>
   ***************************************************
*/

#ifndef _GLCD_GUI_H_
#define _GLCD_GUI_H_

#include "GLCDColor.h"
#include "window.h"

#ifndef NULL
#define NULL	0
#endif

typedef unsigned int size_t;

// **********************************
// Internal attributes of Lib_GLCDgui
// **********************************
void* (*GUI_Malloc_Pointer) (size_t wantedSize);
void (*GUI_Free_Pointer) (void* pointer);

// ****************
// Public functions
// ****************
void GUI_StartLibrary (); // GLCDLowLevel_Init (NORMAL);

void GUI_DefineHeapMalloc ( void* (*_Malloc) (size_t wantedSize) );
void GUI_DefineHeapFree ( void (*_Free) (void* pointer) );

void* GUI_Malloc (size_t wantedSize);
void GUI_Free (void* MemoryToFreepointer);

#endif
