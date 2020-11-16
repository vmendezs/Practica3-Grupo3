#include "manejomemoria.h"
#include "serialutility.h"
#include "mcc_generated_files/i2c1_master.h"
#include "mcc_generated_files/drivers/i2c_simple_master.h"

void procese_memoria(i2c1_address_t dir, Commands *com)
{
    char vector[2];
    vector[0] = com->add_conv[0];
    vector[1] = com->add_conv[1];
    switch(com->bandera){
        case 1://Realiza WB
            i2c_write1ByteRegister(dir, &vector, com->val_conv);
            com->ok = 1;
            com->controlserial=1;
        break;
        
        case 2://Realiza WS
            if(com->num != 0){
                i2c_write1ByteRegister(dir, &vector, com->val_conv);
                com->num--;
                com->add_conv[1]++;
                vector[1] = com->add_conv[1];
                if(com->add_conv[1] == 256){
                    com->add_conv[0] = com->add_conv[0]+1;
                    com->add_conv[1] = 0;
                    if(com->add_conv[0] == 128){
                        com->add_conv[0] = 0;
                        com->add_conv[1] = 0;
                    }
                    vector[0] = com->add_conv[0];
                    vector[1] = com->add_conv[1];
                }                
                if(com->num == 0){
                    com->ok = 1;
                    com->controlserial=1;
                }
            }
        break;
        
        case 3://Realiza RB
            com->val_conv = (short)i2c_read1ByteRegister(dir, &vector);
            convertirASCII(com);
            com->banderaout = 1;
            com->controlserial = 1;
        break;
        
        case 4://Realiza RS
            if(com->num != 0){
                com->val_conv = (short)i2c_read1ByteRegister(dir, &vector);
                convertirASCII(com);
                com->banderaout = 1;
                com->controlserial = 1;
                com->num--;
                com->add_conv[1]++;
                vector[1] = com->add_conv[1];
                    if(com->add_conv[1] == 256){
                        com->add_conv[0] = com->add_conv[0]+1;
                        com->add_conv[1] = 0;
                        if(com->add_conv[0] == 128){
                            com->add_conv[0] = 0;
                            com->add_conv[1] = 0;
                        }
                        vector[0] = com->add_conv[0];
                        vector[1] = com->add_conv[1];
                     }
            }
        break;
    }
}