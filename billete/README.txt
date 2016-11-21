# Organizador Separador de Billetes (OSB)

Composición del grupo de trabajo:

Ing. Telmo Moya
Ing. Daniel Steiner


Introducción:

El Organizador Billetes es necesario para realizar la separación automática de billetes de denominación conocida considerando su valor y el estado de validez del mismo.

Objetivos y alcance del sistema

El objetivo del sistema es presentar la información del estado de procesamiento de un lote de billetes de entrada y dar aviso cuando esté disponible una cantidad especificada de una determinada denominación y rechazara los que no cumplan con estado para circular.
 
Descripción general

El sistema OSB tiene un lector de billetes BV 20 y para la verificación del sistema se utikiza un LCD gráfico.


Catálogo de Requisitos del Sistema 


1.	Requisitos funcionales (comportamientos)

1.1		La información del lote en proceso se visualizará en un display grafico tipo GLCD de 128x64 dots y utilizando la librería grafica disponible
1.2		El recibirá únicamente información por línea serie desde el lector
1.3		El OSB brinda la informaión por el puerto serie USB



2.	Requisitos de interfaces externas

2.1.	El OSB tendrá conectado el un display grafico tipo GLCD de 128x64 dots mediante el BUS expansión de EDU-CIAA
2.2.	La trama con información procesada de señales locales se transmite hacia el equipo de         Propuesta: RS-232 (9600 baudios) 


3.	Requisitos de desarrollo y restricciones de diseño

3.1.	El OSB deberá diseñarse en base a una EDU- CIAA NXP
3.2.	Un OSB deberá diseñarse utilizando los DRIVERS provistos por el curso de la 7ma ESE

4.	Descomposición del sistema en subsistemas:

4.1.	Sensores Lector de billetes, barrera detector sobre vidrio, 
4.2.	Procesador EDU- CIAA NXP
4.3.	Alimentación desde fuente adicional a la placa

