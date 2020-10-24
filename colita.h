#if !defined(COLITA_H)
#define COLITA_H
#ifdef __cplusplus
extern "C" {
	#endif

#include <avr/io.h>

#define TAM 10
#define ERROR 1
#define GOOD 0

typedef unsigned char DATOCOLA;

typedef struct Colita; // estructura de serial
struct Colita{
    DATOCOLA cola_array[TAM]; //arreglo de cola
    int in; //posicion de entrada del arreglo de cola
    int out; //posicion de salida del arreglo de cola
    int weight; //valor de la posicion del arreglo de cola
};

void inicie_colita(Colita *p_cola); //Aqui inicio el arreglo de la cola
char colocar_val_colita(Colita *p_cola, DATOCOLA data); //Añadir datos al arreglo de cola
DATOCOLA obtener_val_colita(Colita *p_cola);
int tam_colita(Colita *p_cola); //Aqui se conocen cuantos datos hay en el arreglo de cola
int colita_full(Colita *p_cola); //Aqui se conoce si el arreglo de cola esta lleno
int colita_empty(Colita *p_cola); //Aqui se conoce si el arreglo de cola esta vacio

#ifdef __cplusplus
} // extern "C"
#endif
#endif