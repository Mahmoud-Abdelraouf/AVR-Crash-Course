/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 19 Feb 2024                *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : GIE_program.c              *****************/
/****************************************************************/

/*****************************< LIB *****************************/
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
/*****************************< MCAL *****************************/
#include "GIE_interface.h"
#include "GIE_private.h"
#include "GIE_config.h"
/*****************************< Function Implementations *****************************/
void GIE_Enable(void) {
    SET_BIT(SREG_REG, I_BIT); /**< Set the Global Interrupt Enable bit */
}

void GIE_Disable(void) {
    CLR_BIT(SREG_REG, I_BIT); /**< Clear the Global Interrupt Enable bit */
}
