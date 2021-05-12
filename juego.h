#ifndef __JUEGO_H__
#define __JUEGO_H__

#include <stdlib.h>
#include <stdio.h>

#define MAX_RUTA 200

/*
Pre: -
Post: Jugara el juego completo con las consignas establecidas. 
*/ 

void jugar(char configuraciones[MAX_RUTA],char archivo_grabacion[MAX_RUTA], int quiere_grabar, configuracion_t configuracion);

#endif /*__JUEGO_H__*/

