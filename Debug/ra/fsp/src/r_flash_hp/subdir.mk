################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/r_flash_hp/r_flash_hp.c 

C_DEPS += \
./ra/fsp/src/r_flash_hp/r_flash_hp.d 

OBJS += \
./ra/fsp/src/r_flash_hp/r_flash_hp.o 

SREC += \
project.srec 

MAP += \
project.map 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/r_flash_hp/%.o: ../ra/fsp/src/r_flash_hp/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-strict-aliasing -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM33 -D_RA_ORDINAL=1 -I"C:/Users/a5163766/OneDrive - Renesas Electronics Corporation/Documents/Code/project/ra_gen" -I"." -I"C:/Users/a5163766/OneDrive - Renesas Electronics Corporation/Documents/Code/project/ra_cfg/fsp_cfg/bsp" -I"C:/Users/a5163766/OneDrive - Renesas Electronics Corporation/Documents/Code/project/ra_cfg/fsp_cfg" -I"C:/Users/a5163766/OneDrive - Renesas Electronics Corporation/Documents/Code/project/src" -I"C:/Users/a5163766/OneDrive - Renesas Electronics Corporation/Documents/Code/project/ra/fsp/inc" -I"C:/Users/a5163766/OneDrive - Renesas Electronics Corporation/Documents/Code/project/ra/fsp/inc/api" -I"C:/Users/a5163766/OneDrive - Renesas Electronics Corporation/Documents/Code/project/ra/fsp/inc/instances" -I"C:/Users/a5163766/OneDrive - Renesas Electronics Corporation/Documents/Code/project/ra/arm/CMSIS_6/CMSIS/Core/Include" -std=c99 -Wno-stringop-overflow -Wno-format-truncation --param=min-pagesize=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

