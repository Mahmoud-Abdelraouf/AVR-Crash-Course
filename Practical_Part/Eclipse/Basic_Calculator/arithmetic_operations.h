/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 18 Mar 2024                *****************/
/******* Version   : 1.0.0                      *****************/
/******* File Name : arithmetic_operations.h    *****************/
/****************************************************************/

/*****************************< Function Implementations *****************************/
/**
 * @brief Perform addition of two integers.
 *
 * This function adds two integers and returns the result.
 *
 * @param num1 The first integer operand.
 * @param num2 The second integer operand.
 * @return The result of the addition operation.
 */
int add(int num1, int num2) {
    return num1 + num2;
}

/**
 * @brief Perform subtraction of two integers.
 *
 * This function subtracts the second integer from the first integer and returns the result.
 *
 * @param num1 The first integer operand (minuend).
 * @param num2 The second integer operand (subtrahend).
 * @return The result of the subtraction operation.
 */
int subtract(int num1, int num2) {
    return num1 - num2;
}

/**
 * @brief Perform multiplication of two integers.
 *
 * This function multiplies two integers and returns the result.
 *
 * @param num1 The first integer operand.
 * @param num2 The second integer operand.
 * @return The result of the multiplication operation.
 */
int multiply(int num1, int num2) {
    return num1 * num2;
}

/**
 * @brief Perform division of two integers.
 *
 * This function divides the first integer by the second integer and returns the result.
 * If the second integer is zero, it returns an error value (-1).
 *
 * @param num1 The dividend.
 * @param num2 The divisor.
 * @return The result of the division operation, or an error value if division by zero occurs.
 */
double divide(int num1, int num2) {
    if (num2 != 0) {
        return ((double)num1 / num2);
    } else {
        /**< Division by zero, handle error */
        return -1; /**< Return a suitable error value */
    }
}
