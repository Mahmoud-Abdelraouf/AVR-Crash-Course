/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 5 Feb 2023                 *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : CLCD_interface.h           *****************/
/****************************************************************/
#ifndef CLCD_INTERFACE_H
#define CLCD_INTERFACE_H



/**
 * @brief Enum defining LCD operation modes.
 */
typedef enum {
    LCD_4BitMode = 4, /**< 4-bit mode */
    LCD_8BitMode = 8  /**< 8-bit mode */
} LCD_Mode_t;

/**
 * @brief Structure representing LCD pin configuration.
 */
typedef struct {
    uint8_t LCD_PortId: 2;  /**< Port ID for the LCD pin */
    uint8_t LCD_PinId: 4;   /**< Pin ID for the LCD pin */
    uint8_t :2;             /**< Padding */
} LCD_PinConfig_t;

/**
 * @brief Structure representing LCD configuration.
 */
typedef struct {
    uint8_t mode;                /**< 8-bit or 4-bit mode indicator */
    LCD_PinConfig_t dataPins[8]; /**< Maximum pins for 8-bit mode */
    LCD_PinConfig_t rsPin;       /**< RS pin */
    LCD_PinConfig_t rwPin;       /**< R/W pin */
    LCD_PinConfig_t enablePin;   /**< Enable pin */
} LCD_Config_t;

/**
 * @brief Sends a command to the LCD module.
 *
 * This function sends a command to the LCD module based on the provided configuration.
 * It sets the RS pin to low for command mode and the RW pin to low for write operation.
 * Depending on the configured mode (4-bit or 8-bit), it calls the corresponding function
 * to send the command.
 *
 * @param[in] config Pointer to the LCD configuration structure.
 * @param[in] command The command to be sent to the LCD.
 * @note This function assumes that the required GPIO module has been initialized separately.
 * @warning If the mode in the configuration is neither 4-bit nor 8-bit, the function returns without action.
 */
void LCD_SendCommand(const LCD_Config_t *config, uint8_t command);

/**
 * @brief Sends a character to the LCD module for display.
 *
 * This function sends a character to the LCD module based on the provided configuration.
 * It sets the RS pin to high for data mode and the RW pin to low for write operation.
 * Depending on the configured mode (4-bit or 8-bit), it calls the corresponding function
 * to send the character.
 *
 * @param[in] config Pointer to the LCD configuration structure.
 * @param[in] character The character to be sent to the LCD for display.
 * @note This function assumes that the required GPIO module has been initialized separately.
 * @warning If the mode in the configuration is neither 4-bit nor 8-bit, the function returns without action.
 */
void LCD_SendChar(const LCD_Config_t *config, uint8_t character);

/**
 * @brief Sends a null-terminated string to the LCD for display.
 *
 * This function sends a null-terminated string to the LCD module for display
 * based on the provided configuration. It iterates through the characters of
 * the string and sends each character to the LCD using the LCD_SendChar function.
 *
 * @param[in] config Pointer to the LCD configuration structure.
 * @param[in] string Pointer to the null-terminated string to be displayed on the LCD.
 * @note This function assumes that the required GPIO module and LCD character functions have been initialized separately.
 */
void LCD_SendString(const LCD_Config_t *config, const uint8_t *string);


#endif /**< CLCD_INTERFACE_H */

