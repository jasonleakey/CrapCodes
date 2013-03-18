################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/FoodFactory/Cabbage.cpp \
../src/FoodFactory/Fish.cpp \
../src/FoodFactory/GuangdongRestaurant.cpp \
../src/FoodFactory/LiangBanCabbage.cpp \
../src/FoodFactory/QingZhengFish.cpp \
../src/FoodFactory/ShousiCabbage.cpp \
../src/FoodFactory/ShuiZhuFish.cpp \
../src/FoodFactory/SichuanRestaurant.cpp \
../src/FoodFactory/main.cpp 

OBJS += \
./src/FoodFactory/Cabbage.o \
./src/FoodFactory/Fish.o \
./src/FoodFactory/GuangdongRestaurant.o \
./src/FoodFactory/LiangBanCabbage.o \
./src/FoodFactory/QingZhengFish.o \
./src/FoodFactory/ShousiCabbage.o \
./src/FoodFactory/ShuiZhuFish.o \
./src/FoodFactory/SichuanRestaurant.o \
./src/FoodFactory/main.o 

CPP_DEPS += \
./src/FoodFactory/Cabbage.d \
./src/FoodFactory/Fish.d \
./src/FoodFactory/GuangdongRestaurant.d \
./src/FoodFactory/LiangBanCabbage.d \
./src/FoodFactory/QingZhengFish.d \
./src/FoodFactory/ShousiCabbage.d \
./src/FoodFactory/ShuiZhuFish.d \
./src/FoodFactory/SichuanRestaurant.d \
./src/FoodFactory/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/FoodFactory/%.o: ../src/FoodFactory/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


