################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/UART/subdir.mk
-include MCAL/TWI/subdir.mk
-include MCAL/TIMER/subdir.mk
-include MCAL/GIE/subdir.mk
-include MCAL/EXTI/subdir.mk
-include MCAL/DIO/subdir.mk
-include HAL/HR_OXIMETER/subdir.mk
-include App/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Max30102_v2.0.lss \

FLASH_IMAGE += \
Max30102_v2.0.hex \

EEPROM_IMAGE += \
Max30102_v2.0.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Max30102_v2.0.elf secondary-outputs

# Tool invocations
Max30102_v2.0.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Max30102_v2.0.map -mmcu=atmega32 -o "Max30102_v2.0.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Max30102_v2.0.lss: Max30102_v2.0.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Max30102_v2.0.elf  >"Max30102_v2.0.lss"
	@echo 'Finished building: $@'
	@echo ' '

Max30102_v2.0.hex: Max30102_v2.0.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Max30102_v2.0.elf  "Max30102_v2.0.hex"
	@echo 'Finished building: $@'
	@echo ' '

Max30102_v2.0.eep: Max30102_v2.0.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Max30102_v2.0.elf  "Max30102_v2.0.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Max30102_v2.0.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Max30102_v2.0.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Max30102_v2.0.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
