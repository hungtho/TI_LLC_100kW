/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : FDC_LLC                                                     **
**  Filename  : BSW_Pwm.c                                                   **
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

#define BSW_PWM_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "Rte_Interface.h"
#include "BSW_Pwm.h"

/****************************************************************************/
/**                                                                        **/
/**                      DEFINITIONS AND MACROS                            **/
/**                                                                        **/
/****************************************************************************/
//
// Defines
//
#define EPWM1_TIMER_TBPRD  2000  // Period register
#define EPWM1_MAX_CMPA     1950
#define EPWM1_MIN_CMPA       50
#define EPWM1_MAX_CMPB     1950
#define EPWM1_MIN_CMPB       50

#define EPWM2_TIMER_TBPRD  2000  // Period register
#define EPWM2_MAX_CMPA     1950
#define EPWM2_MIN_CMPA       50
#define EPWM2_MAX_CMPB     1950
#define EPWM2_MIN_CMPB       50

#define EPWM3_TIMER_TBPRD  2000  // Period register
#define EPWM3_MAX_CMPA      950
#define EPWM3_MIN_CMPA       50
#define EPWM3_MAX_CMPB     1950
#define EPWM3_MIN_CMPB     1050

#define EPWM4_TIMER_TBPRD  2000  // Period register
#define EPWM4_MAX_CMPA      950
#define EPWM4_MIN_CMPA       50
#define EPWM4_MAX_CMPB     1950
#define EPWM4_MIN_CMPB     1050

#define EPWM5_TIMER_TBPRD  2000  // Period register
#define EPWM5_MAX_CMPA      950
#define EPWM5_MIN_CMPA       50
#define EPWM5_MAX_CMPB     1950
#define EPWM5_MIN_CMPB     1050

#define EPWM_CMP_UP           1
#define EPWM_CMP_DOWN         0
/****************************************************************************/
/**                                                                        **/
/**                      TYPEDEFS AND STRUCTURES                           **/
/**                                                                        **/
/****************************************************************************/
volatile struct EPWM_REGS *ePWM_Regs[] = {
        0,
        &EPwm1Regs,
        &EPwm2Regs,
        &EPwm3Regs,
        &EPwm4Regs,
        &EPwm5Regs,
        &EPwm6Regs,
        &EPwm7Regs,
        &EPwm8Regs,
        &EPwm9Regs,
        &EPwm10Regs,
        &EPwm11Regs,
        &EPwm12Regs
};
/****************************************************************************/
/**                                                                        **/
/**                      PROTOTYPES OF LOCAL FUNCTIONS                     **/
/**                                                                        **/
/****************************************************************************/
static void InitEPwm1Example ( void );
static void InitEPwm2Example ( void );
static void InitEPwm3Example ( void );
static void InitEPwm4Example ( void );
static void InitEPwm5Example ( void );
static void InitEPwm6Example ( void );
static void BSW_SET_Deadtime ( byte u8_ch, single f32_dt_ns );



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
single f32_duty = 0.5;
/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Function  | PWM_Init                                                     */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void BSW_Pwm_Init ( void )
{
    InitEPwm1Gpio ( );
    InitEPwm2Gpio ( );
    InitEPwm3Gpio ( );
    InitEPwm4Gpio ( );
    InitEPwm5Gpio ( );
    InitEPwm6Gpio ( );

    InitEPwm1Example();
    InitEPwm2Example();
    InitEPwm3Example();
    InitEPwm4Example();
    InitEPwm5Example();
    InitEPwm6Example();
}

/*--------------------------------------------------------------------------*/
/* Function  | forceOFFPWM                                                  */
/* Name      | PWM Change                                                   */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void BSW_Pwm ( byte u8_ch, word u8_state )
{
    if( u8_state == EN_PWM_On )
    {
        ePWM_Regs[ u8_ch ]->AQCSFRC.bit.CSFA = 0x0;
        ePWM_Regs[ u8_ch ]->AQCSFRC.bit.CSFB = 0x0;
    }
    else
    {
        ePWM_Regs[ u8_ch ]->AQCSFRC.bit.CSFA = 0x1;
//        ePWM_Regs[ u8_ch ]->AQCSFRC.bit.CSFB = 0x1;
    }
}

/*--------------------------------------------------------------------------*/
/* Function  | All_Update_Freq                                              */
/* Name      | Update Freq All                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void BSW_Pwm_Freq_Update ( const st_RteIn_LLC *stp_rteIn, st_RteOut_LLC *stp_rteOut )
{
    BSW_SET_Freq ( 1U, stp_rteOut->st_PwmValue.f32_fre[ LAYER_A ] );
    BSW_SET_Duty ( 1U, f32_duty );

    BSW_SET_Freq ( 2U, stp_rteOut->st_PwmValue.f32_fre[ LAYER_A ] );
    BSW_SET_Duty ( 2U, f32_duty );


    if( stp_rteIn->st_CANValue.u8_LayerB == 1U )
    {
        BSW_SET_Freq ( 3U, stp_rteOut->st_PwmValue.f32_fre[ LAYER_B ] );
        BSW_SET_Duty ( 3U, f32_duty );

        BSW_SET_Freq ( 4U, stp_rteOut->st_PwmValue.f32_fre[ LAYER_B ] );
        BSW_SET_Duty ( 4U, f32_duty );
    }

    if( stp_rteIn->st_CANValue.u8_LayerC == 1U )
    {
//        BSW_SET_Freq ( 5U,  stp_rteOut->st_PwmValue.f32_fre[ LAYER_C ] );
//        BSW_SET_Duty ( 5U, f32_duty );

        BSW_SET_Freq ( 6U,  stp_rteOut->st_PwmValue.f32_fre[ LAYER_C ] );
        BSW_SET_Duty ( 6U, f32_duty );
    }
}
/****************************************************************************/
/**                                                                        **/
/**                      LOCAL FUNCTIONS                                   **/
/**                                                                        **/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Function  | updateDeadtime                                               */
/* Name      | Update Deadtime                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void InitEPwm1Example ( void )
{
   //
   // Setup TBCLK
   //
   EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;
   EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;

   EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm1Regs.TBPRD = EPWM1_TIMER_TBPRD;       // Set timer period
   EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;    // Disable phase loading
   EPwm1Regs.TBPHS.bit.TBPHS = 0x0000;        // Phase is 0
   EPwm1Regs.TBCTR = 0x0000;                  // Clear counter
   EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
   EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;

   //
   // Setup shadow register load on ZERO
   //
   EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   //
   // Set Compare values
   //
   EPwm1Regs.CMPA.bit.CMPA = EPWM1_MIN_CMPA;     // Set compare A value
   EPwm1Regs.CMPB.bit.CMPB = EPWM1_MIN_CMPB;     // Set Compare B value

   //
   // Set actions
   //
   EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on Zero
   EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;

   EPwm1Regs.AQCTLB.bit.CAU = AQ_CLEAR;          // Set PWM1A on Zero
   EPwm1Regs.AQCTLB.bit.CAD = AQ_SET;

   //
   // Interrupt where we will change the Compare Values
   //
   EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm1Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 3rd event

   EPwm1Regs.ETSEL.bit.SOCAEN = 1;        /* Enable SOC on B group  */
   EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;
   EPwm1Regs.ETPS.bit.SOCAPRD = ET_1ST;
}

/*--------------------------------------------------------------------------*/
/* Function  | updateDeadtime                                               */
/* Name      | Update Deadtime                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void InitEPwm2Example ( void )
{
    EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
    EPwm2Regs.TBPRD = EPWM5_TIMER_TBPRD;       // Set timer period
    EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;    // Disable phase loading
    EPwm2Regs.TBPHS.bit.TBPHS = 0x0000;        // Phase is 0
    EPwm2Regs.TBCTR = 0x0000;                  // Clear counter
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;

    //
    // Setup shadow register load on ZERO
    //
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    //
    // Set Compare values
    //
    EPwm2Regs.CMPA.bit.CMPA = EPWM2_MIN_CMPA;  // Set compare A value
    EPwm2Regs.CMPB.bit.CMPB = EPWM2_MAX_CMPB;  // Set Compare B value

    //
    // Set Actions
    //
    EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;            // Set PWM1A on Zero
    EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;

    EPwm2Regs.AQCTLB.bit.CAU = AQ_SET;          // Set PWM1A on Zero
    EPwm2Regs.AQCTLB.bit.CAD = AQ_CLEAR;

    EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm2Regs.DBRED.bit.DBRED = 109;
    EPwm2Regs.DBFED.bit.DBFED = 109;
    //
    // Interrupt where we will change the Compare Values
    //
    EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;  // Select INT on Zero event
    EPwm2Regs.ETSEL.bit.INTEN = 1;             // Enable INT
    EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;        // Generate INT on 3rd event

    EPwm2Regs.ETSEL.bit.SOCAEN = 1;        /* Enable SOC on B group  */
    EPwm2Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;
    EPwm2Regs.ETPS.bit.SOCAPRD = ET_1ST;
}

/*--------------------------------------------------------------------------*/
/* Function  | updateDeadtime                                               */
/* Name      | Update Deadtime                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void InitEPwm3Example ( void )
{
   //
   // Setup TBCLK
   //

   EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;
   EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
   EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm3Regs.TBPRD = EPWM3_TIMER_TBPRD;       // Set timer period
   EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;    // Disable phase loading
   EPwm3Regs.TBPHS.bit.TBPHS = 0x0000;        // Phase is 0
   EPwm3Regs.TBCTR = 0x0000;                  // Clear counter
   EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
   EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;

   //
   // Setup shadow register load on ZERO
   //
   EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
   EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   //
   // Set Compare values
   //
   EPwm3Regs.CMPA.bit.CMPA = EPWM3_MIN_CMPA;  // Set compare A value
   EPwm3Regs.CMPB.bit.CMPB = EPWM3_MAX_CMPB;  // Set Compare B value

   //
   // Set Actions
   //
   EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on Zero
   EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;

   EPwm3Regs.AQCTLB.bit.CAU = AQ_SET;          // Set PWM1A on Zero
   EPwm3Regs.AQCTLB.bit.CAD = AQ_CLEAR;

   EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
   EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;
   EPwm3Regs.DBRED.bit.DBRED = 109;
   EPwm3Regs.DBFED.bit.DBFED = 109;
   //
   // Interrupt where we will change the Compare Values
   //
   EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;  // Select INT on Zero event
   EPwm3Regs.ETSEL.bit.INTEN = 1;             // Enable INT
   EPwm3Regs.ETPS.bit.INTPRD = ET_1ST;        // Generate INT on 3rd event
}


/*--------------------------------------------------------------------------*/
/* Function  | updateDeadtime                                               */
/* Name      | Update Deadtime                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void InitEPwm4Example ( void )
{
   //
   // Setup TBCLK
   //
   EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE;
   EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
   EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm4Regs.TBPRD = EPWM4_TIMER_TBPRD;       // Set timer period
   EPwm4Regs.TBCTL.bit.PHSEN = TB_DISABLE;    // Disable phase loading
   EPwm4Regs.TBPHS.bit.TBPHS = 0x0000;        // Phase is 0
   EPwm4Regs.TBCTR = 0x0000;                  // Clear counter
   EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
   EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm4Regs.TBCTL.bit.PRDLD = TB_SHADOW;

   //
   // Setup shadow register load on ZERO
   //
   EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
   EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   //
   // Set Compare values
   //
   EPwm4Regs.CMPA.bit.CMPA = EPWM4_MIN_CMPA;  // Set compare A value
   EPwm4Regs.CMPB.bit.CMPB = EPWM4_MAX_CMPB;  // Set Compare B value

   //
   // Set Actions
   //
   EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR;            // Set PWM1A on Zero
   EPwm4Regs.AQCTLA.bit.CAD = AQ_SET;

   EPwm4Regs.AQCTLB.bit.CAU = AQ_CLEAR;          // Set PWM1A on Zero
   EPwm4Regs.AQCTLB.bit.CAD = AQ_SET;


   EPwm4Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
   EPwm4Regs.DBCTL.bit.IN_MODE = DBA_ALL;
   EPwm4Regs.DBRED.bit.DBRED = 109;
   EPwm4Regs.DBFED.bit.DBFED = 109;
   //
   // Interrupt where we will change the Compare Values
   //
   EPwm4Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;  // Select INT on Zero event
   EPwm4Regs.ETSEL.bit.INTEN = 1;             // Enable INT
   EPwm4Regs.ETPS.bit.INTPRD = ET_1ST;        // Generate INT on 3rd event

   EPwm4Regs.ETSEL.bit.SOCAEN = 1;        /* Enable SOC on B group  */
   EPwm4Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;
   EPwm4Regs.ETPS.bit.SOCAPRD = ET_1ST;
}

/*--------------------------------------------------------------------------*/
/* Function  | updateDeadtime                                               */
/* Name      | Update Deadtime                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void InitEPwm5Example ( void )
{
   //
   // Setup TBCLK
   //
   EPwm5Regs.TBCTL.bit.PHSEN = TB_ENABLE;
   EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
   EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm5Regs.TBPRD = EPWM5_TIMER_TBPRD;       // Set timer period
   EPwm5Regs.TBCTL.bit.PHSEN = TB_DISABLE;    // Disable phase loading
   EPwm5Regs.TBPHS.bit.TBPHS = 0x0000;        // Phase is 0
   EPwm5Regs.TBCTR = 0x0000;                  // Clear counter
   EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
   EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm5Regs.TBCTL.bit.PRDLD = TB_SHADOW;

   //
   // Setup shadow register load on ZERO
   //
   EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
   EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   //
   // Set Compare values
   //
   EPwm5Regs.CMPA.bit.CMPA = EPWM5_MIN_CMPA;  // Set compare A value
   EPwm5Regs.CMPB.bit.CMPB = EPWM5_MAX_CMPB;  // Set Compare B value

   //
   // Set Actions
   //
   EPwm5Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on Zero
   EPwm5Regs.AQCTLA.bit.CAD = AQ_CLEAR;

   EPwm5Regs.AQCTLB.bit.CAU = AQ_CLEAR;          // Set PWM1A on Zero
   EPwm5Regs.AQCTLB.bit.CAD = AQ_SET;


   EPwm5Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm5Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
   EPwm5Regs.DBCTL.bit.IN_MODE = DBA_ALL;
   EPwm5Regs.DBRED.bit.DBRED = 109;
   EPwm5Regs.DBFED.bit.DBFED = 109;
   //
   // Interrupt where we will change the Compare Values
   //
   EPwm5Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;  // Select INT on Zero event
   EPwm5Regs.ETSEL.bit.INTEN = 1;             // Enable INT
   EPwm5Regs.ETPS.bit.INTPRD = ET_1ST;        // Generate INT on 3rd event
}

/*--------------------------------------------------------------------------*/
/* Function  | updateDeadtime                                               */
/* Name      | Update Deadtime                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void InitEPwm6Example ( void )
{
   //
   // Setup TBCLK
   //
   EPwm6Regs.TBCTL.bit.PHSEN = TB_ENABLE;
   EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
   EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm6Regs.TBPRD = EPWM5_TIMER_TBPRD;       // Set timer period
   EPwm6Regs.TBCTL.bit.PHSEN = TB_DISABLE;    // Disable phase loading
   EPwm6Regs.TBPHS.bit.TBPHS = 0x0000;        // Phase is 0
   EPwm6Regs.TBCTR = 0x0000;                  // Clear counter
   EPwm6Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
   EPwm6Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm6Regs.TBCTL.bit.PRDLD = TB_SHADOW;

   //
   // Setup shadow register load on ZERO
   //
   EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
   EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   //
   // Set Compare values
   //
   EPwm6Regs.CMPA.bit.CMPA = EPWM5_MIN_CMPA;  // Set compare A value
   EPwm6Regs.CMPB.bit.CMPB = EPWM5_MAX_CMPB;  // Set Compare B value

   //
   // Set Actions
   //
   EPwm6Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on Zero
   EPwm6Regs.AQCTLA.bit.CAD = AQ_CLEAR;

   EPwm6Regs.AQCTLB.bit.CAU = AQ_CLEAR;          // Set PWM1A on Zero
   EPwm6Regs.AQCTLB.bit.CAD = AQ_SET;


   EPwm6Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm6Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
   EPwm6Regs.DBCTL.bit.IN_MODE = DBA_ALL;
   EPwm6Regs.DBRED.bit.DBRED = 109;
   EPwm6Regs.DBFED.bit.DBFED = 109;
   //
   // Interrupt where we will change the Compare Values
   //
   EPwm6Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;  // Select INT on Zero event
   EPwm6Regs.ETSEL.bit.INTEN = 1;             // Enable INT
   EPwm6Regs.ETPS.bit.INTPRD = ET_1ST;        // Generate INT on 3rd event
}

/*--------------------------------------------------------------------------*/
/* Function  | updateDeadtime                                               */
/* Name      | Update Deadtime                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
__interrupt void epwm1_isr(void)
{
    if( stg_rteLLCIn.st_CANValue.u8_ClosedLoop == 1U )
    {
        BSW_SET_Freq ( 1U, stg_rteLLCOut.st_PwmValue.f32_fre[ LAYER_A ] );
        BSW_SET_Duty ( 1U, 0.5 );

        BSW_SET_Freq ( 2U, stg_rteLLCOut.st_PwmValue.f32_fre[ LAYER_A ] );
        BSW_SET_Duty ( 2U, 0.5 );

        BSW_SET_Freq ( 3U, stg_rteLLCOut.st_PwmValue.f32_fre[ LAYER_B ] );
        BSW_SET_Duty ( 3U, 0.5 );
    }
    else
    {
        BSW_SET_Freq ( 1U, f32_openloop_fre );
        BSW_SET_Duty ( 1U, 0.5 );

        BSW_SET_Freq ( 2U, f32_openloop_fre );
        BSW_SET_Duty ( 2U, 0.5 );

        BSW_SET_Freq ( 3U, f32_openloop_fre );
        BSW_SET_Duty ( 3U, 0.5 );
    }


    EPwm1Regs.ETCLR.bit.INT = 1;

    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

////
//// epwm2_isr - EPWM2 ISR to update compare values
////
//__interrupt void epwm2_isr(void)
//{
//    EPwm2Regs.ETCLR.bit.INT = 1;
//    // Acknowledge this interrupt to receive more interrupts from group 3
//    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
//}
//
//__interrupt void epwm3_isr(void)
//{
//    EPwm3Regs.ETCLR.bit.INT = 1;
//
//    // Acknowledge this interrupt to receive more interrupts from group 3
//    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
//}

/*--------------------------------------------------------------------------*/
/* Function  | updateDeadtime                                               */
/* Name      | Update Deadtime                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
__interrupt void epwm4_isr(void)
{
    if( stg_rteLLCIn.st_CANValue.u8_ClosedLoop == 1U )
    {
        BSW_SET_Freq ( 4U, stg_rteLLCOut.st_PwmValue.f32_fre[ LAYER_B ] );
        BSW_SET_Duty ( 4U, 0.5 );

        BSW_SET_Freq ( 5U, stg_rteLLCOut.st_PwmValue.f32_fre[ LAYER_C ] );
        BSW_SET_Duty ( 5U, 0.5 );

        BSW_SET_Freq ( 6U, stg_rteLLCOut.st_PwmValue.f32_fre[ LAYER_C ] );
        BSW_SET_Duty ( 6U, 0.5 );
    }
    else
    {
        BSW_SET_Freq ( 4U, f32_openloop_fre );
        BSW_SET_Duty ( 4U, 0.5 );

        BSW_SET_Freq ( 5U, f32_openloop_fre );
        BSW_SET_Duty ( 5U, 0.5 );

        BSW_SET_Freq ( 6U, f32_openloop_fre );
        BSW_SET_Duty ( 6U, 0.5 );
    }

    // Clear INT flag for this timer
    EPwm4Regs.ETCLR.bit.INT = 1;

    // Acknowledge this interrupt to receive more interrupts from group 3
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}


/*--------------------------------------------------------------------------*/
/* Function  | updateDeadtime                                               */
/* Name      | Update Deadtime                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void BSW_SET_Deadtime ( byte u8_ch, single f32_dt_ns )
{
    word deadband;

    deadband = ( word ) ( f32_dt_ns * ( float ) CPU_SPD * 1e-9 );

    ePWM_Regs[ u8_ch ]->DBFED.bit.DBFED = deadband;
    ePWM_Regs[ u8_ch ]->DBRED.bit.DBRED = deadband;
}


/*--------------------------------------------------------------------------*/
/* Function  | updateDuty                                                   */
/* Name      | Duty Update                                                  */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void BSW_SET_Duty ( byte u8_ch, single f32_duty )
{
    ePWM_Regs[ u8_ch ]->CMPA.bit.CMPA = ( word )( ( single )ePWM_Regs[ u8_ch ]->TBPRD * f32_duty );
    ePWM_Regs[ u8_ch ]->CMPB.bit.CMPB = ( word )( ( single )ePWM_Regs[ u8_ch ]->TBPRD * f32_duty );
}
/*--------------------------------------------------------------------------*/
/* Function  | updateFreq                                                   */
/* Name      | Frequency Update                                             */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void BSW_SET_Freq ( byte u8_ch, single f32_freq )
{
    ePWM_Regs[ u8_ch ]->TBPRD = ( word ) ( ( single ) CPU_SPD / ( f32_freq * 2.0f ) - 1.0F );
}

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
