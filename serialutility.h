/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SERIALU_H
#define	SERIALU_H
#include "colita.h"
#include <xc.h> // include processor files - each processor file is guarded.  

#ifdef	__cplusplus
//extern "C" {
#endif /* __cplusplus */

/*
#define ESTADO0 0
#define ESTADO1 1
#define ESTADO2 2
#define ESTADO3 3
#define ESTADO4 4
#define ESTADO5 5
#define ESTADO6 6
#define ESTADO7 7
#define ESTADO8 8
#define ESTADO9 9
#define ESTADO10 10*/
typedef enum{
	ESTADO0,
	ESTADO1,
	ESTADO2,
	ESTADO3,
	ESTADO4,
	ESTADO5,
	ESTADO6,
	ESTADO7,
	ESTADO8,
	ESTADO9,
	ESTADO10
}ESTADOS;

//typedef struct Commands Commands; // estructura de serial
typedef union{
    struct{
        ESTADOS state;
        char input;
        char num[2];
        //char val[510];
        char add[4];
        short numcount;
        short addcount;
        short error;
        short errorcount;
        short ok;
        short okcount;
        short numconvertido;
        short controlserial;
        short serialcount;
    };
}Commands;

void Inicializar_commands(Commands *com);
void error(Commands *com);
void ok(Commands *com);
void convertir(Commands *com);
void mandarcola(Commands *com, Colita *p_cola);
void Read_commands(Commands *com, Colita *p_cola); //Maquina de estados de la comunicacion serial

#ifdef	__cplusplus
//}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */