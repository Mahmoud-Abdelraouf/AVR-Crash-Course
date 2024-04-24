/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 5 Feb 2023                 *****************/
/******* Version   : 1.0.0                      *****************/
/******* File Name : main.c                     *****************/
/****************************************************************/
/**< LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/**< MCAL */
#include "DIO_interface.h"
/**< HAL */
#include "CLCD_interface.h"
/**< Business Logic */
int main() {

	/**< DIO Init */


	/**< LCD Init */
	LCD_Config_t lcd1;

	lcd1.mode = LCD_4BitMode;
	lcd1.enablePin.LCD_PortId = DIO_PORTA;
	lcd1.enablePin.LCD_PinId = DIO_PIN4;

	lcd1.rsPin.LCD_PortId = DIO_PORTA;
	lcd1.rsPin.LCD_PinId = DIO_PIN5;

	for(uint8_t i = 0; i < 4; i++) {
		lcd1.dataPins[i].LCD_PortId = DIO_PORTA;
		lcd1.dataPins[i].LCD_PinId = DIO_PIN3 - i;
	}

	LCD_Init(&lcd1);

	LCD_SendString(&lcd1, "Sue");

	while(1);
}
