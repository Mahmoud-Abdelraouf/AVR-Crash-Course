/*
 * main.c
 *
 *  Created on: Feb 5, 2024
 *      Author: Mahmoud Abdelraouf
 */

/**< LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/**< MCAL */
#include "DIO_interface.h"
#include <util/delay.h>

/**< APP */
int main(void) {
	/**< voidInit */
	DIO_SetPinDirection(DIO_PORTA, DIO_PIN2, DIO_OUTPUT);

	DIO_SetPinValue(DIO_PORTA, DIO_PIN2, DIO_HIGH);
	/**< super loop */
	while(1);


}

