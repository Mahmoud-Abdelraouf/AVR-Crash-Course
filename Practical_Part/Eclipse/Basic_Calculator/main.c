/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 18 Mar 2024                *****************/
/******* Version   : 1.0.0                      *****************/
/******* File Name : main.c                     *****************/
/****************************************************************/

/*****************************< LIB *****************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"
/*****************************< MCAL *****************************/
#include "DIO_interface.h"
/*****************************< HAL *****************************/
#include "CLCD_interface.h"
#include "KPD_interface.h"
/*****************************< Business Logic *****************************/
int main(void) {

	/*****************************< Init Sector *****************************/
	/**<--------------------< LCD Configuration --------------------*/
	// Declare an instance of LCD configuration structure.
	LCD_Config_t lcd1;

	// Set the mode of operation to 4-bit mode.
	lcd1.mode = LCD_4BitMode;

	// Configure data pins for 4-bit mode operation.
	for (u8 i = 0; i < 4; i++) {
	    // Set the port ID for data pin i to DIO_PORTA.
	    lcd1.dataPins[i].LCD_PortId = DIO_PORTA;
	    // Set the pin ID for data pin i using DIO_PIN3 - i.
	    lcd1.dataPins[i].LCD_PinId = DIO_PIN3 - i;
	}

	// Configure enable pin.
	// Set the port ID for the enable pin to DIO_PORTA.
	lcd1.enablePin.LCD_PortId = DIO_PORTA;
	// Set the pin ID for the enable pin to DIO_PIN4.
	lcd1.enablePin.LCD_PinId = DIO_PIN4;

	// Configure rs pin.
	// Set the port ID for the rs pin to DIO_PORTA.
	lcd1.rsPin.LCD_PortId = DIO_PORTA;
	// Set the pin ID for the rs pin to DIO_PIN5.
	lcd1.rsPin.LCD_PinId = DIO_PIN5;

	// Initialize the LCD module with the configured settings.
	LCD_Init(&lcd1);

	/**<--------------------< KPD Configuration --------------------*/
	// Configure data pins for rows and columns
	for (u8 i = 0; i < 4; i++) {
	    // Set the direction of the pin corresponding to the row to OUTPUT
	    DIO_SetPinDirection(DIO_PORTB, DIO_PIN0 + i, DIO_OUTPUT); // Rows
	    // Set the direction of the pin corresponding to the column to INPUT
	    DIO_SetPinDirection(DIO_PORTB, DIO_PIN4 + i, DIO_INPUT); // Columns
	}

	// Variable to store the value of the pressed key
	u8 pressedKey;

	// Loop indefinitely
	while (1) {
	    // Check if a key is pressed
	    if (KPD_GetKeyState(&pressedKey) == E_OK) {
	        // If a key is pressed, send its value to the LCD module
	        LCD_SendString(&lcd1, (uint8_t *)&pressedKey);
	    }
	}
}
