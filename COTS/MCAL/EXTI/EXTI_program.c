/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 19 Feb 2024                *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : EXTI_program.c             *****************/
/****************************************************************/

/*****************************< LIB *****************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/*****************************< MCAL *****************************/
#include "GIE_interface.h"
#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"
/*****************************< callback interface *****************************/
/**
 * @brief Global callback function pointer.
 *
 * This variable serves as a global function pointer for functions that match the
 * signature defined by the typedef `VoidFunctionPointer_t`.
 * It is initialized to NULL and can be assigned a valid function address to serve as a callback.
 */
EXTI_NotificationCallback_t EXTICallback[3] = {NULL};
/*****************************< Function Implementations *****************************/
Std_ReturnType EXTI_Enable(u8 EXTIIndex,u8 EdgeIndex) {
	Std_ReturnType Local_ErrorStatus = E_OK; 

	switch(EXTIIndex) {
		case EXTI_INT0:
			switch(EdgeIndex) {
				case EXTI_RAISING_EDGE:
				SET_BIT(EXTI_MCUCR_REG,ISC00_BIT);
				SET_BIT(EXTI_MCUCR_REG,ISC01_BIT);
				SET_BIT(EXTI_GICR_REG,INT0_BIT);
				break;

				case EXTI_FALLING_EDGE:
				CLR_BIT(EXTI_MCUCR_REG,ISC00_BIT);
				SET_BIT(EXTI_MCUCR_REG,ISC01_BIT);
				SET_BIT(EXTI_GICR_REG,INT0_BIT);
				break;

				case EXTI_ANY_LOGICAL_CHANGE:
				SET_BIT(EXTI_MCUCR_REG,ISC00_BIT);
				CLR_BIT(EXTI_MCUCR_REG,ISC01_BIT);
				SET_BIT(EXTI_GICR_REG,INT0_BIT);
				break;

				case EXTI_U8_LOW_LEVEL:
				CLR_BIT(EXTI_MCUCR_REG,ISC00_BIT);
				CLR_BIT(EXTI_MCUCR_REG,ISC01_BIT);
				SET_BIT(EXTI_GICR_REG,INT0_BIT);
				break;
				
				default : Local_ErrorStatus = E_NOT_OK;
				break;
			}
		break;
		case EXTI_INT1:
			switch(EdgeIndex) {
				case EXTI_RAISING_EDGE:
				SET_BIT(EXTI_MCUCR_REG,ISC10_BIT);
				SET_BIT(EXTI_MCUCR_REG,ISC11_BIT);
				SET_BIT(EXTI_GICR_REG,INT1_BIT);
				break;

				case EXTI_FALLING_EDGE:
				CLR_BIT(EXTI_MCUCR_REG,ISC10_BIT);
				SET_BIT(EXTI_MCUCR_REG,ISC11_BIT);
				SET_BIT(EXTI_GICR_REG,INT1_BIT);
				break;

				case EXTI_ANY_LOGICAL_CHANGE:
				SET_BIT(EXTI_MCUCR_REG,ISC10_BIT);
				CLR_BIT(EXTI_MCUCR_REG,ISC11_BIT);
				SET_BIT(EXTI_GICR_REG,INT1_BIT);
				break;

				case EXTI_U8_LOW_LEVEL:
				CLR_BIT(EXTI_MCUCR_REG,ISC10_BIT);
				CLR_BIT(EXTI_MCUCR_REG,ISC11_BIT);
				SET_BIT(EXTI_GICR_REG,INT1_BIT);
				break;

				default : Local_ErrorStatus = E_NOT_OK;
				break;
			}
		break;		
		case EXTI_INT2:
			switch(EdgeIndex) {
				case EXTI_RAISING_EDGE:
				SET_BIT(EXTI_MCUCR_REG,ISC10_BIT);
				SET_BIT(EXTI_MCUCR_REG,ISC11_BIT);
				SET_BIT(EXTI_GICR_REG,INT1_BIT);
				break;

				case EXTI_FALLING_EDGE:
				CLR_BIT(EXTI_MCUCSR_REG, ISC2_BIT);
				SET_BIT(EXTI_GICR_REG, INT2_BIT);
				break;

				default : Local_ErrorStatus = E_NOT_OK;
				break;
			}
		break;	
		default : Local_ErrorStatus = E_NOT_OK;
		break;
	}
	return Local_ErrorStatus;
}

Std_ReturnType EXTI_Disable(u8 copy_u8EXTIIndex) {
    Std_ReturnType Local_ErrorStatus = E_OK; /**< Local variable to hold the error status */

    switch (copy_u8EXTIIndex) {
        case EXTI_INT0:
            CLR_BIT(EXTI_GICR_REG, INT0_BIT); /**< Clear the external interrupt INT0 enable bit */
            break;

        case EXTI_INT1:
            CLR_BIT(EXTI_GICR_REG, INT1_BIT); /**< Clear the external interrupt INT1 enable bit */
            break;

        case EXTI_INT2:
            CLR_BIT(EXTI_GICR_REG, INT2_BIT); /**< Clear the external interrupt INT2 enable bit */
            break;

        default:
            Local_ErrorStatus = E_NOT_OK; /**< Invalid external interrupt index */
            break;
    }

    return Local_ErrorStatus;
}

Std_ReturnType EXTI_SetCallback(EXTI_NotificationCallback_t callbackFunction, u8 EXTIIndex) {
    Std_ReturnType Local_ErrorStatus = E_OK; /**< Local variable to hold the error status */

    /**< Check if the callback function is not NULL and the EXTIIndex is within valid range */
    if ((callbackFunction != NULL) && (EXTIIndex <= EXTI_INT2)) {
        /**< Set the callback function for the specified external interrupt */
        EXTICallback[EXTIIndex] = callbackFunction;
    } else {
        Local_ErrorStatus = E_NOT_OK; /**< Invalid callback function or external interrupt index */
    }

    return Local_ErrorStatus;
}
/*****************************< INTERRUPT SERVICE ROUTINE SECTION *****************************/
/**
 * @brief Prototype for the Interrupt Service Routine (ISR) of external interrupt 0 (EXTI0).
 *
 * This function prototype declares the ISR for external interrupt 0 (INT0).
 */
void __vector_1(void) __attribute__((signal));

/**
 * @brief Interrupt Service Routine (ISR) for external interrupt 0 (EXTI0).
 *
 * This ISR is called when external interrupt 0 (INT0) occurs. It checks if a callback
 * function is registered for EXTI_INT0 and calls it if available.
 */
void __vector_1(void) {
    if (EXTICallback[EXTI_INT0] != NULL) {
        EXTICallback[EXTI_INT0](); /**< Call the callback function for EXTI_INT0 */
    }
}

/**
 * @brief Prototype for the Interrupt Service Routine (ISR) of external interrupt 1 (EXTI1).
 *
 * This function prototype declares the ISR for external interrupt 1 (INT1).
 */
void __vector_2(void) __attribute__((signal));

/**
 * @brief Interrupt Service Routine (ISR) for external interrupt 1 (EXTI1).
 *
 * This ISR is called when external interrupt 1 (INT1) occurs. It checks if a callback
 * function is registered for EXTI_INT1 and calls it if available.
 */
void __vector_2(void)
{
    if (EXTICallback[EXTI_INT1] != NULL) {
        EXTICallback[EXTI_INT1](); /**< Call the callback function for EXTI_INT1 */
    }
}

/**
 * @brief Prototype for the Interrupt Service Routine (ISR) of external interrupt 2 (EXTI2).
 *
 * This function prototype declares the ISR for external interrupt 2 (INT2).
 */
void __vector_3(void) __attribute__((signal));

/**
 * @brief Interrupt Service Routine (ISR) for external interrupt 2 (EXTI2).
 *
 * This ISR is called when external interrupt 2 (INT2) occurs. It checks if a callback
 * function is registered for EXTI_INT2 and calls it if available.
 */
void __vector_3(void)
{
    if (EXTICallback[EXTI_INT2] != NULL) {
        EXTICallback[EXTI_INT2](); /**< Call the callback function for EXTI_INT2 */
    }
}

