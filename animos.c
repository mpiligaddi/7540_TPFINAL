#include "animos.h"

const int DIA_MINIMO = 1;
const int DIA_MAXIMO = 30;
const char TURNO_MANIANA = 'M';
const char TURNO_TARDE = 'T';
const char TURNO_NOCHE = 'N';
const char PIE_DERECHO = 'D';
const char PIE_IZQUIERDO = 'I';
const char COMIDA_ENSALADA = 'E';
const char COMIDA_HAMBURGUESA = 'H';
const char COMIDA_PIZZA = 'P';
const char COMIDA_GUISO = 'G';
const int HORA_MINIMA_PARA_DORMIR = 0;
const int HORA_MAXIMA_PARA_DORMIR = 12;
const int MAXIMA_VELOCIDAD_VIENTO = 75;
const int MEDIA_VELOCIDAD_VIENTO = 50;
const int MINIMA_VELOCIDAD_VIENTO = 25;
const int HUMEDAD_A_LA_MANIANA = 75;
const int HUMEDAD_A_LA_TARDE = 25;
const int HUMEDAD_A_LA_NOCHE = 50;
const int PUNTOS_ENSALADA = 20;
const int PUNTOS_HAMBURGUESA = 15;
const int PUNTOS_PIZZA = 10;
const int PUNTOS_GUISO = 5;
const int PUNTOS_PIE_IZQUIERDO = 0;
const int PUNTOS_PIE_DERECHO = 10;
const int PUNTOS_MAXIMOS_POR_HORAS_DORMIDAS = 20;
const int PUNTOS_MEDIOS_POR_HORAS_DORMIDAS = 10;
const int PUNTOS_MINIMOS_POR_HORAS_DORMIDAS = 0;
const char ANIMO_MALO = 'M';
const char ANIMO_REGULAR = 'R';
const char ANIMO_BUENO = 'B';


/*
Pre: - 
Post: devuelve true si esta en rango de dias o false si no lo esta
*/

bool esta_en_rango_de_dias (int dia_elegido) {
	return ((dia_elegido >= DIA_MINIMO) && (dia_elegido <= DIA_MAXIMO));
}

/*
Pre: -
Post: devuelve true si esta dentro de los turnos posibles establecidos false si no lo esta 
*/

bool esta_en_turnos_aceptados (char turno_elegido) {
	return ((turno_elegido == TURNO_MANIANA) || (turno_elegido == TURNO_TARDE) || (turno_elegido == TURNO_NOCHE));
}

/*
Pre: -
Post: devuelve true si el usuario eligio alguna de las dos opciones posibles o false si no lo hizo. 
*/

bool es_pie_valido (char pie_levantado) {
	return ((pie_levantado == PIE_DERECHO) || (pie_levantado == PIE_IZQUIERDO));
}

/*
Pre: -
Post: devuelve true si la cena elegida esta dentro de las opciones aceptadas o false si no lo esta. 
*/

bool esta_en_opciones_de_cena (char cena_elegida) {
	return ((cena_elegida == COMIDA_ENSALADA) || (cena_elegida == COMIDA_HAMBURGUESA) || (cena_elegida == COMIDA_PIZZA) || (cena_elegida == COMIDA_GUISO));
}

/*
Pre: -
Post: devuelve true si esta dentro del rango de horarios o false si no lo esta. 
*/

bool esta_en_rango_de_horario (int hora_elegida) {
	return ((hora_elegida >= HORA_MINIMA_PARA_DORMIR) && (hora_elegida <= HORA_MAXIMA_PARA_DORMIR));
}

void preguntar_dia_del_mes(int* dia_del_mes) { 

	printf("Ingresa el dia del mes (entre %i y %i): ", DIA_MINIMO , DIA_MAXIMO);
	scanf("%i", dia_del_mes);
	while (esta_en_rango_de_dias(*dia_del_mes) == false) {
		printf("ese numero no esta en el rango! Era entre %i y %i...Volvelo a ingresar porfi: ", DIA_MINIMO , DIA_MAXIMO);
		scanf("%i", dia_del_mes);
	}
}

void preguntar_hora_del_dia(char* hora_del_dia) { 
	printf("Ingresa la hora del dia (MANIANA (M), TARDE (T), NOCHE (N)): ");
	scanf(" %c", hora_del_dia);
	while (esta_en_turnos_aceptados(*hora_del_dia) == false) {
		printf("Ese turno no esta en las opciones! Volvelo a ingresar porfi: ");
		scanf(" %c", hora_del_dia);
	}
}

void preguntar_sobre_pie_legolas (char* pie_legolas) { 
	printf("Legolas:\n");
	printf("Ingresa con que pie se levanto hoy Legolas (izquierdo (I) o derecho (D)): ");
	scanf(" %c", pie_legolas);
	while (es_pie_valido(*pie_legolas) == false) {
		printf ("El valor ingresado no esta dentro de las opciones. Volve a ingresar porfi: ");
		scanf(" %c", pie_legolas);
	}
}

void preguntar_cena_legolas (char* cena_legolas) { 
	printf("Ingresa que comio Legolas la noche anterior (Ensalada (E), Hamburguesa (H), Pizza (P) o Guiso (G)): ");
	scanf(" %c", cena_legolas);
	while (esta_en_opciones_de_cena(*cena_legolas) == false ) {
		printf("Eso no pudo haber comido! Volve a ingresar porfi: ");
		scanf(" %c", cena_legolas);
	}
}

void preguntar_horas_que_durmio_legolas (int* horas_que_durmio_legolas) { 
	printf("Ingresa la cantidad de horas que durmio Legolas (entre %i y %i): " , HORA_MINIMA_PARA_DORMIR , HORA_MAXIMA_PARA_DORMIR);
	scanf("%i", horas_que_durmio_legolas);
	while (esta_en_rango_de_horario(*horas_que_durmio_legolas) == false ) {
		printf("Eso no pudo haber dormido. Era entre %i y %i horas. Volve a ingresar: " , HORA_MINIMA_PARA_DORMIR , HORA_MAXIMA_PARA_DORMIR);
		scanf("%i", horas_que_durmio_legolas);
	}
}

void preguntar_sobre_pie_gimli (char* pie_gimli) { 
	printf("Gimli:\n");
	printf("Ingresa con que pie se levanto hoy Gimli (izquierdo (I) o derecho (D)): ");
	scanf(" %c", pie_gimli);
	while (es_pie_valido(*pie_gimli) == false){
		printf ("El valor ingresado no esta dentro de las opciones. Volve a ingresar porfi: ");
		scanf(" %c", pie_gimli);
	}
}

void preguntar_cena_gimli (char* cena_gimli) { 
	printf("Ingresa que comio Gimli la noche anterior (Ensalada (E), Hamburguesa (H), Pizza (P) o Guiso (G)): ");
	scanf(" %c", cena_gimli);
	while (esta_en_opciones_de_cena(*cena_gimli) == false ){
		printf("Eso no pudo haber comido! Volve a ingresar porfi: ");
		scanf(" %c", cena_gimli);
	}
}

void preguntar_horas_que_durmio_gimli (int* horas_que_durmio_gimli) { 
	printf("Ingresa la cantidad de horas que durmio Gimli (entre %i y %i): " , HORA_MINIMA_PARA_DORMIR , HORA_MAXIMA_PARA_DORMIR);
	scanf("%i", horas_que_durmio_gimli);
	while (esta_en_rango_de_horario(*horas_que_durmio_gimli) == false ) {
		printf("Eso no pudo haber dormido. Era entre %i y %i horas. Volve a ingresar: " , HORA_MINIMA_PARA_DORMIR , HORA_MAXIMA_PARA_DORMIR);
		scanf("%i", horas_que_durmio_gimli);
	}
}

void mostrar_velocidad_del_viento (int dia_del_mes) {
	
	if ((dia_del_mes >= 1) && (dia_del_mes <= 10)) {
		printf("La velocidad del viento es de %i km por hora\n", MAXIMA_VELOCIDAD_VIENTO);
	}
	else if ((dia_del_mes >=11) && (dia_del_mes <=20)) {
		printf("La velocidad del viento es de %i km por hora\n", MEDIA_VELOCIDAD_VIENTO);
	} else {
		printf("La velocidad del viento es de %i km por hora\n", MINIMA_VELOCIDAD_VIENTO);
	}
}

void mostrar_humedad_ambiente (char hora_del_dia) {

	if (hora_del_dia == TURNO_MANIANA) {
		printf("La humedad en el ambiente es de %i porciento\n", HUMEDAD_A_LA_MANIANA);
	}
	else if (hora_del_dia == TURNO_TARDE) {
		printf("La humedad en el ambiente es de %i porciento\n", HUMEDAD_A_LA_TARDE);
	} else {
		printf("La humedad en el ambiente es de %i porciento\n", HUMEDAD_A_LA_NOCHE);
	}
}

int puntos_pie_elegido(char pie_elegido) {

	if (pie_elegido == PIE_IZQUIERDO) {
		return(PUNTOS_PIE_IZQUIERDO);
	}
	else {
		return(PUNTOS_PIE_DERECHO);
	}
}

int puntos_cena_elegida(char cena_elegida){
	if(cena_elegida == COMIDA_ENSALADA) {
		return(PUNTOS_ENSALADA);
	}
	else if(cena_elegida == COMIDA_PIZZA) {
		return(PUNTOS_PIZZA);
	}
	else if(cena_elegida == COMIDA_HAMBURGUESA) {
		return(PUNTOS_HAMBURGUESA);
	}
	else {
		return(PUNTOS_GUISO);
	}
}

int puntos_de_horas_dormidas(int horas_dormidas) {
	if((horas_dormidas >= 0) && (horas_dormidas <= 4)) {
		return(PUNTOS_MINIMOS_POR_HORAS_DORMIDAS);
	}
	else if((horas_dormidas >= 5) && (horas_dormidas <= 8)) {
		return(PUNTOS_MEDIOS_POR_HORAS_DORMIDAS);
	}
	else {
		return(PUNTOS_MAXIMOS_POR_HORAS_DORMIDAS);
	}
}

void mostrar_animo_legolas(int puntos_totales_legolas){ 
	if ((puntos_totales_legolas >= 5) && (puntos_totales_legolas <= 20)) {
	printf("El animo de Legolas es %c\n" , 
		ANIMO_MALO);
	}
	else if ((puntos_totales_legolas >=21) && (puntos_totales_legolas <= 35)) {
	printf("El animo de Legolas es %c\n" ,
		ANIMO_REGULAR);
	}
	else {
	printf("El animo de Legolas es %c\n", ANIMO_BUENO);
	}
}

char animo (int puntos_totales) {
	if ((puntos_totales >= 5) && (puntos_totales <= 20)) {
	return( ANIMO_MALO );
	}
	else if ((puntos_totales >=21) && (puntos_totales <= 35)) {
	return( ANIMO_REGULAR );
	}
	else {
	return( ANIMO_BUENO );
	}
}

void mostrar_animo_gimli(int puntos_totales_gimli){ 
	if ((puntos_totales_gimli >= 5) && (puntos_totales_gimli <= 20)) {
	printf("El animo de Gimli es %c\n" , 
		ANIMO_MALO);
	}
	else if ((puntos_totales_gimli >=21) && (puntos_totales_gimli <= 35)) {
	printf("El animo de Gimli es %c\n" ,
		ANIMO_REGULAR);
	}
	else {
	printf("El animo de Gimli es %c\n", ANIMO_BUENO);
	}
}

int velocidad_del_viento (int dia_del_mes) {
	
	if ((dia_del_mes >= 1) && (dia_del_mes <= 10)) {
		return(MAXIMA_VELOCIDAD_VIENTO);
	}
	else if ((dia_del_mes >=11) && (dia_del_mes <=20)) {
		return(MEDIA_VELOCIDAD_VIENTO);
	} else {
		return(MINIMA_VELOCIDAD_VIENTO);
	}
}

int humedad_ambiente (char hora_del_dia) {

	if (hora_del_dia == TURNO_MANIANA) {
		return(HUMEDAD_A_LA_MANIANA);
	}
	else if (hora_del_dia == TURNO_TARDE) {
		return(HUMEDAD_A_LA_TARDE);
	} else {
		return(HUMEDAD_A_LA_NOCHE);
	}
}

void mostrar_resumen (int velocidad_viento , int humedad_ambiente , char animo_de_legolas , char animo_de_gimli) { 

	printf("Resumen: %i %i %c %c.\n" , velocidad_viento , humedad_ambiente , animo_de_legolas , animo_de_gimli);
}

void animos(int* viento , int* humedad , char* animo_legolas , char* animo_gimli) { 

	int dia_del_mes;
	char hora_del_dia;

	preguntar_dia_del_mes(&dia_del_mes);
	preguntar_hora_del_dia(&hora_del_dia);

	char pie_legolas;
	char cena_legolas;
	int horas_que_durmio_legolas;

	preguntar_sobre_pie_legolas(&pie_legolas);
	preguntar_cena_legolas(&cena_legolas);
	preguntar_horas_que_durmio_legolas(&horas_que_durmio_legolas);

	char pie_gimli;
	char cena_gimli;
	int horas_que_durmio_gimli;

	preguntar_sobre_pie_gimli(&pie_gimli);
	preguntar_cena_gimli(&cena_gimli);
	preguntar_horas_que_durmio_gimli(&horas_que_durmio_gimli);

	mostrar_velocidad_del_viento(dia_del_mes);
	mostrar_humedad_ambiente(hora_del_dia);
	
	int puntos_totales_legolas = puntos_cena_elegida(cena_legolas) + puntos_pie_elegido(pie_legolas) + puntos_de_horas_dormidas(horas_que_durmio_legolas);
	mostrar_animo_legolas(puntos_totales_legolas);
	
	int puntos_totales_gimli = puntos_cena_elegida(cena_gimli) + puntos_pie_elegido(pie_gimli) + puntos_de_horas_dormidas (horas_que_durmio_gimli);
	mostrar_animo_gimli(puntos_totales_gimli);

	int velocidad_viento = velocidad_del_viento(dia_del_mes);
	int humedad_de_ambiente = humedad_ambiente(hora_del_dia);
	char animo_de_legolas = animo(puntos_totales_legolas);
	char animo_de_gimli = animo(puntos_totales_gimli);

	mostrar_resumen( velocidad_viento , humedad_de_ambiente , animo_de_legolas , animo_de_gimli);

	*animo_legolas = animo(puntos_totales_legolas);
	*animo_gimli = animo(puntos_totales_gimli);
	*viento = velocidad_del_viento(dia_del_mes);
	*humedad = humedad_ambiente(hora_del_dia);

	}

