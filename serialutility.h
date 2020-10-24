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
	char val[510];
	char add[4];
	short numcount;
	short addcount;
};

void Read_commands(Commands *com); //Maquina de estados de la comunicacion serial
void Su_inicie_uart(uint16_t ubrr, Comunicacion *com);	// Inicializa lo que se necesite
														// Para comunicacion serial.
void Su_Atencion_Bajo_Consumo(Comunicacion *com);		// Se configura el bajo consumo
char Su_Hubo_Tecla_Serial(Comunicacion *tec_enable);	// Revisa si se ha recibido y si se
														// recibio guarda el valor
void Su_Transmision(int8_t *tempUnidades, int8_t *bandera, int8_t *tempDecenas);// Transmite
														// unidades, decenas, centigrados y un espacio
void Su_Interrupt_Enable(void);							// Habilita la interrupcion INT0
void Su_Interrupt_Disable(void);						// Desabilita la interrupcion INT0

	#ifdef __cplusplus
} // extern "C"
#endif
#endif