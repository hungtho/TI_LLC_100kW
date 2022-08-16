################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../Source/F2837xS_v210/DSP28xxx_CodeStartBranch.asm \
../Source/F2837xS_v210/DSP28xxx_SectionCopy_nonBIOS.asm \
../Source/F2837xS_v210/F2837xS_DBGIER.asm \
../Source/F2837xS_v210/F2837xS_usDelay.asm 

C_SRCS += \
../Source/F2837xS_v210/F2837xS_Adc.c \
../Source/F2837xS_v210/F2837xS_CpuTimers.c \
../Source/F2837xS_v210/F2837xS_EPwm.c \
../Source/F2837xS_v210/F2837xS_GlobalVariableDefs.c \
../Source/F2837xS_v210/F2837xS_Gpio.c \
../Source/F2837xS_v210/F2837xS_PieCtrl.c \
../Source/F2837xS_v210/F2837xS_PieVect.c \
../Source/F2837xS_v210/F2837xS_SysCtrl.c \
../Source/F2837xS_v210/F2837xS_can.c \
../Source/F2837xS_v210/SWPrioritizedDefaultIsr.c 

C_DEPS += \
./Source/F2837xS_v210/F2837xS_Adc.d \
./Source/F2837xS_v210/F2837xS_CpuTimers.d \
./Source/F2837xS_v210/F2837xS_EPwm.d \
./Source/F2837xS_v210/F2837xS_GlobalVariableDefs.d \
./Source/F2837xS_v210/F2837xS_Gpio.d \
./Source/F2837xS_v210/F2837xS_PieCtrl.d \
./Source/F2837xS_v210/F2837xS_PieVect.d \
./Source/F2837xS_v210/F2837xS_SysCtrl.d \
./Source/F2837xS_v210/F2837xS_can.d \
./Source/F2837xS_v210/SWPrioritizedDefaultIsr.d 

OBJS += \
./Source/F2837xS_v210/DSP28xxx_CodeStartBranch.obj \
./Source/F2837xS_v210/DSP28xxx_SectionCopy_nonBIOS.obj \
./Source/F2837xS_v210/F2837xS_Adc.obj \
./Source/F2837xS_v210/F2837xS_CpuTimers.obj \
./Source/F2837xS_v210/F2837xS_DBGIER.obj \
./Source/F2837xS_v210/F2837xS_EPwm.obj \
./Source/F2837xS_v210/F2837xS_GlobalVariableDefs.obj \
./Source/F2837xS_v210/F2837xS_Gpio.obj \
./Source/F2837xS_v210/F2837xS_PieCtrl.obj \
./Source/F2837xS_v210/F2837xS_PieVect.obj \
./Source/F2837xS_v210/F2837xS_SysCtrl.obj \
./Source/F2837xS_v210/F2837xS_can.obj \
./Source/F2837xS_v210/F2837xS_usDelay.obj \
./Source/F2837xS_v210/SWPrioritizedDefaultIsr.obj 

ASM_DEPS += \
./Source/F2837xS_v210/DSP28xxx_CodeStartBranch.d \
./Source/F2837xS_v210/DSP28xxx_SectionCopy_nonBIOS.d \
./Source/F2837xS_v210/F2837xS_DBGIER.d \
./Source/F2837xS_v210/F2837xS_usDelay.d 

OBJS__QUOTED += \
"Source\F2837xS_v210\DSP28xxx_CodeStartBranch.obj" \
"Source\F2837xS_v210\DSP28xxx_SectionCopy_nonBIOS.obj" \
"Source\F2837xS_v210\F2837xS_Adc.obj" \
"Source\F2837xS_v210\F2837xS_CpuTimers.obj" \
"Source\F2837xS_v210\F2837xS_DBGIER.obj" \
"Source\F2837xS_v210\F2837xS_EPwm.obj" \
"Source\F2837xS_v210\F2837xS_GlobalVariableDefs.obj" \
"Source\F2837xS_v210\F2837xS_Gpio.obj" \
"Source\F2837xS_v210\F2837xS_PieCtrl.obj" \
"Source\F2837xS_v210\F2837xS_PieVect.obj" \
"Source\F2837xS_v210\F2837xS_SysCtrl.obj" \
"Source\F2837xS_v210\F2837xS_can.obj" \
"Source\F2837xS_v210\F2837xS_usDelay.obj" \
"Source\F2837xS_v210\SWPrioritizedDefaultIsr.obj" 

C_DEPS__QUOTED += \
"Source\F2837xS_v210\F2837xS_Adc.d" \
"Source\F2837xS_v210\F2837xS_CpuTimers.d" \
"Source\F2837xS_v210\F2837xS_EPwm.d" \
"Source\F2837xS_v210\F2837xS_GlobalVariableDefs.d" \
"Source\F2837xS_v210\F2837xS_Gpio.d" \
"Source\F2837xS_v210\F2837xS_PieCtrl.d" \
"Source\F2837xS_v210\F2837xS_PieVect.d" \
"Source\F2837xS_v210\F2837xS_SysCtrl.d" \
"Source\F2837xS_v210\F2837xS_can.d" \
"Source\F2837xS_v210\SWPrioritizedDefaultIsr.d" 

ASM_DEPS__QUOTED += \
"Source\F2837xS_v210\DSP28xxx_CodeStartBranch.d" \
"Source\F2837xS_v210\DSP28xxx_SectionCopy_nonBIOS.d" \
"Source\F2837xS_v210\F2837xS_DBGIER.d" \
"Source\F2837xS_v210\F2837xS_usDelay.d" 

ASM_SRCS__QUOTED += \
"../Source/F2837xS_v210/DSP28xxx_CodeStartBranch.asm" \
"../Source/F2837xS_v210/DSP28xxx_SectionCopy_nonBIOS.asm" \
"../Source/F2837xS_v210/F2837xS_DBGIER.asm" \
"../Source/F2837xS_v210/F2837xS_usDelay.asm" 

C_SRCS__QUOTED += \
"../Source/F2837xS_v210/F2837xS_Adc.c" \
"../Source/F2837xS_v210/F2837xS_CpuTimers.c" \
"../Source/F2837xS_v210/F2837xS_EPwm.c" \
"../Source/F2837xS_v210/F2837xS_GlobalVariableDefs.c" \
"../Source/F2837xS_v210/F2837xS_Gpio.c" \
"../Source/F2837xS_v210/F2837xS_PieCtrl.c" \
"../Source/F2837xS_v210/F2837xS_PieVect.c" \
"../Source/F2837xS_v210/F2837xS_SysCtrl.c" \
"../Source/F2837xS_v210/F2837xS_can.c" \
"../Source/F2837xS_v210/SWPrioritizedDefaultIsr.c" 


