/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 19 Feb 2024                *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : GIE_private.h              *****************/
/****************************************************************/
#ifndef ATMEGA32_GIE_PRIVATE_H_
#define ATMEGA32_GIE_PRIVATE_H_

/**
 * @brief Status Register (SREG) register.
 *
 * This macro defines the Status Register (SREG) register, which holds the global interrupt enable bit (I-bit).
 */
#define SREG_REG      (*((volatile u8*)0x5F))

/**
 * @brief Global Interrupt Enable bit (I-bit) position.
 *
 * This macro defines the bit position of the Global Interrupt Enable bit (I-bit) in the Status Register (SREG).
 */
#define I_BIT         7

#endif /* ATMEGA32_GIE_PRIVATE_H_ */
