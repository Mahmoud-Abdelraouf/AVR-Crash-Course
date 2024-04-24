/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 19 Feb 2024                *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : EXTI_interface.h           *****************/
/****************************************************************/
#ifndef ATMEGA32_EXTI_INTERFACE_H_
#define ATMEGA32_EXTI_INTERFACE_H_

/*****************************< MACROS *****************************/
/**
 * @brief Typedefinition for a function pointer with no parameters and void return type.
 *
 * This typedef defines a function pointer type for functions that take no parameters
 * and return void.
 */
typedef void (*EXTI_NotificationCallback_t)(void);

/**
 * @brief Macro definition for external interrupt index 0 (EXTI_INT0).
 *
 * This macro defines the index for external interrupt 0 (INT0).
 */
#define EXTI_INT0                    0

/**
 * @brief Macro definition for external interrupt index 1 (EXTI_INT1).
 *
 * This macro defines the index for external interrupt 1 (INT1).
 */
#define EXTI_INT1                    1

/**
 * @brief Macro definition for external interrupt index 2 (EXTI_INT2).
 *
 * This macro defines the index for external interrupt 2 (INT2).
 */
#define EXTI_INT2                    2

/**
 * @brief Macro definition for rising edge trigger configuration.
 *
 * This macro defines the value for a rising edge trigger configuration
 * used for configuring external interrupts.
 */
#define EXTI_RAISING_EDGE            0

/**
 * @brief Macro definition for falling edge trigger configuration.
 *
 * This macro defines the value for a falling edge trigger configuration
 * used for configuring external interrupts.
 */
#define EXTI_FALLING_EDGE           1

/**
 * @brief Macro definition for any logical change trigger configuration.
 *
 * This macro defines the value for an any logical change trigger configuration
 * used for configuring external interrupts.
 */
#define EXTI_ANY_LOGICAL_CHANGE     2

/**
 * @brief Macro definition for low level trigger configuration.
 *
 * This macro defines the value for a low level trigger configuration
 * used for configuring external interrupts.
 */
#define EXTI_U8_LOW_LEVEL           3
/*****************************< PROTOTYPES *****************************/
/**
 * @brief Enables the specified external interrupt with the given edge trigger configuration.
 *
 * This function enables the specified external interrupt (INT0, INT1, INT2) with the provided
 * edge trigger configuration. The function configures the external interrupt's trigger mode
 * based on the given EdgeIndex.
 *
 * @param[in] EXTIIndex The index of the external interrupt (EXTI_INT0, EXTI_INT1, EXTI_INT2).
 * @param[in] EdgeIndex The edge trigger configuration for the interrupt.
 *                      - EXTI_RAISING_EDGE: Rising edge trigger.
 *                      - EXTI_FALLING_EDGE: Falling edge trigger.
 *                      - EXTI_ANY_LOGICAL_CHANGE: Any logical change trigger.
 *                      - EXTI_U8_LOW_LEVEL: Low level trigger.
 * @return Std_ReturnType E_OK if the operation was successful, E_NOT_OK otherwise.
 */
Std_ReturnType EXTI_Enable(u8 EXTIIndex, u8 EdgeIndex);

/**
 * @brief Disables the specified external interrupt.
 *
 * This function disables the specified external interrupt (INT0, INT1, INT2).
 *
 * @param[in] copy_u8EXTIIndex The index of the external interrupt (EXTI_INT0, EXTI_INT1, EXTI_INT2).
 * @return Std_ReturnType E_OK if the operation was successful, E_NOT_OK otherwise.
 */
Std_ReturnType EXTI_Disable(u8 EXTIIndex);

/**
 * @brief Sets the callback function for the specified external interrupt.
 *
 * This function sets the callback function to be called when the specified external interrupt (INT0, INT1, INT2) occurs.
 *
 * @param[in] callbackFunction The callback function to be called when the interrupt occurs.
 * @param[in] EXTIIndex The index of the external interrupt (EXTI_INT0, EXTI_INT1, EXTI_INT2).
 * @return Std_ReturnType E_OK if the operation was successful, E_NOT_OK otherwise.
 */
Std_ReturnType EXTI_SetCallback(EXTI_NotificationCallback_t callbackFunction, u8 EXTIIndex);


#endif /* ATMEGA32_EXTI_INTERFACE_H_ */
