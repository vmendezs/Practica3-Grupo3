/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC18F47K42
        Driver Version    :  2.00
*/

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/device_config.h"
#include "mcc_generated_files/uart1.h"
#include "colita.h"
#include "serialutility.h"

void main(void)
{
    //volatile uint8_t rxData;
    Colita p_cola;
    Commands com;
    //int posicion = 0x03; 
    // Initialize the device
    SYSTEM_Initialize();
    inicie_colita(&p_cola);
    Inicializar_commands(&com);

    while(1){
      if(UART1_is_rx_ready() && !com->controlserial){
        com->input= UART1_Read();
        Read_commands(&com, &p_cola);
      }
      if(UART1_is_tx_ready() && com->controlserial){
        if(com->error){
          error(&com); 
        }
        if(com->ok){
          ok(&com); 
        }
        if(!colita_empty(&p_cola)){
          mandarcola(&com,&p_cola);
        }
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