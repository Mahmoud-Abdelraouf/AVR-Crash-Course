/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 25 Mar 2024                *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : main.c                     *****************/
/****************************************************************/

#define F_CPU 16000000UL
/*****************************< LIB *****************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"
/*****************************< MCAL *****************************/
#include "DIO_interface.h"
/*****************************< HAL *****************************/
#include "CLCD_interface.h"
/*****************************< APP *****************************/

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
		lcd1.dataPins[i].LCD_PinId = DIO_PIN3 + i;
	}

	// Configure enable pin.
	// Set the port ID for the enable pin to DIO_PORTA.
	lcd1.enablePin.LCD_PortId = DIO_PORTA;
	// Set the pin ID for the enable pin to DIO_PIN4.
	lcd1.enablePin.LCD_PinId = DIO_PIN2;

	// Configure rs pin.
	// Set the port ID for the rs pin to DIO_PORTA.
	lcd1.rsPin.LCD_PortId = DIO_PORTA;
	// Set the pin ID for the rs pin to DIO_PIN5.
	lcd1.rsPin.LCD_PinId = DIO_PIN1;

	// Initialize the LCD module with the configured settings.
	LCD_Init(&lcd1);
	LCD_Clear(&lcd1);

	/**-----------------------< Display "Suhaylla" in Arabic -----------------*/
	/**---< Define the Arabic characters in Unicode values ---*/
	/**< Define the CustomChar_t object for each character */
	CustomChar_t seenChar = {
		.pattern = {0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x02, 0x0C}, // "س"
		.charIndex = 0
	};
	CustomChar_t hehChar = {
		.pattern = {0x00, 0x00, 0x00, 0x18, 0x04, 0x1F, 0x04, 0x18},  // "ه"
		.charIndex = 1
	};
	CustomChar_t yehChar = {
		.pattern = {0x00, 0x00, 0x00, 0x01, 0x12, 0x01F, 0x02, 0x11},  // "ي"
		.charIndex = 2
	};
	CustomChar_t lamChar = {
		.pattern = {0x00, 0x02, 0x02, 0x12, 0x12, 0x1F, 0x00, 0x02},  // "ل"
		.charIndex = 3
	};
	CustomChar_t tehMarbutaChar = {
		.pattern = {0x05, 0x00, 0x07, 0x08, 0x09, 0x06, 0x00, 0x00}, // "ة"
		.charIndex = 4
	};

	/**< Define the custom characters on the LCD */
	LCD_DefineCustomChar(&lcd1, &seenChar);
	LCD_DefineCustomChar(&lcd1, &hehChar);
	LCD_DefineCustomChar(&lcd1, &yehChar);
	LCD_DefineCustomChar(&lcd1, &lamChar);
	LCD_DefineCustomChar(&lcd1, &tehMarbutaChar);

	// Display the characters
	LCD_GoToXYPos(&lcd1, LCD_ROW_1, LCD_COLUMN_1);
	LCD_SendChar(&lcd1, 4); /**< Display "ة" */
	LCD_SendChar(&lcd1, 3); /**< Display "ل" */
	LCD_SendChar(&lcd1, 2); /**< Display "ي" */
	LCD_SendChar(&lcd1, 1); /**< Display "ه" */
	LCD_SendChar(&lcd1, 0); /**< Display "س" */
	/*****************************< Loop indefinitely *****************************/
	while(1) {

	}
}
