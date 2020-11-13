#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/device_config.h"
#include "mcc_generated_files/uart1.h"
#include "mcc_generated_files/tmr0.h"
#include "serialutility.h"
#include "manejomemoria.h"
#include "mcc_generated_files/i2c1_master.h"
#include "mcc_generated_files/drivers/i2c_simple_master.h"

void main(void)
{
    //volatile uint8_t rxData;
    Commands com;
    i2c1_address_t dir = 0x50;
    /*char registro[2];
    uint16_t dato = 0x15;
    registro[0] = 0x00;
    registro[1] = 0xF0;*/
    
    // Initialize the device
    SYSTEM_Initialize();
    Inicializar_commands(&com);

    while(1){
        if(com.bandera != 0){
            procese_memoria(dir, &com);
            com.bandera = 0;
        }
        
        if(UART1_is_rx_ready() && !com.controlserial){
            com.input= UART1_Read();
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
    
    
    /*while(1)
    {
        // Logic to echo received data
        if(UART1_is_rx_ready())
        {
            rxData = UART1_Read();
            colocar_val_colita(&p_cola, rxData);
            
            if(UART1_is_tx_ready())
            {
                UART1_Write(obtener_val_colita(&p_cola)); 
            }
        }
    }*/
}