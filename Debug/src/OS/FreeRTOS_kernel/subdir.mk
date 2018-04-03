################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/OS/FreeRTOS_kernel/croutine.c \
../src/OS/FreeRTOS_kernel/event_groups.c \
../src/OS/FreeRTOS_kernel/heap_1.c \
../src/OS/FreeRTOS_kernel/list.c \
../src/OS/FreeRTOS_kernel/port.c \
../src/OS/FreeRTOS_kernel/queue.c \
../src/OS/FreeRTOS_kernel/tasks.c \
../src/OS/FreeRTOS_kernel/timers.c 

OBJS += \
./src/OS/FreeRTOS_kernel/croutine.o \
./src/OS/FreeRTOS_kernel/event_groups.o \
./src/OS/FreeRTOS_kernel/heap_1.o \
./src/OS/FreeRTOS_kernel/list.o \
./src/OS/FreeRTOS_kernel/port.o \
./src/OS/FreeRTOS_kernel/queue.o \
./src/OS/FreeRTOS_kernel/tasks.o \
./src/OS/FreeRTOS_kernel/timers.o 

C_DEPS += \
./src/OS/FreeRTOS_kernel/croutine.d \
./src/OS/FreeRTOS_kernel/event_groups.d \
./src/OS/FreeRTOS_kernel/heap_1.d \
./src/OS/FreeRTOS_kernel/list.d \
./src/OS/FreeRTOS_kernel/port.d \
./src/OS/FreeRTOS_kernel/queue.d \
./src/OS/FreeRTOS_kernel/tasks.d \
./src/OS/FreeRTOS_kernel/timers.d 


# Each subdirectory must supply rules for building sources it contributes
src/OS/FreeRTOS_kernel/%.o: ../src/OS/FreeRTOS_kernel/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/yama/Desktop/workspace/WorkStation/src" -I"/home/yama/Desktop/workspace/WorkStation/src/Configure" -I"/home/yama/Desktop/workspace/WorkStation/src/MID" -I"/home/yama/Desktop/workspace/WorkStation/src/MID/ConfigManagement" -I"/home/yama/Desktop/workspace/WorkStation/src/MID/Monitor" -I"/home/yama/Desktop/workspace/WorkStation/src/MID/NetWork" -I"/home/yama/Desktop/workspace/WorkStation/src/MID/Performance Management" -I"/home/yama/Desktop/workspace/WorkStation/src/MID/PostOffice" -I"/home/yama/Desktop/workspace/WorkStation/src/MID/Signal" -I"/home/yama/Desktop/workspace/WorkStation/src/OS" -I"/home/yama/Desktop/workspace/WorkStation/src/OS/FreeRTOS_kernel" -I"/home/yama/Desktop/workspace/WorkStation/src/PHY" -I"/home/yama/Desktop/workspace/WorkStation/src/PHY/Lib" -I"/home/yama/Desktop/workspace/WorkStation/src/PHY/Lib/cmsis_core" -I"/home/yama/Desktop/workspace/WorkStation/src/PHY/Lib/cmsis_lib" -I"/home/yama/Desktop/workspace/WorkStation/src/PHY/Lib/cmsis_lib/stm32f4xx" -I"/home/yama/Desktop/workspace/WorkStation/src/PHY/MCU" -I"/home/yama/Desktop/workspace/WorkStation/src/PHY/MCU/ARM" -I"/home/yama/Desktop/workspace/WorkStation/src/PHY/MCU/ARM/stm32f4xx" -I"/home/yama/Desktop/workspace/WorkStation/src/PHY/Peripheral" -I"/home/yama/Desktop/workspace/WorkStation/src/PHY/Peripheral/DriveLed" -I"/home/yama/Desktop/workspace/WorkStation/src/PHY/Peripheral/EthernetENC28J60" -I"/home/yama/Desktop/workspace/WorkStation/src/PHY/Peripheral/LCD1202" -I"/home/yama/Desktop/workspace/WorkStation/src/PHY/Peripheral/LCD5110" -I"/home/yama/Desktop/workspace/WorkStation/src/PHY/Peripheral/ReadTemperature" -I"/home/yama/Desktop/workspace/WorkStation/src/semihosting" -I"/home/yama/Desktop/workspace/WorkStation/src/semihosting/console" -I"/home/yama/Desktop/workspace/WorkStation/src/semihosting/log" -I"/home/yama/Desktop/workspace/WorkStation/src/semihosting/newlib" -std=gnu11 -c -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -std=gnu90 -O0 -ffunction-sections -fdata-sections -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


