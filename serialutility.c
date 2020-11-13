#include "serialutility.h"
#include "mcc_generated_files/uart1.h"
#include "mcc_generated_files/tmr0.h"
#include "mcc_generated_files/drivers/i2c_simple_master.h"
#include <xc.h>

//Variables globales
char auxseri[2];
int count,times;

void Inicializar_commands(Commands *com){
    com->val_conv = 0;
    com->add_conv[0] = 0;
    com->state= ESTADO0;
    com->error= 0;
    com->ok=0;
    com->banderaout=0;
    com->controlserial=0;
    com->serialcount=0;
    count= 0;
    times=0;
}

void error(Commands *com){
    if(count==0){
        UART1_Write('E');
        count++;
    }
    if(count==1){
        UART1_Write('R');
        count++;
    }
    if(count==2){
        UART1_Write('R');
        count++;
    }
    if(count==3){
        UART1_Write('\n');
        count=0;
        com->error= 0;
        com->controlserial=0;
    }
}

void ok(Commands *com){
    if(count==0){
        UART1_Write('O');
        count++;
    }
    if(count==1){
        UART1_Write('K');
        count++;
    }
    if(count==2){
        UART1_Write('\n');
        count = 0;
        com->ok= 0;
        com->controlserial=0;
    }
}

short convertir(char a, char b){
    short x,y,z;
    //convertir valores
    if((short)b>47 && (short)b<58){
        x= (short)b - 48;
    }
    else if((short)b>64 && (short)b<71){
        x= (short)b - 55;
    }
    if((short)a>47 && (short)a<58){
        y= (short)a - 48;
    }
    else if((short)a>64 && (short)a<71){
        y= (short)a - 55;
    }
    
    z= (y*16)+x;
    return z;
}

void convertirASCII(Commands *com){
    int high,low;
    float auxi;
    high = com->val_conv / 16;
    low = com->val_conv - (high*16);
    if(high>=0 && high<=9){
        high = high + 48;
    }
    else if(high>=10 && high<=15){
        high = high + 55;
    }
    else{
        com->error= 1;
        com->controlserial=1;
    }
    
    if(low>=0 && low<=9){
        low = low + 48;
    }
    else if(low>=10 && low<=15){
        low = low + 55;
    }
    else{
        com->error= 1;
        com->controlserial=1;
    }
    com->output[0] = (char)high;
    com->output[1] = (char)low;
}

void writeHEX(Commands *com){
    if(count==0){
        UART1_Write(com->output[0]);
        count++;
    }
    if(count==1){
        UART1_Write(com->output[1]);
        count++;
    }
    if(count==2){
        UART1_Write('\n');
        count = 0;
        com->controlserial=0;
        com->banderaout=0;
    }
}

/*void mandarcola(Commands *com){
    if(com->serialcount < (2*(com->numconvertido))){
        //UART1_Write(obtener_val_colita(p_cola));
        com->serialcount = com->serialcount + 1;
    }
    else{
        com->serialcount=0;
        com->controlserial=0;
    }
}*/

void Read_commands(Commands *com){
    
    switch (com->state)
    {
        case ESTADO0:
			
            if ((com->input)=='R'){
				
                com->state=ESTADO1;
            }
            else if((com->input)=='W'){
                com->state=ESTADO2;
            }
            else
            {
                com->state=ESTADO0;
            }
                         
        break;

        case ESTADO1:
					
            if ((com->input)=='B'){
                com->state=ESTADO3;
            }
            else if((com->input) == 'S'){
                com->state = ESTADO4;
                }
            else
            {	 
                com->state=ESTADO0;
            }         
            
        break;
        
        case ESTADO2: //
            if ((com->input)=='B'){
                com->state=ESTADO5;
            }
            else if((com->input) == 'S'){
                com->state = ESTADO6;
                }
            else
            {	 
                com->state=ESTADO0;
            }    
        break;

        case ESTADO3: //
            if((com->input)=='\n'){
                com->add_conv[1] = convertir(auxseri[0],auxseri[1]);
                com->state=ESTADO0;
                com->bandera = 3;
                count= 0;
                break;
            }
            if(count < 2){
                auxseri[count]= com->input;
                count++;
                if(auxseri[0] > 55){
                    com->error= 1;
                    com->controlserial=1;
                    com->state=ESTADO0;
                    count=0;
                    break;
                }
                if(count == 2){
                    com->add_conv[0]= convertir(auxseri[0], auxseri[1]);
                }
                break;
            }
            else if(count >= 2 && count < 4 ){
                    auxseri[count-2]= com->input;
                    count++;
                }
            else{
                com->error= 1;
                com->controlserial=1;
                count=0;
                com->state=ESTADO0;
            }
        break;

        case ESTADO4: // 
            if((com->input)==','){
                com->add_conv[1] = convertir(auxseri[0],auxseri[1]);
                com->state=ESTADO7;
                count= 0;
                break;
            }
            if(count < 2){
                auxseri[count]= com->input;
                count++;
                if(auxseri[0] > 55){
                    com->error= 1;
                    com->controlserial=1;
                    com->state=ESTADO0;
                    count=0;
                    break;
                }
                if(count == 2){
                    com->add_conv[0]= convertir(auxseri[0], auxseri[1]);
                }
                break;
            }
            else if(count >= 2 && count < 4 ){
                    auxseri[count-2]= com->input;
                    count++;
                }
            else{
                com->error= 1;
                com->controlserial=1;
                count=0;
                com->state=ESTADO0;
            }
        break;
    
        case ESTADO5: // Se coloca el valor de la direccion de memoria
            if((com->input)==','){
                com->add_conv[1] = convertir(auxseri[0],auxseri[1]);
                com->state=ESTADO8;
                count= 0;
                break;
            }
            if(count < 2){
                auxseri[count]= com->input;
                count++;
                if(auxseri[0] > 55){
                    com->error= 1;
                    com->controlserial=1;
                    com->state=ESTADO0;
                    count=0;
                    break;
                }
                if(count == 2){
                    com->add_conv[0]= convertir(auxseri[0], auxseri[1]);
                }
                break;
            }
            else if(count >= 2 && count < 4 ){
                    auxseri[count-2]= com->input;
                    count++;
                }
            else{
                com->error= 1;
                com->controlserial=1;
                count=0;
                com->state=ESTADO0;
            }
        break;

        case ESTADO6: //Recepcion de direccion de inicio para escritura    
            if((com->input)==','){
                com->add_conv[1] = convertir(auxseri[0],auxseri[1]);
                com->state=ESTADO9;
                count= 0;
                break;
            }
            if(count < 2){
                auxseri[count]= com->input;
                count++;
                if(auxseri[0] > 55){
                    com->error= 1;
                    com->controlserial=1;
                    com->state=ESTADO0;
                    count=0;
                    break;
                }
                if(count == 2){
                    com->add_conv[0]= convertir(auxseri[0], auxseri[1]);
                }
                break;
            }
            else if(count >= 2 && count < 4 ){
                    auxseri[count-2]= com->input;
                    count++;
                }
            else{
                com->error= 1;
                com->controlserial=1;
                count=0;
                com->state=ESTADO0;
            }
        break;
    
        case ESTADO7: //Lee "num" posiciones de memoria
            if((com->input)=='\n'){
                com->num = convertir(auxseri[0],auxseri[1]);
                com->state=ESTADO0;
                com->bandera = 4;
                count= 0;
                break;
            }
            if(count < 2){
                auxseri[count] = com->input;
                count++;
            }
            else{
                count = 0;
                com->controlserial=1;
                com->error = 1;
                com->state=ESTADO0;
            }
        break;
        case ESTADO8: // Se escribe el valor de esa dirección de memoria
            if((com->input)=='\n'){
                //Realiza WB
                com->val_conv = convertir(auxseri[0], auxseri[1]);
                com->bandera = 1;
                com->state=ESTADO0;
                count= 0;
                break;
            }
            if(count < 2){
                auxseri[count] = com->input;
                count++;
            }
            else{
                count = 0;
                com->controlserial=1;
                com->error = 1;
                com->state=ESTADO0;
            }
        break;
    
        case ESTADO9: //Recepcion de veces de escritura
            if((com->input)==','){
                com->num = convertir(auxseri[0],auxseri[1]);
                com->state=ESTADO10;
                count= 0;
                break;
            }
            if(count < 2){
                auxseri[count] = com->input;
                count++;
            }
            else{
                count = 0;
                com->controlserial=1;
                com->error = 1;
                com->state=ESTADO0;
            }
        break;

        case ESTADO10: //Escribe el "num" numero de veces en la memoria
            if((com->input)=='\n'){
                com->bandera = 0;
                com->state=ESTADO0;
                count= 0;
                break;
            }
            if(count < 2){
                auxseri[count]= com->input;
                count++;
                if(count == 2){
                    com->val_conv = convertir(auxseri[0], auxseri[1]);
                    com->bandera = 2;
                    count= 0;
                    break;
                }
            }
            else{
                com->error= 1;
                com->controlserial=1;
                count=0;
                com->state=ESTADO0;
            }
        break;

        default:
        break;
    }
}