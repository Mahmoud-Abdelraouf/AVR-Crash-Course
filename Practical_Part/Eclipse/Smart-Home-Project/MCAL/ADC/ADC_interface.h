/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 19 Feb 2024                *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : ADC_interface.h             *****************/
/****************************************************************/
#ifndef ATMEGA32_ADC_INTERFACE_H_
#define ATMEGA32_ADC_INTERFACE_H_

/**
 * @brief Function pointer type for ADC notification callback.
 *
 * This typedef defines a function pointer type for the ADC notification callback function.
 * The callback function takes a single parameter, which is the ADC result (16-bit unsigned integer).
 */
typedef void (*ADC_NotificationCallback_t)(uint16_t);

/**
 * @brief Macro defining ADC channel 1.
 *
 * This macro represents ADC channel 1, which corresponds to the physical pin PA1 on the ATmega32.
 * It is commonly used for analog input signals.
 */
#define ADC_CHANNEL1                  1

/**
 * @brief Macro defining ADC channel 2.
 *
 * This macro represents ADC channel 2, which corresponds to the physical pin PA2 on the ATmega32.
 * It is commonly used for analog input signals.
 */
#define ADC_CHANNEL2                  2

/**
 * @brief Macro defining ADC channel 3.
 *
 * This macro represents ADC channel 3, which corresponds to the physical pin PA3 on the ATmega32.
 * It is commonly used for analog input signals.
 */
#define ADC_CHANNEL3                  3

/**
 * @brief Macro defining ADC channel 4.
 *
 * This macro represents ADC channel 4, which corresponds to the physical pin PA4 on the ATmega32.
 * It is commonly used for analog input signals.
 */
#define ADC_CHANNEL4                  4

/**
 * @brief Macro defining ADC channel 5.
 *
 * This macro represents ADC channel 5, which corresponds to the physical pin PA5 on the ATmega32.
 * It is commonly used for analog input signals.
 */
#define ADC_CHANNEL5                  5

/**
 * @brief Macro defining ADC channel 6.
 *
 * This macro represents ADC channel 6, which corresponds to the physical pin PA6 on the ATmega32.
 * It is commonly used for analog input signals.
 */
#define ADC_CHANNEL6                  6

/**
 * @brief Macro defining ADC channel 7.
 *
 * This macro represents ADC channel 7, which corresponds to the physical pin PA7 on the ATmega32.
 * It is commonly used for analog input signals.
 */
#define ADC_CHANNEL7                  7

/**
 * @brief Initialize the ADC module.
 *
 * This function configures the ADC module with the following settings:
 * 1. Select Vref = AVCC.
 * 2. Right adjust the ADC result.
 * 3. Disable auto-triggering.
 * 4. Select ADC clock division factor CLK/64.
 * 5. Enable the ADC module.
 *
 * This function directly manipulates the ADC Multiplexer Selection Register (ADMUX)
 * and the ADC Control and Status Register A (ADCSRA) to configure the ADC settings.
 */
void ADC_vInit(void);

/**
 * @brief Synchronously gets the digital value from the ADC for the specified channel without blocking.
 *
 * This function reads the digital value from the ADC for the specified channel without blocking.
 * It waits for the conversion to complete and returns the result.
 *
 * @param[in] ChannelNb The ADC channel number.
 * @param[out] DigitalValue Pointer to where the digital value will be stored.
 * @return Std_ReturnType E_OK if the operation was successful, E_NOT_OK otherwise.
 */
Std_ReturnType ADC_GetDigitalValueSynchNonBlocking(u8 ChannelNb, u16 *DigitalValue);

/**
 * @brief Asynchronously starts an ADC conversion for the specified channel with a callback function.
 *
 * This function initiates an ADC conversion for the specified channel asynchronously
 * and sets up a callback function to be called upon completion of the conversion.
 *
 * @param[in] ChannelNb The ADC channel number.
 * @param[in] callbackFunction_t The callback function to be called upon completion of the ADC conversion.
 * @return Std_ReturnType E_OK if the operation was successful, E_NOT_OK otherwise.
 */
Std_ReturnType ADC_GetDigitalValueAsync(u8 ChannelNb, ADC_NotificationCallback_t callbackFunction);

/**
 * @brief Reads the value from the ADC Data Register (ADC).
 *
 * This function reads the current value from the ADC Data Register (ADC).
 *
 * @param[out] ADCValue Pointer to where the ADC value will be stored.
 * @return Std_ReturnType E_OK if the operation was successful, E_NOT_OK otherwise.
 */
Std_ReturnType ADC_GetADCRegValue(u16 *ADCValue);

#endif /**< ATMEGA32_ADC_INTERFACE_H_ */
