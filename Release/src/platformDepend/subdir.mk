################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/platformDepend/platform.cpp \
../src/platformDepend/portisr.cpp \
../src/platformDepend/timerisr.cpp 

OBJS += \
./src/platformDepend/platform.o \
./src/platformDepend/portisr.o \
./src/platformDepend/timerisr.o 

CPP_DEPS += \
./src/platformDepend/platform.d \
./src/platformDepend/portisr.d \
./src/platformDepend/timerisr.d 


# Each subdirectory must supply rules for building sources it contributes
src/platformDepend/%.o: ../src/platformDepend/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -Wall -O3 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


