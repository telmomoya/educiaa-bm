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


#include "GLCDgui.h"

#include "GLCDLowLevel.h"
#include "GLCDPrimitives.h"
#include "SystemFont5x7.h"
#include "window.h"

// ******************
// Private attributes
// ******************

void GUI_StartLibrary ()
{
	GLCDLowLevel_Init ( NORMAL );
	GLCDPrimitives_ClearScreen ( WHITE );
	GLCDLowLevel_SwapBuffer ();
}

void GUI_DefineHeapMalloc ( void* (*_Malloc) (size_t wantedSize) )
{
	GUI_Malloc_Pointer = _Malloc;
}

void GUI_DefineHeapFree ( void (*_Free) (void* pointer) )
{
	GUI_Free_Pointer = _Free;
}

void* GUI_Malloc (size_t wantedSize)
{
    return GUI_Malloc_Pointer (wantedSize);
}

void GUI_Free (void* MemoryToFreepointer)
{
	GUI_Free_Pointer (MemoryToFreepointer);
}
