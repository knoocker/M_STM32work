################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal.c \
C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cortex.c \
C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dma.c \
C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash.c \
C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash_ex.c \
C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_gpio.c \
C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c \
C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c_ex.c \
C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr.c \
C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr_ex.c \
C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc.c \
C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc_ex.c \
C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim.c \
C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim_ex.c 

OBJS += \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal.o \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_cortex.o \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_dma.o \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_flash.o \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_flash_ex.o \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_gpio.o \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_i2c.o \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_i2c_ex.o \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_pwr.o \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_pwr_ex.o \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_rcc.o \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_rcc_ex.o \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_tim.o \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_tim_ex.o 

C_DEPS += \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal.d \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_cortex.d \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_dma.d \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_flash.d \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_flash_ex.d \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_gpio.d \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_i2c.d \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_i2c_ex.d \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_pwr.d \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_pwr_ex.d \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_rcc.d \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_rcc_ex.d \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_tim.d \
./Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_tim_ex.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal.o: C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F303xC -I"C:/Git/Marek/STM32work/M01_Input_capture/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_cortex.o: C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cortex.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F303xC -I"C:/Git/Marek/STM32work/M01_Input_capture/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_dma.o: C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dma.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F303xC -I"C:/Git/Marek/STM32work/M01_Input_capture/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_flash.o: C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F303xC -I"C:/Git/Marek/STM32work/M01_Input_capture/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_flash_ex.o: C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash_ex.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F303xC -I"C:/Git/Marek/STM32work/M01_Input_capture/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_gpio.o: C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F303xC -I"C:/Git/Marek/STM32work/M01_Input_capture/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_i2c.o: C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F303xC -I"C:/Git/Marek/STM32work/M01_Input_capture/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_i2c_ex.o: C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c_ex.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F303xC -I"C:/Git/Marek/STM32work/M01_Input_capture/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_pwr.o: C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F303xC -I"C:/Git/Marek/STM32work/M01_Input_capture/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_pwr_ex.o: C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr_ex.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F303xC -I"C:/Git/Marek/STM32work/M01_Input_capture/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_rcc.o: C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F303xC -I"C:/Git/Marek/STM32work/M01_Input_capture/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_rcc_ex.o: C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc_ex.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F303xC -I"C:/Git/Marek/STM32work/M01_Input_capture/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_tim.o: C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F303xC -I"C:/Git/Marek/STM32work/M01_Input_capture/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/STM32F3xx_HAL_Driver/stm32f3xx_hal_tim_ex.o: C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim_ex.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F303xC -I"C:/Git/Marek/STM32work/M01_Input_capture/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"C:/Git/Marek/STM32work/M01_Input_capture/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


