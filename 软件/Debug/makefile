################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv5/tools/compiler/arm_5.0.4

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./Driver/Soft_SPI.obj" \
"./Peripheralib/UART.obj" \
"./Peripheralib/TFT.obj" \
"./Peripheralib/SD.obj" \
"./Peripheralib/Relay.obj" \
"./Peripheralib/PWM.obj" \
"./Peripheralib/NRF.obj" \
"./Peripheralib/JDQ.obj" \
"./Peripheralib/ENC.obj" \
"./Peripheralib/Button.obj" \
"./Peripheralib/ADC.obj" \
"./uip/uiplib.obj" \
"./uip/uip_arp.obj" \
"./uip/uip.obj" \
"./uip/uip-split.obj" \
"./uip/uip-neighbor.obj" \
"./uip/uip-fw.obj" \
"./uip/timer.obj" \
"./uip/tapdev.obj" \
"./uip/psock.obj" \
"./uip/clock-arch.obj" \
"./startup_ccs.obj" \
"./main.obj" \
"./Common.obj" \
-l"libc.a" \
-l"C:\ti\ccsv5\tools\compiler\arm_5.0.4\lib\driverlib.lib" \
"../tm4c123gh6pm.cmd" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include uip/subdir_vars.mk
-include Peripheralib/subdir_vars.mk
-include Driver/subdir_vars.mk
-include subdir_rules.mk
-include uip/subdir_rules.mk
-include Peripheralib/subdir_rules.mk
-include Driver/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: TivaEthernet.out

# Tool invocations
TivaEthernet.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccsv5/tools/compiler/arm_5.0.4/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -g --diag_warning=225 --display_error_number --diag_wrap=off -z --stack_size=512 -m"TivaEthernet.map" --heap_size=0 -i"C:/ti/ccsv5/tools/compiler/arm_5.0.4/lib" -i"C:/ti/ccsv5/tools/compiler/arm_5.0.4/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="TivaEthernet_linkInfo.xml" --rom_model -o "TivaEthernet.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(TMS470_EXECUTABLE_OUTPUTS__QUOTED) "TivaEthernet.out"
	-$(RM) "Common.pp" "main.pp" "startup_ccs.pp" "uip\clock-arch.pp" "uip\psock.pp" "uip\tapdev.pp" "uip\timer.pp" "uip\uip-fw.pp" "uip\uip-neighbor.pp" "uip\uip-split.pp" "uip\uip.pp" "uip\uip_arp.pp" "uip\uiplib.pp" "Peripheralib\ADC.pp" "Peripheralib\Button.pp" "Peripheralib\ENC.pp" "Peripheralib\JDQ.pp" "Peripheralib\NRF.pp" "Peripheralib\PWM.pp" "Peripheralib\Relay.pp" "Peripheralib\SD.pp" "Peripheralib\TFT.pp" "Peripheralib\UART.pp" "Driver\Soft_SPI.pp" 
	-$(RM) "Common.obj" "main.obj" "startup_ccs.obj" "uip\clock-arch.obj" "uip\psock.obj" "uip\tapdev.obj" "uip\timer.obj" "uip\uip-fw.obj" "uip\uip-neighbor.obj" "uip\uip-split.obj" "uip\uip.obj" "uip\uip_arp.obj" "uip\uiplib.obj" "Peripheralib\ADC.obj" "Peripheralib\Button.obj" "Peripheralib\ENC.obj" "Peripheralib\JDQ.obj" "Peripheralib\NRF.obj" "Peripheralib\PWM.obj" "Peripheralib\Relay.obj" "Peripheralib\SD.obj" "Peripheralib\TFT.obj" "Peripheralib\UART.obj" "Driver\Soft_SPI.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
