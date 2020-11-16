
#include "colita.h"
#include <xc.h>


void inicie_colita(Colita *p_cola) //Aqui inicio el arreglo de la cola
{
    p_cola->in = 0;
    p_cola->out = 0;
    p_cola->weight = 0;
}

char colocar_val_colita(Colita *p_cola, DATOCOLA data) //Añadir datos al arreglo de cola
{
    //Se agrega dato en la cola
    if(!(colita_full(p_cola))) 
    {
        p_cola->cola_array[p_cola->in] = data;
        p_cola->in++;
        p_cola->weight++;
    }
    else
    {
        return ERROR; //Cola llena
    }

    //Verificar si el apuntador de entrada esta fuera del arreglo de la cola
    if((p_cola->in) == TAM)
    {
        p_cola->in = 0;
        return GOOD;
    }
}

DATOCOLA obtener_val_colita(Colita *p_cola)
{
    DATOCOLA valor_cola;
    //Se obtiene dato de la cola
    if(!(colita_empty(p_cola))) 
    {
        valor_cola = p_cola->cola_array[p_cola->out];
        p_cola->out++;
        p_cola->weight--;
    }
    else
    {
        return ERROR; //Cola llena
    }
    return valor_cola;
    //Verificar si el apuntador de entrada esta fuera del arreglo de la cola
    if((p_cola->out) == TAM)
    {
        p_cola->out = 0;
        return GOOD;
    }
}

int tam_colita(Colita *p_cola) //Aqui se conocen cuantos datos hay en el arreglo de cola
{
    return (p_cola->weight);
}

int colita_full(Colita *p_cola) //Aqui se conoce si el arreglo de cola esta lleno
{
    if((p_cola->weight) >= TAM)
    {
        return ERROR; //Cola llena, manda error
    }
    else
    {
        return GOOD;
    }
}

int colita_empty(Colita *p_cola) //Aqui se conoce si el arreglo de cola esta vacio
{
    if((p_cola->weight) <= 0)
    {
        return ERROR; //Cola vacia, manda error
    }
    else
    {
        return GOOD;
    }
}
