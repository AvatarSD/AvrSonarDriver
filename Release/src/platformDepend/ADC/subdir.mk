################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/platformDepend/ADC/Analog.cpp 

OBJS += \
./src/platformDepend/ADC/Analog.o 

CPP_DEPS += \
./src/platformDepend/ADC/Analog.d 


# Each subdirectory must supply rules for building sources it contributes
src/platformDepend/ADC/%.o: ../src/platformDepend/ADC/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -Wall -O3 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


