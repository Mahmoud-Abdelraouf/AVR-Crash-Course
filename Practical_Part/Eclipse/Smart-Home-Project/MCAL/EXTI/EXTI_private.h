/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 19 Feb 2024                *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : EXTI_private.h             *****************/
/****************************************************************/
#ifndef ATMEGA32_EXTI_PRIVATE_H_
#define ATMEGA32_EXTI_PRIVATE_H_

/*****************************< REGISTERS *****************************/
/**
 * @brief External Interrupt MCU Control Register (MCUCR) register.
 *
 * This register is used to configure the interrupt sense control for external interrupts 0 and 1.
 */
#define EXTI_MCUCR_REG     (*((volatile u8*)0x55))

/**
 * @brief General Interrupt Control Register (GICR) register.
 *
 * This register is used to enable external interrupts INT0, INT1, and INT2.
 */
#define EXTI_GICR_REG      (*((volatile u8*)0x5B))

/**
 * @brief External Interrupt MCU Control and Status Register (MCUCSR) register.
 *
 * This register is used to configure the interrupt sense control for external interrupt 2.
 */
#define EXTI_MCUCSR_REG    (*((volatile u8*)0x54))

/*****************************< BITS *****************************/
/**< MCUCR BITS */ 
/**
 * @brief Bit position for interrupt sense control bit ISC11 in MCUCR register.
 *
 * This bit is used in conjunction with ISC10 to configure the interrupt sense control for external interrupt 1.
 */
#define ISC11_BIT                 3

/**
 * @brief Bit position for interrupt sense control bit ISC10 in MCUCR register.
 *
 * This bit is used in conjunction with ISC11 to configure the interrupt sense control for external interrupt 1.
 */
#define ISC10_BIT                 2

/**
 * @brief Bit position for interrupt sense control bit ISC01 in MCUCR register.
 *
 * This bit is used in conjunction with ISC00 to configure the interrupt sense control for external interrupt 0.
 */
#define ISC01_BIT                 1

/**
 * @brief Bit position for interrupt sense control bit ISC00 in MCUCR register.
 *
 * This bit is used in conjunction with ISC01 to configure the interrupt sense control for external interrupt 0.
 */
#define ISC00_BIT                 0

/**< GICR BITS */ 
/**
 * @brief Bit position for interrupt enable bit INT1 in GICR register.
 *
 * This bit enables external interrupt 1 (INT1).
 */
#define INT1_BIT                  7

/**
 * @brief Bit position for interrupt enable bit INT0 in GICR register.
 *
 * This bit enables external interrupt 0 (INT0).
 */
#define INT0_BIT                  6

/**
 * @brief Bit position for interrupt enable bit INT2 in GICR register.
 *
 * This bit enables external interrupt 2 (INT2).
 */
#define INT2_BIT                  5

/**< MCUCSR BITS */ 
/**
 * @brief Bit position for interrupt sense control bit ISC2 in MCUCSR register.
 *
 * This bit is used to configure the interrupt sense control for external interrupt 2.
 */
#define ISC2_BIT                  6


#endif /**< ATMEGA32_EXTI_PRIVATE_H_ */
