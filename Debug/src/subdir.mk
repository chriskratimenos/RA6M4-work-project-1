################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hal_entry.c \
../src/hal_warmstart.c \
../src/i2c_sensor.c \
../src/s1_button.c \
../src/s2_button.c \
../src/vee_flash.c 

C_DEPS += \
./src/hal_entry.d \
./src/hal_warmstart.d \
./src/i2c_sensor.d \
./src/s1_button.d \
./src/s2_button.d \
./src/vee_flash.d 

OBJS += \
./src/hal_entry.o \
./src/hal_warmstart.o \
./src/i2c_sensor.o \
./src/s1_button.o \
./src/s2_button.o \
./src/vee_flash.o 

SREC += \
project.srec 

MAP += \
project.map 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-strict-aliasing -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM33 -D_RA_ORDINAL=1 -I"C:/Users/a5163766/OneDrive - Renesas Electronics Corporation/Documents/Code/project/ra_gen" -I"." -I"C:/Users/a5163766/OneDrive - Renesas Electronics Corporation/Documents/Code/project/ra_cfg/fsp_cfg/bsp" -I"C:/Users/a5163766/OneDrive - Renesas Electronics Corporation/Documents/Code/project/ra_cfg/fsp_cfg" -I"C:/Users/a5163766/OneDrive - Renesas Electronics Corporation/Documents/Code/project/src" -I"C:/Users/a5163766/OneDrive - Renesas Electronics Corporation/Documents/Code/project/ra/fsp/inc" -I"C:/Users/a5163766/OneDrive - Renesas Electronics Corporation/Documents/Code/project/ra/fsp/inc/api" -I"C:/Users/a5163766/OneDrive - Renesas Electronics Corporation/Documents/Code/project/ra/fsp/inc/instances" -I"C:/Users/a5163766/OneDrive - Renesas Electronics Corporation/Documents/Code/project/ra/arm/CMSIS_6/CMSIS/Core/Include" -std=c99 -Wno-stringop-overflow -Wno-format-truncation --param=min-pagesize=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

