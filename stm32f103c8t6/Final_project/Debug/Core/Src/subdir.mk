################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/CAN.c \
../Core/Src/HCompass_HMC5883L_3.c \
../Core/Src/HServo_Motor.c \
../Core/Src/MY_NRF24.c \
../Core/Src/Temperature_Battery.c \
../Core/Src/freertos.c \
../Core/Src/main.c \
../Core/Src/new_NMEA.c \
../Core/Src/steering_pid.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_hal_timebase_tim.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c 

OBJS += \
./Core/Src/CAN.o \
./Core/Src/HCompass_HMC5883L_3.o \
./Core/Src/HServo_Motor.o \
./Core/Src/MY_NRF24.o \
./Core/Src/Temperature_Battery.o \
./Core/Src/freertos.o \
./Core/Src/main.o \
./Core/Src/new_NMEA.o \
./Core/Src/steering_pid.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_hal_timebase_tim.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o 

C_DEPS += \
./Core/Src/CAN.d \
./Core/Src/HCompass_HMC5883L_3.d \
./Core/Src/HServo_Motor.d \
./Core/Src/MY_NRF24.d \
./Core/Src/Temperature_Battery.d \
./Core/Src/freertos.d \
./Core/Src/main.d \
./Core/Src/new_NMEA.d \
./Core/Src/steering_pid.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_hal_timebase_tim.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/CAN.cyclo ./Core/Src/CAN.d ./Core/Src/CAN.o ./Core/Src/CAN.su ./Core/Src/HCompass_HMC5883L_3.cyclo ./Core/Src/HCompass_HMC5883L_3.d ./Core/Src/HCompass_HMC5883L_3.o ./Core/Src/HCompass_HMC5883L_3.su ./Core/Src/HServo_Motor.cyclo ./Core/Src/HServo_Motor.d ./Core/Src/HServo_Motor.o ./Core/Src/HServo_Motor.su ./Core/Src/MY_NRF24.cyclo ./Core/Src/MY_NRF24.d ./Core/Src/MY_NRF24.o ./Core/Src/MY_NRF24.su ./Core/Src/Temperature_Battery.cyclo ./Core/Src/Temperature_Battery.d ./Core/Src/Temperature_Battery.o ./Core/Src/Temperature_Battery.su ./Core/Src/freertos.cyclo ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/new_NMEA.cyclo ./Core/Src/new_NMEA.d ./Core/Src/new_NMEA.o ./Core/Src/new_NMEA.su ./Core/Src/steering_pid.cyclo ./Core/Src/steering_pid.d ./Core/Src/steering_pid.o ./Core/Src/steering_pid.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_hal_timebase_tim.cyclo ./Core/Src/stm32f1xx_hal_timebase_tim.d ./Core/Src/stm32f1xx_hal_timebase_tim.o ./Core/Src/stm32f1xx_hal_timebase_tim.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su

.PHONY: clean-Core-2f-Src

