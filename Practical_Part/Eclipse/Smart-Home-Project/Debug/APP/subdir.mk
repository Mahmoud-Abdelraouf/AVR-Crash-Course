################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/main.c 

OBJS += \
./APP/main.o 

C_DEPS += \
./APP/main.d 


# Each subdirectory must supply rules for building sources it contributes
APP/%.o: ../APP/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Projects\Embedded\Bare_Matel\AVR-Crash-Course\Practical_Part\Eclipse\Smart-Home-Project\APP" -I"D:\Projects\Embedded\Bare_Matel\AVR-Crash-Course\Practical_Part\Eclipse\Smart-Home-Project\HAL" -I"D:\Projects\Embedded\Bare_Matel\AVR-Crash-Course\Practical_Part\Eclipse\Smart-Home-Project\MCAL" -I"D:\Projects\Embedded\Bare_Matel\AVR-Crash-Course\Practical_Part\Eclipse\Smart-Home-Project\LIB" -I"D:\Projects\Embedded\Bare_Matel\AVR-Crash-Course\Practical_Part\Eclipse\Smart-Home-Project\HAL\CLCD" -I/Smart_Home_project/HAL/KPD -I"D:\Projects\Embedded\Bare_Matel\AVR-Crash-Course\Practical_Part\Eclipse\Smart-Home-Project\MCAL\DIO" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


