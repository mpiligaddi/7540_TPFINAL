#include "defendiendo_torres.h"
#include <stdbool.h>
#include <math.h>
#include <string.h>

 #define VACIO 0
 #define TORRE 'T'
 #define ELFOS 'L'
 #define ENANOS 'G'
 #define ORCOS 'O'
 #define ENTRADA 'E'
 #define VIDA_INICIAL_TORRE 600
 #define PUNTOS_CRITICO_GIMLI 100
 #define PUNTOS_CRITICO_LEGOLAS  70
 #define GANADO 1
 #define PERDIDO -1
 #define JUGANDO 0
 #define CANTIDAD_EXTRA 10
 #define MAX_CANTIDAD_ENANOS 5
 #define ANIMO_MALO 'M'
 #define ANIMO_REGULAR 'R'
 #define ANIMO_BUENO 'B'
 #define CAMINO ' '
 #define TERRENO_CHICO 15
 #define TERRENO_GRANDE 20
 #define TERRENO 'X'
 #define NO_POSIBLE -1
 #define POSIBLE 0
 #define VIDA_ORCO 200 
 #define NUMERO_RANDOM 100
 #define MAX_DEFENSORES_EXTRAS 10
 #define GOLPE_CRITICO_ENANOS 100
 #define GOLPE_FALLIDO 0 
 #define FUERZA_ATAQUE_ENANOS 60
 #define FUERZA_ATAQUE_ELFOS 30
 #define GOLPE_CRITICO_ELFOS 70
 #define CRITICO_MALO 0
 #define CRITICO_BUENO 25
 #define CRITICO_REGULAR 10 
 #define PRIMER_NIVEL 1
 #define SEGUNDO_NIVEL 2
 #define TERCER_NIVEL 3
 #define CUARTO_NIVEL 4
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
 #define DEFAULT -1 
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
 #define CAMINO_DEFAULT "camino_default.txt"
 #define CONFIG_DEFAULT "config_default.txt"

/*
Pre: -
Post: devuelve el fallo de los enanos. 
*/

int fallo_elfos(configuracion_t* configuracion, int viento) {
	(*configuracion).fallo_elfos = (viento/2);
	return (*configuracion).fallo_elfos;
}

/*
Pre: -
Post: devuelve el fallo de los elfos. 
*/

int fallo_enanos(configuracion_t* configuracion, int humedad) {
	(*configuracion).fallo_enanos = (humedad/2);
	return (*configuracion).fallo_enanos;
}

/*
Pre: -
Post: devuelve el critico de los elfos. 
*/

int critico_elfos(configuracion_t* configuracion , char animo_legolas) {

		if(animo_legolas == ANIMO_MALO) {
			(*configuracion).critico_elfos = CRITICO_MALO;
		}
		else if (animo_legolas == ANIMO_BUENO) {
			(*configuracion).critico_elfos = CRITICO_BUENO;
		}
		else {
			(*configuracion).critico_elfos = CRITICO_REGULAR;
		}

		return (*configuracion).critico_elfos;
}

/*
Pre: -
Post: devuelve el critico de los enanos. 
*/

int critico_enanos(configuracion_t* configuracion , char animo_gimli) {

		if(animo_gimli == ANIMO_MALO) {
			(*configuracion).critico_enanos = CRITICO_MALO;
		}
		else if (animo_gimli == ANIMO_BUENO) {
			(*configuracion).critico_enanos = CRITICO_BUENO;
		}
		else {
			(*configuracion).critico_enanos = CRITICO_REGULAR;
		}

		return (*configuracion).critico_enanos;
} 

/*
 * Inicializará el juego, cargando la informacion de las torres y
 * los ataques críticos y fallo de Legolas y Gimli.
 * NO inicializará el primer nivel.
 */

void inicializar_juego(juego_t* juego, int viento, int humedad, char animo_legolas, char animo_gimli, configuracion_t* configuracion) {

	if((*configuracion).resistencia_torre_1 == DEFAULT) {
		(*configuracion).resistencia_torre_1 = VIDA_INICIAL_TORRE;
	}
	if(((*configuracion).resistencia_torre_2) == DEFAULT) {
		(*configuracion).resistencia_torre_2 = VIDA_INICIAL_TORRE;
	}
	if(((*configuracion).cant_enanos_inicial.nivel_1) == DEFAULT) {
		(*configuracion).cant_enanos_inicial.nivel_1 = ENANOS_NIVEL_1; 
	}
	if(((*configuracion).cant_enanos_inicial.nivel_2) == DEFAULT) {
		(*configuracion).cant_enanos_inicial.nivel_2 = ENANOS_NIVEL_2; 
	}
	if(((*configuracion).cant_enanos_inicial.nivel_3) == DEFAULT) {
		(*configuracion).cant_enanos_inicial.nivel_3 = ENANOS_NIVEL_3; 
	}
	if(((*configuracion).cant_enanos_inicial.nivel_4) == DEFAULT) {
		(*configuracion).cant_enanos_inicial.nivel_4 = ENANOS_NIVEL_4; 
	}
	if(((*configuracion).cant_elfos_inicial.nivel_1) == DEFAULT) {
		(*configuracion).cant_elfos_inicial.nivel_1 = ELFOS_NIVEL_1;
	}
	if(((*configuracion).cant_elfos_inicial.nivel_2) == DEFAULT) {
		(*configuracion).cant_elfos_inicial.nivel_2 = ELFOS_NIVEL_2;
	}
	if(((*configuracion).cant_elfos_inicial.nivel_3) == DEFAULT) {
		(*configuracion).cant_elfos_inicial.nivel_3 = ELFOS_NIVEL_3;
	}
	if(((*configuracion).cant_elfos_inicial.nivel_4) == DEFAULT) {
		(*configuracion).cant_elfos_inicial.nivel_4 = ELFOS_NIVEL_4;
	}
	if(((*configuracion).enanos_extra) == DEFAULT) {
		(*configuracion).enanos_extra = ENANOS_EXTRA;
	}
	if(((*configuracion).elfos_extra) == DEFAULT) {
		(*configuracion).elfos_extra = ELFOS_EXTRA;
	}
	if(((*configuracion).costo_torre_1) == DEFAULT) {
		(*configuracion).costo_torre_1 = COSTO_POR_ENANO_EXTRA;
	}
	if(((*configuracion).costo_torre_2) == DEFAULT) {
		(*configuracion).costo_torre_2 = COSTO_POR_ELFO_EXTRA;
	}
	if ((*configuracion).fallo_enanos == DEFAULT) {
		(*configuracion).fallo_enanos = fallo_enanos(&(*configuracion), humedad);
	}
	if (((*configuracion).critico_enanos == DEFAULT)) { 
		(*configuracion).critico_enanos = critico_enanos(&(*configuracion), animo_gimli);
	}
	if (((*configuracion).fallo_elfos == DEFAULT)) {
		(*configuracion).fallo_elfos = fallo_elfos(&(*configuracion), viento);
	}
	if (((*configuracion).critico_elfos == DEFAULT)) {
		(*configuracion).critico_elfos = critico_elfos(&(*configuracion), animo_legolas);
	}
	if(((*configuracion).velocidad) == DEFAULT) {
		(*configuracion).velocidad = VELOCIDAD_DEFAULT;
	}
	if (atoi((*configuracion).caminos) == DEFAULT){
		strcpy((*configuracion).caminos , CONFIG_DEFAULT);
	}

	(*juego).torres.resistencia_torre_1 = (*configuracion).resistencia_torre_1;

	(*juego).torres.resistencia_torre_2 = (*configuracion).resistencia_torre_2;

	(*juego).torres.enanos_extra = (*configuracion).enanos_extra;

	(*juego).torres.elfos_extra = (*configuracion).elfos_extra;

	(*juego).critico_legolas = (*configuracion).critico_elfos;

	(*juego).critico_gimli = (*configuracion).critico_enanos;

	(*juego).fallo_legolas = (*configuracion).fallo_elfos;

	(*juego).fallo_gimli = (*configuracion).fallo_enanos;

}

/*
 * Recibe un juego con todas sus estructuras válidas. 
 * El juego se dará por ganado si el juego está en el ultimo nivel y éste ha sido terminado.
 * El juego se dará por perdido, si alguna de las torres llega a 0 en su resistencia.
 * Devolverá:
 * >  0 si el estado es jugando.
 * > -1 si el estado es perdido.
 * >  1 si el estado es ganado.
 */

int estado_juego(juego_t juego) {

	if(((juego.torres.resistencia_torre_1) <= VACIO) || ((juego.torres.resistencia_torre_2) <= VACIO)) {
		return PERDIDO;
	}
	else if ((estado_nivel(juego.nivel) == GANADO) && (juego.nivel_actual == CUARTO_NIVEL)) {
		return GANADO;
	} 
	else {
		return JUGANDO;
	}
}


/*
 * Recibe un nivel con todas sus estructuras válidas. 
 * El nivel se dará por ganado cuando estén TODOS los orcos de ese 
 * nivel muertos (esto es, con vida menor o igual a 0).
 * Devolverá:
 * >  0 si el estado es jugando.
 * >  1 si el estado es ganado.
 */

int estado_nivel(nivel_t nivel) { 
	int enemigos_muertos=VACIO;
	for(int i=0 ; i < nivel.tope_enemigos ; i++) {
		if(nivel.enemigos[i].vida<=VACIO) {
			enemigos_muertos++;
		}
	}

	if(enemigos_muertos == nivel.max_enemigos_nivel) {
		return GANADO;
	}

	else {
		return JUGANDO;
	}	
}

/*
Pre: -
Post: devuelve true si el usuario eligio alguna coordenada dentro del rango  o false si no lo hizo. 
*/

bool coordenadas_invalidas(nivel_t* nivel , coordenada_t posicion) { 

	bool son_invalidas = false; 

	for(int i=(*nivel).tope_defensores ; i >= 0 ; i--) {
		if(((*nivel).defensores[i].posicion.fil == posicion.fil) && ((*nivel).defensores[i].posicion.col == posicion.col)) {
			son_invalidas = true; 
		}
	}
	for(int i=0 ; i < (*nivel).tope_camino_1 ; i++) {
		if(((*nivel).camino_1[i].fil == posicion.fil) && ((*nivel).camino_1[i].col == posicion.col)) {
			son_invalidas = true;
		}
	}
	for(int i=0 ; i < (*nivel).tope_camino_2 ; i++) {
		if(((*nivel).camino_2[i].fil == posicion.fil) && ((*nivel).camino_2[i].col == posicion.col)) {
			son_invalidas = true;
		}
	}
	return son_invalidas; 
} 

/* 
 * Agregará un defensor en el nivel recibido como parametro.
 * Devolverá:
 * >  0 si pudo agregar el defensor correctamente.
 * > -1 si no pudo (la coordenada es parte del camino de ese nivel, 
 * existe otro defensor, etc.)
 */

int agregar_defensor(nivel_t* nivel, coordenada_t posicion, char tipo){

	if(coordenadas_invalidas(&(*nivel), posicion) == true) {
		return NO_POSIBLE;
	}
	else {
		if(tipo == ENANOS) { 
			(*nivel).defensores[(*nivel).tope_defensores].posicion.fil = posicion.fil;
			(*nivel).defensores[(*nivel).tope_defensores].posicion.col = posicion.col;
			(*nivel).defensores[(*nivel).tope_defensores].tipo=tipo;
			(*nivel).defensores[(*nivel).tope_defensores].fuerza_ataque = FUERZA_ATAQUE_ENANOS;
			((*nivel).tope_defensores)++;
		return POSIBLE;
	}

		else if(tipo == ELFOS) {  
			(*nivel).defensores[(*nivel).tope_defensores].posicion.fil = posicion.fil;
			(*nivel).defensores[(*nivel).tope_defensores].posicion.col = posicion.col;
			(*nivel).defensores[(*nivel).tope_defensores].tipo=tipo;
			(*nivel).defensores[(*nivel).tope_defensores].fuerza_ataque = FUERZA_ATAQUE_ELFOS;
			((*nivel).tope_defensores)++;
		return POSIBLE;
		}
	}
	return NO_POSIBLE;
}

/*
Pre: -
Post: Inicializa el terreno que sera mostrado por pantalla. 
*/

void inicializar_terreno(juego_t juego, char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO]){
	if(juego.nivel_actual < TERCER_NIVEL) {
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
Post: Muestra el terreno por pantalla.
*/

void mostrar_terreno(juego_t juego, char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO]){

	if(juego.nivel_actual < TERCER_NIVEL) { 
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
}

/*
Pre: -
Post: Posiciona los caminos en el terreno.
*/

void poner_caminos(juego_t* juego, char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO]) {
		for(int i=0 ; i < (*juego).nivel.tope_camino_1; i++) {
			terreno[(*juego).nivel.camino_1[i].fil][(*juego).nivel.camino_1[i].col] = CAMINO;
	}
		for(int i=0 ; i < (*juego).nivel.tope_camino_2; i++) {
			terreno[(*juego).nivel.camino_2[i].fil][(*juego).nivel.camino_2[i].col] = CAMINO;
	}
} 

/*
Pre: -
Post: Determina la ubicacion de las entradas y de las torres, segun el nivel.
*/

void poner_entrada_y_torre(juego_t* juego, char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO]){

	if((*juego).nivel_actual == PRIMER_NIVEL) { 

		terreno[(*juego).nivel.camino_1[(*juego).nivel.tope_camino_1-1].fil][(*juego).nivel.camino_1[(*juego).nivel.tope_camino_1-1].col] = TORRE;
		terreno[(*juego).nivel.camino_1[0].fil][(*juego).nivel.camino_1[0].col] = ENTRADA;

	}

	else if((*juego).nivel_actual == SEGUNDO_NIVEL) {

		terreno[(*juego).nivel.camino_1[(*juego).nivel.tope_camino_1-1].fil][(*juego).nivel.camino_1[(*juego).nivel.tope_camino_1-1].col] = TORRE;
		terreno[(*juego).nivel.camino_1[0].fil][(*juego).nivel.camino_1[0].col] = ENTRADA;
	}

	else if((*juego).nivel_actual == TERCER_NIVEL) {

		terreno[(*juego).nivel.camino_1[(*juego).nivel.tope_camino_1-1].fil][(*juego).nivel.camino_1[(*juego).nivel.tope_camino_1-1].col] = TORRE;
		terreno[(*juego).nivel.camino_1[0].fil][(*juego).nivel.camino_1[0].col] = ENTRADA;

		terreno[(*juego).nivel.camino_2[(*juego).nivel.tope_camino_2-1].fil][(*juego).nivel.camino_2[(*juego).nivel.tope_camino_2-1].col] = TORRE;
		terreno[(*juego).nivel.camino_2[0].fil][(*juego).nivel.camino_2[0].col] = ENTRADA;
	}

	else if((*juego).nivel_actual == CUARTO_NIVEL) {

		terreno[(*juego).nivel.camino_1[(*juego).nivel.tope_camino_1-1].fil][(*juego).nivel.camino_1[(*juego).nivel.tope_camino_1-1].col] = TORRE;
		terreno[(*juego).nivel.camino_1[0].fil][(*juego).nivel.camino_1[0].col] = ENTRADA;

		terreno[(*juego).nivel.camino_2[(*juego).nivel.tope_camino_2-1].fil][(*juego).nivel.camino_2[(*juego).nivel.tope_camino_2-1].col] = TORRE;
		terreno[(*juego).nivel.camino_2[0].fil][(*juego).nivel.camino_2[0].col] = ENTRADA;
	}
}

/*
Pre: -
Post: Posiciona los defensores en el terreno.
*/

void poner_defensor(nivel_t* nivel , char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO]) { 

	for(int i=0 ; i < (*nivel).tope_defensores ; i++) {
		if((*nivel).defensores[i].tipo == ENANOS) {
			terreno[(*nivel).defensores[i].posicion.fil][(*nivel).defensores[i].posicion.col]=ENANOS; 
		}
		else {
			terreno[(*nivel).defensores[i].posicion.fil][(*nivel).defensores[i].posicion.col]=ELFOS;
		}
	}
}

/*
Pre: La cantidad de enemigos debe estar dentro de un rango determinado, segun el nivel.
Post: Inicializa los enemigos para cada nivel.
*/

void generar_enemigo(juego_t* juego) {

if((*juego).nivel.max_enemigos_nivel > (*juego).nivel.tope_enemigos) { 

	if(((*juego).nivel_actual == PRIMER_NIVEL) || ((*juego).nivel_actual == SEGUNDO_NIVEL)) { 

		(*juego).nivel.enemigos[(*juego).nivel.tope_enemigos].vida= VIDA_ORCO + rand() % NUMERO_RANDOM;
		(*juego).nivel.enemigos[(*juego).nivel.tope_enemigos].camino = 1;
		(*juego).nivel.enemigos[(*juego).nivel.tope_enemigos].pos_en_camino = 0;
		((*juego).nivel.tope_enemigos)++;
	}

	else if(((*juego).nivel_actual == TERCER_NIVEL) || ((*juego).nivel_actual == CUARTO_NIVEL)) { 

		(*juego).nivel.enemigos[(*juego).nivel.tope_enemigos].vida= VIDA_ORCO + rand() % NUMERO_RANDOM;
		(*juego).nivel.enemigos[(*juego).nivel.tope_enemigos].camino = 1;
		(*juego).nivel.enemigos[(*juego).nivel.tope_enemigos].pos_en_camino = 0;
		((*juego).nivel.tope_enemigos)++;

		(*juego).nivel.enemigos[(*juego).nivel.tope_enemigos].vida= VIDA_ORCO + rand() % NUMERO_RANDOM;
		(*juego).nivel.enemigos[(*juego).nivel.tope_enemigos].camino = 2;
		(*juego).nivel.enemigos[(*juego).nivel.tope_enemigos].pos_en_camino = 0;
		((*juego).nivel.tope_enemigos)++;
		}
	}
}

/*
Pre: - 
Post: devuelve true si esta en rango aceptado o false si no lo esta
*/

bool son_contiguas(coordenada_t pos_enano , coordenada_t pos_enemigo) {

	bool esta_en_rango=false;

	if((pos_enemigo.col == pos_enano.col-1) || (pos_enemigo.col == pos_enano.col) || (pos_enemigo.col == pos_enano.col+1)){
		if((pos_enemigo.fil == pos_enano.fil-1) || (pos_enemigo.fil == pos_enano.fil) || (pos_enemigo.fil == pos_enano.fil +1)) {
			esta_en_rango=true;
		}
	}
	return esta_en_rango;
}

/*
Pre: - 
Post: devuelve true si es un ataque fallido o false si no lo es.
*/

bool es_fallado(juego_t* juego, int num_def) {

	bool fallo=false;
	int numero_random=rand() % NUMERO_RANDOM;

	if((*juego).nivel.defensores[num_def].tipo == ENANOS) {
		if(numero_random < (*juego).fallo_gimli) {
			fallo=true;
			}
		}
		else {
			if(numero_random < (*juego).fallo_legolas) {
				fallo=true;
			}
		}
	return fallo;
}	

/*
Pre: - 
Post: determina, a traves de un numero random, que tipo de ataque tendra un tipo de defensor en un turno determinado. 
*/

void calcular_golpe_defensores(juego_t* juego, int num_def) { 

	if(es_fallado(&(*juego), num_def) == false) { 

		int numero_random=rand() % NUMERO_RANDOM;

		if((*juego).nivel.defensores[num_def].tipo == ENANOS) {
			if(numero_random < (*juego).critico_gimli) {
				(*juego).nivel.defensores[num_def].fuerza_ataque = GOLPE_CRITICO_ENANOS;
		}
			else {
				(*juego).nivel.defensores[num_def].fuerza_ataque = FUERZA_ATAQUE_ENANOS;
			}
		}
	else {
		if(numero_random < (*juego).critico_legolas) {
			(*juego).nivel.defensores[num_def].fuerza_ataque = GOLPE_CRITICO_ELFOS;
		}
		else {
			(*juego).nivel.defensores[num_def].fuerza_ataque = FUERZA_ATAQUE_ELFOS;
		}
	}
}
	else {
		(*juego).nivel.defensores[num_def].fuerza_ataque = GOLPE_FALLIDO;
	}
}

/*
Pre: Los defensores deben ser del tipo enanos, tener vida mayor a cero y estar en un rango determinado para que puedan atacar.
Post: Los enanos realizan su ataque.
*/

void ataque_enanos(juego_t* juego) {

	bool ya_ataco = false;

		for(int i=0 ; i < (*juego).nivel.tope_defensores ; i++)  {
			
			for(int j=0 ; j < (*juego).nivel.tope_enemigos ; j++ ) { 

				if((*juego).nivel.enemigos[j].camino == 1){ 

					if((ya_ataco==false) && ((*juego).nivel.defensores[i].tipo == ENANOS) && (son_contiguas((*juego).nivel.defensores[i].posicion , (*juego).nivel.camino_1[(*juego).nivel.enemigos[j].pos_en_camino]) == true) && ((*juego).nivel.enemigos[j].vida > VACIO)) {
						calcular_golpe_defensores(&(*juego), i);
						(*juego).nivel.enemigos[j].vida = (*juego).nivel.enemigos[j].vida-((*juego).nivel.defensores[i].fuerza_ataque);
						ya_ataco=true;		
				}
			}
				else if((*juego).nivel.enemigos[j].camino == 2){
					if((ya_ataco==false) && ((*juego).nivel.defensores[i].tipo == ENANOS) && (son_contiguas((*juego).nivel.defensores[i].posicion , (*juego).nivel.camino_2[(*juego).nivel.enemigos[j].pos_en_camino]) == true) && ((*juego).nivel.enemigos[j].vida > VACIO)) {
						calcular_golpe_defensores(&(*juego), i);
						(*juego).nivel.enemigos[j].vida = (*juego).nivel.enemigos[j].vida-((*juego).nivel.defensores[i].fuerza_ataque);
						ya_ataco=true;		
				}
			}
		}
		ya_ataco=false;
	}
} 

/*
Pre: - 
Post: devuelve true si esta en rango aceptado o false si no lo esta
*/

bool esta_en_rango_elfo(coordenada_t pos_elfos , coordenada_t pos_enemigo) {
	bool esta_en_rango = false; 
		if((abs(pos_elfos.fil-pos_enemigo.fil) + abs(pos_elfos.col-pos_enemigo.col)) <= 3 ) {
					esta_en_rango=true;
			}
	return esta_en_rango;
}

/*
Pre: Los defensores deben ser del tipo elfos, tener vida mayor a cero y estar en un rango determinado, para que puedan atacar.
Post: Los elfos realizan su ataque.
*/		

void ataque_elfos(juego_t* juego) {

		for(int i=0 ; i < (*juego).nivel.tope_defensores ; i++)  {

			for(int j=0 ; j < (*juego).nivel.tope_enemigos ; j++ ) { 
				
				if((*juego).nivel.enemigos[j].camino == 1) {

					if(((*juego).nivel.defensores[i].tipo == ELFOS) && (esta_en_rango_elfo((*juego).nivel.defensores[i].posicion,(*juego).nivel.camino_1[(*juego).nivel.enemigos[j].pos_en_camino]) == true) && ((*juego).nivel.enemigos[j].vida > VACIO)) {
							calcular_golpe_defensores(&(*juego), i);
							(*juego).nivel.enemigos[j].vida = (*juego).nivel.enemigos[j].vida-((*juego).nivel.defensores[i].fuerza_ataque);
						}
					}
				else if((*juego).nivel.enemigos[j].camino == 2) {

					if(((*juego).nivel.defensores[i].tipo == ELFOS) && (esta_en_rango_elfo((*juego).nivel.defensores[i].posicion,(*juego).nivel.camino_2[(*juego).nivel.enemigos[j].pos_en_camino]) == true) && ((*juego).nivel.enemigos[j].vida > VACIO)) {
							calcular_golpe_defensores(&(*juego), i);
							(*juego).nivel.enemigos[j].vida = (*juego).nivel.enemigos[j].vida-((*juego).nivel.defensores[i].fuerza_ataque);
						}
					}
				}
			}
		}

/*
Pre: -
Post: Las torres son daniadas por los enemigos si estos estan en una posicion determinada del terreno.
*/

void danio_torres(juego_t* juego) {

	for(int i=0 ; i < (*juego).nivel.tope_enemigos ; i++) {
		if((*juego).nivel.enemigos[i].pos_en_camino == ((*juego).nivel.tope_camino_1-1) && ((*juego).nivel.enemigos[i].camino == 1)) {
			(*juego).torres.resistencia_torre_1=(*juego).torres.resistencia_torre_1-((*juego).nivel.enemigos[i].vida);
			(*juego).nivel.enemigos[i].vida = VACIO;
		}
		if((*juego).nivel.enemigos[i].pos_en_camino == ((*juego).nivel.tope_camino_2-1) && ((*juego).nivel.enemigos[i].camino == 2)) {
			(*juego).torres.resistencia_torre_2=(*juego).torres.resistencia_torre_2-((*juego).nivel.enemigos[i].vida);
			(*juego).nivel.enemigos[i].vida = VACIO;
		}
	}	
}

/*
Pre: -
Post: Los enemigos realizan su jugada.
*/	

void jugada_enemigos(juego_t* juego) { 

if(((*juego).nivel_actual == PRIMER_NIVEL) || ((*juego).nivel_actual == SEGUNDO_NIVEL)) {
	for(int i=0 ; i < (*juego).nivel.tope_enemigos ; i++)  {
		if((*juego).nivel.enemigos[i].vida > VACIO)  { 
			(*juego).nivel.enemigos[i].pos_en_camino++; 
		}
	}
}

else if (((*juego).nivel_actual == TERCER_NIVEL) || ((*juego).nivel_actual == CUARTO_NIVEL)) {

	for(int i=0 ; i < (*juego).nivel.tope_enemigos ; i++)  {

		if(((*juego).nivel.enemigos[i].camino == 1) && ((*juego).nivel.enemigos[i].vida > VACIO))  { 
			(*juego).nivel.enemigos[i].pos_en_camino++; 
		}
		if(((*juego).nivel.enemigos[i].camino == 2) && ((*juego).nivel.enemigos[i].vida > VACIO)) { 
			(*juego).nivel.enemigos[i].pos_en_camino++; 
		}
	}
}

danio_torres(&(*juego));

if(((*juego).nivel.tope_enemigos < (*juego).nivel.max_enemigos_nivel)) { 
		generar_enemigo(&(*juego));
	}
}

/*
Pre: -
Post: Posiciona los enemigos en el terreno.
*/

void poner_enemigo(char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO], coordenada_t camino_1[MAX_LONGITUD_CAMINO], coordenada_t camino_2[MAX_LONGITUD_CAMINO] , int tope_camino_1 , int tope_camino_2, enemigo_t enemigos[MAX_ENEMIGOS]) {
	for(int i=0 ; i < tope_camino_1 ; i++) {
		if((enemigos[i].camino == 1) &&  (enemigos[i].vida > VACIO)) {
			terreno[camino_1[enemigos[i].pos_en_camino].fil][camino_1[enemigos[i].pos_en_camino].col] = ORCOS;
		}
	}
	for(int j=0 ; j < tope_camino_2 ; j++) {
		if((enemigos[j].camino == 2) && (enemigos[j].vida > VACIO)) {
			terreno[camino_2[enemigos[j].pos_en_camino].fil][camino_2[enemigos[j].pos_en_camino].col] = ORCOS;
		}
	}
}

/*
 * Jugará un turno y dejará el juego en el estado correspondiente.
 * Harán su jugada enanos, elfos y orcos en ese orden.
 */

void jugar_turno(juego_t* juego) {

	if((*juego).nivel.tope_enemigos != VACIO) {
		ataque_enanos(&(*juego));
		ataque_elfos(&(*juego));
	}
		jugada_enemigos(&(*juego));
}

/* 
 * Mostrará el mapa dependiendo del nivel en que se encuentra el jugador.
 */

void mostrar_juego(juego_t juego) {

	char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO];

	system("clear");

	printf("=======================================================\n");
	printf("               DEFENDIENDO LAS TORRES 					\n");
	printf("                  NIVEL ACTUAL: %i\n" , juego.nivel_actual);
	printf("        VIDA TORRE 1: %i  VIDA TORRE 2: %i\n",juego.torres.resistencia_torre_1,juego.torres.resistencia_torre_2);
	printf("=======================================================\n");

	inicializar_terreno(juego, terreno);
	poner_caminos(&juego,terreno);
	poner_defensor((&(juego.nivel)) , terreno);
	poner_enemigo(terreno, juego.nivel.camino_1 , juego.nivel.camino_2, juego.nivel.tope_camino_1 , juego.nivel.tope_camino_2, juego.nivel.enemigos);
	poner_entrada_y_torre(&juego, terreno);
	mostrar_terreno(juego, terreno);  
	printf("========================================================\n");
	
}



