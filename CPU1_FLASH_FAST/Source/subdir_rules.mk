################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Source/ADC.obj: ../Source/ADC.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Source" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Source/F2837xS_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/ADC.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/ASW.obj: ../Source/ASW.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Source" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Source/F2837xS_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/ASW.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/CAN.obj: ../Source/CAN.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Source" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Source/F2837xS_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/CAN.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/GPIO.obj: ../Source/GPIO.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Source" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Source/F2837xS_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/GPIO.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/MODE.obj: ../Source/MODE.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Source" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Source/F2837xS_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/MODE.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/PWM.obj: ../Source/PWM.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Source" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Source/F2837xS_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/PWM.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/Sleep.obj: ../Source/Sleep.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Source" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Source/F2837xS_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/Sleep.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/TIMER.obj: ../Source/TIMER.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Source" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Source/F2837xS_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/TIMER.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Source/main.obj: ../Source/main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_common_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Source" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Source/F2837xS_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header/F2837xS_headers_v210" --include_path="D:/BHDC_Project/Workspace/YHTEC_BHDC_FLASH/Header" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="Source/main.d_raw" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


