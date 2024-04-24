/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 19 Feb 2024                *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : ADC_private.h              *****************/
/****************************************************************/
#ifndef ATMEGA32_ADC_DRIVER_H_
#define ATMEGA32_ADC_DRIVER_H_

/**
 * @brief ADC Multiplexer Selection Register (ADMUX).
 *
 * This register controls the reference voltage selection, 
 * the ADC input channel selection, and the ADC left adjust result option.
 */
#define ADC_ADMUX_REG          (*((volatile uint8_t *)0x27))

/**
 * @brief ADC Control and Status Register A (ADCSRA).
 *
 * This register controls the ADC enable/disable, ADC start conversion, 
 * ADC auto-triggering, ADC interrupt enable, ADC prescaler selection, 
 * and ADC conversion complete flag.
 */
#define ADC_ADCSRA_REG         (*((volatile uint8_t *)0x26))

/**
 * @brief ADC Data Register High (ADCH).
 *
 * This register holds the higher 8 bits of the ADC result when the result is right adjusted.
 */
#define ADC_ADCH_REG           (*((volatile uint8_t *)0x25))

/**
 * @brief ADC Data Register Low (ADCL).
 *
 * This register holds the lower 2 bits of the ADC result when the result is right adjusted.
 */
#define ADC_ADCL_REG           (*((volatile uint8_t *)0x24))

/**
 * @brief ADC Data Register (ADC).
 *
 * This register is used for accessing the full 10-bit ADC result in a single 16-bit register when the result is left adjusted.
 */
#define ADC_ADC_REG            (*((volatile uint16_t *)0x24))

/**
 * @brief Special Function IO Register (SFIOR).
 *
 * This register is used for setting the ADC trigger source when auto-triggering is enabled.
 */
#define ADC_SFIOR_REG          (*((volatile uint8_t *)0x50))


#endif /**< ATMEGA32_ADC_DRIVER_H_ */