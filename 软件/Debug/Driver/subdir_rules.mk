################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Driver/Soft_SPI.obj: ../Driver/Soft_SPI.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -g --include_path="C:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --include_path="D:/Arduino/TI7/TivaEthernet" --include_path="D:/Arduino/TI7/TivaEthernet/Peripheralib" --include_path="D:/Arduino/TI7/TivaEthernet/Driver" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Driver/Soft_SPI.pp" --obj_directory="Driver" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


