################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/MID/main.c 

OBJS += \
./src/MID/main.o 

C_DEPS += \
./src/MID/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/MID/%.o: ../src/MID/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/yama/Documents/Embedded/WorkStation-master/src/Configure" -I"/home/yama/Documents/Embedded/WorkStation-master/src" -I"/home/yama/Documents/Embedded/WorkStation-master/src/Configure" -I"/home/yama/Documents/Embedded/WorkStation-master/src/MID" -I"/home/yama/Documents/Embedded/WorkStation-master/src/MID/ConfigManagement" -I"/home/yama/Documents/Embedded/WorkStation-master/src/MID/Monitor" -I"/home/yama/Documents/Embedded/WorkStation-master/src/MID/NetWork" -I"/home/yama/Documents/Embedded/WorkStation-master/src/MID/Performance Management" -I"/home/yama/Documents/Embedded/WorkStation-master/src/MID/PostOffice" -I"/home/yama/Documents/Embedded/WorkStation-master/src/MID/Signal" -I"/home/yama/Documents/Embedded/WorkStation-master/src/OS" -I"/home/yama/Documents/Embedded/WorkStation-master/src/OS/FreeRTOS_kernel" -I"/home/yama/Documents/Embedded/WorkStation-master/src/PHY" -I"/home/yama/Documents/Embedded/WorkStation-master/src/PHY/Lib" -I"/home/yama/Documents/Embedded/WorkStation-master/src/PHY/Lib/cmsis_core" -I"/home/yama/Documents/Embedded/WorkStation-master/src/PHY/Lib/cmsis_lib" -I"/home/yama/Documents/Embedded/WorkStation-master/src/PHY/Lib/cmsis_lib/stm32f4xx" -I"/home/yama/Documents/Embedded/WorkStation-master/src/PHY/MCU" -I"/home/yama/Documents/Embedded/WorkStation-master/src/PHY/MCU/ARM" -I"/home/yama/Documents/Embedded/WorkStation-master/src/PHY/MCU/ARM/stm32f4xx" -I"/home/yama/Documents/Embedded/WorkStation-master/src/PHY/Peripheral" -I"/home/yama/Documents/Embedded/WorkStation-master/src/PHY/Peripheral/DriveLed" -I"/home/yama/Documents/Embedded/WorkStation-master/src/PHY/Peripheral/EthernetENC28J60" -I"/home/yama/Documents/Embedded/WorkStation-master/src/PHY/Peripheral/LCD1202" -I"/home/yama/Documents/Embedded/WorkStation-master/src/PHY/Peripheral/LCD5110" -I"/home/yama/Documents/Embedded/WorkStation-master/src/PHY/Peripheral/ReadTemperature" -I"/home/yama/Documents/Embedded/WorkStation-master/src/semihosting" -I"/home/yama/Documents/Embedded/WorkStation-master/src/semihosting/log" -I"/home/yama/Documents/Embedded/WorkStation-master/src/semihosting/newlib" -I"/home/yama/Documents/Embedded/WorkStation-master/src/PHY/Peripheral/LCD5110" -I"/home/yama/Documents/Embedded/WorkStation-master/src/MID/ConfigManagement" -I"/home/yama/Documents/Embedded/WorkStation-master/src/MID/PostOffice" -I"/home/yama/Documents/Embedded/WorkStation-master/src/MID/Signal" -I"/home/yama/Documents/Embedded/WorkStation-master/src/MID/Performance Management" -I"/home/yama/Documents/Embedded/WorkStation-master/src/MID/Monitor" -I"/home/yama/Documents/Embedded/WorkStation-master/src/PHY/Peripheral/DriveLed" -I"/home/yama/Documents/Embedded/WorkStation-master/src/PHY/Peripheral/EthernetENC28J60" -I"/home/yama/Documents/Embedded/WorkStation-master/src/PHY/Peripheral/ReadTemperature" -I"/home/yama/Documents/Embedded/WorkStation-master/src/MID" -I"/home/yama/Documents/Embedded/WorkStation-master/src/OS/FreeRTOS_kernel" -I"/home/yama/Documents/Embedded/WorkStation-master/src/PHY/Lib/cmsis_core" -I"/home/yama/Documents/Embedded/WorkStation-master/src/PHY/Lib/cmsis_lib/stm32f4xx" -I"/home/yama/Documents/Embedded/WorkStation-master/src/PHY/MCU/ARM/stm32f4xx" -I"/home/yama/Documents/Embedded/WorkStation-master/src/PHY/Peripheral/LCD1202" -std=gnu11 -c -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -std=gnu90 -O0 -ffunction-sections -fdata-sections -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


