#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "animos.h"
#include "defendiendo_torres.h"
#include "utiles.h"
#include "extras.h"
#include <stdlib.h>
#include <string.h>


#define MAX_NOMBRE 30
#define ENANOS 'G'
#define ELFOS 'L'
#define TERRENO_CHICO 15
#define TERRENO_GRANDE 20
#define MAX_DEFENSORES 50
#define NO_POSIBLE -1 
#define PERDIDO -1
#define GANADO 1
#define JUGANDO 0
#define MAX_CANTIDAD_ENANOS 5 
#define MAX_CANTIDAD_ELFOS 5
#define MAX_CANTIDAD_ENEMIGOS_NIVEL_1 100
#define MAX_CANTIDAD_ENEMIGOS_NIVEL_2 200
#define MAX_CANTIDAD_ENEMIGOS_NIVEL_3 300 
#define MAX_CANTIDAD_ENEMIGOS_NIVEL_4 500 
#define MAX_CANTIDAD_DEFENSORES_NIVEL_3 6
#define MAX_CANTIDAD_DEFENSORES_NIVEL_4 8
#define NUMERO_RANDOM 100
#define AFIRMATIVO 'S'
#define MAX_DEFENSORES_EXTRAS 10
#define PRIMER_NIVEL 1
#define SEGUNDO_NIVEL 2
#define TERCER_NIVEL 3
#define CUARTO_NIVEL 4
#define VACIO 0
#define ERROR -1
#define VIDA_PERDIDA 50
#define FIL_TORRE_NIVEL_1 3
#define COL_TORRE_NIVEL_1 0
#define FIL_ENTRADA_NIVEL_1 12
#define COL_ENTRADA_NIVEL_1 14
#define FIL_TORRE_NIVEL_2 9
#define COL_TORRE_NIVEL_2 14
#define FIL_ENTRADA_NIVEL_2 13
#define COL_ENTRADA_NIVEL_2 0
#define FIL_TORRE_NIVEL_3 19
#define COL_TORRE_NIVEL_3 8
#define FIL_ENTRADA_NIVEL_3 0
#define COL_ENTRADA_NIVEL_3 3
#define FIL_TORRE_2_NIVEL_3 19
#define COL_TORRE_2_NIVEL_3 11
#define FIL_ENTRADA_2_NIVEL_3 0
#define COL_ENTRADA_2_NIVEL_3 16
#define FIL_TORRE_NIVEL_4 0
#define COL_TORRE_NIVEL_4 5
#define FIL_ENTRADA_NIVEL_4 19
#define COL_ENTRADA_NIVEL_4 2
#define FIL_TORRE_2_NIVEL_4 0
#define COL_TORRE_2_NIVEL_4 11
#define FIL_ENTRADA_2_NIVEL_4 19
#define COL_ENTRADA_2_NIVEL_4 14
#define ENANOS_INICIO 12
#define ELFOS_INICIO 12
#define VIDA_INICIAL_TORRE 600
#define MAX_JUGADORES 100
#define ENANOS_EXTRA 10
#define ELFOS_EXTRA 10
#define RANKING_AUX "ranking__archivo_aux.csv"
#define DEFAULT -1
#define MAX_RUTA 200
#define GRABACION_ACEPTADA 0
#define GRABACION_RECHAZADA -1
#define CONFIG_DEFAULT "config_default.txt"
#define LETRA_DEFAULT 'X'
#define MULTIPLO_1 25
#define MULTIPLO_2 50
#define RESULTADO_ESPERADO 0

/*
Pre: - 
Post: devuelve true si esta en rango valido de coordenadas o false si no lo esta
*/

bool rango_invalido(juego_t* juego , coordenada_t posicion) {
	bool es_invalido=false;
		if(((*juego).nivel_actual == PRIMER_NIVEL) || ((*juego).nivel_actual == SEGUNDO_NIVEL)) { 
			if(((posicion.fil >= TERRENO_CHICO)) || ((posicion.col >= TERRENO_CHICO))) {
				es_invalido=true;
	}
		else {
			if((posicion.fil >= TERRENO_GRANDE) || (posicion.col >= TERRENO_GRANDE)) {
				es_invalido=true;
			}
		}
	}
	return es_invalido; 
}

/*
Pre: - 
Post: Las variables pedidas deben tener un valor valido.
*/

void preguntar_enanos(juego_t *juego, coordenada_t posicion_aux) {
	
	printf("Ingrese una fila: ");
	scanf("%i", &(posicion_aux.fil));
	printf("Ingrese una columna: ");
	scanf("%i", &(posicion_aux.col));

	while ((rango_invalido(&(*juego),posicion_aux) == true)  || agregar_defensor(&(juego->nivel),posicion_aux, ENANOS) == NO_POSIBLE) {
		printf ("El valor ingresado no esta dentro del rango. Volve a ingresar fila y columna porfi:\n");
		printf("Ingrese una fila: ");
		scanf("%i", &(posicion_aux.fil));
		printf("Ingrese una columna: ");
		scanf("%i", &(posicion_aux.col));
	}
}

/*
Pre: - 
Post: Las variables pedidas deben tener un valor valido.
*/

void preguntar_elfos(juego_t *juego, coordenada_t posicion_aux) {

	printf("Ingrese una fila: ");
	scanf("%i", &(posicion_aux.fil));
	printf("Ingrese una columna: ");
	scanf("%i", &(posicion_aux.col));

	while ((rango_invalido(&(*juego),posicion_aux) == true)  || agregar_defensor(&(juego->nivel),posicion_aux, ELFOS) == NO_POSIBLE) {
		printf ("El valor ingresado no esta dentro del rango. Volve a ingresar fila y columna porfi:\n");
		printf("Ingrese una fila: ");
		scanf("%i", &(posicion_aux.fil));
		printf("Ingrese una columna: ");
		scanf("%i", &(posicion_aux.col));
	}
}

/*
Pre: - 
Post: La cantidad de enanos y elfos a pedir debe respetarse segun cada nivel.
*/

void inicializar_defensores(juego_t* juego,configuracion_t* configuracion) {

	coordenada_t posicion_aux;

	printf("POSICION DE LOS DEFENSORES A ELECCION DEL JUGADOR: \n");

	if((*juego).nivel_actual == PRIMER_NIVEL) { 
		while (((*juego).nivel.tope_defensores) < (*configuracion).cant_enanos_inicial.nivel_1){
			preguntar_enanos(&(*juego), posicion_aux);
		}
		while (((*juego).nivel.tope_defensores) < (((*configuracion).cant_elfos_inicial.nivel_1)+(*configuracion).cant_enanos_inicial.nivel_1)) {
			preguntar_elfos(&(*juego), posicion_aux);
		}
	}
	else if((*juego).nivel_actual == SEGUNDO_NIVEL) { 
		while (((*juego).nivel.tope_defensores) < (*configuracion).cant_elfos_inicial.nivel_2) {
			preguntar_elfos(&(*juego), posicion_aux);
		}
		while (((*juego).nivel.tope_defensores) < (((*configuracion).cant_enanos_inicial.nivel_2)+(*configuracion).cant_elfos_inicial.nivel_2)) {
			preguntar_enanos(&(*juego), posicion_aux);
		}
	}
	else if((*juego).nivel_actual == TERCER_NIVEL) { 
		while (((*juego).nivel.tope_defensores) < (*configuracion).cant_enanos_inicial.nivel_3) {
			preguntar_enanos(&(*juego), posicion_aux);
		}
		while (((*juego).nivel.tope_defensores) < (((*configuracion).cant_elfos_inicial.nivel_3)+(*configuracion).cant_enanos_inicial.nivel_3)) {
			preguntar_elfos(&(*juego), posicion_aux);
		}
	}
	else if((*juego).nivel_actual == CUARTO_NIVEL) { 
		while (((*juego).nivel.tope_defensores) < (*configuracion).cant_enanos_inicial.nivel_4) {
			preguntar_enanos(&(*juego), posicion_aux);
		}
		while (((*juego).nivel.tope_defensores) < (((*configuracion).cant_elfos_inicial.nivel_4)+(*configuracion).cant_enanos_inicial.nivel_4)) {
			preguntar_elfos(&(*juego), posicion_aux);
		}
	}
    printf("Ingreso finalizado\n");
	
} 

/*
Pre: la cantidad de defensores utilizados deben ser menor al tope de defensores extras.
Post: disminuye la cantidad de defensores extras y la resistencia de la respectiva torre, en caso de que el usuario halla elegido agregar un defensor extra.
*/

void realizar_cambios(int* resistencia_torre, int costo_torre, int* cant_def_extras) {
	(*resistencia_torre) = (*resistencia_torre) - (costo_torre);
	(*cant_def_extras)--;
}
/*
Pre: -
Post: imprime una pregunta por pantalla sobre que tipo de defensor quiere agregar el usuario.
*/

void imprimir_pregunta(int costo_torre_1, int costo_torre_2, int cant_enanos_extra, int cant_elfos_extra) {
	printf ("Parece que tiene a disposicion %i enanos y %i elfos mas para agregar! Desea agregar alguno disponible? le costara %i puntos de vida a su Torre 1 (caso enanos) y %i puntos de vida a su Torre 2 (caso elfos). Seleccione S (si) o cualquier otra letra (no).\n", cant_enanos_extra, cant_elfos_extra, costo_torre_1, costo_torre_2);
}

/*
Pre: - 
Post: Agrega defensores extras en un determinado momento de la partida, si el jugador lo desea.
*/

void ofrecer_extras(juego_t* juego, configuracion_t* configuracion, int turnos) { 

	char letra;
	coordenada_t posicion_aux;
	char tipo_defensor;
	int primer_resultado = (turnos%MULTIPLO_1);
	int segundo_resultado = (turnos%MULTIPLO_2);

	if(((*juego).nivel_actual == PRIMER_NIVEL) && ((*juego).torres.enanos_extra > VACIO) && ((*juego).torres.resistencia_torre_1 > VACIO) && (((*juego).nivel.tope_enemigos) < MAX_CANTIDAD_ENEMIGOS_NIVEL_1) && (primer_resultado == RESULTADO_ESPERADO)) {
		imprimir_pregunta((*configuracion).costo_torre_1, (*configuracion).costo_torre_2, (*juego).torres.enanos_extra, (*juego).torres.elfos_extra);
		scanf(" %c", &letra);
		if(letra == AFIRMATIVO) {
			preguntar_enanos(&(*juego), posicion_aux);
			realizar_cambios(&(*juego).torres.resistencia_torre_1,(*configuracion).costo_torre_1,&(*juego).torres.enanos_extra);
		}
	}
	else if(((*juego).nivel_actual == SEGUNDO_NIVEL) && ((*juego).torres.elfos_extra > VACIO) && ((*juego).torres.resistencia_torre_2 > VACIO) && (segundo_resultado == RESULTADO_ESPERADO) && (((*juego).nivel.tope_enemigos) < MAX_CANTIDAD_ENEMIGOS_NIVEL_2)) {
		imprimir_pregunta((*configuracion).costo_torre_1, (*configuracion).costo_torre_2, (*juego).torres.enanos_extra, (*juego).torres.elfos_extra);
		scanf(" %c", &letra);
		if(letra == AFIRMATIVO ) {
			preguntar_elfos(&(*juego), posicion_aux);
			realizar_cambios(&(*juego).torres.resistencia_torre_2,(*configuracion).costo_torre_2,&(*juego).torres.elfos_extra);
		}
	}
	else if(((*juego).nivel_actual == TERCER_NIVEL) && (segundo_resultado == RESULTADO_ESPERADO) && ((*juego).torres.resistencia_torre_2 > VACIO) && ((*juego).torres.resistencia_torre_1 > VACIO) && (((*juego).nivel.tope_enemigos) < MAX_CANTIDAD_ENEMIGOS_NIVEL_3)) {
		imprimir_pregunta((*configuracion).costo_torre_1, (*configuracion).costo_torre_2, (*juego).torres.enanos_extra, (*juego).torres.elfos_extra);
		scanf(" %c", &letra);
		if(letra == AFIRMATIVO) {
			printf("Ingrese que tipo de defensor quiere agregar. L (ELFO) G (ENANO): \n");
			scanf(" %c", &tipo_defensor);
			if((tipo_defensor == ELFOS) && ((*juego).torres.elfos_extra > VACIO)) { 
				preguntar_elfos(&(*juego), posicion_aux);
				realizar_cambios(&(*juego).torres.resistencia_torre_2,(*configuracion).costo_torre_2,&(*juego).torres.elfos_extra);
			}
			else if((tipo_defensor == ENANOS) && ((*juego).torres.enanos_extra > VACIO)) { 
				preguntar_enanos(&(*juego), posicion_aux);
				realizar_cambios(&(*juego).torres.resistencia_torre_1,(*configuracion).costo_torre_1,&(*juego).torres.enanos_extra);
			}
			else {	
				return;
			}
		}	
	}
	else if(((*juego).nivel_actual == CUARTO_NIVEL) && (segundo_resultado == RESULTADO_ESPERADO) && ((*juego).torres.resistencia_torre_2 > VACIO) && ((*juego).torres.resistencia_torre_1 > VACIO) && (((*juego).nivel.tope_enemigos) < MAX_CANTIDAD_ENEMIGOS_NIVEL_4)) {
		imprimir_pregunta((*configuracion).costo_torre_1, (*configuracion).costo_torre_2, (*juego).torres.enanos_extra, (*juego).torres.elfos_extra);
		scanf(" %c", &letra);
		if(letra == AFIRMATIVO) {
			printf("Ingrese que tipo de defensor quiere agregar. L (ELFO) G (ENANO): \n");
			scanf(" %c", &tipo_defensor);
			if((tipo_defensor == ELFOS) && ((*juego).torres.elfos_extra > VACIO)) { 
				preguntar_elfos(&(*juego), posicion_aux);
				realizar_cambios(&(*juego).torres.resistencia_torre_2,(*configuracion).costo_torre_2,&(*juego).torres.elfos_extra);
			}
			else if((tipo_defensor == ENANOS) && ((*juego).torres.enanos_extra > VACIO)) { 
				preguntar_enanos(&(*juego), posicion_aux);
				realizar_cambios(&(*juego).torres.resistencia_torre_1,(*configuracion).costo_torre_1,&(*juego).torres.enanos_extra);
			}
			else {	
				return;
			}
		}	
	}
}

/*
Pre: - 
Post: Inicializa la configuracion personalizada.
*/

void inicializar_config_personalizada(juego_t* juego, configuracion_t* configuracion, caminos_t* caminos) {
	
	if((*juego).nivel_actual == PRIMER_NIVEL) {
	
		leer_caminos(&(*configuracion), &(*caminos), PRIMER_NIVEL);

		((*juego).nivel.max_enemigos_nivel) = MAX_CANTIDAD_ENEMIGOS_NIVEL_1; 
		(*juego).nivel.tope_camino_1 = (*caminos).tope_camino_1;

		for(int j=0 ; j < (*caminos).tope_camino_1 ; j++) {
			(*juego).nivel.camino_1[j].fil = (*caminos).camino_1[j].fil;
			(*juego).nivel.camino_1[j].col = (*caminos).camino_1[j].col;
		} 
		mostrar_juego(*juego);
	}

	else if((*juego).nivel_actual == SEGUNDO_NIVEL) {

		leer_caminos(&(*configuracion), &(*caminos), SEGUNDO_NIVEL); 

		((*juego).nivel.max_enemigos_nivel) = MAX_CANTIDAD_ENEMIGOS_NIVEL_2; 

		(*juego).nivel.tope_camino_1 = (*caminos).tope_camino_1;

		for(int j=0 ; j < (*caminos).tope_camino_1 ; j++) {
			(*juego).nivel.camino_1[j].fil = (*caminos).camino_1[j].fil;
			(*juego).nivel.camino_1[j].col = (*caminos).camino_1[j].col;
		} 
		mostrar_juego(*juego);
	}

	else if((*juego).nivel_actual == TERCER_NIVEL) {

		leer_caminos(&(*configuracion), &(*caminos), TERCER_NIVEL); 

		((*juego).nivel.max_enemigos_nivel) = MAX_CANTIDAD_ENEMIGOS_NIVEL_3; 

		(*juego).nivel.tope_camino_1 = (*caminos).tope_camino_1;
		(*juego).nivel.tope_camino_2 = (*caminos).tope_camino_2;

		for(int j=0 ; j < (*caminos).tope_camino_1 ; j++) {
			(*juego).nivel.camino_1[j].fil = (*caminos).camino_1[j].fil;
			(*juego).nivel.camino_1[j].col = (*caminos).camino_1[j].col;
		} 
		for(int i=0 ; i < (*caminos).tope_camino_2 ; i++) {
			(*juego).nivel.camino_2[i].fil = (*caminos).camino_2[i].fil;
			(*juego).nivel.camino_2[i].col = (*caminos).camino_2[i].col;
		} 
		mostrar_juego(*juego);
	}

	else if((*juego).nivel_actual == CUARTO_NIVEL) {

		leer_caminos(&(*configuracion), &(*caminos), CUARTO_NIVEL); 

		((*juego).nivel.max_enemigos_nivel) = MAX_CANTIDAD_ENEMIGOS_NIVEL_4; 

		(*juego).nivel.tope_camino_1 = (*caminos).tope_camino_1;
		(*juego).nivel.tope_camino_2 = (*caminos).tope_camino_2;

		for(int j=0 ; j < (*caminos).tope_camino_1 ; j++) {
			(*juego).nivel.camino_1[j].fil = (*caminos).camino_1[j].fil;
			(*juego).nivel.camino_1[j].col = (*caminos).camino_1[j].col;
		} 
		for(int i=0 ; i < (*caminos).tope_camino_2 ; i++) {
			(*juego).nivel.camino_2[i].fil = (*caminos).camino_2[i].fil;
			(*juego).nivel.camino_2[i].col = (*caminos).camino_2[i].col;
		} 
		mostrar_juego(*juego);
	}
}

/*
Pre: - 
Post: Inicializa la configuracion default.
*/

void inicializar_config_default(juego_t* juego, configuracion_t* configuracion, caminos_t* caminos) {

	coordenada_t entrada;
	coordenada_t torre;
	coordenada_t torre_2;
	coordenada_t entrada_2;
	
	if((*juego).nivel_actual == PRIMER_NIVEL) {

		((*juego).nivel.max_enemigos_nivel) = MAX_CANTIDAD_ENEMIGOS_NIVEL_1; 

		entrada.fil = FIL_ENTRADA_NIVEL_1;
		entrada.col = COL_ENTRADA_NIVEL_1;

		torre.fil = FIL_TORRE_NIVEL_1;
		torre.col = COL_TORRE_NIVEL_1;

		obtener_camino((*juego).nivel.camino_1, &((*juego).nivel.tope_camino_1) ,entrada, torre);
		mostrar_juego(*juego);
	}

	else if((*juego).nivel_actual == SEGUNDO_NIVEL) {

		((*juego).nivel.max_enemigos_nivel) = MAX_CANTIDAD_ENEMIGOS_NIVEL_2; 

		torre.fil = FIL_TORRE_NIVEL_2;
		torre.col = COL_TORRE_NIVEL_2;

		entrada.fil = FIL_ENTRADA_NIVEL_2;
		entrada.col = COL_ENTRADA_NIVEL_2;

		obtener_camino((*juego).nivel.camino_1, &((*juego).nivel.tope_camino_1) , entrada , torre);
		mostrar_juego(*juego);
	}

	else if((*juego).nivel_actual == TERCER_NIVEL) {

		((*juego).nivel.max_enemigos_nivel) = MAX_CANTIDAD_ENEMIGOS_NIVEL_3; 

		entrada.fil = FIL_ENTRADA_NIVEL_3; 
		entrada.col = COL_ENTRADA_NIVEL_3;

		torre.fil = FIL_TORRE_NIVEL_3;
		torre.col = COL_TORRE_NIVEL_3; 

		obtener_camino((*juego).nivel.camino_1, &((*juego).nivel.tope_camino_1) , entrada, torre);

		torre_2.fil = FIL_TORRE_2_NIVEL_3;
		torre_2.col = COL_TORRE_2_NIVEL_3;

		entrada_2.fil = FIL_ENTRADA_2_NIVEL_3;
		entrada_2.col = COL_ENTRADA_2_NIVEL_3;

		obtener_camino((*juego).nivel.camino_2, &((*juego).nivel.tope_camino_2) , entrada_2 , torre_2);

		mostrar_juego(*juego);
	}

	else if((*juego).nivel_actual == CUARTO_NIVEL) {

		((*juego).nivel.max_enemigos_nivel) = MAX_CANTIDAD_ENEMIGOS_NIVEL_4; 

		entrada.fil = FIL_ENTRADA_NIVEL_4; 
		entrada.col = COL_ENTRADA_NIVEL_4;

		torre.fil = FIL_TORRE_NIVEL_4; 
		torre.col = COL_TORRE_NIVEL_4; 

		obtener_camino((*juego).nivel.camino_1, &((*juego).nivel.tope_camino_1) , entrada , torre);

		torre_2.fil = FIL_TORRE_2_NIVEL_4;
		torre_2.col = COL_TORRE_2_NIVEL_4;

		entrada_2.fil = FIL_ENTRADA_2_NIVEL_4; 
		entrada_2.col = COL_ENTRADA_2_NIVEL_4; 

		obtener_camino((*juego).nivel.camino_2, &((*juego).nivel.tope_camino_2) , entrada_2 , torre_2);

		mostrar_juego(*juego);
	}
}


/*
Pre: - 
Post: Inicializa todos los niveles en su turno correspondiente y con la configuracion determinada por el usuario.
*/

void inicializar_nivel(juego_t* juego,configuracion_t* configuracion,char configuraciones[MAX_RUTA], caminos_t* caminos) {

	(*juego).nivel.tope_camino_1 = VACIO;
	(*juego).nivel.tope_camino_2 = VACIO;
	((*juego).nivel.tope_defensores) = VACIO;
	((*juego).nivel.tope_enemigos) = VACIO;

	if((strcmp(configuraciones, CONFIG_DEFAULT) != 0) && (strcmp(((*configuracion).caminos),CONFIG_DEFAULT) != 0)) {
		inicializar_config_personalizada(&(*juego), &(*configuracion), &(*caminos));
	}
	if((strcmp(configuraciones, CONFIG_DEFAULT) != 0) && (strcmp(((*configuracion).caminos),CONFIG_DEFAULT) == 0)) {
		inicializar_config_default(&(*juego), &(*configuracion), &(*caminos));
	}
	if(strcmp(configuraciones, CONFIG_DEFAULT) == 0) {
		inicializar_config_default(&(*juego), &(*configuracion), &(*caminos));
	}
	inicializar_defensores(&(*juego), &(*configuracion));
	mostrar_juego(*juego);
}

/*
Pre: - 
Post: Muestra mensaje por pantalla luego de finalizado el juego.
*/

void mostrar_resultados(juego_t juego) {

	if((estado_juego(juego)) == PERDIDO) {
		printf("Perdiste la batalla!! La proxima tendras mas suerte.\n");
	}
	else {
		printf("Ganaste la batalla!! Felicitaciones!\n");
	}
}

/*
Pre: -
Post: devuelve los enemigos muertos segun el nivel perdido. 
*/

int orcos_muertos_por_nivel_incompleto(juego_t* juego) {
	int enemigos_muertos = VACIO;
	if((estado_juego(*juego)) == PERDIDO) {
		for(int i=0 ; i < (*juego).nivel.tope_enemigos ; i++) {
			if((*juego).nivel.enemigos[i].vida <= VACIO) {
				enemigos_muertos++;
				}	
			}
		}
	return enemigos_muertos;
}

/*
Pre: -
Post: devuelve los enemigos muertos segun el nivel ganado. 
*/

int orcos_muertos_por_nivel_completo(juego_t* juego) {
	int enemigos_muertos = VACIO;
	if(((*juego).nivel_actual) == SEGUNDO_NIVEL) {
		enemigos_muertos = MAX_CANTIDAD_ENEMIGOS_NIVEL_1;
	}
	else if(((*juego).nivel_actual) == TERCER_NIVEL) {
		enemigos_muertos = MAX_CANTIDAD_ENEMIGOS_NIVEL_1 + MAX_CANTIDAD_ENEMIGOS_NIVEL_2;
	}
	else if(((*juego).nivel_actual) == CUARTO_NIVEL)  {
		enemigos_muertos = MAX_CANTIDAD_ENEMIGOS_NIVEL_1 + MAX_CANTIDAD_ENEMIGOS_NIVEL_2 + MAX_CANTIDAD_ENEMIGOS_NIVEL_3;
	}
	return enemigos_muertos;
}

/*
Pre: -
Post: actualiza o crea un ranking segun el archivo de configuracion recibido. 
*/

void escribir_ranking(int puntaje,char archivo_ranking[MAX_RUTA]) {

	char participante[MAX_NOMBRE];

	printf("Por favor, escriba su nombre para que pueda ser cargado al ranking:\n");
	scanf("%s", participante);

	char extension[MAX_RUTA] = "ranking__";
	char letra = LETRA_DEFAULT;

	size_t i = strlen(extension);
	int j=0;

	while(letra != '.') {
		letra=archivo_ranking[j];
		extension[i]=letra;
		i++;
		j++;
	}

	strcat(extension, "csv\0"); 

	FILE* archivo_de_ranking = fopen(extension, "r");

	if(!archivo_de_ranking){
		archivo_de_ranking = fopen(extension, "w");
		fprintf(archivo_de_ranking, "%s;%i\n",participante,puntaje);
	}

	else {

		FILE* archivo_ranking_aux = fopen(RANKING_AUX, "w");

		if(!archivo_ranking_aux) {
			fclose(archivo_de_ranking);
			printf("El archivo no pudo crearse!\n");
			return;
		}

		char participante_aux[MAX_NOMBRE];
		int puntaje_aux;
		int leidos = fscanf(archivo_de_ranking, "%[^;];%i\n", participante_aux, &puntaje_aux);
		if(leidos < 2) {
			fprintf(archivo_ranking_aux, "%s;%i\n", participante, puntaje );
		}
		else {
			while(leidos == 2) {
				if((puntaje > puntaje_aux)||((puntaje == puntaje_aux) && (strcmp(participante, participante_aux) < 0))) {
					fprintf(archivo_ranking_aux, "%s;%i\n", participante, puntaje);
					puntaje = DEFAULT;
				}
				fprintf(archivo_ranking_aux, "%s;%i\n", participante_aux, puntaje_aux );
				leidos = fscanf(archivo_de_ranking, "%[^;];%i\n", participante_aux, &puntaje_aux);
			}
			if(puntaje != DEFAULT) {
				fprintf(archivo_ranking_aux,"%s;%i\n", participante , puntaje);
			}
		}
		fclose(archivo_ranking_aux);
		rename(RANKING_AUX,extension);
	}
	fclose(archivo_de_ranking);
}

/*
Pre: -
Post: devuelve el puntaje que obtuvo el usuario para ser sumado al ranking. 
*/

int puntacion(juego_t juego, configuracion_t configuracion) {
	
	int puntaje_total = VACIO;
	int orcos_muertos = orcos_muertos_por_nivel_completo(&juego) + orcos_muertos_por_nivel_incompleto(&juego);
	int enanos_inicio = ((configuracion.cant_enanos_inicial.nivel_1) + (configuracion.cant_enanos_inicial.nivel_2) + (configuracion.cant_enanos_inicial.nivel_3) + (configuracion.cant_enanos_inicial.nivel_4));
	int elfos_inicio = ((configuracion.cant_elfos_inicial.nivel_1) + (configuracion.cant_elfos_inicial.nivel_2) + (configuracion.cant_elfos_inicial.nivel_3) + (configuracion.cant_elfos_inicial.nivel_4));
	int enanos_extra = (configuracion.enanos_extra);
	int elfos_extra = (configuracion.elfos_extra);
	int vida_torre_1 = (configuracion.resistencia_torre_1);
	int vida_torre_2 = (configuracion.resistencia_torre_2);
	
	puntaje_total=((orcos_muertos*1000)/((vida_torre_1)+(vida_torre_2)+(enanos_inicio)+(elfos_inicio)+(enanos_extra)+(elfos_extra)));
	return puntaje_total;
}

/*
Pre: -
Post: Jugara el juego completo con las consignas establecidas. 
*/

void jugar(char configuraciones[MAX_RUTA], char archivo_grabacion[MAX_RUTA], int quiere_grabar, configuracion_t configuracion) { 
	
	printf("BIENVENIDO A TOWER DEFENSE VOL.1. POR FAVOR,INGRESE LOS DATOS CORRESPONDIENTES:\n");

	int viento;
	int humedad;
	char animo_legolas;
	char animo_gimli;
	juego_t juego;
	juego.nivel_actual = PRIMER_NIVEL;
	caminos_t caminos;
	int contador_turnos = VACIO;

	animos(&viento , &humedad , &animo_legolas , &animo_gimli); 
	inicializar_juego(&juego, viento, humedad, animo_legolas, animo_gimli, &configuracion);
	inicializar_nivel(&juego,&configuracion,configuraciones, &caminos);

	FILE* partida_grabada;

	if (quiere_grabar == GRABACION_ACEPTADA) { 
		partida_grabada = fopen(archivo_grabacion, "w");
		if (!partida_grabada){
			printf("Imposible iniciar la grabacion!\n");
			return;
		}
	}
	
	while(estado_juego(juego) == JUGANDO) { 
		if((estado_nivel(juego.nivel) == GANADO) && (estado_juego(juego) == JUGANDO)) { 
			juego.nivel_actual++;
			contador_turnos = 0;
			inicializar_nivel(&juego, &configuracion,configuraciones, &caminos);
		} 
		mostrar_juego(juego);
		detener_el_tiempo(configuracion.velocidad);
		jugar_turno(&juego);
		contador_turnos++;
		ofrecer_extras(&juego,&configuracion, contador_turnos);
		if(partida_grabada) { 
			fwrite(&juego, sizeof(juego_t), 1, partida_grabada);
		}
	}

	if(partida_grabada) { 
		fclose(partida_grabada);
	}

	system("clear");

	mostrar_resultados(juego);

	int puntaje_total=puntacion(juego,configuracion);

	escribir_ranking(puntaje_total,configuraciones);

}