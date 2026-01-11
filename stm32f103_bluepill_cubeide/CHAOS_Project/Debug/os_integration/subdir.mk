################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Dati/60_Repositories/10_Public/Bluepill_Carrier/Test/generated/os_integration/chaos_demo_tasks.c \
C:/Dati/60_Repositories/10_Public/Bluepill_Carrier/Test/generated/os_integration/chaos_hooks.c 

OBJS += \
./os_integration/chaos_demo_tasks.o \
./os_integration/chaos_hooks.o 

C_DEPS += \
./os_integration/chaos_demo_tasks.d \
./os_integration/chaos_hooks.d 


# Each subdirectory must supply rules for building sources it contributes
os_integration/chaos_demo_tasks.o: C:/Dati/60_Repositories/10_Public/Bluepill_Carrier/Test/generated/os_integration/chaos_demo_tasks.c os_integration/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Dati/60_Repositories/10_Public/Bluepill_Carrier/Test/generated/os_integration" -I"C:/Dati/60_Repositories/10_Public/Bluepill_Carrier/Test/generated/os" -I"C:/Dati/60_Repositories/10_Public/Bluepill_Carrier/Test/generated/os_cfg" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
os_integration/chaos_hooks.o: C:/Dati/60_Repositories/10_Public/Bluepill_Carrier/Test/generated/os_integration/chaos_hooks.c os_integration/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Dati/60_Repositories/10_Public/Bluepill_Carrier/Test/generated/os_integration" -I"C:/Dati/60_Repositories/10_Public/Bluepill_Carrier/Test/generated/os" -I"C:/Dati/60_Repositories/10_Public/Bluepill_Carrier/Test/generated/os_cfg" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-os_integration

clean-os_integration:
	-$(RM) ./os_integration/chaos_demo_tasks.cyclo ./os_integration/chaos_demo_tasks.d ./os_integration/chaos_demo_tasks.o ./os_integration/chaos_demo_tasks.su ./os_integration/chaos_hooks.cyclo ./os_integration/chaos_hooks.d ./os_integration/chaos_hooks.o ./os_integration/chaos_hooks.su

.PHONY: clean-os_integration

