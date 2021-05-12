#ifndef __EXTRAS_H__
#define __EXTRAS_H__

#include <stdlib.h>
#include <stdio.h>
#include "defendiendo_torres.h"

#define MAX_FILAS 30
#define MAX_COLUMNAS 30
#define MAX_LONGITUD_CAMINO 200
#define MAX_ENEMIGOS 500
#define MAX_DEFENSORES 50
#define MAX_RUTA 200

/* 
 * Escribira la configuracion establecida por el usuario en un archivo de texto.
 */

void escribir_configuracion(FILE* configuraciones, configuracion_t* configuracion);

/* 
 * Creará la configuracion con los datos ingresados por el usuario.
 */

void crear_configuracion(configuracion_t* configuracion);

/* 
 * Creará los caminos elegidos por el usuario para todos los niveles. 
 */

void inicializar_caminos_en_niveles(caminos_t* caminos,FILE* archivo_camino);

/* 
 * Leerá los caminos elegidos por el usuario para todos los niveles. 
 */

int leer_caminos(configuracion_t* configuracion, caminos_t* caminos, int nivel);

/* 
 * Leerá la configuracion elegida por el usuario. 
 */

int leer_configuracion(configuracion_t* configuracion, char archivo_config[MAX_RUTA]);


#endif /* __EXTRAS_H__ */