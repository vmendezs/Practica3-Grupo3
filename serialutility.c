#include "serialutility.h"
#include <avr/io.h>
#include "colita.h"

void Inicializar_commands(Commands *com){
    com->state= ESTADO0;
    com->addcount= 0;
    com->error= 0;
    com->numcount= 0;
    com->ok=0;
}

void Read_commands(Commands *com, Colita *p_cola){
    switch (com->state)
    {
        case ESTADO0:
			
            if ((com->input)=='R'){
				
                com->state=ESTADO1;
            }
            else if((com->tecla)=='W'){
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
                com->state=ESTADO0;
                com->addcount= 0;
                break;
            }
            com->add[com->addcount]= com->input;
            com->addcount++;
        break;

        case ESTADO4: // 
            if((com->input)==','){
                com->state=ESTADO7;
                com->addcount= 0;
                break;
            }
            com->add[com->addcount]= com->input;
            com->addcount++;   
        break;
    
        case ESTADO5: // 
            if((com->input)==','){
                com->state=ESTADO8;
                com->addcount= 0;
                break;
            }
            com->add[com->addcount]= com->input;
            com->addcount++;   
        break;

        case ESTADO6: // 
            if((com->input)==','){
                com->state=ESTADO9;
                com->addcount= 0;
                break;
            }
            if(com->addount<4){
                com->add[com->addcount]= com->input;
                com->addcount++;  
            }
            else{
                com->error= 1;
                com->addcount=0;
                com->state=ESTADO0;
                break;
            }  
        break;
    
        case ESTADO7: // 
            if((com->input)=='\n'){
                //Realiza RS
                com->state=ESTADO0;
                com->numcount= 0;
                break;
            }
            com->num[com->numcount]= com->input;
            com->numcount++;   
        break;

        case ESTADO8: // 
            if((com->input)=='\n'){
                //Realiza WB
                com->state=ESTADO0;
                com->ok=1;
                com->numcount= 0;
                break;
            }
            colocar_val_colita(&p_cola, com->input);
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
                com->numcount=0;
                com->state=ESTADO0;
                break;
            } 
        break;

        case ESTADO10: // 
            if((com->input)=='\n'){
                //Realiza WS
                com->ok=1;
                com->state=ESTADO0;
                com->numcount= 0;
                break;
            }
            if((com->input)==','){
                break;
            }
            if(!colita_full(&p_cola)){
                colocar_val_colita(&p_cola,com->input);
            }
            else
            {
                /* Guardar los datos en memoria 
                y mover las 10 posiciones de add*/
                inicie_colita(&p_cola);
                colocar_val_colita(&p_cola,com->input);
            }
            
            //com->val[com->numcount]= com->input;
            //com->numcount++;   
        break;

        default:
        break;
    }
}