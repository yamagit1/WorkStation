################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/PHY/MCU/ARM/stm32f4xx/FreeRTOSHook.c \
../src/PHY/MCU/ARM/stm32f4xx/startup_stm32f4xx.c \
../src/PHY/MCU/ARM/stm32f4xx/system_stm32f4xx.c 

OBJS += \
./src/PHY/MCU/ARM/stm32f4xx/FreeRTOSHook.o \
./src/PHY/MCU/ARM/stm32f4xx/startup_stm32f4xx.o \
./src/PHY/MCU/ARM/stm32f4xx/system_stm32f4xx.o 

C_DEPS += \
./src/PHY/MCU/ARM/stm32f4xx/FreeRTOSHook.d \
./src/PHY/MCU/ARM/stm32f4xx/startup_stm32f4xx.d \
./src/PHY/MCU/ARM/stm32f4xx/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/PHY/MCU/ARM/stm32f4xx/%.o: ../src/PHY/MCU/ARM/stm32f4xx/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/yama/eclipse-workspace/WorkStation/src/Configure" -I"/home/yama/eclipse-workspace/WorkStation/src/APP/SchedulingShareMemory" -I"/home/yama/eclipse-workspace/WorkStation/src/APP/SchedulingShareProcess" -I"/home/yama/eclipse-workspace/WorkStation/src/MID/ConfigManagement" -I"/home/yama/eclipse-workspace/WorkStation/src/MID/PostOffice" -I"/home/yama/eclipse-workspace/WorkStation/src/MID/Signal" -I"/home/yama/eclipse-workspace/WorkStation/src/MID/Performance Management" -I"/home/yama/eclipse-workspace/WorkStation/src/MID/Monitor" -I"/home/yama/eclipse-workspace/WorkStation/src/PHY/Peripheral/DriveLed" -I"/home/yama/eclipse-workspace/WorkStation/src/PHY/Peripheral/EthernetENC28J60" -I"/home/yama/eclipse-workspace/WorkStation/src/PHY/Peripheral/ReadTemperature" -I"/home/yama/eclipse-workspace/WorkStation/src/MID" -I"/home/yama/eclipse-workspace/WorkStation/src/OS/FreeRTOS_kernel" -I"/home/yama/eclipse-workspace/WorkStation/src/PHY/Lib/cmsis_core" -I"/home/yama/eclipse-workspace/WorkStation/src/PHY/Lib/cmsis_lib/stm32f4xx" -I"/home/yama/eclipse-workspace/WorkStation/src/PHY/MCU/ARM/stm32f4xx" -I"/home/yama/eclipse-workspace/WorkStation/src/PHY/MCU/ATMega/ArduinoUNO" -I"/home/yama/eclipse-workspace/WorkStation/src/PHY/Peripheral/LCD1202" -std=gnu11 -c -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -std=gnu90 -O0 -ffunction-sections -fdata-sections -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

