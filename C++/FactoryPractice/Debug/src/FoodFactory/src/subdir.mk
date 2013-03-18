################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/FoodFactory/src/Fish.cpp \
../src/FoodFactory/src/GuangdongRestaurant.cpp \
../src/FoodFactory/src/LiangBanCabbage.cpp \
../src/FoodFactory/src/QingZhengFish.cpp \
../src/FoodFactory/src/ShousiCabbage.cpp \
../src/FoodFactory/src/ShuiZhuFish.cpp \
../src/FoodFactory/src/SichuanRestaurant.cpp \
../src/FoodFactory/src/main.cpp 

OBJS += \
./src/FoodFactory/src/Fish.o \
./src/FoodFactory/src/GuangdongRestaurant.o \
./src/FoodFactory/src/LiangBanCabbage.o \
./src/FoodFactory/src/QingZhengFish.o \
./src/FoodFactory/src/ShousiCabbage.o \
./src/FoodFactory/src/ShuiZhuFish.o \
./src/FoodFactory/src/SichuanRestaurant.o \
./src/FoodFactory/src/main.o 

CPP_DEPS += \
./src/FoodFactory/src/Fish.d \
./src/FoodFactory/src/GuangdongRestaurant.d \
./src/FoodFactory/src/LiangBanCabbage.d \
./src/FoodFactory/src/QingZhengFish.d \
./src/FoodFactory/src/ShousiCabbage.d \
./src/FoodFactory/src/ShuiZhuFish.d \
./src/FoodFactory/src/SichuanRestaurant.d \
./src/FoodFactory/src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/FoodFactory/src/%.o: ../src/FoodFactory/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


