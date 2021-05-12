#include "animos.h"
#include "defendiendo_torres.h"
#include "utiles.h"
#include "extras.h"
#include "juego.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -1
#define MAX_JUGADORES 100
#define VACIO 0
#define MAX_NOMBRE 30
#define ARCHIVO_DEFAULT "ranking__config_default.csv"
#define MAX_VELOCIDAD 10
#define VELOCIDAD_DEFAULT 1
#define PRIMER_NIVEL 1
#define SEGUNDO_NIVEL 2
#define TERCER_NIVEL 3
#define CUARTO_NIVEL 4
#define GRABACION_ACEPTADA 0
#define GRABACION_RECHAZADA -1
#define CONFIG_DEFAULT "config_default.txt"
#define DEFAULT -1
#define MAX_COMANDO 20
#define PARAMETRO_DOS 2

/*
Pre: -
Post: Imprimira el aviso de los comandos que pueden ser ingresados. 
*/

void imprimir_aviso() {

	printf("================================================\n");
	printf("Debe ingresar alguno de los siguientes comandos:\n");
	printf("================================================\n");
	printf("--- ranking ---\n==>listar=cantidad a mostrar (opcional)\n==>config=archivo de configuracion (opcional)\n");
	printf("================================================\n");
	printf("--- crear_camino ---\n==>archivo de caminos \n");
	printf("================================================\n");
	printf("--- crear_configuracion ---\n==>archivo de configuracion\n");
	printf("================================================\n");
	printf("--- poneme_la_repe ---\n==>grabacion=archivo de grabacion\n==>velocidad=velocidad requerida (opcional)\n");
	printf("================================================\n");
	printf("--- jugar ---\n==>config=archivo de configuracion (opcional)\n==>grabacion=archivo de grabacion (opcional)\n");
	printf("================================================\n");

}

/*
Pre: -
Post: Creara una configuracion diferente a la default, con datos ingresados por el usuario. La misma sera cargada en un archivo de texto. 
*/

void comando_crear_configuracion(int argc , char *argv[]) {

	configuracion_t configuracion;

	if (argc == 3) { 

		size_t n = strlen(argv[2]);

		if(n >= 4) {

			char archivo_config[MAX_RUTA];
			strcpy(archivo_config, argv[2]);

			if(strcmp (&(archivo_config[n-4]), ".txt") == 0) {

				FILE* configuraciones = fopen(archivo_config, "w"); 

				if (configuraciones == NULL) {
					printf("El archivo no pudo crearse!\n");
					return;
				}
			
				crear_configuracion(&configuracion);
				escribir_configuracion(configuraciones,&configuracion);

				fclose(configuraciones);
			}
			else {
				printf("El archivo debe tener una extension .txt \n");
				return;
			}
		}
		else {
			printf("El archivo debe tener una extension .txt \n");
			return;
		}
	}
	else {
		imprimir_aviso();
		return;
	}
}

/*
Pre: -
Post: Creara los caminos de los diferentes niveles con las coordenadas ingresadas por el usuario. Las mismas seran cargadas en un archivo de texto. 
*/

void comando_crear_camino(int argc , char *argv[]) {

	caminos_t caminos;
	caminos.nivel_actual = PRIMER_NIVEL;
	char arch_caminos[MAX_RUTA];

	if(argc == 3) { 
		strcpy(arch_caminos, argv[2]);
		size_t n = strlen(arch_caminos);

		if(strcmp (&(arch_caminos[n-4]), ".txt") == 0) {

			FILE* archivo_de_caminos = fopen(arch_caminos, "w");

			if(!archivo_de_caminos){
				printf("No se pudo crear el archivo!\n");
				return;
			}
			while(caminos.nivel_actual <= CUARTO_NIVEL) {
				inicializar_caminos_en_niveles(&caminos,archivo_de_caminos);
				caminos.nivel_actual++;
			}
			fclose(archivo_de_caminos);
		}
		else {
			printf("El nombre del archivo caminos debe tener extension .txt\n");
		}
	}
	else {
		imprimir_aviso();
	}
}

/*
Pre: -
Post: crea una determinada cantidad de jugadores para mostrar segun la cantidad introducida por el usuario.
*/

void parametro_listar(char *argv[],int* cant_jugadores, int i) { 
	
	char param_listar[MAX_RUTA]="listar";
	char jugadores_a_mostrar[MAX_JUGADORES];
	strcpy(param_listar, argv[i]);
	strcpy(jugadores_a_mostrar,&(param_listar[7]));

	if(atoi(jugadores_a_mostrar) < VACIO) {
		printf("La cantidad de jugadores a mostrar no puede ser negativa :(\n");
		return;
	}
	*cant_jugadores = atoi(jugadores_a_mostrar);
}

/*
Pre: -
Post: crea un archivo de ranking segun una configuracion determinada. 
*/

void parametro_config(char *argv[], char archivo_ranking[MAX_RUTA], int i) {

	char param_config[MAX_RUTA]="config";
	char extension_texto[MAX_RUTA]="texto";
	char archivo_config[MAX_RUTA];

	strcpy(param_config, argv[i]);
	strcpy(archivo_config,&(param_config[7]));
	size_t n = strlen(archivo_config);

	if(n >= 4) {

		strcpy(extension_texto, &(archivo_config[n-4]));

		if(strcmp (extension_texto, ".txt") == 0) {

			strcpy(archivo_ranking, "ranking__");

			char letra;

			size_t i = strlen(archivo_ranking);

			int j=0;

			while(letra != '.') {
				letra=archivo_config[j];
				archivo_ranking[i]=letra;
				i++;
				j++;
			}
					
			strcat(archivo_ranking, "csv\0");

		}

		else {
			printf("El archivo debe tener una extension .txt\n"); 
			return;
		}
	}
			
	else {
		printf("El archivo debe tener, como minimo, la extension .txt\n"); 
		return;
	}
}

/*
Pre: -
Post: mostrara el ranking segun una configuracion determinada. En caso de ingresarse el nombre del programa y la palabra "ranking", se mostrara el ranking de la config default. Incluyendo el nombre del programa y ranking, se podra poner "listar=" seguido de la cantidad de jugadores que quieren ser mostrados del ranking. Tambien se podra poner "config=" seguido de una config deteminada para mostrar un ranking especifico. "listar=" y "config=" pueden ingresarse juntas en caso de que se desee (Si las mismas son ingresadas juntas, se debe respetar el orden escrito anteriormente) 
*/

void comando_ranking(int argc , char *argv[]) {

	char archivo_ranking[MAX_RUTA];
	int cant_jugadores = DEFAULT;
	int i = PARAMETRO_DOS;
	char participante[MAX_NOMBRE];
	int puntaje = VACIO;

	if((argc == 2) || ((argc == 3) && (strncmp("config=",argv[2],7) != 0))) {
		strcpy(archivo_ranking, ARCHIVO_DEFAULT); 
	} 

	while(i < argc){
	    if(strncmp("listar=", argv[i], 7) == 0){
	        parametro_listar(argv,&cant_jugadores, i);
	    }
	    if(strncmp("config=",argv[i],7) == 0){
	        parametro_config(argv,archivo_ranking, i);
	    }
	    i++;
	}

	FILE* ranking = fopen(archivo_ranking, "r");

	if(!ranking) {
		printf("El archivo no existe!\n");
		return;
	}

	int leidos = fscanf(ranking, "%[^;];%i\n",participante,&puntaje);
	int contador_jugadores=1;

	if(cant_jugadores != DEFAULT) { 
		while((leidos == 2) && (contador_jugadores <= cant_jugadores)) {
			printf("%s;%i\n", participante, puntaje);
			leidos=fscanf(ranking, "%[^;];%i\n",participante,&puntaje);
			contador_jugadores++;
		}
	}
	else {
		while(leidos == 2) {
			printf("%s;%i\n", participante, puntaje);
			leidos=fscanf(ranking, "%[^;];%i\n",participante,&puntaje);
		}
	}
	fclose(ranking);
}

/*
Pre: Para poder reproducirse una partida, la misma antes debe haber sido grabada.
Post: Reproducira la repeticion de una partida determinada. Se podra ingresar el comando "grabacion=" seguido del archivo de configuracion que se utilizo en la partida (grabada) que se quiere reproducir. Si se quiere reproducir la config default, se debera incluir unicamente "config=". Se podra tambien ingresar el comando "velocidad=" seguido de la velocidad con la que se quiere reproducir la partida, en caso de no ingresar ningun numero, se tendra en cuenta la velocidad default (1)
*/

void comando_poneme_la_repe(int argc , char *argv[]) {

	char comando_grabacion[MAX_RUTA];
	char archivo_grabacion[MAX_JUGADORES];
	char comando_velocidad[MAX_RUTA];
	juego_t juego;
	float velocidad_juego = VELOCIDAD_DEFAULT;
	char velocidad[MAX_VELOCIDAD];

	if((argc > 2) && (argc < 5)) { 

		if(strncmp("grabacion=",argv[2],10) == 0) {

			strcpy(comando_grabacion, argv[2]);

			strcpy(archivo_grabacion,&(comando_grabacion[10]));

			size_t n = strlen(archivo_grabacion);

			if(strcmp (&(archivo_grabacion[n-4]), ".dat") == 0) {

				FILE* partida_grabada = fopen(archivo_grabacion, "r");

				if (!partida_grabada){
					printf("El archivo no existe!\n");
					return;
				}

				if(argc > 3){
	  				if(strncmp("velocidad=",argv[3],10) == 0) {
	  					strcpy(comando_velocidad, argv[3]);
	       				strcpy(velocidad,&(comando_velocidad[10]));
	       				velocidad_juego = (float) atof(velocidad);
	   				}
	   				else {
	   					imprimir_aviso();
	   					return;
	   				}
				}

				fread(&juego, sizeof(juego_t), 1, partida_grabada);

				while(!feof(partida_grabada)){
	    			mostrar_juego(juego);
	    			detener_el_tiempo(velocidad_juego);
	    			fread(&juego, sizeof(juego_t), 1, partida_grabada);
				}
				fclose(partida_grabada);
			}
			else {
				printf("El nombre del archivo de grabacion debe ser .dat\n");
				return;
			}
		}
		else {
			imprimir_aviso();
			return;
		}
	}
	else {
		imprimir_aviso();
		return;		
	}
}

/*
Pre: -
Post: inicializa la configuracion con los valores default.
*/


void inicializar_configuracion(configuracion_t* configuracion) {

	(*configuracion).resistencia_torre_1=DEFAULT;
	(*configuracion).resistencia_torre_2=DEFAULT;
	(*configuracion).cant_enanos_inicial.nivel_1=DEFAULT;
	(*configuracion).cant_elfos_inicial.nivel_1=DEFAULT;
	(*configuracion).cant_enanos_inicial.nivel_2=DEFAULT;
	(*configuracion).cant_elfos_inicial.nivel_2=DEFAULT;
	(*configuracion).cant_enanos_inicial.nivel_3=DEFAULT;
	(*configuracion).cant_elfos_inicial.nivel_3=DEFAULT;
	(*configuracion).cant_enanos_inicial.nivel_4=DEFAULT;
	(*configuracion).cant_elfos_inicial.nivel_4=DEFAULT;
	(*configuracion).enanos_extra=DEFAULT;
	(*configuracion).elfos_extra=DEFAULT;
	(*configuracion).costo_torre_1=DEFAULT;
	(*configuracion).costo_torre_2=DEFAULT;
	(*configuracion).critico_elfos=DEFAULT;
	(*configuracion).critico_enanos=DEFAULT;
	(*configuracion).fallo_elfos=DEFAULT;
	(*configuracion).fallo_enanos=DEFAULT;
	(*configuracion).velocidad=DEFAULT;
	strcpy((*configuracion).caminos, CONFIG_DEFAULT);

}

/*
Pre: -
Post: reemplaza los valores default de la configuracion por valores personalizados.
*/

void parametro_config_juego(char *argv[], int i,char archivo_config[MAX_RUTA], configuracion_t* configuracion) { 
	
	char comando_config[MAX_RUTA]="config";

	strcpy(comando_config, argv[i]);

	strcpy(archivo_config,&(comando_config[7]));

	size_t n = strlen(archivo_config);

	if(strcmp (&(archivo_config[n-4]), ".txt") == 0) {
		leer_configuracion(&(*configuracion),archivo_config);
	}
	else {
		printf("El archivo de configuracion debe tener una extension .txt\n Se tomara la configuracion default\n");
		strcpy(archivo_config, CONFIG_DEFAULT);
		return;
	}
}

/*
Pre: -
Post: determina si se realizara una grabacion de la partida del juego o no.
*/

void parametro_grabacion(char *argv[], int* grabacion, int i, char archivo_grabacion[MAX_RUTA]) {

	char comando_grabacion[MAX_RUTA]="grabacion";

	strcpy(comando_grabacion, argv[i]);

	strcpy(archivo_grabacion,&(comando_grabacion[10]));

	size_t n = strlen(archivo_grabacion);

	if(strcmp (&(archivo_grabacion[n-4]), ".dat") == 0) {
		(*grabacion) = GRABACION_ACEPTADA;
	}
	else {
		(*grabacion) = GRABACION_RECHAZADA;
	}
}

/*
Pre: -
Post: Jugara la partida con una configuracion determinada o con la default. En caso de que el usuario ingrese el usuario "config=" se tomara la config default, en caso de que ingrese el mismo comando seguido del nombre de su config, se tomara la ingresada. Se podra tener un cuarto comando para poder grabar (o no) la partida. Si el usuario ingresa "grabacion=" la partida no se grabara, pero si ingresa "grabacion=" seguido de un archivo de extension .dat , la partida se grabara y se almacenara en ese archivo binario. 
*/


void comando_jugar(int argc , char *argv[]) {

	char archivo_config[MAX_RUTA];
	char archivo_grabacion[MAX_JUGADORES];
	configuracion_t configuracion;
	int i = PARAMETRO_DOS;
	int grabacion = VACIO;

	inicializar_configuracion(&configuracion);

	if((argc == 2) || ((argc == 3) && (strncmp("config=",argv[2],7) != 0))) {
		strcpy(archivo_config, CONFIG_DEFAULT);
	} 
	while(i < argc) {
	    if(strncmp("config=", argv[i], 7) == 0){
	        parametro_config_juego(argv, i, archivo_config, &configuracion);
	    }
	    if(strncmp("grabacion=",argv[i],10) == 0){
	        parametro_grabacion(argv, &grabacion, i, archivo_grabacion);
	    }
	    i++;
	}
	jugar(archivo_config, archivo_grabacion, grabacion, configuracion);
}

/*
Pre: -
Post: Llama a los comandos segun el que introduzca el usuario. 
*/

void llamar_comando(int argc , char *argv[]) {
	
	if(argc > 1) {

		char comando[MAX_COMANDO];
		strcpy(comando, argv[1]);

		if(strcmp(comando, "crear_configuracion") == 0) {
			comando_crear_configuracion(argc,argv);
		}
		if(strcmp(comando, "crear_camino") == 0) {
			comando_crear_camino(argc,argv);
		}
		if(strcmp(comando, "ranking") == 0) {
			comando_ranking(argc,argv);
		}		
		if(strcmp(comando, "poneme_la_repe") == 0) {
			comando_poneme_la_repe(argc,argv);
		}
		if(strcmp(comando, "jugar") == 0) {
			comando_jugar(argc,argv);
		}
	}
	else {
		imprimir_aviso();
	}
}

int main(int argc, char *argv[]){

	srand((unsigned)time(NULL));

	llamar_comando(argc, argv);

	return 0;
}

