################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
MCU_Resource_Files/Source/F2837xS_v210/%.obj: ../MCU_Resource_Files/Source/F2837xS_v210/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-c2000_18.1.8.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/07_Working/YHTEC_LLC_100kW" --include_path="C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-c2000_18.1.8.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="MCU_Resource_Files/Source/F2837xS_v210/$(basename $(<F)).d_raw" --obj_directory="MCU_Resource_Files/Source/F2837xS_v210" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

MCU_Resource_Files/Source/F2837xS_v210/%.obj: ../MCU_Resource_Files/Source/F2837xS_v210/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-c2000_18.1.8.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/07_Working/YHTEC_LLC_100kW" --include_path="C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-c2000_18.1.8.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="MCU_Resource_Files/Source/F2837xS_v210/$(basename $(<F)).d_raw" --obj_directory="MCU_Resource_Files/Source/F2837xS_v210" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


