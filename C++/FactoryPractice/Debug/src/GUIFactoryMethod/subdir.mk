################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/GUIFactoryMethod/GUIFactory.cpp 

OBJS += \
./src/GUIFactoryMethod/GUIFactory.o 

CPP_DEPS += \
./src/GUIFactoryMethod/GUIFactory.d 


# Each subdirectory must supply rules for building sources it contributes
src/GUIFactoryMethod/%.o: ../src/GUIFactoryMethod/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


