/* Esto es una gran cagada
 * solo sirve para que cualquier cambio minimo recompile aspectrum completo
 * cada .c deberia incluir solo los .h que necesite
 * ademas cada .h deberia comprobar que no si incluye dos veces.
 * ademas lo de u8 no es muy bonito si tenemos en cuenta que ya existe byte como tipo de variable
 * he dicho. Alea.
 */

typedef unsigned char u8;

// needed by debugger 
void screenRedraw_forZXDEB (void);
void keyboardHandler_forZXDEB (void);

// all includes needed 
  
#include "main.h"
#include "z80.h"
  
#ifndef CPP_COMPILATION
#include "macros.h"
#else	/*  */
#include "macros.cpp"
#endif	/*  */
  
#include "sound.h"
#include "v_alleg.h"
#include "snaps.h"
#include "debugger.h"
#include "disasm.h"
#include "graphics.h"
// extern Z80Regs spectrumZ80;

