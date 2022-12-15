################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/HR_OXIMETER/HR_OXIMETER_prg.c 

OBJS += \
./HAL/HR_OXIMETER/HR_OXIMETER_prg.o 

C_DEPS += \
./HAL/HR_OXIMETER/HR_OXIMETER_prg.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/HR_OXIMETER/%.o: ../HAL/HR_OXIMETER/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


