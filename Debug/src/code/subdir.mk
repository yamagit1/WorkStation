################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/code/main.c 

OBJS += \
./src/code/main.o 

C_DEPS += \
./src/code/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/code/%.o: ../src/code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/yama/eclipse-workspace/WorkStation/src/code" -I"/home/yama/eclipse-workspace/WorkStation/src/OS/FreeRTOS_kernel" -I"/home/yama/eclipse-workspace/WorkStation/src/PHY/Lib/cmsis_core" -I"/home/yama/eclipse-workspace/WorkStation/src/PHY/Lib/cmsis_lib/stm32f4xx" -I"/home/yama/eclipse-workspace/WorkStation/src/PHY/MCU/ARM/stm32f4xx" -I"/home/yama/eclipse-workspace/WorkStation/src/PHY/MCU/ATMega/ArduinoUNO" -std=gnu11 -c -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -std=gnu90 -O0 -ffunction-sections -fdata-sections -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


