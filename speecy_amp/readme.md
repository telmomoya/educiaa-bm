Emulador de Spectrum con salida VGA para EduCIAA
==================================

Es una aplicación baremetal multicore: M4 corre el emulador ASpectrum y M0 genera las señales VGA.
La emulación puede funcionar más rápido que el Spectrum original.
Para almacenar el frame VGA (48kb) se usan las memorias AHB32 y AHB16.
El render que corre en M4 escribe en ellas y M0 las lee para generar las señales RGB. Para minimizar los accesos de escritura se utiliza un render diferencial que sólo escribe las actualizaciones.

La generación de los sincronismos VGA es muy simple, está implementada por polling y por lo tanto en el código se ven claramente los momentos de los sincronismos y pórticos.
Para las señales RGB se usa GPIO por DMA que (a diferencia de implementaciones que usan SPI para video monocromático) permite obtener hasta 256 colores por pixel (aunque aquí el Spectrum sólo usa 8).

Para más detalles de la emulación, render y uso de memoria pueden ver la versión single-core para TFT.