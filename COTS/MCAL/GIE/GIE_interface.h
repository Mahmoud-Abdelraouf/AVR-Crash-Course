/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 19 Feb 2024                *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : GIE_interface.h            *****************/
/****************************************************************/
#ifndef ATMEGA32_GIE_INTERFACE_H_
#define ATMEGA32_GIE_INTERFACE_H_

/**
 * @brief Enables global interrupts.
 *
 * This function sets the Global Interrupt Enable bit (I-bit) in the Status Register (SREG),
 * enabling global interrupts.
 */
void GIE_Enable(void);

/**
 * @brief Disables global interrupts.
 *
 * This function clears the Global Interrupt Enable bit (I-bit) in the Status Register (SREG),
 * disabling global interrupts.
 */
void GIE_Disable(void);

#endif /* ATMEGA32_GIE_INTERFACE_H_ */
