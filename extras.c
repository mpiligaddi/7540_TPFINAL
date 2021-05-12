#include "defendiendo_torres.h"
#include "animos.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define ERROR -1  
#define MAX_RUTA 100
#define MAX_JUGADORES 100
#define MAX_NOMBRE 30
#define VELOCIDAD_DEFAULT 1
#define VIDA_INICIAL_TORRE 600
#define COSTO_POR_ENANO_EXTRA 50
#define COSTO_POR_ELFO_EXTRA 50
#define ENANOS_EXTRA 10
#define ELFOS_EXTRA 10
#define MAX_LONGITUD_CAMINO 200
#define MAX_CONFIG 100
#define ENANOS_NIVEL_1 5
#define ENANOS_NIVEL_2 0
#define ENANOS_NIVEL_3 3
#define ENANOS_NIVEL_4 4
#define ELFOS_NIVEL_1 0
#define ELFOS_NIVEL_2 5
#define ELFOS_NIVEL_3 3
#define ELFOS_NIVEL_4 4
#define NIVEL_1 1
#define NIVEL_2 2
#define NIVEL_3 3
#define NIVEL_4 4
#define MINIMO_VALIDO -1 
#define VACIO 0
#define GOLPE_FALLIDO 0
#define GOLPE_CRITICO_ENANOS 100
#define GOLPE_CRITICO_ELFOS 70
#define DEFAULT -1
#define ENANOS_INICIO 12
#define ELFOS_INICIO 12
#define ARRIBA 'W'
#define ABAJO 'S'
#define IZQUIERDA 'A'
#define DERECHA 'D'
#define TERMINADO 'N'
#define TERRENO_CHICO 15
#define TERRENO_GRANDE 20
#define POSIBLE 0
#define NO_POSIBLE -1
#define TERRENO 'X'
#define CAMINO ' '
#define CAMINO_1 1
#define CAMINO_2 2
#define TORRE 'T'
#define ENTRADA 'E'
#define PRIMER_NIVEL 1
#define SEGUNDO_NIVEL 2
#define TERCER_NIVEL 3
#define CUARTO_NIVEL 4
#define CRITICO_MALO 0
#define CRITICO_BUENO 25
#define CRITICO_REGULAR 10 
#define ANIMO_MALO 'M'
#define ANIMO_REGULAR 'R'
#define ANIMO_BUENO 'B'
#define CONFIG_DEFAULT "config_default.txt"
#define MAXIMO_VALIDO 200
#define DEF_ENANOS "enanos"
#define DEF_ELFOS "elfos"
#define TORRE_1 1
#define TORRE_2 2
#define LETRA_DEFAULT 'X'
#define FORMATO_TORRES "RESISTENCIA_TORRES=%i,%i\n"
#define FORMATO_ENANOS_INICIO "ENANOS_INICIO=%i,%i,%i,%i\n"
#define FORMATO_ELFOS_INICIO "ELFOS_INICIO=%i,%i,%i,%i\n"
#define FORMATO_ENANOS_EXTRA "ENANOS_EXTRA=%i,%i\n"
#define FORMATO_ELFOS_EXTRA "ELFOS_EXTRA=%i,%i\n"
#define FORMATO_ANIMO_ENANOS "ANIMO_ENANOS=%i,%i\n"
#define FORMATO_ANIMO_ELFOS "ANIMO_ELFOS=%i,%i\n"
#define FORMATO_VELOCIDAD "VELOCIDAD=%f\n"
#define FORMATO_CAMINOS "CAMINOS=%s\n"

/*
Pre: -
Post: Escribira la configuracion que ingrese el usuario en un archivo determinado.
*/

void escribir_configuracion(FILE* configuraciones, configuracion_t* configuracion) {

	fprintf(configuraciones,FORMATO_TORRES, (*configuracion).resistencia_torre_1, (*configuracion).resistencia_torre_2);
	fprintf(configuraciones,FORMATO_ENANOS_INICIO,(*configuracion).cant_enanos_inicial.nivel_1,(*configuracion).cant_enanos_inicial.nivel_2,(*configuracion).cant_enanos_inicial.nivel_3,(*configuracion).cant_enanos_inicial.nivel_4);
	fprintf(configuraciones,FORMATO_ELFOS_INICIO,(*configuracion).cant_elfos_inicial.nivel_1,(*configuracion).cant_elfos_inicial.nivel_2,(*configuracion).cant_elfos_inicial.nivel_3,(*configuracion).cant_elfos_inicial.nivel_4);
	fprintf(configuraciones,FORMATO_ENANOS_EXTRA,(*configuracion).enanos_extra,(*configuracion).costo_torre_1);
	fprintf(configuraciones,FORMATO_ELFOS_EXTRA,(*configuracion).elfos_extra,(*configuracion).costo_torre_2);
	fprintf(configuraciones,FORMATO_ANIMO_ENANOS,(*configuracion).fallo_enanos,(*configuracion).critico_enanos);
	fprintf(configuraciones,FORMATO_ANIMO_ELFOS,(*configuracion).fallo_elfos,(*configuracion).critico_elfos);
	fprintf(configuraciones,FORMATO_VELOCIDAD, (*configuracion).velocidad);
	fprintf(configuraciones,FORMATO_CAMINOS, (*configuracion).caminos); 
}

/*
Pre: -
Post: Carga las resistencias de las torres segun la resistencia requerida por el usuario. 
*/

void ingresar_resistencia_torre(int* resistencia_torre, int num_torre) {
	
	printf("RESISTENCIA TORRE %i: \n", num_torre);
	scanf("%i", resistencia_torre);
	while (((*resistencia_torre) < MINIMO_VALIDO) || ((*resistencia_torre) == VACIO)) {
		printf("La resistencia de las Torres tienen que ser mayores o iguales a -1. Tampoco pueden ser 0.\nVolvelo a ingresar porfi: ");
		scanf("%i",resistencia_torre);
	}
}

/*
Pre: -
Post: Carga la cantidad de defensores segun la cantidad requerida por el usuario. 
*/

void ingresar_cant_defensores(int* cant_defensores, char* tipo) {

	scanf("%i", cant_defensores);
	while(((*cant_defensores) < MINIMO_VALIDO) || ((*cant_defensores) > MAXIMO_VALIDO)) {
		printf("La cantidad de %s debe ser mayor o igual a -1. Tambien debe ser menor a 200.\nVolvelo a ingresar porfi:", tipo);
		scanf("%i",cant_defensores);
	}
}

/*
Pre: -
Post: Carga los defensores requeridos por el usuario. 
*/

void ingresar_defensores(nivel_actual_t* cant_defensores_inicial, char* tipo) {

	for(int i=1 ; i <= 4 ; i++) { 

		printf("DEFENSORES: %s. NIVEL %i: \n", tipo, i);

		if(i==NIVEL_1) { 
			ingresar_cant_defensores(&((*cant_defensores_inicial).nivel_1), tipo);
		}
		if(i==NIVEL_2) { 
			ingresar_cant_defensores(&((*cant_defensores_inicial).nivel_2), tipo);
		}
		if(i==NIVEL_3) { 
			ingresar_cant_defensores(&((*cant_defensores_inicial).nivel_3), tipo);
		}
		if(i==NIVEL_4) { 
			ingresar_cant_defensores(&((*cant_defensores_inicial).nivel_4), tipo);
		}
	}
}

/*
Pre: -
Post: Carga los defensores extras requeridos por el usuario.
*/

void ingresar_cant_defensores_extras(int* cant_defensores_extras, char* tipo) {

	printf("DEFENSORES EXTRAS: %s\n", tipo );
	scanf("%i", cant_defensores_extras);
	while(((*cant_defensores_extras) < MINIMO_VALIDO) || ((*cant_defensores_extras) > MAXIMO_VALIDO)) {
		printf("La cantidad de %s extras debe ser mayor o igual a -1. Tambien debe ser menor a 200.\nVolvelo a ingresar porfi:", tipo);
		scanf("%i",cant_defensores_extras);
	}
}

/*
Pre: -
Post: Carga los costos de las torres segun los costos requeridos por el usuario. 
*/

void ingresar_costo_torre(int* costo_torre, int num_torre) {
	
	printf("COSTO TORRE %i: \n", num_torre);
	scanf("%i", costo_torre);
	while (((*costo_torre) < MINIMO_VALIDO) || ((*costo_torre) == VACIO)) {
		printf("El costode las Torres tienen que ser mayores o iguales a -1. Tampoco pueden ser 0.\nVolvelo a ingresar porfi:");
		scanf("%i",costo_torre);
	}
}

/*
Pre: -
Post: Carga los fallos (golpes fallidos) de ambos tipos de defensores segun los requeridos por el usuario. 
*/

void ingresar_fallo_defensor(int* fallo_defensor, char* tipo) {
	
	printf("FALLO DE DEFENSORES: %s \n", tipo);
	scanf("%i", fallo_defensor);
	while ((*fallo_defensor) < MINIMO_VALIDO) {
		printf("El porcentaje de fallo debe ser mayor o igual a -1.\nVolvelo a ingresar porfi: ");
		scanf("%i",fallo_defensor);
	}
}

/*
Pre: -
Post: Carga los golpes criticos de ambos tipos de defensores segun los requeridos por el usuario. 
*/

void ingresar_critico_defensor(int* critico_defensor, char* tipo) {
	
	printf("CRITICO DE DEFENSORES: %s \n", tipo);
	scanf("%i", critico_defensor);
	while ((*critico_defensor) < MINIMO_VALIDO) {
		printf("El porcentaje de critico debe ser mayor o igual a -1.\nVolvelo a ingresar porfi: ");
		scanf("%i",critico_defensor);
	}
}

/*
Pre: -
Post: Carga la velocidad requerida por el usuario. 
*/

void ingresar_velocidad(float* velocidad) {
	
	printf("VELOCIDAD: \n");
	scanf("%f", velocidad);
	while (((*velocidad) == VACIO) || ((*velocidad) < DEFAULT)) {
		printf("La velocidad no puede ser cero ni menor a -1. Volve a ingresar porfi: ");
		scanf("%f",velocidad);
	}
}

/*
Pre: -
Post: Carga el camino requerido por el usuario. 
*/

void ingresar_caminos(char* caminos) {

	char arch_caminos[MAX_RUTA];

	printf("CAMINO: \n");
	scanf("%s", caminos);

	strcpy(arch_caminos, caminos);
	size_t n = strlen(arch_caminos);

	while((strcmp (&(arch_caminos[n-4]), ".txt") != 0) && (atoi(caminos) != -1)) {
		printf("El camino ingresado debe estar cargado anteriormente y tener una extension .txt\n Volve a ingresar porfi\n");
		scanf("%s", caminos);
		strcpy(arch_caminos, caminos);
		n = strlen(arch_caminos);
	}

	if(atoi(caminos) != -1) { 

		FILE* archivo_de_caminos = fopen(arch_caminos, "r");

		while(!archivo_de_caminos){
			printf("El camino ingresado debe estar cargado anteriormente. Volve a ingresar porfi\n");
			scanf("%s", caminos);
			strcpy(arch_caminos, caminos);
			archivo_de_caminos = fopen(arch_caminos, "r");
		}
		fclose(archivo_de_caminos);
	}
}

/*
Pre: -
Post: Creara las configuraciones que el usuario considere necesarias. 
*/

void crear_configuracion(configuracion_t* configuracion) {
				
	printf("Para crear una nueva configuracion, complete los siguientes datos:\n");

	ingresar_resistencia_torre(&((*configuracion).resistencia_torre_1), TORRE_1);

	ingresar_resistencia_torre(&((*configuracion).resistencia_torre_2), TORRE_2);

	ingresar_defensores(&((*configuracion).cant_enanos_inicial), DEF_ENANOS);

	ingresar_defensores(&((*configuracion).cant_elfos_inicial), DEF_ELFOS);

	ingresar_cant_defensores_extras(&((*configuracion).enanos_extra), DEF_ENANOS);

	ingresar_cant_defensores_extras(&((*configuracion).elfos_extra), DEF_ELFOS);

	ingresar_costo_torre(&(*configuracion).costo_torre_1, TORRE_1);

	ingresar_costo_torre(&(*configuracion).costo_torre_2, TORRE_2);

	ingresar_fallo_defensor(&(*configuracion).fallo_enanos, DEF_ENANOS);

	ingresar_critico_defensor(&(*configuracion).critico_enanos, DEF_ENANOS);

	ingresar_fallo_defensor(&(*configuracion).fallo_elfos, DEF_ELFOS);

	ingresar_critico_defensor(&(*configuracion).critico_elfos, DEF_ELFOS);

	ingresar_velocidad(&(*configuracion).velocidad);

	ingresar_caminos((*configuracion).caminos);

}

/*
Pre: -
Post: Inicializara el terreno para crear los caminos personalizados. 
*/

void inicializar_terreno_para_caminos(int nivel_actual, char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO]){
	if(nivel_actual < TERCER_NIVEL) {
		for (int i = 0; i < TERRENO_CHICO; i++) {
			for (int j = 0; j < TERRENO_CHICO; j++) {
				terreno[i][j] = TERRENO;
			}
		}
	}
	else {
		for(int i = 0; i < TERRENO_GRANDE; i++) {
			for (int j = 0; j < TERRENO_GRANDE; j++) {
				terreno[i][j] = TERRENO;
			}
		}
	}
}

/*
Pre: -
Post: Mostrara el terreno para crear los caminos personalizados. 
*/

void mostrar_terreno_para_caminos(int nivel_actual, char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO]){

	if(nivel_actual < TERCER_NIVEL) { 
		for (int i = 0; i < TERRENO_CHICO; i++) {
			for (int j = 0; j < TERRENO_CHICO; j++) {
				printf("%c  ", terreno[i][j]);
				
		}
					printf("  \n");		
	}
}
	else {
			for (int i = 0; i < TERRENO_GRANDE; i++) {
				for (int j = 0; j < TERRENO_GRANDE; j++) {
					printf("%c  ", terreno[i][j]);
			}
						printf("  \n");
		}
	}
	printf("  \n");
}

/*
Pre: -
Post: Introducira en el terreno los caminos personalizados con la entrada y torre en el lugar correspondiente. 
*/

void poner_caminos_creados(caminos_t* caminos, char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO]) {

	for(int i=0 ; i < (*caminos).tope_camino_1; i++) {
		terreno[(*caminos).camino_1[i].fil][(*caminos).camino_1[i].col] = CAMINO;
	}
	for(int i=0 ; i < (*caminos).tope_camino_2; i++) {
		terreno[(*caminos).camino_2[i].fil][(*caminos).camino_2[i].col] = CAMINO;
	}
	if((*caminos).tope_camino_1 > VACIO) { 
		terreno[(*caminos).camino_1[0].fil][(*caminos).camino_1[0].col] = ENTRADA;
		terreno[(*caminos).camino_1[(*caminos).tope_camino_1-1].fil][(*caminos).camino_1[(*caminos).tope_camino_1-1].col] = TORRE;
	}
	if((*caminos).tope_camino_2 > VACIO) { 
		terreno[(*caminos).camino_2[0].fil][(*caminos).camino_2[0].col] = ENTRADA;
		terreno[(*caminos).camino_2[(*caminos).tope_camino_2-1].fil][(*caminos).camino_2[(*caminos).tope_camino_2-1].col] = TORRE;
	}
}

/*
Pre: -
Post: Mostrara el terreno del juego para los caminos personalizados. 
*/

void mostrar_juego_para_caminos(caminos_t caminos){

	char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO];

	inicializar_terreno_para_caminos(caminos.nivel_actual, terreno);
	poner_caminos_creados(&caminos,terreno);
	mostrar_terreno_para_caminos(caminos.nivel_actual, terreno);

}

/*
Pre: -
Post: Devuelve true si el rango para posicionar los caminos es invalido o false si no lo es. 
*/

bool rango_invalido_caminos(caminos_t* caminos , coordenada_t posicion) {
	bool es_invalido=false;

	if(((*caminos).nivel_actual == PRIMER_NIVEL) || ((*caminos).nivel_actual == SEGUNDO_NIVEL)) { 
		if((posicion.fil >= TERRENO_CHICO) || (posicion.col >= TERRENO_CHICO) || (posicion.fil < VACIO) || (posicion.col < VACIO)) {
			es_invalido=true;
		}
	}
	else if (((*caminos).nivel_actual == TERCER_NIVEL) || ((*caminos).nivel_actual == CUARTO_NIVEL)) {
		if((posicion.fil >= TERRENO_GRANDE) || (posicion.col >= TERRENO_GRANDE) || (posicion.fil < VACIO) || (posicion.col < VACIO)) {
			es_invalido=true;
		}
	}
	return es_invalido; 
}

/*
Pre: -
Post: Devuelve true si las coordenadas para posicionar los caminos son invalidas o false si no lo son. 
*/

bool coordenadas_invalidas_caminos(caminos_t* caminos , coordenada_t posicion) { 

	bool son_invalidas = false;  

	for(int i=0 ; i < (*caminos).tope_camino_1 ; i++) {
		if(((*caminos).camino_1[i].fil == posicion.fil) && ((*caminos).camino_1[i].col == posicion.col)) {
			son_invalidas = true;
		}
	}
	for(int i=0 ; i < (*caminos).tope_camino_2 ; i++) {
		if(((*caminos).camino_2[i].fil == posicion.fil) && ((*caminos).camino_2[i].col == posicion.col)) {
			son_invalidas = true;
		}
	}
	return son_invalidas; 
} 

/*
Pre: -
Post: Devuelve -1 si no se pudieron agregar las coordenadas de los caminos o 0 si pudieron ser agregadas. 
*/

int agregar_caminos_creados(caminos_t* caminos, coordenada_t posicion, int camino){

	if(coordenadas_invalidas_caminos(&(*caminos), posicion) == true) {
		return NO_POSIBLE;
	}
	if(camino == CAMINO_1) { 
		(*caminos).camino_1[(*caminos).tope_camino_1].fil = posicion.fil;
		(*caminos).camino_1[(*caminos).tope_camino_1].col = posicion.col;
		((*caminos).tope_camino_1)++;
		return POSIBLE;
	}
	if(camino == CAMINO_2) {  
		(*caminos).camino_2[(*caminos).tope_camino_2].fil = posicion.fil;
		(*caminos).camino_2[(*caminos).tope_camino_2].col = posicion.col;
		((*caminos).tope_camino_2)++;
		return POSIBLE;
	}
	return NO_POSIBLE;
}

/*
Pre: -
Post: Preguntara al usuario donde quiere posicionar la entrada y las coordenadas de los caminos. 
*/

void preguntar_caminos(caminos_t* caminos , coordenada_t posicion_aux, int camino) {

	char letra = LETRA_DEFAULT; 

	if(camino == CAMINO_1) { 

		printf("POSICION ENTRADA 1:\n");
		printf("Ingrese una fila: ");
		scanf("%i", &(posicion_aux.fil));
		printf("Ingrese una columna: ");
		scanf("%i", &(posicion_aux.col));

		while((rango_invalido_caminos(&(*caminos),posicion_aux) == true) || (agregar_caminos_creados(&(*caminos),posicion_aux,CAMINO_1)==NO_POSIBLE)) {
			printf ("El valor ingresado no esta dentro del rango. Volve a ingresar fila y columna porfi:\n");
			printf("Ingrese una fila: ");
			scanf("%i", &(posicion_aux.fil));
			printf("Ingrese una columna: ");
			scanf("%i", &(posicion_aux.col));
		} 

		mostrar_juego_para_caminos(*caminos);

		while (letra != TERMINADO) { 

			printf("Ingrese una tecla, W (ARRIBA) A (IZQUIERDA) S (ABAJO) D (DERECHA) :\n");
			printf("En caso de querer finalizar el camino, presione la tecla N (TERMINADO) \n");

			scanf(" %c", &letra);

			while((letra != TERMINADO) && (letra != ARRIBA) && (letra != ABAJO) && (letra != DERECHA) && (letra != IZQUIERDA)) {
				printf ("La letra ingresada no es valida. Volve a ingresar porfi:\n");
				scanf("	%c", &letra);
			}

    		if(letra == ARRIBA) {
    			posicion_aux.fil--;
    		}
    		else if(letra == ABAJO) {
   				posicion_aux.fil++;
   			}
    		else if(letra == DERECHA) {
    			posicion_aux.col++;
    		}
   			else if(letra == IZQUIERDA) {
    			posicion_aux.col--;
    		}

   			if(rango_invalido_caminos(&(*caminos), posicion_aux) == true || agregar_caminos_creados(&(*caminos),posicion_aux, CAMINO_1) == NO_POSIBLE) {
        		printf ("El valor ingresado no esta dentro del rango. Volve a ingresar porfi:\n");
      			posicion_aux.fil = (*caminos).camino_1[(*caminos).tope_camino_1-1].fil;
       			posicion_aux.col = (*caminos).camino_1[(*caminos).tope_camino_1-1].col;
    		}
   			mostrar_juego_para_caminos(*caminos);
		}
	}

	else if(camino == CAMINO_2) {

		printf("POSICION ENTRADA 2:\n");
		printf("Ingrese una fila: ");
		scanf("%i", &(posicion_aux.fil));
		printf("Ingrese una columna: ");
		scanf("%i", &(posicion_aux.col));

		while((rango_invalido_caminos(&(*caminos),posicion_aux) == true)|| (agregar_caminos_creados(&(*caminos),posicion_aux,CAMINO_2)==NO_POSIBLE)) { 
			printf ("El valor ingresado no esta dentro del rango. Volve a ingresar fila y columna porfi:\n");
			printf("Ingrese una fila: ");
			scanf("%i", &(posicion_aux.fil));
			printf("Ingrese una columna: ");
			scanf("%i", &(posicion_aux.col));
		} 

		mostrar_juego_para_caminos(*caminos);

		while (letra != TERMINADO) { 

			printf("Ingrese una tecla, W (ARRIBA) A (IZQUIERDA) S (ABAJO) D (DERECHA) :\n");
			printf("En caso de querer finalizar el camino, presione la tecla N (TERMINADO) \n");

			scanf(" %c", &letra);

			while((letra != TERMINADO) && (letra != ARRIBA) && (letra != ABAJO) && (letra != DERECHA) && (letra != IZQUIERDA)) {
				printf ("La letra ingresada no es valida. Volve a ingresar porfi:\n");
				scanf("	%c", &letra);
			}

   			if(letra == ARRIBA) {
    			posicion_aux.fil--;
    		}
    		else if(letra == ABAJO) {
    			posicion_aux.fil++;
   			}
    		else if(letra == DERECHA) {
    			posicion_aux.col++;
    		}
   			else if(letra == IZQUIERDA) {
   				posicion_aux.col--;
    		}

   			if(rango_invalido_caminos(&(*caminos), posicion_aux) == true || agregar_caminos_creados(&(*caminos),posicion_aux, CAMINO_2) == NO_POSIBLE){
        		printf ("El valor ingresado no esta dentro del rango. Volve a ingresar porfi:\n");
      			posicion_aux.fil = (*caminos).camino_2[(*caminos).tope_camino_2-1].fil;
   				posicion_aux.col = (*caminos).camino_2[(*caminos).tope_camino_2-1].col;
    		}
   			
   			mostrar_juego_para_caminos(*caminos);
		}
	}
}

/*
Pre: -
Post: Escribira las coordenadas de los caminos creados por el usuario en un archivo determinado. 
*/

void escribir_camino(FILE* archivo_camino, caminos_t* caminos) {

	if((*caminos).nivel_actual == PRIMER_NIVEL) { 
		fprintf(archivo_camino, "NIVEL=%i\n",(*caminos).nivel_actual);
		fprintf(archivo_camino, "CAMINO=1\n");
		for(int i=0 ; i < (*caminos).tope_camino_1 ; i++) { 
			fprintf(archivo_camino, "%i;%i\n", (*caminos).camino_1[i].fil, (*caminos).camino_1[i].col);
		}
	}
	
	else if((*caminos).nivel_actual == SEGUNDO_NIVEL) { 
		fprintf(archivo_camino, "NIVEL=%i\n",(*caminos).nivel_actual);
		fprintf(archivo_camino, "CAMINO=1\n");
		for(int i=0 ; i < (*caminos).tope_camino_1 ; i++) { 
			fprintf(archivo_camino, "%i;%i\n", (*caminos).camino_1[i].fil, (*caminos).camino_1[i].col);
		}
	}
	
	else if((*caminos).nivel_actual == TERCER_NIVEL) { 
		fprintf(archivo_camino, "NIVEL=%i\n",(*caminos).nivel_actual);
		fprintf(archivo_camino, "CAMINO=1\n");
		for(int i=0 ; i < (*caminos).tope_camino_1 ; i++) { 
			fprintf(archivo_camino, "%i;%i\n", (*caminos).camino_1[i].fil, (*caminos).camino_1[i].col);
		}
		fprintf(archivo_camino, "CAMINO=2\n");
		for(int i=0 ; i < (*caminos).tope_camino_2 ; i++) { 
			fprintf(archivo_camino, "%i;%i\n", (*caminos).camino_2[i].fil, (*caminos).camino_2[i].col);
		}
	}

	else if((*caminos).nivel_actual == CUARTO_NIVEL) { 
		fprintf(archivo_camino, "NIVEL=%i\n",(*caminos).nivel_actual);
		fprintf(archivo_camino, "CAMINO=1\n");
		for(int i=0 ; i < (*caminos).tope_camino_1 ; i++) { 
			fprintf(archivo_camino, "%i;%i\n", (*caminos).camino_1[i].fil, (*caminos).camino_1[i].col);
		}
		fprintf(archivo_camino, "CAMINO=2\n");
		for(int i=0 ; i < (*caminos).tope_camino_2 ; i++) { 
			fprintf(archivo_camino, "%i;%i\n", (*caminos).camino_2[i].fil, (*caminos).camino_2[i].col);
		}
	}
}


/*
Pre: -
Post: Inicializara los caminos creados por el usuario. 
*/

void inicializar_caminos(caminos_t* caminos) {

	coordenada_t posicion_aux;

	printf("CREA TU PROPIO CAMINO!! :) \n");

	if((*caminos).nivel_actual == PRIMER_NIVEL) { 
		printf("        NIVEL 1 \n");
		preguntar_caminos(&(*caminos), posicion_aux, CAMINO_1);
		mostrar_juego_para_caminos(*caminos);
	}

	if((*caminos).nivel_actual == SEGUNDO_NIVEL) { 
		printf("        NIVEL 2 \n");
		preguntar_caminos(&(*caminos), posicion_aux, CAMINO_1);
		mostrar_juego_para_caminos(*caminos);
	}

	if((*caminos).nivel_actual == TERCER_NIVEL) { 
		printf("        NIVEL 3 \n");
		preguntar_caminos(&(*caminos), posicion_aux, CAMINO_1);
		mostrar_juego_para_caminos(*caminos);
		preguntar_caminos(&(*caminos), posicion_aux, CAMINO_2);
		mostrar_juego_para_caminos(*caminos);
	}

	if((*caminos).nivel_actual == CUARTO_NIVEL) { 
		printf("        NIVEL 4 \n");
		preguntar_caminos(&(*caminos), posicion_aux, CAMINO_1);
		mostrar_juego_para_caminos(*caminos);
		preguntar_caminos(&(*caminos), posicion_aux, CAMINO_2);
		mostrar_juego_para_caminos(*caminos);
	}
}


/*
Pre: -
Post: Inicializara los caminos creados por el usuario segun cada nivel.
*/

void inicializar_caminos_en_niveles(caminos_t* caminos, FILE* archivo_camino) {

	(*caminos).tope_camino_1 = 0;
	(*caminos).tope_camino_2 = 0;

	if((*caminos).nivel_actual == PRIMER_NIVEL) {
		mostrar_juego_para_caminos(*caminos);
		inicializar_caminos(&(*caminos));
		system("clear");
		printf("==== Ingreso del camino 1 para NIVEL 1 finalizado exitosamente ===\n");
		printf("          ==== Resumen del camino a continuacion ====\n");
		mostrar_juego_para_caminos(*caminos);
		escribir_camino(archivo_camino, &(*caminos)); 
	}

	if((*caminos).nivel_actual == SEGUNDO_NIVEL) {
		mostrar_juego_para_caminos(*caminos);
		inicializar_caminos(&(*caminos));
		system("clear");
		printf("==== Ingreso del camino 1 para NIVEL 2 finalizado exitosamente ===\n");
		printf("          ==== Resumen del camino a continuacion ====\n");
		mostrar_juego_para_caminos(*caminos);
		escribir_camino(archivo_camino, &(*caminos)); 
	}

	if((*caminos).nivel_actual == TERCER_NIVEL) {
		mostrar_juego_para_caminos(*caminos);
		inicializar_caminos(&(*caminos));
		system("clear");
		printf("==== Ingreso del camino 1 y 2 para NIVEL 3 finalizado exitosamente ===\n");
		printf("          ==== Resumen del camino a continuacion ====\n");
		mostrar_juego_para_caminos(*caminos);
		escribir_camino(archivo_camino, &(*caminos)); 
	}

	if((*caminos).nivel_actual == CUARTO_NIVEL) {
		mostrar_juego_para_caminos(*caminos);
		inicializar_caminos(&(*caminos));
		system("clear");
		printf("==== Ingreso del camino 1 y 2 para NIVEL 4 finalizado exitosamente ===\n");
		printf("          ==== Resumen del camino a continuacion ====\n");
		mostrar_juego_para_caminos(*caminos);
		escribir_camino(archivo_camino, &(*caminos)); 
	}
}

/*
Pre: -
Post: Leera las coordenadas de los caminos creados por el usuario de un archivo determinado. 
*/

void leer_caminos(configuracion_t* configuracion, caminos_t* caminos, int nivel) {

	int camino_1;
	int camino_2;
	int leidos;
	(*caminos).tope_camino_1 = 0; 
	(*caminos).tope_camino_2 = 0;

	FILE* archivo_de_caminos = fopen((*configuracion).caminos, "r");

	if(!archivo_de_caminos){
		printf("No se pudo leer el archivo!\n");
		return;
	}
	
	leidos = fscanf(archivo_de_caminos , "NIVEL=%i\n", &(*caminos).nivel_actual);
	leidos = fscanf(archivo_de_caminos, "CAMINO=%i\n", &(camino_1)); 

	if(((*caminos).nivel_actual == PRIMER_NIVEL)) { 
		leidos=fscanf(archivo_de_caminos, "%i;%i\n",  &(*caminos).camino_1[(*caminos).tope_camino_1].fil, &(*caminos).camino_1[(*caminos).tope_camino_1].col);
		while(leidos == 2) { 
			((*caminos).tope_camino_1)++;
			leidos = fscanf(archivo_de_caminos, "%i;%i\n",  &(*caminos).camino_1[(*caminos).tope_camino_1].fil, &(*caminos).camino_1[(*caminos).tope_camino_1].col);
		}
		leidos = fscanf(archivo_de_caminos , "NIVEL=%i\n", &(*caminos).nivel_actual); 
		leidos = fscanf(archivo_de_caminos, "CAMINO=%i\n", &(camino_1));
	}
	
	if(((*caminos).nivel_actual == SEGUNDO_NIVEL) && ((nivel == SEGUNDO_NIVEL) || (nivel == TERCER_NIVEL) || (nivel == CUARTO_NIVEL))) { 
		(*caminos).tope_camino_1 = 0; 
		leidos=fscanf(archivo_de_caminos, "%i;%i\n",  &(*caminos).camino_1[(*caminos).tope_camino_1].fil, &(*caminos).camino_1[(*caminos).tope_camino_1].col);
		while(leidos == 2) { 
			((*caminos).tope_camino_1)++;
			leidos = fscanf(archivo_de_caminos, "%i;%i\n",  &(*caminos).camino_1[(*caminos).tope_camino_1].fil, &(*caminos).camino_1[(*caminos).tope_camino_1].col);
		}
		leidos = fscanf(archivo_de_caminos , "NIVEL=%i\n", &(*caminos).nivel_actual); 
		leidos = fscanf(archivo_de_caminos, "CAMINO=%i\n", &(camino_1));
	}

	if(((*caminos).nivel_actual == TERCER_NIVEL) && ((nivel == TERCER_NIVEL) || (nivel == CUARTO_NIVEL))) { 
		(*caminos).tope_camino_1 = 0; 
		(*caminos).tope_camino_2 = 0; 
		leidos=fscanf(archivo_de_caminos, "%i;%i\n",  &(*caminos).camino_1[(*caminos).tope_camino_1].fil, &(*caminos).camino_1[(*caminos).tope_camino_1].col);
		while(leidos == 2) { 
			((*caminos).tope_camino_1)++;
			leidos = fscanf(archivo_de_caminos, "%i;%i\n",  &(*caminos).camino_1[(*caminos).tope_camino_1].fil, &(*caminos).camino_1[(*caminos).tope_camino_1].col);
		}
		fscanf(archivo_de_caminos, "CAMINO=%i\n", &(camino_2)); 
		leidos = fscanf(archivo_de_caminos, "%i;%i\n",  &(*caminos).camino_2[(*caminos).tope_camino_2].fil, &(*caminos).camino_2[(*caminos).tope_camino_2].col);
		while(leidos == 2) { 
			((*caminos).tope_camino_2)++;
			leidos = fscanf(archivo_de_caminos, "%i;%i\n",  &(*caminos).camino_2[(*caminos).tope_camino_2].fil, &(*caminos).camino_2[(*caminos).tope_camino_2].col);
		}
		leidos = fscanf(archivo_de_caminos , "NIVEL=%i\n", &(*caminos).nivel_actual); 
		leidos = fscanf(archivo_de_caminos, "CAMINO=%i\n", &(camino_1));
	}

	if((((*caminos).nivel_actual == CUARTO_NIVEL) && (nivel == CUARTO_NIVEL))) { 
		(*caminos).tope_camino_1 = 0; 
		(*caminos).tope_camino_2 = 0; 
		leidos=fscanf(archivo_de_caminos, "%i;%i\n",  &(*caminos).camino_1[(*caminos).tope_camino_1].fil, &(*caminos).camino_1[(*caminos).tope_camino_1].col);
		while(leidos == 2) { 
			((*caminos).tope_camino_1)++;
			leidos = fscanf(archivo_de_caminos, "%i;%i\n",  &(*caminos).camino_1[(*caminos).tope_camino_1].fil, &(*caminos).camino_1[(*caminos).tope_camino_1].col);
		}
		fscanf(archivo_de_caminos, "CAMINO=%i\n", &(camino_2)); 
		leidos = fscanf(archivo_de_caminos, "%i;%i\n",  &(*caminos).camino_2[(*caminos).tope_camino_2].fil, &(*caminos).camino_2[(*caminos).tope_camino_2].col);
		while(leidos == 2) { 
			((*caminos).tope_camino_2)++;
			leidos = fscanf(archivo_de_caminos, "%i;%i\n",  &(*caminos).camino_2[(*caminos).tope_camino_2].fil, &(*caminos).camino_2[(*caminos).tope_camino_2].col);
			}
		}
	fclose(archivo_de_caminos);
}

/*
Pre: -
Post: Leera la configuracion creada por el usuario de un archivo determinado. 
*/

int leer_configuracion(configuracion_t* configuracion, char archivo_config[MAX_RUTA]) {

	FILE* configuraciones = fopen(archivo_config, "r");

	if(!configuraciones){
		printf("No se pudo leer el archivo!\n");
		return ERROR;
	}
	
	char info_juego[MAX_NOMBRE];

	int leidos = fscanf(configuraciones, "%[^=]", info_juego);

	while(leidos != EOF) {

		if(strcmp(info_juego, "RESISTENCIA_TORRES") == 0) {
			leidos=fscanf(configuraciones,"=%i,%i\n", &(*configuracion).resistencia_torre_1, &(*configuracion).resistencia_torre_2);
		}
		else if(strcmp(info_juego, "ENANOS_INICIO") == 0) {
			leidos=fscanf(configuraciones,"=%i,%i,%i,%i\n",&(*configuracion).cant_enanos_inicial.nivel_1,&(*configuracion).cant_enanos_inicial.nivel_2,&(*configuracion).cant_enanos_inicial.nivel_3,&(*configuracion).cant_enanos_inicial.nivel_4);
		}
		else if(strcmp(info_juego, "ELFOS_INICIO") == 0) {
			leidos=fscanf(configuraciones,"=%i,%i,%i,%i\n",&(*configuracion).cant_elfos_inicial.nivel_1,&(*configuracion).cant_elfos_inicial.nivel_2,&(*configuracion).cant_elfos_inicial.nivel_3,&(*configuracion).cant_elfos_inicial.nivel_4);	
		}
		else if(strcmp(info_juego, "ENANOS_EXTRA") == 0) {
			leidos=fscanf(configuraciones,"=%i,%i\n",&(*configuracion).enanos_extra,&(*configuracion).costo_torre_1);
		}
		else if(strcmp(info_juego, "ELFOS_EXTRA") == 0) {
			leidos=fscanf(configuraciones,"=%i,%i\n",&(*configuracion).elfos_extra,&(*configuracion).costo_torre_2);
		}
		else if(strcmp(info_juego, "ANIMO_ENANOS") == 0) {
			leidos=fscanf(configuraciones,"=%i,%i\n",&(*configuracion).fallo_enanos,&(*configuracion).critico_enanos);
		}
		else if(strcmp(info_juego, "ANIMO_ELFOS") == 0) {
			leidos=fscanf(configuraciones,"=%i,%i\n",&(*configuracion).fallo_elfos,&(*configuracion).critico_elfos);
		}
		else if(strcmp(info_juego, "VELOCIDAD") == 0) {
			leidos=fscanf(configuraciones,"=%f\n", &(*configuracion).velocidad);
		}
		else if((strcmp(info_juego, "CAMINOS")) == 0) {
			leidos=fscanf(configuraciones, "=%[^\n]\n", (*configuracion).caminos);
		}

		leidos=fscanf(configuraciones, "%[^=]", info_juego);
	}

	return 0;
}