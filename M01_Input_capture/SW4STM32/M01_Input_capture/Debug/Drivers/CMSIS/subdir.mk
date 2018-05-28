################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Git/Marek/STM32work/M01_Input_capture/Src/system_stm32f3xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32f3xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32f3xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32f3xx.o: C:/Git/Marek/STM32work/M01_Input_capture/Src/system_stm32f3xx.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F303xC -I"C:/Git/Marek/STM32work/M01_Input_capture/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


