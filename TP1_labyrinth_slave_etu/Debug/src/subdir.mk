################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/labyrinth_slave.c \
../src/tools.c 

OBJS += \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/labyrinth_slave.o \
./src/tools.o 

C_DEPS += \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/labyrinth_slave.d \
./src/tools.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -D__LPC17XX__ -I"/home/jeanetie.delucing/Documents/workspace/CMSISv2p00_LPC17xx/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


