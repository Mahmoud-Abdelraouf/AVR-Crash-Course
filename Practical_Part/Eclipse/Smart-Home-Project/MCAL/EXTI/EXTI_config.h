/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 19 Feb 2024                *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : EXTI_config.h              *****************/
/****************************************************************/
/**
 * @file atmega32_exti_config.h
 * @brief Configuration file for external interrupts (EXTI) on ATmega32.
 *
 * This file provides configuration options for external interrupts (EXTI) on the ATmega32 microcontroller.
 * Users can select the interrupt trigger mode for each external interrupt (INT0, INT1, INT2) by specifying
 * one of the available options: FALLING_EDGE, RISING_EDGE, LOW_LEVEL, or LOGICAL_CHANGE.
 */

#ifndef ATMEGA32_EXTI_CONFIG_H_
#define ATMEGA32_EXTI_CONFIG_H_

/**
 * @brief Selects the sense control for external interrupt INT0.
 *
 * Possible options:
 * - FALLING_EDGE: Triggered on falling edge.
 * - RISING_EDGE: Triggered on rising edge.
 * - LOW_LEVEL: Triggered on low level.
 * - LOGICAL_CHANGE: Triggered on logical change (both rising and falling edges).
 */
#define EXT_INT0_SENSE_CONTROL         FALLING_EDGE

/**
 * @brief Selects the sense control for external interrupt INT1.
 *
 * Possible options:
 * - FALLING_EDGE: Triggered on falling edge.
 * - RISING_EDGE: Triggered on rising edge.
 * - LOW_LEVEL: Triggered on low level.
 * - LOGICAL_CHANGE: Triggered on logical change (both rising and falling edges).
 */
#define EXT_INT1_SENSE_CONTROL         FALLING_EDGE

/**
 * @brief Selects the sense control for external interrupt INT2.
 *
 * Possible options:
 * - FALLING_EDGE: Triggered on falling edge.
 * - RISING_EDGE: Triggered on rising edge.
 */
#define EXT_INT2_SENSE_CONTROL         FALLING_EDGE

#endif /* ATMEGA32_EXTI_CONFIG_H_ */

