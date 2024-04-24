/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 19 Feb 2024                *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : ADC_config.h               *****************/
/****************************************************************/
#ifndef ATMEGA32_ADC_CONFIG_H_
#define ATMEGA32_ADC_CONFIG_H_

/**
 * @brief Maximum timeout value for ADC operations.
 *
 * This defines the maximum value for the timeout duration (in microseconds) 
 * used in ADC operations to prevent infinite loops in case of failure or 
 * unresponsive ADC hardware.
 */
#define ADC_TIME_OUT_MAX_VALUE            50000

#endif /**< ATMEGA32_ADC_CONFIG_H_ */
