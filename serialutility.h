#if !defined(SERIALU_H)
#define SERIALU_H
#ifdef __cplusplus
extern "C" {
#endif

#include <avr/io.h>

/*Estados Máquina*/
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

typedef struct Commands Commands; // estructura de serial
struct Commands{
	ESTADOS state;
	char input;
	char num[2];
	//char val[510];
	char add[4];
	short numcount;
	short addcount;
	int error;
	int ok;
};

void Inicializar_commands(Commands *com);
void Read_commands(Commands *com, Colita *p_cola); //Maquina de estados de la comunicacion serial

	#ifdef __cplusplus
} // extern "C"
#endif
#endif