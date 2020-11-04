#include "serialutility.h"
#include "mcc_generated_files/uart1.h"
#include <xc.h>
#include "colita.h"

void Inicializar_commands(Commands *com){
    com->state= ESTADO0;
    com->addcount= 0;
    com->error= 0;
    com->errorcount= 0;
    com->numcount= 0;
    com->ok=0;
    com->okcount= 0;
    com->controlserial=0;
    com->numconvertido=0;
    com->serialcount=0;
}

void error(Commands *com){
    if(com->errorcount==0){
        UART1_Write('E');
        com->errorcount= com->errorcount+1;
    }
    if(com->errorcount==1){
        UART1_Write('R');
        com->errorcount= com->errorcount+1;
    }
    if(com->errorcount==2){
        UART1_Write('R');
        com->errorcount= com->errorcount+1;
    }
    if(com->errorcount==3){
        UART1_Write('\n');
        com->errorcount=0;
        com->error= 0;
        com->controlserial=0;
    }
}

void ok(Commands *com){
    if(com->okcount==0){
        UART1_Write('O');
        com->okcount= com->okcount+1;
    }
    if(com->okcount==1){
        UART1_Write('K');
        com->okcount= com->okcount+1;
    }
    if(com->okcount==2){
        UART1_Write('\n');
        com->okcount=0;
        com->ok= 0;
        com->controlserial=0;
    }
}

void convertir(Commands *com){
    short x,y;
    if((short)com->num[0]>47 && (short)com->num[0]<58){
        x= (short)com->num[0] - 48;
    }
    else if((short)com->num[0]>64 && (short)com->num[0]<71){
        x= (short)com->num[0] - 55;
    }
    if((short)com->num[1]>47 && (short)com->num[1]<58){
        y= (short)com->num[1] - 48;
    }
    else if((short)com->num[1]>64 && (short)com->num[1]<71){
        y= (short)com->num[1] - 55;
    }
    com->numconvertido= (y*16)+x;
}

void mandarcola(Commands *com, Colita *p_cola){
    if(com->serialcount < (2*(com->numconvertido))){
        UART1_Write(obtener_val_colita(p_cola));
        com->serialcount = com->serialcount + 1;
    }
    else{
        com->serialcount=0;
        com->controlserial=0;
    }
}

void Read_commands(Commands *com, Colita *p_cola){
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
                //Realizar y responder RB
                com->num[0]= '0';
                com->num[1]= '1';
                convertir(com);
                com->controlserial=1;
                com->state=ESTADO0;
                com->addcount= 0;
                break;
            }
            if(com->addcount<4){
                com->add[com->addcount]= com->input;
                com->addcount++;  
            }
            else{
                com->error= 1;
                com->controlserial=1;
                com->addcount=0;
                com->state=ESTADO0;
            }  
        break;

        case ESTADO4: // 
            if((com->input)==','){
                com->state=ESTADO7;
                com->addcount= 0;
                break;
            }
            if(com->addcount<4){
                com->add[com->addcount]= com->input;
                com->addcount++;  
            }
            else{
                com->error= 1;
                com->controlserial=1;
                com->addcount=0;
                com->state=ESTADO0;
            }    
        break;
    
        case ESTADO5: // 
            if((com->input)==','){
                com->state=ESTADO8;
                com->addcount= 0;
                break;
            }
            if(com->addcount<4){
                com->add[com->addcount]= com->input;
                com->addcount++;  
            }
            else{
                com->error= 1;
                com->controlserial=1;
                com->addcount=0;
                com->state=ESTADO0;
            }   
        break;

        case ESTADO6: // 
            if((com->input)==','){
                com->state=ESTADO9;
                com->addcount= 0;
                break;
            }
            if(com->addcount<4){
                com->add[com->addcount]= com->input;
                com->addcount++;  
            }
            else{
                com->error= 1;
                com->controlserial=1;
                com->addcount=0;
                com->state=ESTADO0;
            }  
        break;
    
        case ESTADO7: // Toca arreglar esta vaina
            if((com->input)=='\n'){
                //Realiza RS
                convertir(com);
                com->controlserial=1;
                com->state=ESTADO0;
                com->numcount= 0;
                break;
            }
            if( !(com->input>47 && com->input<58) && !(com->input>64 && com->input<71)){
                com->error=1;
                com->numcount=0;
                com->controlserial=1;
                com->state=ESTADO0;
            }
            if(com->numcount<2){
                com->num[com->numcount]= com->input;
                com->numcount++; 
            }
            else{
                com->error= 1;
                com->numcount=0;
                com->controlserial=1;
                com->state=ESTADO0;
            }   
        break;

        case ESTADO8: // 
            if((com->input)=='\n'){
                //Realiza WB
                com->state=ESTADO0;
                com->ok=1;
                com->controlserial=1;
                com->numcount= 0;
                break;
            }
            colocar_val_colita(p_cola, com->input);
            //com->val[com->numcount]= com->input;
            //com->numcount++;   
        break;
    
        case ESTADO9: // 
            if((com->input)==','){
                com->state=ESTADO10;
                com->numcount= 0;
                break;
            }
            if(com->numcount<2){
                com->num[com->numcount]= com->input;
                com->numcount++;  
            }
            else{
                com->error= 1;
                com->controlserial=1;
                com->numcount=0;
                com->state=ESTADO0;
            } 
        break;

        case ESTADO10: // 
            if((com->input)=='\n'){
                //Realiza WS
                com->ok=1;
                com->controlserial=1;
                com->state=ESTADO0;
                com->numcount= 0;
                break;
            }
            if((com->input)==','){
                break;
            }
            if(!colita_full(p_cola)){
                colocar_val_colita(p_cola,com->input);
            }
            else
            {
                /* Guardar los datos en memoria 
                y mover las 10 posiciones de add*/
                inicie_colita(p_cola);
                colocar_val_colita(p_cola,com->input);
            }
            
            //com->val[com->numcount]= com->input;
            //com->numcount++;   
        break;

        default:
        break;
    }
}