################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/DA_Transformer.c \
../src/Seg_TimerCounterHandler.c \
../src/SwitchHandler.c \
../src/main.c \
../src/sawtooth_wave.c \
../src/triangle_wave.c 

OBJS += \
./src/DA_Transformer.o \
./src/Seg_TimerCounterHandler.o \
./src/SwitchHandler.o \
./src/main.o \
./src/sawtooth_wave.o \
./src/triangle_wave.o 

C_DEPS += \
./src/DA_Transformer.d \
./src/Seg_TimerCounterHandler.d \
./src/SwitchHandler.d \
./src/main.d \
./src/sawtooth_wave.d \
./src/triangle_wave.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -I../../intergration_test1_bsp/microblaze_0/include -mlittle-endian -mcpu=v10.0 -mxl-soft-mul -Wl,--no-relax -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


