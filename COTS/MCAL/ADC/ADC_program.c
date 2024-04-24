/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 19 Feb 2024                *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : ADC_program.c              *****************/
/****************************************************************/

/*****************************< LIB *****************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/*****************************< MCAL *****************************/
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"
/*****************************< callback interface *****************************/
/**< Create an instance of the ADC notification callback function */
ADC_NotificationCallback_t callback = NULL;

/**
 * @brief ADC busy flag.
 *
 * This variable represents the ADC busy flag, indicating whether the ADC is currently busy with a conversion or not.
 * When the ADC is busy, this flag is set to a non-zero value; otherwise, it is set to 0.
 */
static uint8_t ADC_BusyFlag = 0;
/*****************************< Function Implementations *****************************/
void ADC_vInit(void) {
    CLR_BIT(ADC_ADMUX_REG, 7); /**< Select Vref = AVCC */
    SET_BIT(ADC_ADMUX_REG, 6); /**< Select Vref = AVCC */

    CLR_BIT(ADC_ADMUX_REG, 5); /**< Right adjust the ADC result */

    CLR_BIT(ADC_ADCSRA_REG, 5); /**< Disable auto-triggering */

    SET_BIT(ADC_ADCSRA_REG, 2); /**< Select ADC clock division factor CLK/64 */
    SET_BIT(ADC_ADCSRA_REG, 1); /**< Select ADC clock division factor CLK/64 */
    CLR_BIT(ADC_ADCSRA_REG, 0); /**< Select ADC clock division factor CLK/64 */

    SET_BIT(ADC_ADCSRA_REG, 7); /**< Enable the ADC module */
}

Std_ReturnType ADC_GetDigitalValueSynchNonBlocking(u8 ChannelNb, u16 *DigitalValue) {
    Std_ReturnType Local_ErrorStatus = E_OK; /**< Local variable to hold the error status */
    u32 Local_TimeOutCounter = 0; /**< Local variable to track timeout */

    /**< Check if the channel number is valid and the pointer to DigitalValue is not NULL */
    if ((ChannelNb < 32) && (DigitalValue != NULL)) {
        /**< Clear MUX[4..0] */
        ADC_ADMUX_REG &= 0b11100000;
        /**< Select Channel */
        ADC_ADMUX_REG |= ChannelNb;
        /**< Start Conversion */
        SET_BIT(ADC_ADCSRA_REG, 6);
        /**< Wait for conversion completion or timeout */
        while ((GET_BIT(ADC_ADCSRA_REG, 4) == 0) && (Local_TimeOutCounter < ADC_TIME_OUT_MAX_VALUE)) {
            Local_TimeOutCounter++;
        }
        /**< Check if conversion completed within timeout */
        if (GET_BIT(ADC_ADCSRA_REG, 4) != 0) {
            /**< Clear flag */
            SET_BIT(ADC_ADCSRA_REG, 4);
            /**< Read the Digital Value */
            *DigitalValue = ADC_ADC_REG;
        } else {
            /**< Conversion timed out */
            Local_ErrorStatus = E_NOT_OK;
        }
    } else {
        /**< Invalid channel number or DigitalValue pointer is NULL */
        Local_ErrorStatus = E_NOT_OK;
    }

    return Local_ErrorStatus;
}

Std_ReturnType ADC_GetDigitalValueAsync(u8 ChannelNb, ADC_NotificationCallback_t callbackFunction) {
    Std_ReturnType Local_ErrorStatus = E_OK; /**< Local variable to hold the error status */

    /**< Check if the callback function pointer is valid and the ADC is not busy */
    if ((callbackFunction != NULL) && (ADC_BusyFlag == 0)) {
        /**< Set Flag to indicate ADC is Busy */
        ADC_BusyFlag = 1;

        /**< Update Global Pointer to the provided callback function */
        callback = callbackFunction;

        /**< Enable ADC Interrupt */
        SET_BIT(ADC_ADCSRA_REG, 3);

        /**< Clear MUX[4..0] */
        ADC_ADMUX_REG &= 0b11100000;

        /**< Select the specified channel */
        ADC_ADMUX_REG |= ChannelNb;

        /**< Start Conversion */
        SET_BIT(ADC_ADCSRA_REG, 6);
    } else {
        /**< Either the callback function pointer is invalid, or the ADC is already busy */
        Local_ErrorStatus = E_NOT_OK;
    }

    return Local_ErrorStatus;
}

Std_ReturnType ADC_GetADCRegValue(u16 *ADCValue) {
    Std_ReturnType Local_ErrorStatus = E_OK; /**< Local variable to hold the error status */

    /* Check if the pointer to ADCValue is not NULL */
    if (ADCValue != NULL) {
        /* Read ADC Register */
        *ADCValue = ADC_ADC_REG;
    } else {
        /* Pointer to ADCValue is NULL */
        Local_ErrorStatus = E_NOT_OK;
    }

    return Local_ErrorStatus;
}
/*****************************< INTERRUPT SERVICE ROUTINE SECTION *****************************/
/**
 * @brief ADC Interrupt Service Routine (ISR) prototype.
 *
 * This function is the prototype for the ADC Interrupt Service Routine (ISR).
 * It is used to handle the ADC conversion complete interrupt.
 */
void __vector_16(void) __attribute__((signal));

/**
 * @brief ADC Interrupt Service Routine (ISR).
 *
 * This ISR is called when an ADC conversion is complete.
 * It clears the ADC busy flag, disables ADC interrupts, and calls the notification function if available.
 */
void __vector_16(void) {
    /* Check if a notification function is registered */
    if(callback != NULL) {
        /**< Clear ADC Busy Flag */
        ADC_BusyFlag = 0;
        /**< Clear ADC Interrupt Enable */
        CLR_BIT(ADC_ADCSRA_REG, 3);
        /**< Call the notification function */
        callback(ADC_ADC_REG);
    }
}

