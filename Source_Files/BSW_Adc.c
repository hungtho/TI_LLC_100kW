/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : FDC_LLC                                                     **
**  Filename  : BSW_Adc.c                                                   **
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

#define BSW_ADC_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "BSW_Adc.h"
#include "ASW_Ctrl.h"
#include "math.h"

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
static void BSW_Conf_ADC_A ( void );
static void BSW_Conf_ADC_B ( void );
static void BSW_Conf_ADC_C ( void );
static void BSW_Conf_ADC_D ( void );
static single BSW_ScaleADC_I ( single f32_in );
static single BSW_Log_e_calculation ( single f32_AverAdc );
static single BSW_MovingAvg ( const word u16_ptrArrNumbers[], word u16_buffer_size );

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/
single f32g_LLC_Iout_LPF = 0.0f;
single f32g_LLC_IoutA_LPF = 0.0f;
single f32g_LLC_IoutB_LPF = 0.0f;
single f32g_LLC_IoutC_LPF = 0.0f;
single f32g_LLC_ILinkA_LPF = 0.0f;
single f32g_LLC_ILinkB_LPF = 0.0f;
single f32g_LLC_ILinkC_LPF = 0.0f;
single f32g_LLC_Vout_LPF = 0.0f;
single f32g_LLC_VLink_LPF = 0.0f;

single f32g_LLC_TMP_LPF[ TEMP_CH ] = { 0.0f, };

single f32g_LLC_Power = 0.0f;

/****************************************************************************/
/**                                                                        **/
/**                      GLOBAL VARIABLES                                  **/
/**                                                                        **/
/****************************************************************************/
static word u16s_LLC_ADCA5Buff_I_OutA [ MAX_SAMPLES ];
static word u16s_LLC_ADCA4Buff_I_OutB [ MAX_SAMPLES ];
static word u16s_LLC_ADCA3Buff_I_OutC [ MAX_SAMPLES ];
static word u16s_LLC_ADCA2Buff_Vout [ MAX_SAMPLES ];
static word u16s_LLC_ADCA1Buff_VLink [ MAX_SAMPLES ];

static word u16s_LLC_ADCC4Buff_I_LinkA [ MAX_SAMPLES ];
static word u16s_LLC_ADCC3Buff_I_LinkB [ MAX_SAMPLES ];
static word u16s_LLC_ADCC2Buff_I_LinkC [ MAX_SAMPLES ];

static byte u8s_adca_update_start = 0U;
static byte u8s_adcc_update_start = 0U;
static byte u8s_counterisra = 0U;
static byte u8s_counterisrb = 0U;
static byte u8s_counterisrc = 0U;

static single f32s_LLC_ADCA0_TMP_CH1 = 0.0f;
static single f32s_LLC_ADCB14_TMP_CH2 = 0.0f;
static single f32s_LLC_ADCB15_TMP_CH3 = 0.0f;
static single f32s_LLC_ADCB0_TMP_CH4 = 0.0f;
static single f32s_LLC_ADCB1_TMP_CH5 = 0.0f;
static single f32s_LLC_ADCB2_TMP_CH6 = 0.0f;
static single f32s_LLC_ADCB3_TMP_CH7 = 0.0f;
static single f32s_LLC_ADCD0_TMP_CH8 = 0.0f;
static single f32s_LLC_ADCD1_TMP_CH9 = 0.0f;
static single f32s_LLC_ADCD2_TMP_CH10 = 0.0f;
static single f32s_LLC_ADCD3_TMP_CH11 = 0.0f;
static single f32s_LLC_ADCD4_TMP_CH12 = 0.0f;

static st_Z_1  sts_zILinkA, sts_zILinkB, sts_zILinkC ;
static st_Z_1  sts_zIoutA, sts_zIoutB, sts_zIoutC;
static st_Z_1  sts_zVLink;
static st_Z_1  sts_zVout;

static st_COEF_1  st_coefLPF_Isen;
static st_COEF_1  st_coefLPF_Vsen;

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Function  |  ADC Initialization                                          */
/* Name      |  ADC_Init                                                    */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void BSW_Adc_Init ( void )
{
    BSW_Conf_ADC_A ( );
    BSW_Conf_ADC_B ( );
    BSW_Conf_ADC_C ( );
    BSW_Conf_ADC_D ( );

    sts_zILinkA.in = 0.0f;
    sts_zILinkA.out = 0.0f;
    sts_zILinkB.in = 0.0f;
    sts_zILinkB.out = 0.0f;
    sts_zILinkC.in = 0.0f;
    sts_zILinkC.out = 0.0f;

    sts_zIoutA.in = 0.0f;
    sts_zIoutA.out = 0.0f;
    sts_zIoutB.in = 0.0f;
    sts_zIoutB.out = 0.0f;
    sts_zIoutC.in = 0.0f;
    sts_zIoutC.out = 0.0f;

    sts_zVLink.in = 0.0f;
    sts_zVLink.out = 0.0f;
    sts_zVout.in = 0.0f;
    sts_zVout.out = 0.0f;

    st_coefLPF_Isen.a0 = 0.0f;
    st_coefLPF_Isen.a1 = 0.0f;
    st_coefLPF_Isen.b0 = 0.0f;
    st_coefLPF_Isen.b1 = 0.0f;
    st_coefLPF_Vsen.a0 = 0.0f;
    st_coefLPF_Vsen.a1 = 0.0f;
    st_coefLPF_Vsen.b0 = 0.0f;
    st_coefLPF_Vsen.b1 = 0.0f;

    st_coefLPF_Isen = Asw_Get1stLPFcoef ( 2000.0f, FREQ_SAMPLING );
    st_coefLPF_Vsen = Asw_Get1stLPFcoef ( 2000.0f, FREQ_SAMPLING );

    return;
}

/*--------------------------------------------------------------------------*/
/* Function  | Update ADC values on each reset                              */
/* Name      |  ADC_Update                                                  */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void BSW_Adc_Update ( void )
{
    static single f32s_LLC_IoutA = 0.0f;
    static single f32s_LLC_IoutB = 0.0f;
    static single f32s_LLC_IoutC = 0.0f;
    static single f32s_LLC_ILinkA = 0.0f;
    static single f32s_LLC_ILinkB = 0.0f;
    static single f32s_LLC_ILinkC = 0.0f;
    static single f32s_LLC_Vout = 0.0f;
    static single f32s_LLC_VLink = 0.0f;

    single f32_LLCAdcAver_IoutA = 0.0f;
    single f32_LLCAdcAver_IoutB = 0.0f;
    single f32_LLCAdcAver_IoutC = 0.0f;
    single f32_LLCAdcAver_ILinkA = 0.0f;
    single f32_LLCAdcAver_ILinkB = 0.0f;
    single f32_LLCAdcAver_ILinkC = 0.0f;
    single f32_LLCAdcAver_Vout = 0.0f;
    single f32_LLCAdcAver_VLink = 0.0f;

    if ( u8s_adca_update_start == 1U )
    {
        f32_LLCAdcAver_IoutA = BSW_MovingAvg ( u16s_LLC_ADCA5Buff_I_OutA, MAX_SAMPLES );
        f32_LLCAdcAver_IoutB = BSW_MovingAvg ( u16s_LLC_ADCA4Buff_I_OutB, MAX_SAMPLES );
        f32_LLCAdcAver_IoutC = BSW_MovingAvg ( u16s_LLC_ADCA3Buff_I_OutC, MAX_SAMPLES );
        f32_LLCAdcAver_Vout = BSW_MovingAvg ( u16s_LLC_ADCA2Buff_Vout, MAX_SAMPLES );
        f32_LLCAdcAver_VLink = BSW_MovingAvg ( u16s_LLC_ADCA1Buff_VLink, MAX_SAMPLES );

        f32s_LLC_IoutA = BSW_ScaleADC_I ( f32_LLCAdcAver_IoutA );
        f32s_LLC_IoutB = BSW_ScaleADC_I ( f32_LLCAdcAver_IoutB );
        f32s_LLC_IoutC = BSW_ScaleADC_I ( f32_LLCAdcAver_IoutC );
        f32s_LLC_Vout = BSW_ScaleADC_I ( f32_LLCAdcAver_Vout );
        f32s_LLC_VLink = BSW_ScaleADC_I ( f32_LLCAdcAver_VLink );

        f32g_LLC_IoutA_LPF = Asw_FirstLPF ( f32s_LLC_IoutA, &sts_zIoutA, st_coefLPF_Isen );
        f32g_LLC_IoutB_LPF = Asw_FirstLPF ( f32s_LLC_IoutB, &sts_zIoutB, st_coefLPF_Isen );
        f32g_LLC_IoutC_LPF = Asw_FirstLPF ( f32s_LLC_IoutC, &sts_zIoutC, st_coefLPF_Isen );
        f32g_LLC_Vout_LPF = Asw_FirstLPF ( f32s_LLC_Vout, &sts_zVout, st_coefLPF_Vsen );
        f32g_LLC_VLink_LPF = Asw_FirstLPF ( f32s_LLC_VLink, &sts_zVLink, st_coefLPF_Vsen );

        f32g_LLC_Iout_LPF = f32g_LLC_IoutA_LPF + f32g_LLC_IoutB_LPF + f32g_LLC_IoutC_LPF;
        f32g_LLC_Power =  ( f32g_LLC_Iout_LPF * f32g_LLC_Vout_LPF / 1000.0f );

        u8s_adca_update_start = 0;
    }

    if ( u8s_adcc_update_start == 1U )
    {
        f32_LLCAdcAver_ILinkA = BSW_MovingAvg ( u16s_LLC_ADCC4Buff_I_LinkA, MAX_SAMPLES );
        f32_LLCAdcAver_ILinkB = BSW_MovingAvg ( u16s_LLC_ADCC3Buff_I_LinkB, MAX_SAMPLES );
        f32_LLCAdcAver_ILinkC = BSW_MovingAvg ( u16s_LLC_ADCC2Buff_I_LinkC, MAX_SAMPLES );

        f32s_LLC_ILinkA = BSW_ScaleADC_I ( f32_LLCAdcAver_ILinkA );
        f32s_LLC_ILinkB = BSW_ScaleADC_I ( f32_LLCAdcAver_ILinkB );
        f32s_LLC_ILinkC = BSW_ScaleADC_I ( f32_LLCAdcAver_ILinkC );

        f32g_LLC_ILinkA_LPF = Asw_FirstLPF ( f32s_LLC_ILinkA, &sts_zILinkA, st_coefLPF_Isen );
        f32g_LLC_ILinkB_LPF = Asw_FirstLPF ( f32s_LLC_ILinkB, &sts_zILinkB, st_coefLPF_Isen );
        f32g_LLC_ILinkC_LPF = Asw_FirstLPF ( f32s_LLC_ILinkC, &sts_zILinkC, st_coefLPF_Isen );


        f32g_LLC_TMP_LPF[ TMP_CH1 ] = BSW_Log_e_calculation ( f32s_LLC_ADCA0_TMP_CH1 );
        f32g_LLC_TMP_LPF[ TMP_CH2 ] = BSW_Log_e_calculation ( f32s_LLC_ADCB14_TMP_CH2 );
        f32g_LLC_TMP_LPF[ TMP_CH3 ] = BSW_Log_e_calculation ( f32s_LLC_ADCB15_TMP_CH3 );
        f32g_LLC_TMP_LPF[ TMP_CH4 ] = BSW_Log_e_calculation ( f32s_LLC_ADCB0_TMP_CH4 );
        f32g_LLC_TMP_LPF[ TMP_CH5 ] = BSW_Log_e_calculation ( f32s_LLC_ADCB1_TMP_CH5 );
        f32g_LLC_TMP_LPF[ TMP_CH6 ] = BSW_Log_e_calculation ( f32s_LLC_ADCB2_TMP_CH6 );
        f32g_LLC_TMP_LPF[ TMP_CH7 ] = BSW_Log_e_calculation ( f32s_LLC_ADCB3_TMP_CH7 );
        f32g_LLC_TMP_LPF[ TMP_CH8 ] = BSW_Log_e_calculation ( f32s_LLC_ADCD0_TMP_CH8 );
        f32g_LLC_TMP_LPF[ TMP_CH9 ] = BSW_Log_e_calculation ( f32s_LLC_ADCD1_TMP_CH9 );
        f32g_LLC_TMP_LPF[ TMP_CH10 ] = BSW_Log_e_calculation ( f32s_LLC_ADCD2_TMP_CH10 );
        f32g_LLC_TMP_LPF[ TMP_CH11 ] = BSW_Log_e_calculation ( f32s_LLC_ADCD3_TMP_CH11 );
        f32g_LLC_TMP_LPF[ TMP_CH12 ] = BSW_Log_e_calculation ( f32s_LLC_ADCD4_TMP_CH12 );

        u8s_adcc_update_start = 0;
    }
}

/*--------------------------------------------------------------------------*/
/* Function  |  ADC Interrupt Handler                                       */
/* Name      |  adc_isr                                                     */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
interrupt void adca_isr ( void )
{
    volatile word TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER    &= MINT1;
    PieCtrlRegs.PIEIER1.all &= MG1_1;
    PieCtrlRegs.PIEACK.all = 0xFFFF;
    __asm("  NOP");
    EINT;
    SET_TP18;

    u16s_LLC_ADCA5Buff_I_OutA [ u8s_counterisra ] = AdcaResultRegs.ADCRESULT0;     /*  I-OUT-A  */
    u16s_LLC_ADCA4Buff_I_OutB [ u8s_counterisra ] = AdcaResultRegs.ADCRESULT1;     /*  I-OUT-B  */
    u16s_LLC_ADCA3Buff_I_OutC [ u8s_counterisra ] = AdcaResultRegs.ADCRESULT2;     /*  I-OUT-C  */
    u16s_LLC_ADCA2Buff_Vout [ u8s_counterisra ] = AdcaResultRegs.ADCRESULT3;       /*  V_OUT */
    u16s_LLC_ADCA1Buff_VLink [ u8s_counterisra ] = AdcaResultRegs.ADCRESULT4;      /*  V_LINK */
    f32s_LLC_ADCA0_TMP_CH1 = AdcaResultRegs.ADCRESULT5;                            /*  TMP_CH1 */

    ++ u8s_counterisra;
    if (u8s_counterisra >= MAX_SAMPLES)
    {
        u8s_counterisra = 0U;
        u8s_adca_update_start = 1U;
    }

    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;      /* clear INT1 flag */

    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;
    CLEAR_TP18;
}

/*--------------------------------------------------------------------------*/
/* Function  |  ADC Interrupt Handler                                       */
/* Name      |  adc_isr                                                     */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
interrupt void adcb_isr ( void )
{
    volatile word TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER    &= MINT1;
    PieCtrlRegs.PIEIER1.all &= MG1_2;
    PieCtrlRegs.PIEACK.all = 0xFFFF;
    __asm("  NOP");
    EINT;
    SET_TP18;

    f32s_LLC_ADCB14_TMP_CH2 = AdcbResultRegs.ADCRESULT4;        /*  TMP_CH2 */
    f32s_LLC_ADCB15_TMP_CH3 = AdcbResultRegs.ADCRESULT5;        /*  TMP_CH3 */
    f32s_LLC_ADCB0_TMP_CH4 = AdcbResultRegs.ADCRESULT0;         /*  TMP_CH4 */
    f32s_LLC_ADCB1_TMP_CH5 = AdcbResultRegs.ADCRESULT1;         /*  TMP_CH5 */
    f32s_LLC_ADCB2_TMP_CH6 = AdcbResultRegs.ADCRESULT2;         /*  TMP_CH6 */
    f32s_LLC_ADCB3_TMP_CH7 = AdcbResultRegs.ADCRESULT3;         /*  TMP_CH7 */

    ++ u8s_counterisrb;
    if( u8s_counterisrb >= MAX_SAMPLES)
    {
        u8s_counterisrb = 0U;
    }

    AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;      /* clear INT1 flag */
    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;
    CLEAR_TP18;
}

/*--------------------------------------------------------------------------*/
/* Function  |  ADC Interrupt Handler                                       */
/* Name      |  adc_isr                                                     */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
interrupt void adcc_isr ( void )
{
    volatile word TempPIEIER = PieCtrlRegs.PIEIER1.all;
    IER |= M_INT1;
    IER    &= MINT1;
    PieCtrlRegs.PIEIER1.all &= MG1_3;
    PieCtrlRegs.PIEACK.all = 0xFFFF;
    __asm("  NOP");
    EINT;
    SET_TP18;

    u16s_LLC_ADCC4Buff_I_LinkA [ u8s_counterisrc ] = AdccResultRegs.ADCRESULT0;     /*  I-LINK-A  */
    u16s_LLC_ADCC3Buff_I_LinkB [ u8s_counterisrc ] = AdccResultRegs.ADCRESULT1;     /*  I-LINK-B  */
    u16s_LLC_ADCC2Buff_I_LinkC [ u8s_counterisrc ] = AdccResultRegs.ADCRESULT2;     /*  I-LINK-C  */

    f32s_LLC_ADCD0_TMP_CH8 = AdcdResultRegs.ADCRESULT0;         /*  TMP_CH8 */
    f32s_LLC_ADCD1_TMP_CH9 = AdcdResultRegs.ADCRESULT1;         /*  TMP_CH9 */
    f32s_LLC_ADCD2_TMP_CH10 = AdcdResultRegs.ADCRESULT2;         /*  TMP_CH10 */
    f32s_LLC_ADCD3_TMP_CH11 = AdcdResultRegs.ADCRESULT3;         /*  TMP_CH11 */
    f32s_LLC_ADCD4_TMP_CH12 = AdcdResultRegs.ADCRESULT4;         /*  TMP_CH12 */

    ++ u8s_counterisrc;
    if (u8s_counterisrc >= MAX_SAMPLES)
    {
        u8s_counterisrc = 0U;
        u8s_adcc_update_start = 1U;
    }

    AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;      /* clear INT1 flag */
    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;
    CLEAR_TP18;
}


/****************************************************************************/
/**                                                                        **/
/**                      LOCAL FUNCTIONS                                   **/
/**                                                                        **/
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Function  |   u16_ADC_A Configuration                                    */
/* Name      |   Conf_u16_ADC_A                                             */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void BSW_Conf_ADC_A ( void )
{
    word acqps;
    EALLOW;
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6;
    AdcaRegs.ADCCTL2.bit.RESOLUTION = ADC_RESOLUTION_12BIT;
    AdcaRegs.ADCCTL2.bit.SIGNALMODE = ADC_SIGNALMODE_SINGLE;
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    DELAY_US( 1000 );
    EDIS;

    EALLOW;
    if ( ADC_RESOLUTION_12BIT == AdcaRegs.ADCCTL2.bit.RESOLUTION ) {  acqps = 14; }
    else { acqps = 63; }

    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 5;  /* I-OUT-A, ADC group A channel 5 */
    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 4;  /* I-OUT-B, ADC group A channel 4 */
    AdcaRegs.ADCSOC2CTL.bit.CHSEL = 3;  /* I-OUT-C, ADC group A channel 3 */
    AdcaRegs.ADCSOC3CTL.bit.CHSEL = 1;  /* V_OUT, ADC group A channel 1 */
    AdcaRegs.ADCSOC4CTL.bit.CHSEL = 2;  /* V_LINK, ADC group A channel 2*/
    AdcaRegs.ADCSOC5CTL.bit.CHSEL = 0;  /* TMP_CH1, ADC group A channel 0 */

    AdcaRegs.ADCSOC0CTL.bit.ACQPS = acqps;
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = acqps;
    AdcaRegs.ADCSOC2CTL.bit.ACQPS = acqps;
    AdcaRegs.ADCSOC3CTL.bit.ACQPS = acqps;
    AdcaRegs.ADCSOC4CTL.bit.ACQPS = acqps;
    AdcaRegs.ADCSOC5CTL.bit.ACQPS = acqps;

    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 5;           /* SOC Trigger Source is EPWM1 ADCSOCA */
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 9;           /* SOC Trigger Source is EPWM3 ADCSOCA */
    AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = 13;          /* SOC Trigger Source is EPWM5 ADCSOCA */

    AdcaRegs.ADCSOC3CTL.bit.TRIGSEL = 9;           /* SOC Trigger Source is EPWM3 ADCSOCA */
    AdcaRegs.ADCSOC4CTL.bit.TRIGSEL = 9;           /* SOC Trigger Source is EPWM3 ADCSOCA */
    AdcaRegs.ADCSOC5CTL.bit.TRIGSEL = 9;           /* SOC Trigger Source is EPWM3 ADCSOCA */

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 5;         /* 5 means number of ADC conversions are completed */
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;           /* Enable the interrupt for ADC group A*/
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    EDIS;
}

/*--------------------------------------------------------------------------*/
/* Function  |  u16_ADC_B Configuration                                     */
/* Name      |   conf_u16_ADC_B                                             */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void BSW_Conf_ADC_B ( void )
{
    word acqps;
    EALLOW;
    AdcbRegs.ADCCTL2.bit.PRESCALE = 6;
    AdcbRegs.ADCCTL2.bit.RESOLUTION = ADC_RESOLUTION_12BIT;
    AdcbRegs.ADCCTL2.bit.SIGNALMODE = ADC_SIGNALMODE_SINGLE;
    AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    DELAY_US ( 1000 );
    EDIS;

    EALLOW;
    if ( ADC_RESOLUTION_12BIT == AdcbRegs.ADCCTL2.bit.RESOLUTION ) {  acqps = 14; }
    else { acqps = 63; }

    AdcbRegs.ADCSOC0CTL.bit.CHSEL = 0;      /* TMP_CH4 */
    AdcbRegs.ADCSOC1CTL.bit.CHSEL = 1;      /* TMP_CH5 */
    AdcbRegs.ADCSOC2CTL.bit.CHSEL = 2;      /* TMP_CH6 */
    AdcbRegs.ADCSOC3CTL.bit.CHSEL = 3;      /* TMP_CH7 */
    AdcbRegs.ADCSOC4CTL.bit.CHSEL = 14;     /* TMP_CH2 */
    AdcbRegs.ADCSOC5CTL.bit.CHSEL = 15;     /* TMP_CH3 */

    AdcbRegs.ADCSOC0CTL.bit.ACQPS = acqps;
    AdcbRegs.ADCSOC1CTL.bit.ACQPS = acqps;
    AdcbRegs.ADCSOC2CTL.bit.ACQPS = acqps;
    AdcbRegs.ADCSOC3CTL.bit.ACQPS = acqps;
    AdcbRegs.ADCSOC4CTL.bit.ACQPS = acqps;
    AdcbRegs.ADCSOC5CTL.bit.ACQPS = acqps;

    AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = 9;       /* SOC Trigger Source is EPWM3A ADCSOCA */
    AdcbRegs.ADCSOC1CTL.bit.TRIGSEL = 9;       /* SOC Trigger Source is EPWM3A ADCSOCA */
    AdcbRegs.ADCSOC2CTL.bit.TRIGSEL = 9;       /* SOC Trigger Source is EPWM3A ADCSOCA */
    AdcbRegs.ADCSOC3CTL.bit.TRIGSEL = 9;       /* SOC Trigger Source is EPWM3A ADCSOCA */
    AdcbRegs.ADCSOC4CTL.bit.TRIGSEL = 9;       /* SOC Trigger Source is EPWM3A ADCSOCA */
    AdcbRegs.ADCSOC5CTL.bit.TRIGSEL = 9;       /* SOC Trigger Source is EPWM3A ADCSOCA */

    AdcbRegs.ADCINTSEL1N2.bit.INT1SEL = 5;
    AdcbRegs.ADCINTSEL1N2.bit.INT1E = 1;
    AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    EDIS;
}

/*--------------------------------------------------------------------------*/
/* Function  |  u16_ADC_C Configuration                                     */
/* Name      |   conf_u16_ADC_C                                             */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void BSW_Conf_ADC_C ( void )
{
    word acqps;
    EALLOW;
    AdccRegs.ADCCTL2.bit.PRESCALE = 6;
    AdccRegs.ADCCTL2.bit.RESOLUTION = ADC_RESOLUTION_12BIT;
    AdccRegs.ADCCTL2.bit.SIGNALMODE = ADC_SIGNALMODE_SINGLE;
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    DELAY_US ( 1000 );
    EDIS;

    EALLOW;
    if ( ADC_RESOLUTION_12BIT == AdccRegs.ADCCTL2.bit.RESOLUTION ) {  acqps = 14; }
    else { acqps = 63; }

    AdccRegs.ADCSOC0CTL.bit.CHSEL = 4;  /* I-LINK-A */
    AdccRegs.ADCSOC1CTL.bit.CHSEL = 3;  /* I-LINK-B */
    AdccRegs.ADCSOC2CTL.bit.CHSEL = 2;  /* I-LINK-C */

    AdccRegs.ADCSOC0CTL.bit.ACQPS = acqps;
    AdccRegs.ADCSOC1CTL.bit.ACQPS = acqps;
    AdccRegs.ADCSOC2CTL.bit.ACQPS = acqps;

    AdccRegs.ADCSOC0CTL.bit.TRIGSEL = 5;       /* SOC Trigger Source is EPWM1 ADCSOCA */
    AdccRegs.ADCSOC1CTL.bit.TRIGSEL = 9;       /* SOC Trigger Source is EPWM3 ADCSOCA */
    AdccRegs.ADCSOC2CTL.bit.TRIGSEL = 9;      /* SOC Trigger Source is EPWM5 ADCSOCA */

    AdccRegs.ADCINTSEL1N2.bit.INT1SEL = 2;     /* 2 means number of ADC inputs */
    AdccRegs.ADCINTSEL1N2.bit.INT1E = 1;
    AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

    EDIS;
}

/*--------------------------------------------------------------------------*/
/* Function  |  u16_ADC_B Configuration                                     */
/* Name      |   conf_u16_ADC_B                                             */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void BSW_Conf_ADC_D ( void )
{
    word acqps;

    EALLOW;
    AdcdRegs.ADCCTL2.bit.PRESCALE = 6;
    AdcdRegs.ADCCTL2.bit.RESOLUTION = ADC_RESOLUTION_12BIT;
    AdcdRegs.ADCCTL2.bit.SIGNALMODE = ADC_SIGNALMODE_SINGLE;
    AdcdRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcdRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    DELAY_US ( 1000 );
    EDIS;

    EALLOW;
    if ( ADC_RESOLUTION_12BIT == AdcdRegs.ADCCTL2.bit.RESOLUTION ) {  acqps = 14; }
    else { acqps = 63; }

    AdcdRegs.ADCSOC0CTL.bit.CHSEL = 0;       /* TMP_CH8 */
    AdcdRegs.ADCSOC1CTL.bit.CHSEL = 1;       /* TMP_CH9 */
    AdcdRegs.ADCSOC2CTL.bit.CHSEL = 2;       /* TMP_CH10 */
    AdcdRegs.ADCSOC3CTL.bit.CHSEL = 3;       /* TMP_CH11 */
    AdcdRegs.ADCSOC4CTL.bit.CHSEL = 4;       /* TMP_CH12 */

    AdcdRegs.ADCSOC0CTL.bit.ACQPS = acqps;
    AdcdRegs.ADCSOC1CTL.bit.ACQPS = acqps;
    AdcdRegs.ADCSOC2CTL.bit.ACQPS = acqps;
    AdcdRegs.ADCSOC3CTL.bit.ACQPS = acqps;
    AdcdRegs.ADCSOC4CTL.bit.ACQPS = acqps;

    AdcdRegs.ADCSOC0CTL.bit.TRIGSEL = 9;         /* SOC Trigger Source is EPWM3 ADCSOCA */
    AdcdRegs.ADCSOC1CTL.bit.TRIGSEL = 9;         /* SOC Trigger Source is EPWM3 ADCSOCA */
    AdcdRegs.ADCSOC2CTL.bit.TRIGSEL = 9;         /* SOC Trigger Source is EPWM3 ADCSOCA */
    AdcdRegs.ADCSOC3CTL.bit.TRIGSEL = 9;         /* SOC Trigger Source is EPWM3 ADCSOCA */
    AdcdRegs.ADCSOC4CTL.bit.TRIGSEL = 9;          /* SOC Trigger Source is EPWM3 ADCSOCA */

    EDIS;
}

/*--------------------------------------------------------------------------*/
/* Function  |  log_e_calculation                                           */
/* Name      |   Log E Calc                                                 */
/*--------------------------------------------------------------------------*/
/* Parameter | Avg ADC Value                                                */
/* Return    | Result                                                       */
/*--------------------------------------------------------------------------*/
static single BSW_Log_e_calculation ( single f32_AverAdc )
{
    single f32_rtn = 0.0f;
    f32_rtn = ( -39.47f *( ( single ) log  ( ( single ) f32_AverAdc ) ) ) + 325.33f ;  /* Based on Calibration on 24th Oct 2019 */
    if ( f32_rtn >= 170.0f ) { f32_rtn = 170.0f; }
    if ( f32_rtn <= 0.0f ) { f32_rtn = 0.0f; }

    return f32_rtn;
}

/*--------------------------------------------------------------------------*/
/* Function  |  scaleADC_I                                                  */
/* Name      |  Scaling of ADC value                                        */
/*--------------------------------------------------------------------------*/
/* Parameter | input, channel                                               */
/* Return    | Result                                                       */
/*--------------------------------------------------------------------------*/
static single BSW_ScaleADC_I ( single f32_in )
{
    single f32_rtn = 0.0F;
    single f_scaleI = 0.0F;
    single f_ADC_I = 0.0F;

    f_ADC_I =  ( single ) f32_in * f_scaleI;

    f32_rtn =  f_ADC_I + 0.01f ;

    f32_rtn = ( 117.3f * f32_rtn ) - 125.17f;
    f32_rtn = f32_rtn * 1.04f;   /* 1.04 is current factor for better current accurancy in 40kW area */

    return f32_rtn;
}

/*--------------------------------------------------------------------------*/
/* Function  | avg_cal                                                      */
/* Name      | Calculate average                                            */
/*--------------------------------------------------------------------------*/
/* Parameter | ADC Values, Max Samples                                      */
/* Return    | Result                                                       */
/*--------------------------------------------------------------------------*/
static single BSW_MovingAvg ( const word u16_ptrArrNumbers[], word u16_buffer_size )
{
  byte u8_cnt = 0U;
  single f32_AvgRet;
  word u16_Max = u16_ptrArrNumbers[ 0U ];
  word u16_Min = u16_ptrArrNumbers[ 0U ];
  word u16_Sum = 0U;

  for( u8_cnt = 0U; u8_cnt < u16_buffer_size; u8_cnt++ )
  {
    u16_Sum += u16_ptrArrNumbers[ u8_cnt ];
    if( u16_ptrArrNumbers[ u8_cnt ] > u16_Max ){ u16_Max = u16_ptrArrNumbers[ u8_cnt ]; }
    if( u16_ptrArrNumbers[ u8_cnt ] < u16_Min ){ u16_Min = u16_ptrArrNumbers[ u8_cnt ]; }
  }

  u16_Sum = u16_Sum - ( ( uint32_t )u16_Max + u16_Min );
  f32_AvgRet = ( single )( ( single )u16_Sum / ( u16_buffer_size -2U ) );

  /*return the average*/
  return ( f32_AvgRet );
}

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
