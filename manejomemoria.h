/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MANEJOMEMORIA_H
#define	MANEJOMEMORIA_H

#include "serialutility.h"
#include "mcc_generated_files/i2c1_master.h"
#include "mcc_generated_files/drivers/i2c_simple_master.h"
#include <xc.h> // include processor files - each processor file is guarded.  

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

void procese_memoria(i2c1_address_t dir, Commands *com);
    

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

