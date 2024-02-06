/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 5 Feb 2023                 *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : CLCD_program.c             *****************/
/****************************************************************/

/*****************************< LIB *****************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/*****************************< MCAL *****************************/
#include "DIO_interface.h"
#include <util/delay.h>
/*****************************< HAL *****************************/
#include "CLCD_interface.h"
#include "CLCD_private.h"
#include "CLCD_config.h"

/*****************************< Function Implementations *****************************/
void LCD_Init(const LCD_Config_t *config) 
{
    if(config == NULL)
    {
        return;
    }

    /**< Init the Mode of the en, rs, rw */
    DIO_SetPortDirection(config->enablePin.LCD_PortId, config->enablePin.LCD_PinId, DIO_OUTPUT);
    DIO_SetPortDirection(config->rsPin.LCD_PortId, config->rsPin.LCD_PinId, DIO_OUTPUT);
    DIO_SetPortDirection(config->rwPin.LCD_PortId, config->rwPin.LCD_PinId, DIO_OUTPUT);

    if(config->mode == LCD_4BitMode)
    {
        /**< Init the Mode of Data Pins */
        for(uint8_t i = 0; i < 4; i++)
        {
            DIO_SetPortDirection(config->dataPins[i].LCD_PortId, config->dataPins[i].LCD_PinId, DIO_OUTPUT);
        }
    }
    else if(LCD_8BitMode)
    {
        for(uint8_t i = 0; i < 8; i++)
        {
            DIO_SetPortDirection(config->dataPins[i].LCD_PortId, config->dataPins[i].LCD_PinId, DIO_OUTPUT);
        }
    }
    else
    {
        return;
    }
    
    _delay_ms(20);
    LCD_SendCommand(config, _LCD_8BIT_MODE_2_LINE);
    _delay_ms(5);
    LCD_SendCommand(config, _LCD_8BIT_MODE_2_LINE);
    _delay_us(150);
    LCD_SendCommand(config, _LCD_8BIT_MODE_2_LINE);

    LCD_SendCommand(config, _LCD_CLEAR);
    LCD_SendCommand(config, _LCD_RETURN_HOME);
    LCD_SendCommand(config, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
    LCD_SendCommand(config, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
    if(config->mode == LCD_4BitMode)
    {
        LCD_SendCommand(config, _LCD_4BIT_MODE_2_LINE);
    }
    LCD_SendCommand(config, 0x80);
}

void LCD_SendCommand(const LCD_Config_t *config, uint8_t command) 
{
    /**< Set RS pin to low for command --> RS = 0 */
    DIO_SetPinValue(config->rsPin.LCD_PortId, config->rsPin.LCD_PinId, DIO_LOW);
    /**< Set RW pin to low for write  --> RW = 0 */
    DIO_SetPinValue(config->rwPin.LCD_PortId, config->rwPin.LCD_PinId, DIO_LOW);

    if(config->mode == LCD_4BitMode)
    {
        HAL_LCD_Send4Bits(config, command);
    }
    else if(config->mode == LCD_8BitMode)
    {
        HAL_LCD_Send8Bits(config, command);
    }
    else
    {
        return;
    }
}

void LCD_SendChar(const LCD_Config_t *config, uint8_t character) 
{
    /**< Set RS pin to low for command --> RS = 0 */
    DIO_SetPinValue(config->rsPin.LCD_PortId, config->rsPin.LCD_PinId, DIO_HIGH);
    /**< Set RW pin to low for write  --> RW = 0 */
    DIO_SetPinValue(config->rwPin.LCD_PortId, config->rwPin.LCD_PinId, DIO_LOW);

    if(config->mode == LCD_4BitMode)
    {
        HAL_LCD_Send4Bits(config, character);
    }
    else if(config->mode == LCD_8BitMode)
    {
        HAL_LCD_Send8Bits(config, character);
    }
    else
    {
        return;
    }
}

void LCD_SendString(const LCD_Config_t *config, const uint8_t *string) 
{
    uint8_t Local_Counter = 0;
    
    while(string[Local_Counter] != '\0')
    {
        LCD_SendChar(config, string[Local_Counter]);
        Local_Counter++;
    }
}

/*****************************< Private helper function to send 4 bits *****************************/ 
static void HAL_LCD_Send4Bits(const LCD_Config_t *config, uint8_t value) 
{
    /**< Send the 4-MSB */
    for(uint8_t i = 0; i < 4; i++)
    {
        DIO_SetPinValue(config->dataPins[i].LCD_PortId, config->dataPins[i].LCD_PinId, value >> (4 + i) & 0x01);
    }

    /**< Set the enable pin to high */
    DIO_SetPinValue(config->enablePin.LCD_PortId, config->enablePin.LCD_PinId, DIO_HIGH);
    /**< Set the Pulse time to be 5msec */
    MCAL_STK_SetDelay_ms(5);
    /**< Set the enable pin to low */
    DIO_SetPinValue(config->enablePin.LCD_PortId, config->enablePin.LCD_PinId, DIO_LOW);

    /**< Shift the 4-LSB command to the 4-MSB */
    value <<= 4;

    /**< Send the 4-LSB */
    for(uint8_t i = 0; i < 4; i++)
    {
        MCAL_GPIO_SetPinValue(config->dataPins[i].LCD_PortId, config->dataPins[i].LCD_PinId, value >> (4 + i) & 0x01);
    }

    /**< Set the enable pin to high */
    DIO_SetPinValue(config->enablePin.LCD_PortId, config->enablePin.LCD_PinId, DIO_HIGH);
    /**< Set the Pulse time to be 5msec */
    MCAL_STK_SetDelay_ms(5);
    /**< Set the enable pin to low */
    DIO_SetPinValue(config->enablePin.LCD_PortId, config->enablePin.LCD_PinId, DIO_LOW);
}

/*****************************< Private helper function to send 8 bits *****************************/ 
static void HAL_LCD_Send8Bits(const LCD_Config_t *config, uint8_t value) 
{
     /**< Send the 8-Bit */
    for(uint8_t i = 0; i < 8; i++)
    {
        DIO_SetPinValue(config->dataPins[i].LCD_PortId, config->dataPins[i].LCD_PinId, value >> i & 0x01);
    }

    /**< Set the enable pin to high */
    DIO_SetPinValue(config->enablePin.LCD_PortId, config->enablePin.LCD_PinId, DIO_HIGH);
    /**< Set the Pulse time to be 5msec */
    MCAL_STK_SetDelay_ms(5);
    /**< Set the enable pin to low */
    DIO_SetPinValue(config->enablePin.LCD_PortId, config->enablePin.LCD_PinId, DIO_LOW);
}
