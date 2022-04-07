################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BinarySearchTree.cpp \
../src/CSVparser.cpp 

CPP_DEPS += \
./src/BinarySearchTree.d \
./src/CSVparser.d 

OBJS += \
./src/BinarySearchTree.o \
./src/CSVparser.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/BinarySearchTree.d ./src/BinarySearchTree.o ./src/CSVparser.d ./src/CSVparser.o

.PHONY: clean-src

