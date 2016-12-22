Aspectrum para EduCIAA
======================
Emulador de ZXSpectrum con pantalla TFT

Port del emulador ASpectrum para PC a la EduCIAA NXP baremetal, maneja una pantalla ILI9341 SPI y recibe el teclado por el Serial USB.
El resultado es una emulación en tiempo real, la resolución de la pantalla TFT es similar a la del Spectrum original y por lo tanto se ve bastante bien, chico pero bien.
Lo más determinante en el rendimiento fue optimizar la rutina gráfica para minimizar las escrituras por SPI: se hizo que el render trabaje en forma diferencial, es decir que compara el frame actual con una copia que mantiene del frame anterior y sólo actualiza las diferencias.

La ROM del Spectrum (16KB) va a flash de la Educiaa (en un array constante) hecho con bin2header (en Win) desde un dump que se descarga con los fuentes de ASpectrum.
De la misma manera los juegos, son dumps de la memoria y registros del Z80 en un único archivo en formato "sna", que ya es estandar de estos emuladores. Los dumps se hicieron con un emulador en una PC.
Entre las dos cosas (ROM y dumps) usan hasta 64KB de la memoria MFlashA512 (12,5%).

La biblioteca para el manejo del TFT es portada de una escrita para STM32 por  [Tilen Majerle](https://stm32f4-discovery.net/tag/tilen-majerle/)

