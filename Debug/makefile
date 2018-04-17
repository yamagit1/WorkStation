################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/semihosting/newlib/subdir.mk
-include src/semihosting/log/subdir.mk
-include src/PHY/Peripheral/ReadTemperature/subdir.mk
-include src/PHY/Peripheral/LCD5110/subdir.mk
-include src/PHY/Peripheral/LCD1202/subdir.mk
-include src/PHY/Peripheral/EthernetENC28J60/subdir.mk
-include src/PHY/Peripheral/DriveLed/subdir.mk
-include src/PHY/MCU/ARM/stm32f4xx/subdir.mk
-include src/PHY/Lib/cmsis_lib/stm32f4xx/subdir.mk
-include src/OS/FreeRTOS_kernel/subdir.mk
-include src/MID/Signal/subdir.mk
-include src/MID/PostOffice/subdir.mk
-include src/MID/Performance\ Management/subdir.mk
-include src/MID/Monitor/subdir.mk
-include src/MID/ConfigManagement/subdir.mk
-include src/MID/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
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
SECONDARY_FLASH += \
WorkStation.bin \

SECONDARY_SIZE += \
WorkStation.siz \


# All Target
all: WorkStation.elf secondary-outputs

# Tool invocations
WorkStation.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM GNU C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "/home/yama/Desktop/workspace/WorkStation/ldscripts/LinkScript_stm32f4xx.ld" -Xlinker --gc-sections -Wl,-Map,"WorkStation.map" -o "WorkStation.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

WorkStation.bin: WorkStation.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary "WorkStation.elf"  "WorkStation.bin"
	@echo 'Finished building: $@'
	@echo ' '

WorkStation.siz: WorkStation.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "WorkStation.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) WorkStation.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
