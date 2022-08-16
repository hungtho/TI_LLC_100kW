/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : FDC_LLC                                                     **
**  Filename  : main.c                                                      **
**  Version   : -.- (PCB : )                                                **
**  Date      : 2020.12.01                                                  **
**                                                                          **
******************************************************************************
**                                                                          **
**  (c) 2020 YOUNG HWA TECH Co., Ltd. All Rights Reserved                   **
**                                                                          **
**                       YOUNG HWA TECH Co., Ltd.                           **
******************************************************************************

VERSION HISTORY:
----------------

Version     : -.-
Date        : ----.--.--
Revised by  : Tran Duc Hung
Description : Original version.

*/

#define MAIN_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "F28x_Project.h"
#include "F2837xS_SWPrioritizedIsrLevels.h"
#include "math.h"
#include "ASW_Config.h"
#include "ASW_Ctrl.h"
#include <ASW_Diag.h>
#include "BSW_Can.h"
#include "BSW_Timer.h"
#include "BSW_Adc.h"
#include "BSW_Gpio.h"
#include "BSW_Pwm.h"
#include "Rte_Interface.h"

/****************************************************************************/
/**                                                                        **/
/**                      DEFINITIONS AND MACROS                            **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                      TYPEDEFS AND STRUCTURES                           **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                      PROTOTYPES OF LOCAL FUNCTIONS                     **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                      GLOBAL VARIABLES                                  **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void main ( void )
{
    InitSysCtrl();
    EALLOW;
    ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 0x0;
    EDIS;
    DINT;               /* Disable all interrupts */

    InitCpuTimers( );                               /* Timer Interrupt GPIO setting */
    ConfigCpuTimer ( &CpuTimer1, 200, 100.0 );      /*  CPU timer setting (CPU clock : 200Mhz, period : 1.0 --> 1us, for 1e3 ---> 1ms)  */

    CpuSysRegs.PCLKCR2.bit.EPWM1=1;
    CpuSysRegs.PCLKCR2.bit.EPWM2=1;
    CpuSysRegs.PCLKCR2.bit.EPWM3=1;
    CpuSysRegs.PCLKCR2.bit.EPWM4=1;
    CpuSysRegs.PCLKCR2.bit.EPWM5=1;

    DINT;

    InitPieCtrl();

//
// Disable CPU interrupts and clear all CPU interrupt flags:
//
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

//
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
//
    EALLOW; // This is needed to write to EALLOW protected registers
    PieVectTable.EPWM1_INT = &epwm1_isr;
//    PieVectTable.EPWM2_INT = &epwm2_isr;
//    PieVectTable.EPWM3_INT = &epwm3_isr;
    PieVectTable.EPWM4_INT = &epwm4_isr;

    PieVectTable.ADCA1_INT = &adca_isr;              /* function for ADC1 interrupt 1 */
    PieVectTable.ADCB1_INT = &adcb_isr;              /* function for ADC1 interrupt 1 */
    PieVectTable.ADCC1_INT = &adcc_isr;              /* function for ADC1 interrupt 1 */
    PieVectTable.XINT1_INT = &Over_Volt_isr;        /* function for XINT1 interrupt */
    PieVectTable.XINT2_INT = &Fualt_isr;            /* function for XINT2 interrupt */

    PieVectTable.TIMER1_INT = &cpu_timer1_isr;      /* function for cpu_Timer0 interrupt */


    EDIS;   // This is needed to disable write to EALLOW protected registers

//
// For this example, only initialize the ePWM
//
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    BSW_Adc_Init ( );
    BSW_Gpio_Init ( );
    BSW_Can_Init ( );
    BSW_Pwm_Init ();

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

//
// Step 4. User specific code, enable interrupts:
//
// Enable CPU INT3 which is connected to EPWM1-3 INT:
//
    IER |= M_INT1;
    IER |= M_INT3;
    IER |= M_INT12;
    IER |= M_INT13;
//
// Enable EPWM INTn in the PIE: Group 3 interrupt 1-3
//
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
//    PieCtrlRegs.PIEIER3.bit.INTx2 = 1;
//    PieCtrlRegs.PIEIER3.bit.INTx3 = 1;
    PieCtrlRegs.PIEIER3.bit.INTx4 = 1;
//    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;      /* Enable the PIE block */

//    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;      /* Enable CPU0_Timer0  */
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;      /* Enable the PIE block */
    PieCtrlRegs.PIEIER1.bit.INTx4 = 1;      /* Enable PIE interrupt XINT1  */
    PieCtrlRegs.PIEIER1.bit.INTx5 = 1;      /* Enable PIE interrupt XINT2  */
    PieCtrlRegs.PIEIER12.bit.INTx1 = 1;     /* Enable PIE interrupt XINT3  */
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;      /* Enable interrupt for ADCA */
    PieCtrlRegs.PIEIER1.bit.INTx2 = 1;      /* Enable interrupt for ADCB */
    PieCtrlRegs.PIEIER1.bit.INTx3 = 1;      /* Enable interrupt for ADCC */
//
// Enable global Interrupts and higher priority real-time debug events:
//
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM
//

    ENABLE_BUFF1;
    ENABLE_BUFF2;
    CpuTimer1Regs.TCR.bit.TSS = 0;          /* start timer1 */

    for( ; ; )
    {
        while( u8g_task_flag_100u != 1U ){}
        u8g_task_flag_100u = 0U;

        RTE_Task_Run ();
    }
}

/****************************************************************************/
/**                                                                        **/
/**                      LOCAL FUNCTIONS                                   **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
