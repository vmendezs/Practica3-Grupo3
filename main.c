#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/device_config.h"
#include "mcc_generated_files/uart1.h"
#include "mcc_generated_files/tmr0.h"
#include "mcc_generated_files/delay.h"
#include "serialutility.h"
#include "manejomemoria.h"
#include "colita.h"
#include "mcc_generated_files/i2c1_master.h"
#include "mcc_generated_files/drivers/i2c_simple_master.h"

void main(void)
{
    //volatile uint8_t rxData;
    Colita p_cola;
    Commands com;
    DATOCOLA data;
    i2c1_address_t dir = 0x50;
    int band;
    /*char registro[2];
    uint16_t dato = 0x15;
    registro[0] = 0x00;
    registro[1] = 0xF0;*/
    
    // Initialize the device
    SYSTEM_Initialize();
    Inicializar_commands(&com);
    inicie_colita(&p_cola);

    while(1){
        if(com.bandera != 0){
            procese_memoria(dir, &com);
            if(com.num != 0){
                com.bandera = 4;
            }else{
                com.bandera = 0;}
        }
        if(UART1_is_rx_ready() && colita_empty(&p_cola)){
            data = UART1_Read();
            colocar_val_colita(&p_cola, data);
        }
        if(!colita_empty(&p_cola)){
            com.input= (char)obtener_val_colita(&p_cola);
            Read_commands(&com);
        }
        if(UART1_is_tx_ready() && com.controlserial){
            if(com.error){
                error(&com); 
            }
            if(com.ok){
              ok(&com); 
            }
            if(com.banderaout){
                writeHEX(&com);
            }
            //Sacar dato de mem cuando leemos
        }
        
    }
}