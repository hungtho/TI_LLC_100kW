################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Source/F2837xS_v210/DSP28xxx_CodeStartBranch.obj: ../Source/F2837xS_v210/DSP28xxx_CodeStartBranch.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/F2837xS_v210/DSP28xxx_CodeStartBranch.d_raw" --obj_directory="Source/F2837xS_v210" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/F2837xS_v210/DSP28xxx_SectionCopy_nonBIOS.obj: ../Source/F2837xS_v210/DSP28xxx_SectionCopy_nonBIOS.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/F2837xS_v210/DSP28xxx_SectionCopy_nonBIOS.d_raw" --obj_directory="Source/F2837xS_v210" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/F2837xS_v210/F2837xS_Adc.obj: ../Source/F2837xS_v210/F2837xS_Adc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/F2837xS_v210/F2837xS_Adc.d_raw" --obj_directory="Source/F2837xS_v210" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/F2837xS_v210/F2837xS_CpuTimers.obj: ../Source/F2837xS_v210/F2837xS_CpuTimers.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/F2837xS_v210/F2837xS_CpuTimers.d_raw" --obj_directory="Source/F2837xS_v210" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/F2837xS_v210/F2837xS_DBGIER.obj: ../Source/F2837xS_v210/F2837xS_DBGIER.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/F2837xS_v210/F2837xS_DBGIER.d_raw" --obj_directory="Source/F2837xS_v210" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/F2837xS_v210/F2837xS_EPwm.obj: ../Source/F2837xS_v210/F2837xS_EPwm.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/F2837xS_v210/F2837xS_EPwm.d_raw" --obj_directory="Source/F2837xS_v210" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/F2837xS_v210/F2837xS_GlobalVariableDefs.obj: ../Source/F2837xS_v210/F2837xS_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/F2837xS_v210/F2837xS_GlobalVariableDefs.d_raw" --obj_directory="Source/F2837xS_v210" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/F2837xS_v210/F2837xS_Gpio.obj: ../Source/F2837xS_v210/F2837xS_Gpio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/F2837xS_v210/F2837xS_Gpio.d_raw" --obj_directory="Source/F2837xS_v210" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/F2837xS_v210/F2837xS_PieCtrl.obj: ../Source/F2837xS_v210/F2837xS_PieCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/F2837xS_v210/F2837xS_PieCtrl.d_raw" --obj_directory="Source/F2837xS_v210" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/F2837xS_v210/F2837xS_PieVect.obj: ../Source/F2837xS_v210/F2837xS_PieVect.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/F2837xS_v210/F2837xS_PieVect.d_raw" --obj_directory="Source/F2837xS_v210" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/F2837xS_v210/F2837xS_SysCtrl.obj: ../Source/F2837xS_v210/F2837xS_SysCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/F2837xS_v210/F2837xS_SysCtrl.d_raw" --obj_directory="Source/F2837xS_v210" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/F2837xS_v210/F2837xS_can.obj: ../Source/F2837xS_v210/F2837xS_can.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/F2837xS_v210/F2837xS_can.d_raw" --obj_directory="Source/F2837xS_v210" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/F2837xS_v210/F2837xS_usDelay.obj: ../Source/F2837xS_v210/F2837xS_usDelay.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/F2837xS_v210/F2837xS_usDelay.d_raw" --obj_directory="Source/F2837xS_v210" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/F2837xS_v210/SWPrioritizedDefaultIsr.obj: ../Source/F2837xS_v210/SWPrioritizedDefaultIsr.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/F2837xS_v210/SWPrioritizedDefaultIsr.d_raw" --obj_directory="Source/F2837xS_v210" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


