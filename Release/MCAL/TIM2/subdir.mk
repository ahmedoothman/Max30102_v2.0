################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/TIM2/TIM2_prg.c 

OBJS += \
./MCAL/TIM2/TIM2_prg.o 

C_DEPS += \
./MCAL/TIM2/TIM2_prg.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/TIM2/%.o: ../MCAL/TIM2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


