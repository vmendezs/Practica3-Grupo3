#include "manejomemoria.h"
#include "serialutility.h"
#include "mcc_generated_files/i2c1_master.h"
#include "mcc_generated_files/drivers/i2c_simple_master.h"

short regg;

void procese_memoria(i2c1_address_t dir, Commands *com)
{
    switch(com->bandera){
        case 1://Realiza WB
            i2c_write1ByteRegister(dir, &(com->add_conv), com->val_conv);
            com->ok = 1;
            com->controlserial=1;
        break;
        case 2://Realiza WS
            /*if((com->add_conv[1] == 255) && (com->add_conv[0] < 127)){
                com->add_conv[0] = com->add_conv[0] + 1;
            }*/
            if(com->num != 0){
                i2c_write1ByteRegister(dir, &(com->add_conv), com->val_conv);
                com->num--;
                com->add_conv[1]++;
                if(com->add_conv[1] > 255){
                    com->add_conv[0] = com->add_conv[0]+1;
                    com->add_conv[1]=0;
                }
                if(com->num == 0){
                    com->ok = 1;
                    com->controlserial=1;    
                }  
            }
        break;
        case 3://Realiza RB
            com->val_conv = (short)i2c_read1ByteRegister(dir, &(com->add_conv));
            convertirASCII(com);
            com->banderaout = 1;
            com->controlserial = 1;
        break;
        case 4://Realiza RS
            if( (com->veces) < (com->num) ){
                regg = (uint8_t)((com->add_conv[1]) + (com->veces));
                com->val_conv = (short)i2c_read1ByteRegister(dir, &regg);
                convertirASCII(com);
                com->banderaout = 1;
                com->controlserial = 1;
                com->veces++;
            }
            else{
                com->veces = 0;
            }
        break;
    }
}