/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : FDC_LLC                                                     **
**  Filename  : ASW_Fault.c                                                 **
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

#define ASW_FAULT_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "F2837xS_SWPrioritizedIsrLevels.h"
#include "F28x_Project.h"
#include "math.h"
#include "ASW_Config.h"
#include <ASW_LLCState.h>
#include <ASW_Diag.h>
#include "ASW_Ctrl.h"
#include "BSW_Adc.h"
#include "BSW_Gpio.h"
#include "BSW_Pwm.h"
#include "BSW_Timer.h"

/****************************************************************************/
/**                                                                        **/
/**                      DEFINITIONS AND MACROS                            **/
/**                                                                        **/
/****************************************************************************/
#define OVER_CNT  (3U)
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
static en_STATE_DEF DiagAdc_LLCInputV ( en_STATE_DEF u8_HV_V, st_AdcLimitValue *stp_AdcLimit, single f32_adcRealInputV );
static en_STATE_DEF DiagAdc_LLCInputI ( en_STATE_DEF u8_HV_I, st_AdcLimitValue *stp_AdcLimit, single f32_adcRealInputI );
static en_STATE_DEF DiagAdc_LLCOutputV ( en_STATE_DEF u8_LV_V, st_AdcLimitValue *stp_AdcLimit, single f32_adcRealOutputV );
static en_STATE_DEF DiagAdc_LLCOutputI ( en_STATE_DEF u8_LV_I, st_AdcLimitValue *stp_AdcLimit, single f32_adcRealOutputI );
static en_STATE_DEF DiagAdc_LLCTemp ( en_STATE_DEF u8_Temp, st_AdcLimitValue *stp_AdcLimit, single f32_adcRealTemp );

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
static st_AdcLimitValue sts_VinLimit;
static st_AdcLimitValue sts_IinLimit;
static st_AdcLimitValue sts_VoutLimit;
static st_AdcLimitValue sts_IoutLimit;
static st_AdcLimitValue sts_TempSw3Limit;
static st_AdcLimitValue sts_TempSw4Limit;

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
void Asw_LLC_AdcInit ( void )
{
    sts_VinLimit.f32_limit [ NOR_LOWER ] = LLC_VIN_NOR_LOWER;
    sts_VinLimit.f32_limit [ NOR_UPPER ] = LLC_VIN_NOR_UPPER;
    sts_VinLimit.f32_limit [ NOR_RECOVER_LOWER ] = LLC_VIN_NOR_RECOVER_LOWER;
    sts_VinLimit.f32_limit [ NOR_RECOVER_UPPER ] = LLC_VIN_NOR_RECOVER_UPPER;

    sts_IinLimit.f32_limit [ NOR_LOWER ] = LLC_IIN_NOR_LOWER;
    sts_IinLimit.f32_limit [ NOR_UPPER ] = LLC_IIN_NOR_UPPER;
    sts_IinLimit.f32_limit [ NOR_RECOVER_LOWER ] = LLC_IIN_NOR_RECOVER_LOWER;
    sts_IinLimit.f32_limit [ NOR_RECOVER_UPPER ] = LLC_IIN_NOR_RECOVER_UPPER;

    sts_VoutLimit.f32_limit [ NOR_LOWER ] = LLC_VOUT_NOR_LOWER;
    sts_VoutLimit.f32_limit [ NOR_UPPER ] = LLC_VOUT_NOR_UPPER;
    sts_VoutLimit.f32_limit [ NOR_RECOVER_LOWER ] = LLC_VOUT_NOR_RECOVER_LOWER;
    sts_VoutLimit.f32_limit [ NOR_RECOVER_UPPER ] = LLC_VOUT_NOR_RECOVER_UPPER;

    sts_IoutLimit.f32_limit [ NOR_LOWER ] = LLC_IOUT_NOR_LOWER;
    sts_IoutLimit.f32_limit [ NOR_UPPER ] = LLC_IOUT_NOR_UPPER;
    sts_IoutLimit.f32_limit [ NOR_RECOVER_LOWER ] = LLC_IOUT_NOR_RECOVER_LOWER;
    sts_IoutLimit.f32_limit [ NOR_RECOVER_UPPER ] = LLC_IOUT_NOR_RECOVER_UPPER;

    sts_TempSw3Limit.f32_limit [ NOR_LOWER ] = LLC_TEMP_NOR_LOWER;
    sts_TempSw3Limit.f32_limit [ NOR_UPPER ] = LLC_TEMP_NOR_UPPER;
    sts_TempSw3Limit.f32_limit [ NOR_RECOVER_LOWER ] = LLC_TEMP_NOR_RECOVER_LOWER;
    sts_TempSw3Limit.f32_limit [ NOR_RECOVER_UPPER ] = LLC_TEMP_NOR_RECOVER_UPPER;
//    sts_TempSw3Limit.f32_limit [ FAULT_UPPER ] = LLC_TEMP_FAULT_UPPER;

    sts_TempSw4Limit.f32_limit [ NOR_LOWER ] = LLC_TEMP_NOR_LOWER;
    sts_TempSw4Limit.f32_limit [ NOR_UPPER ] = LLC_TEMP_NOR_UPPER;
    sts_TempSw4Limit.f32_limit [ NOR_RECOVER_LOWER ] = LLC_TEMP_NOR_RECOVER_LOWER;
    sts_TempSw4Limit.f32_limit [ NOR_RECOVER_UPPER ] = LLC_TEMP_NOR_RECOVER_UPPER;
//    sts_TempSw4Limit.f32_limit [ FAULT_UPPER ] = LLC_TEMP_FAULT_UPPER;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void Asw_LLC_DiagAdcValues ( st_DiagnosisType *stp_DiagFlags, const st_RealValuesType *stp_adcValues )
{
    st_AdcLimitValue *stp_AdcVinLimit = &sts_VinLimit;
    st_AdcLimitValue *stp_AdcIinLimit = &sts_IinLimit;
    st_AdcLimitValue *stp_AdcVoutLimit = &sts_VoutLimit;
    st_AdcLimitValue *stp_AdcIoutLimit = &sts_IoutLimit;
    st_AdcLimitValue *stp_AdcTempSw3Limit = &sts_TempSw3Limit;
    st_AdcLimitValue *stp_AdcTempSw4Limit = &sts_TempSw4Limit;

    stp_DiagFlags->u8_VLink = DiagAdc_LLCInputV ( stp_DiagFlags->u8_VLink, stp_AdcVinLimit, stp_adcValues->f32_VLink );
    stp_DiagFlags->u8_ILinkA = DiagAdc_LLCInputI ( stp_DiagFlags->u8_ILinkA, stp_AdcIinLimit, stp_adcValues->f32_ILinkA );
    stp_DiagFlags->u8_ILinkB = DiagAdc_LLCInputI ( stp_DiagFlags->u8_ILinkB, stp_AdcIinLimit, stp_adcValues->f32_ILinkB );
    stp_DiagFlags->u8_ILinkC = DiagAdc_LLCInputI ( stp_DiagFlags->u8_ILinkC, stp_AdcIinLimit, stp_adcValues->f32_ILinkC );
    stp_DiagFlags->u8_Vout = DiagAdc_LLCOutputV ( stp_DiagFlags->u8_Vout, stp_AdcVoutLimit, stp_adcValues->f32_Vout );
    stp_DiagFlags->u8_IoutA = DiagAdc_LLCOutputI ( stp_DiagFlags->u8_IoutA, stp_AdcIoutLimit, stp_adcValues->f32_IoutA );
    stp_DiagFlags->u8_IoutB = DiagAdc_LLCOutputI ( stp_DiagFlags->u8_IoutB, stp_AdcIoutLimit, stp_adcValues->f32_IoutB );
    stp_DiagFlags->u8_IoutC = DiagAdc_LLCOutputI ( stp_DiagFlags->u8_IoutC, stp_AdcIoutLimit, stp_adcValues->f32_IoutC );

    stp_DiagFlags->u8_TMP_CH1 = DiagAdc_LLCTemp ( stp_DiagFlags->u8_TMP_CH1, stp_AdcTempSw3Limit, stp_adcValues->f32_TMP_CH[ TMP_CH1] );
    stp_DiagFlags->u8_TMP_CH2 = DiagAdc_LLCTemp ( stp_DiagFlags->u8_TMP_CH2, stp_AdcTempSw4Limit, stp_adcValues->f32_TMP_CH[ TMP_CH2] );
    stp_DiagFlags->u8_TMP_CH3 = DiagAdc_LLCTemp ( stp_DiagFlags->u8_TMP_CH3, stp_AdcTempSw3Limit, stp_adcValues->f32_TMP_CH[ TMP_CH3] );
    stp_DiagFlags->u8_TMP_CH4 = DiagAdc_LLCTemp ( stp_DiagFlags->u8_TMP_CH4, stp_AdcTempSw4Limit, stp_adcValues->f32_TMP_CH[ TMP_CH4] );
    stp_DiagFlags->u8_TMP_CH5 = DiagAdc_LLCTemp ( stp_DiagFlags->u8_TMP_CH5, stp_AdcTempSw3Limit, stp_adcValues->f32_TMP_CH[ TMP_CH5] );
    stp_DiagFlags->u8_TMP_CH6 = DiagAdc_LLCTemp ( stp_DiagFlags->u8_TMP_CH6, stp_AdcTempSw4Limit, stp_adcValues->f32_TMP_CH[ TMP_CH6] );
    stp_DiagFlags->u8_TMP_CH7 = DiagAdc_LLCTemp ( stp_DiagFlags->u8_TMP_CH7, stp_AdcTempSw3Limit, stp_adcValues->f32_TMP_CH[ TMP_CH7] );
    stp_DiagFlags->u8_TMP_CH8 = DiagAdc_LLCTemp ( stp_DiagFlags->u8_TMP_CH8, stp_AdcTempSw4Limit, stp_adcValues->f32_TMP_CH[ TMP_CH8] );
    stp_DiagFlags->u8_TMP_CH9 = DiagAdc_LLCTemp ( stp_DiagFlags->u8_TMP_CH9, stp_AdcTempSw3Limit, stp_adcValues->f32_TMP_CH[ TMP_CH9] );
    stp_DiagFlags->u8_TMP_CH10 = DiagAdc_LLCTemp ( stp_DiagFlags->u8_TMP_CH10, stp_AdcTempSw4Limit, stp_adcValues->f32_TMP_CH[ TMP_CH10 ] );
    stp_DiagFlags->u8_TMP_CH11 = DiagAdc_LLCTemp ( stp_DiagFlags->u8_TMP_CH11, stp_AdcTempSw4Limit, stp_adcValues->f32_TMP_CH[ TMP_CH11 ] );
    stp_DiagFlags->u8_TMP_CH12 = DiagAdc_LLCTemp ( stp_DiagFlags->u8_TMP_CH12, stp_AdcTempSw4Limit, stp_adcValues->f32_TMP_CH[ TMP_CH12 ] );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
en_STATE_DEF Asw_Adc_NormalMode( st_AdcLimitValue *stp_Limit, single f32_adcRealValue )
{
    en_STATE_DEF u8_rtn = STATE_NORMAL;

    if( f32_adcRealValue < stp_Limit->f32_limit[ NOR_LOWER ] )
    {
        stp_Limit->u16_FaultOvertCnt = 0U;

        if( stp_Limit->u16_FaultUnderCnt < MAX_FLT_CNT )
        {
            stp_Limit->u16_FaultUnderCnt++;
            u8_rtn = STATE_NORMAL;
        }
        else
        {
            u8_rtn = STATE_UNDER; /* exist problem */
        }
    }
    else if( ( stp_Limit->f32_limit[ NOR_LOWER ] <= f32_adcRealValue ) && ( f32_adcRealValue <= stp_Limit->f32_limit[ NOR_UPPER ] ) )
    {
        u8_rtn = STATE_NORMAL; /* no problem */
        stp_Limit->u16_FaultUnderCnt = 0U;
        stp_Limit->u16_FaultOvertCnt = 0U;
    }
    else
    {
        stp_Limit->u16_FaultUnderCnt = 0U;

        if( stp_Limit->u16_FaultOvertCnt < MAX_FLT_CNT )
        {
            stp_Limit->u16_FaultOvertCnt++;
            u8_rtn = STATE_NORMAL;
        }
        else
        {
            u8_rtn = STATE_OVER; /* exist problem */
        }
    }

    return u8_rtn;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
en_STATE_DEF Asw_Adc_UnderMode ( st_AdcLimitValue *stp_Limit, single f32_adcRealValue )
{
    en_STATE_DEF u8_rtn = STATE_NORMAL;

    if( f32_adcRealValue < stp_Limit->f32_limit[ NOR_RECOVER_LOWER ] )
    {
        stp_Limit->u16_FaultOvertCnt = 0U;
        u8_rtn = STATE_UNDER; /* exist problem */
    }
    else if( ( stp_Limit->f32_limit[ NOR_RECOVER_LOWER ] <= f32_adcRealValue ) && ( f32_adcRealValue <= stp_Limit->f32_limit[ NOR_RECOVER_UPPER ] ) )
    {
        u8_rtn = STATE_NORMAL; /* no problem */
        stp_Limit->u16_FaultUnderCnt = 0U;
        stp_Limit->u16_FaultOvertCnt = 0U;
    }
    else
    {
        stp_Limit->u16_FaultUnderCnt = 0U;

        if( stp_Limit->u16_FaultOvertCnt < MAX_FLT_CNT )
        {
            stp_Limit->u16_FaultOvertCnt++;
            u8_rtn = STATE_UNDER;
        }
        else
        {
            u8_rtn = STATE_OVER; /* exist problem */
        }
    }

    return u8_rtn;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
en_STATE_DEF Asw_Adc_OverMode ( st_AdcLimitValue *stp_Limit, single f32_adcRealValue )
{
    en_STATE_DEF u8_rtn = STATE_NORMAL;

    if( f32_adcRealValue > stp_Limit->f32_limit[ NOR_RECOVER_UPPER ] )
    {
        stp_Limit->u16_FaultUnderCnt = 0U;
        u8_rtn = STATE_OVER; /* exist problem */
    }
    else if( ( stp_Limit->f32_limit[ NOR_RECOVER_LOWER ] <= f32_adcRealValue ) && ( f32_adcRealValue <= stp_Limit->f32_limit[ NOR_RECOVER_UPPER ] ) )
    {
        u8_rtn = STATE_NORMAL; /* no problem */
        stp_Limit->u16_FaultUnderCnt = 0U;
        stp_Limit->u16_FaultOvertCnt = 0U;
    }
    else
    {
        stp_Limit->u16_FaultOvertCnt = 0U;

        if( stp_Limit->u16_FaultUnderCnt < MAX_FLT_CNT )
        {
            stp_Limit->u16_FaultUnderCnt++;
            u8_rtn = STATE_OVER;
        }
        else
        {
            u8_rtn = STATE_UNDER; /* exist problem */
        }
    }

    return u8_rtn;
}

///*--------------------------------------------------------------------------*/
///* Function  |                                                              */
///* Name      |                                                              */
///*--------------------------------------------------------------------------*/
///* Parameter | Nothing                                                      */
///* Return    | Nothing                                                      */
///*--------------------------------------------------------------------------*/
//en_STATE_DEF Asw_Adc_TempNormalMode ( st_AdcLimitValue *stp_Limit, single f32_adcRealTemp )
//{
//    en_STATE_DEF u8_rtn = stg_AswLLCDiagFlag.u8_TempSW3;
//
//    if( ( stp_Limit->f32_limit[ NOR_LOWER ] <= f32_adcRealTemp ) && ( f32_adcRealTemp <= stp_Limit->f32_limit[ NOR_UPPER ] ) )
//    {
//        u8_rtn = STATE_NORMAL; /* no problem */
//        stp_Limit->u16_FaultUnderCnt = 0U;
//        stp_Limit->u16_FaultOvertCnt = 0U;
//        stp_Limit->u16_DeratingCnt = 0U;
//    }
//    else if( f32_adcRealTemp < stp_Limit->f32_limit[ NOR_LOWER ] )
//    {
//        stp_Limit->u16_FaultOvertCnt = 0U;
//        stp_Limit->u16_DeratingCnt = 0U;
//
//        if( stp_Limit->u16_FaultUnderCnt < MAX_FLT_CNT )
//        {
//            stp_Limit->u16_FaultUnderCnt++;
//        }
//        else
//        {
//            u8_rtn = STATE_UNDER; /* exist problem */
//        }
//    }
//    else if( f32_adcRealTemp > stp_Limit->f32_limit[ FAULT_UPPER ] )
//    {
//        stp_Limit->u16_FaultUnderCnt = 0U;
//        stp_Limit->u16_DeratingCnt = 0U;
//
//        if( stp_Limit->u16_FaultOvertCnt < MAX_FLT_CNT )
//        {
//            stp_Limit->u16_FaultOvertCnt++;
//        }
//        else
//        {
//            u8_rtn = STATE_OVER; /* exist problem */
//        }
//    }
//    else
//    {
//        stp_Limit->u16_FaultUnderCnt = 0U;
//        stp_Limit->u16_FaultOvertCnt = 0U;
//        if( stp_Limit->u16_DeratingCnt < MAX_FLT_CNT )
//        {
//            stp_Limit->u16_DeratingCnt++;
//        }
//        else
//        {
//            u8_rtn = STATE_DERATING;
//        }
//    }
//    return u8_rtn;
//}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
//en_STATE_DEF Asw_Adc_TempFaultMode ( st_AdcLimitValue *stp_Limit, single f32_adcRealTemp )
//{
//    en_STATE_DEF u8_rtn = stg_AswLLCDiagFlag.u8_TempSW3;
//
//    if( ( stp_Limit->f32_limit[ NOR_RECOVER_LOWER ] <= f32_adcRealTemp ) && ( f32_adcRealTemp <= stp_Limit->f32_limit[ NOR_RECOVER_UPPER ] ) )
//    {
//        u8_rtn = STATE_NORMAL; /* no problem */
//        stp_Limit->u16_FaultUnderCnt = 0U;
//        stp_Limit->u16_FaultOvertCnt = 0U;
//        stp_Limit->u16_DeratingCnt = 0U;
//    }
//    else if( f32_adcRealTemp < stp_Limit->f32_limit[ NOR_RECOVER_LOWER ] )
//    {
//        stp_Limit->u16_FaultOvertCnt = 0U;
//        stp_Limit->u16_DeratingCnt = 0U;
//
//        if( stp_Limit->u16_FaultUnderCnt < MAX_FLT_CNT )
//        {
//            stp_Limit->u16_FaultUnderCnt++;
//        }
//        else
//        {
//            u8_rtn = STATE_UNDER; /* exist problem */
//        }
//    }
//    else
//    {
//        stp_Limit->u16_FaultUnderCnt = 0U;
//        stp_Limit->u16_DeratingCnt = 0U;
//
//        if( stp_Limit->u16_FaultOvertCnt < MAX_FLT_CNT )
//        {
//            stp_Limit->u16_FaultOvertCnt++;
//        }
//        else
//        {
//            u8_rtn = STATE_OVER; /* exist problem */
//        }
//    }
//    return u8_rtn;
//}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void Asw_LLC_DiagCanState ( st_DiagnosisType *stp_DiagFlags, const st_CANRxValuesType_LLC *stp_canSts )
{
    stp_DiagFlags->u8_CanBusOffSts = stp_canSts->u8_canBusoffStatus;
    stp_DiagFlags->u8_CanTimeoutSts = stp_canSts->u8_canTimeoutStatus;
}
/****************************************************************************/
/**                                                                        **/
/**                      LOCAL FUNCTIONS                                   **/
/**                                                                        **/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static en_STATE_DEF DiagAdc_LLCInputV ( en_STATE_DEF u8_HV_V, st_AdcLimitValue *stp_AdcLimit, single f32_adcRealInputV )
{
    en_STATE_DEF u8_rtn = STATE_NORMAL;

#if DIAG_LLC_INVOLT_ON
    switch( u8_HV_V )
    {
        case STATE_NORMAL:
            u8_rtn = Asw_Adc_NormalMode ( stp_AdcLimit, f32_adcRealInputV );
            break;
        case STATE_UNDER:
            u8_rtn = Asw_Adc_UnderMode ( stp_AdcLimit, f32_adcRealInputV );
          break;
        case STATE_OVER:
            u8_rtn = Asw_Adc_OverMode ( stp_AdcLimit, f32_adcRealInputV );
          break;
        default:
            u8_rtn = STATE_NORMAL;
          break;
    }

#else
    u8_rtn = STATE_NORMAL; /* no problem */
#endif
    return u8_rtn;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static en_STATE_DEF DiagAdc_LLCInputI ( en_STATE_DEF u8_HV_I, st_AdcLimitValue *stp_AdcLimit, single f32_adcRealInputI )
{
    en_STATE_DEF u8_rtn = STATE_NORMAL;
#if DIAG_LLC_INCURR_ON
    static byte u8_OverCntIin = 0U;
    static byte u8_FlagIin = 0U;
    if( u8_OverCntIin < 3U )
    {
        switch( u8_HV_I )
        {
        case STATE_NORMAL:
            u8_rtn = Asw_Adc_NormalMode ( stp_AdcLimit, f32_adcRealInputI );
            u8_Flag = 0U;
            break;
        case STATE_OVER:
            u8_rtn = Asw_Adc_OverMode ( stp_AdcLimit, f32_adcRealInputI );
            if( u8_FlagIin == 0U )
            {
                u8_OverCntIin++;
                u8_FlagIin = 1U;
            }
            break;
        default:
            u8_rtn = STATE_NORMAL;
            break;
        }
    }
    else
    {
        u8_rtn = STATE_OVER;
    }

#else
    u8_rtn = STATE_NORMAL; /* no problem */
#endif
    return u8_rtn;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static en_STATE_DEF DiagAdc_LLCOutputV ( en_STATE_DEF u8_LV_V, st_AdcLimitValue *stp_AdcLimit, single f32_adcRealOutputV )
{
    en_STATE_DEF u8_rtn = STATE_NORMAL;

#if DIAG_LLC_OUTVOLT_ON
    switch( u8_LV_V )
    {
        case STATE_NORMAL:
            u8_rtn = Asw_Adc_NormalMode ( stp_AdcLimit, f32_adcRealOutputV );
            break;
        case STATE_UNDER:
            u8_rtn = Asw_Adc_UnderMode ( stp_AdcLimit, f32_adcRealOutputV );
          break;
        case STATE_OVER:
            u8_rtn = Asw_Adc_OverMode ( stp_AdcLimit, f32_adcRealOutputV );
          break;
        default:
            u8_rtn = STATE_NORMAL;
          break;
    }

#else
    u8_rtn = STATE_NORMAL; /* no problem */
#endif
    return u8_rtn;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static en_STATE_DEF DiagAdc_LLCOutputI ( en_STATE_DEF u8_LV_I, st_AdcLimitValue *stp_AdcLimit, single f32_adcRealOutputI )
{
    en_STATE_DEF u8_rtn = STATE_NORMAL;

#if DIAG_LLC_OUTCURR_ON
    static byte u8_OverCntIout = 0U;
    static byte u8_FlagIout = 0U;
    if( u8_OverCntIout < OVER_CNT )
    {
        switch( u8_LV_I )
        {
        case STATE_NORMAL:
            u8_rtn = Asw_Adc_NormalMode ( stp_AdcLimit, f32_adcRealOutputI );
            u8_Flag = 0U;
            break;
        case STATE_OVER:
            u8_rtn = Asw_Adc_OverMode ( stp_AdcLimit, f32_adcRealOutputI );
            if( u8_FlagIout == 0U )
            {
                u8_OverCntIout++;
                u8_FlagIout = 1U;
            }
            break;
        default:
            u8_rtn = STATE_NORMAL;
            break;
        }
    }
    else
    {
        u8_rtn = STATE_OVER;
    }

#else
    u8_rtn = STATE_NORMAL; /* no problem */
#endif
    return u8_rtn;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static en_STATE_DEF DiagAdc_LLCTemp ( en_STATE_DEF u8_Temp, st_AdcLimitValue *stp_AdcLimit, single f32_adcRealTemp )
{
    en_STATE_DEF u8_rtn = STATE_NORMAL;

#if DIAG_LLC_TEMP_ON
    switch( u8_Temp )
    {
    case STATE_NORMAL:
        u8_rtn = Asw_Adc_NormalMode ( stp_AdcLimit, f32_adcRealTemp );
        break;
    case STATE_UNDER:
        u8_rtn = Asw_Adc_UnderMode ( stp_AdcLimit, f32_adcRealTemp );
      break;
    case STATE_OVER:
        u8_rtn = Asw_Adc_OverMode ( stp_AdcLimit, f32_adcRealTemp );
        break;
    default:
        u8_rtn = STATE_NORMAL;
        break;
    }

#else
    u8_rtn = STATE_NORMAL; /* no problem */
#endif
    return u8_rtn;
}

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
