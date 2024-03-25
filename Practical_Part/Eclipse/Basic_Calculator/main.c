/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 18 Mar 2024                *****************/
/******* Version   : 1.0.0                      *****************/
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
#include "KPD_interface.h"
/*****************************< APP *****************************/
#include "main.h"
#include "arithmetic_operations.h"
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

	/**< Display a welcome message */
	LCD_SendString(&lcd1, (uint8_t *)"Welcome to my");
	LCD_GoToXYPos(&lcd1, 0, 1);
	LCD_SendString(&lcd1, (uint8_t *)"Basic Calculator");

	// Add a short delay (e.g., 5 milliseconds)
	_delay_ms(1000);

	// Clear the LCD display
	LCD_Clear(&lcd1);


	/**<--------------------< KPD Configuration --------------------*/
	// Configure data pins for rows and columns
	for (u8 i = 0; i < 4; i++) {
	    // Set the direction of the pin corresponding to the row to OUTPUT
	    DIO_SetPinDirection(DIO_PORTB, DIO_PIN4 + i, DIO_OUTPUT); // Rows
	    // Set the direction of the pin corresponding to the column to INPUT
	    DIO_SetPinDirection(DIO_PORTD, DIO_PIN2 + i, DIO_INPUT); // Columns
	}

	// Variable to store the currently pressed key on the keypad
	uint8_t pressedKey = '\0';

    // Variable to store the result of the operation
    double result = 0;

    // Variable to store the operator
    char operator;

    // Variable to store the first and second operands
    int firstOperand = 0, secondOperand = 0;

    /*****************************< Loop indefinitely *****************************/
    while (1) {
        // Check if a key is pressed
        if (KPD_GetKeyState(&pressedKey) == E_OK) {
            // If a key is pressed, send its value to the LCD module
            LCD_SendString(&lcd1, (uint8_t *)&pressedKey);

            // Check if the pressed key is 'c' (clear)
            if (pressedKey == 'c') {
               // Clear the LCD display
               LCD_Clear(&lcd1);

               // Write new content to the LCD
               LCD_SendString(&lcd1, (uint8_t *)"Clearing...");
               // Add a short delay (e.g., 5 milliseconds)
			  _delay_ms(1000);

               // Clear the LCD display
               LCD_Clear(&lcd1);

               // Reset the operands and operator for the next calculation
			   firstOperand = 0;
			   secondOperand = 0;
			   operator = '\0';
            } else if (pressedKey >= '0' && pressedKey <= '9') {
                /**< If the pressed key is a numeric digit, handle it as before */
                // Convert the ASCII character to its numeric value
                int numericValue = ascii_to_numeric(pressedKey);

                // Update the operands based on the entered digits
                if (operator == '\0') {
                    // If no operator is entered yet, update the first operand
                    firstOperand = (firstOperand * 10) + numericValue;
                } else {
                    // If an operator is entered, update the second operand
                    secondOperand = (secondOperand * 10) + numericValue;
                }
            } else if (pressedKey == '+' || pressedKey == '-' || pressedKey == '*' || pressedKey == '/') {
                // If the pressed key is an operator (+, -, *, /), update the operator
                operator = pressedKey;
            } else if (pressedKey == '=') {
                // If the pressed key is '=', perform the calculation based on the operator
                switch (operator) {
                    case '+':
                        result = add(firstOperand, secondOperand);
                        break;
                    case '-':
                        result = subtract(firstOperand, secondOperand);
                        break;
                    case '*':
                        result = multiply(firstOperand, secondOperand);
                        break;
                    case '/':
                        result = divide(firstOperand, secondOperand);
                        break;
                    default:
                        // Handle invalid operator
                        result = -1; // Return a suitable error value
                        break;
                }
                // Display the result on the LCD using the appropriate function
                LCD_Clear(&lcd1);
                LCD_SendNumber(&lcd1, result); // Or LCD_SendIntegerNumber(&lcd1, result) for int result

                // Reset the operands and operator for the next calculation
                firstOperand = 0;
                secondOperand = 0;
                operator = '\0';
            }
        }
    }
}

/*****************************< Function Implementations *****************************/
int ascii_to_numeric(char ascii_char) {
    if (ascii_char >= '0' && ascii_char <= '9') {
        return ascii_char - '0';
    } else {
        // Handle error or invalid input
        return -1; // Return a suitable error value
    }
}
