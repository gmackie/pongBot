################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hal/CortexM3/GNU/hal_assert.c 

S_SRCS += \
../hal/CortexM3/GNU/hal.s \
../hal/CortexM3/GNU/hw_reg_access.s 

OBJS += \
./hal/CortexM3/GNU/hal.o \
./hal/CortexM3/GNU/hal_assert.o \
./hal/CortexM3/GNU/hw_reg_access.o 

C_DEPS += \
./hal/CortexM3/GNU/hal_assert.d 


# Each subdirectory must supply rules for building sources it contributes
hal/CortexM3/GNU/%.o: ../hal/CortexM3/GNU/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Assembler'
	arm-none-eabi-gcc -c -mthumb -mcpu=cortex-m3 -specs=bare.specs  -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hal/CortexM3/GNU/%.o: ../hal/CortexM3/GNU/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU C Compiler'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -DACTEL_STDIO_THRU_UART -IN:\project\SoftConsole\project_MSS_MSS_CM3_0\project_MSS_MSS_CM3_0_hw_platform -IN:\project\SoftConsole\project_MSS_MSS_CM3_0\project_MSS_MSS_CM3_0_hw_platform\CMSIS -IN:\project\SoftConsole\project_MSS_MSS_CM3_0\project_MSS_MSS_CM3_0_hw_platform\CMSIS\startup_gcc -IN:\project\SoftConsole\project_MSS_MSS_CM3_0\project_MSS_MSS_CM3_0_hw_platform\drivers -IN:\project\SoftConsole\project_MSS_MSS_CM3_0\project_MSS_MSS_CM3_0_hw_platform\drivers\mss_gpio -IN:\project\SoftConsole\project_MSS_MSS_CM3_0\project_MSS_MSS_CM3_0_hw_platform\drivers\mss_i2c -IN:\project\SoftConsole\project_MSS_MSS_CM3_0\project_MSS_MSS_CM3_0_hw_platform\drivers\mss_nvm -IN:\project\SoftConsole\project_MSS_MSS_CM3_0\project_MSS_MSS_CM3_0_hw_platform\drivers\mss_pdma -IN:\project\SoftConsole\project_MSS_MSS_CM3_0\project_MSS_MSS_CM3_0_hw_platform\drivers\mss_rtc -IN:\project\SoftConsole\project_MSS_MSS_CM3_0\project_MSS_MSS_CM3_0_hw_platform\drivers\mss_spi -IN:\project\SoftConsole\project_MSS_MSS_CM3_0\project_MSS_MSS_CM3_0_hw_platform\drivers\mss_timer -IN:\project\SoftConsole\project_MSS_MSS_CM3_0\project_MSS_MSS_CM3_0_hw_platform\drivers\mss_uart -IN:\project\SoftConsole\project_MSS_MSS_CM3_0\project_MSS_MSS_CM3_0_hw_platform\hal -IN:\project\SoftConsole\project_MSS_MSS_CM3_0\project_MSS_MSS_CM3_0_hw_platform\hal\CortexM3 -IN:\project\SoftConsole\project_MSS_MSS_CM3_0\project_MSS_MSS_CM3_0_hw_platform\hal\CortexM3\GNU -O0 -ffunction-sections -fdata-sections -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


