Core vs. Core
=============
AMP Chess
---------

Los cores de la EDU-CIAA se enfrentan al ajedrez por el puerto serie usando la versión sin hash table, de [Andre Adrian](http://www.andreadrian.de/schach), del motor de ajedrez [micromax](http://home.hccnet.nl/h.g.muller/max-src2.html) y firmware bare-metal del [proyecto CIAA](https://github.com/ciaa/Firmware).
La versión human vs computer, EDUCIAA Chess, está disponible [aquí](https://github.com/telmomoya/educiaa-bm/tree/master/umax)

```
Comienza M0 que juega con las blancas. M4 juega con las negras y muestra el tablero. Un sencillo IPC (shared memory polling) pasa los movimientos de un core al otro.


8  r n b q k b n r
7  + + + + + + + +
6  . . . . . . . .
5  . . . . . . . .
4  . . . . . . . .
3  . . . . . . . .
2  * * * * * * * *
1  R N B Q K B N R 

   a b c d e f g h

```