/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : FDC_LLC                                                     **
**  Filename  : ASW_Ctrl.c                                                  **
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

#define ASW_CTRL_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "Rte_ApiOut.h"
#include "ASW_Ctrl.h"
#include "BSW_Adc.h"
#include "BSW_Can.h"
#include "BSW_Pwm.h"
#include "BSW_Gpio.h"

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
static single Asw_Picontroller ( single f32_ref, single f32_in, st_PID_ERRORS *stp_error, st_PID_GAINS st_K );
static single Asw_Limiter ( single f32_in, single f32_upper, single f32_lower );
static void Asw_ResetError ( st_PID_ERRORS *stp_error );

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
 static st_PID_ERRORS sts_eVoLLC, sts_eIoutA, sts_eIoutB, sts_eIoutC ;
 static st_PID_GAINS sts_kVoLLC, sts_kIoLLC;

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
void Asw_LLC_PiCofficient ( void )
{
    sts_kVoLLC.P = 0.1f;
    sts_kVoLLC.I = 0.0094f;
//  sts_kVoLLC.P = 1.1f;
//  sts_kVoLLC.I = 0.054f;
    sts_kVoLLC.D = 0.0f;
    sts_kVoLLC.a = 1.0f/sts_kVoLLC.P;

//  sts_kIoLLC.P = 5.1f;
//  sts_kIoLLC.I = 0.13f;

    sts_kIoLLC.P = 0.15f;
    sts_kIoLLC.I = 0.000373f;
    sts_kIoLLC.D = 0.0f;
    sts_kIoLLC.a = 1.0f/sts_kIoLLC.P;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void Asw_LLC_PiInit ( void )
{
    Asw_ResetError ( &sts_eIoutA );
    Asw_ResetError ( &sts_eIoutB );
    Asw_ResetError ( &sts_eIoutC );
    Asw_ResetError ( &sts_eVoLLC );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void Asw_LLC_PiCtrl ( const st_CANRxValuesType_LLC *stp_canValues, single f32_Ioref, const st_RealValuesType *stp_adcValues )
{
    single f32_iLLCPiSetpoint = 0.0f;
    single f32_vLLCPiSetpoint = 0.0f;

    single f32_vLLCPIconout = 0.0f;
    single f32_iLLCPIconout = 0.0f;
    single f32_eVoLLCLimiter = 0.0f;
    single f32_eIoLLCLimiter =  0.0f;

    f32_vLLCPiSetpoint = stp_canValues->f32_CmdLLC_TargetVolt;

    f32_vLLCPIconout = Asw_Picontroller ( f32_vLLCPiSetpoint, stp_adcValues->f32_Vout, &sts_eVoLLC, sts_kVoLLC );
    f32_eVoLLCLimiter = Asw_Limiter ( f32_vLLCPIconout, f32_Ioref, 1.0f );
    sts_eVoLLC.f32_past = f32_eVoLLCLimiter;
    sts_eVoLLC.f32_w = ( f32_vLLCPIconout - sts_eVoLLC.f32_past ) * sts_kVoLLC.a;

    if( stp_canValues->u8_IG_Enable == 1U )
    {

        f32_iLLCPiSetpoint = f32_eVoLLCLimiter;
        f32_iLLCPIconout = Asw_Picontroller ( f32_iLLCPiSetpoint, stp_adcValues->f32_IoutA, &sts_eIoutA, sts_kIoLLC );
        f32_eIoLLCLimiter = Asw_Limiter ( f32_iLLCPIconout, LLC_DUTY_MAX, LLC_DUTY_MIN );
        sts_eIoutA.f32_past = f32_eIoLLCLimiter;
        sts_eIoutA.f32_w = ( f32_iLLCPIconout - sts_eIoutA.f32_past ) * sts_kIoLLC.a;
        stg_rteLLCOut.st_PwmValue.f32_fre[ LAYER_A ] = Asw_Limiter ( ( SYS_FRE/f32_eIoLLCLimiter ), LLC_FRE_MAX, LLC_FRE_MIN );


        if( stp_canValues->u8_LayerB == 1U )
        {
            f32_iLLCPiSetpoint = f32_eVoLLCLimiter;
            f32_iLLCPIconout = Asw_Picontroller ( f32_iLLCPiSetpoint, stp_adcValues->f32_IoutB, &sts_eIoutB, sts_kIoLLC );
            f32_eIoLLCLimiter = Asw_Limiter ( f32_iLLCPIconout, LLC_DUTY_MAX, LLC_DUTY_MIN );
            sts_eIoutB.f32_past = f32_eIoLLCLimiter;
            sts_eIoutB.f32_w = ( f32_iLLCPIconout - sts_eIoutB.f32_past ) * sts_kIoLLC.a;
            stg_rteLLCOut.st_PwmValue.f32_fre[ LAYER_B ] = Asw_Limiter ( ( SYS_FRE/f32_eIoLLCLimiter ), LLC_FRE_MAX, LLC_FRE_MIN );
        }

        if( stp_canValues->u8_LayerC == 1U )
        {
            f32_iLLCPiSetpoint = f32_eVoLLCLimiter;
            f32_iLLCPIconout = Asw_Picontroller ( f32_iLLCPiSetpoint, stp_adcValues->f32_IoutC, &sts_eIoutC, sts_kIoLLC );
            f32_eIoLLCLimiter = Asw_Limiter ( f32_iLLCPIconout, LLC_DUTY_MAX, LLC_DUTY_MIN );
            sts_eIoutC.f32_past = f32_eIoLLCLimiter;
            sts_eIoutC.f32_w = ( f32_iLLCPIconout - sts_eIoutC.f32_past ) * sts_kIoLLC.a;
            stg_rteLLCOut.st_PwmValue.f32_fre[ LAYER_C ] = Asw_Limiter ( ( SYS_FRE/f32_eIoLLCLimiter ), LLC_FRE_MAX, LLC_FRE_MIN );
        }
    }
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
single Asw_SoftStart ( single f32_CmdTarget, single f32_RefTemp, single f32_scale )
{
    single f32_refValueTemp = 0.0f;

    if( f32_CmdTarget >= f32_RefTemp )
    {
        f32_refValueTemp = f32_RefTemp + ( f32_CmdTarget/f32_scale );
        if( f32_refValueTemp >= f32_CmdTarget )
        {
            f32_refValueTemp = f32_CmdTarget;
        }
    }
    else
    {
        f32_refValueTemp = f32_RefTemp - ( f32_CmdTarget/f32_scale );
        if( f32_refValueTemp < f32_CmdTarget )
        {
            f32_refValueTemp = f32_CmdTarget;
        }
    }
    return ( single )f32_refValueTemp;
}

/*--------------------------------------------------------------------------*/
/* Function  | get1stLPFcoef                                                */
/* Name      | 1st Oder Low Pass Filter                                     */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
st_COEF_1 Asw_Get1stLPFcoef ( single cutoff, single freqSampling )
{
    single w_cut;
    st_COEF_1 coef;
    w_cut = ( single ) TWOPI * cutoff;

    coef.a0 = 1.0f;
    coef.a1 = ( w_cut - ( 2.0f * freqSampling ) ) /( ( 2.0f * freqSampling ) + w_cut );
    coef.b0 = w_cut / ( ( 2.0f * freqSampling ) + w_cut );
    coef.b1 = coef.b0;

    return coef;
}

/*--------------------------------------------------------------------------*/
/* Function  | firstLPF                                                     */
/* Name      | 1st Oder Low Pass Filter                                     */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
single Asw_FirstLPF ( single in, st_Z_1 *Zn1, st_COEF_1 coef )
{
    single out;

    out = ( -coef.a1 * Zn1->out ) + ( coef.b0 * ( in + Zn1->in ) );
    Zn1->in = in;
    Zn1->out = out;

    return out;
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
static single Asw_Picontroller ( single f32_ref, single f32_in, st_PID_ERRORS *stp_error, st_PID_GAINS st_K )
{
    single f32_out;

    stp_error->f32_e = f32_ref - f32_in;
    stp_error->f32_sum += (stp_error->f32_e - stp_error->f32_w )*st_K.I; /*- error->w*/
    f32_out = ( st_K.P * stp_error->f32_e ) + stp_error->f32_sum;

    return f32_out;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static single Asw_Limiter ( single f32_in, single f32_upper, single f32_lower )
{
    single f32_limit;

    if( f32_in >= f32_upper )
    {
        f32_limit = f32_upper;
    }
    else if( f32_in <= f32_lower )
    {
        f32_limit = f32_lower;
    }
    else
    {
        f32_limit = f32_in;
    }

    return f32_limit;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Asw_ResetError ( st_PID_ERRORS *stp_error )
{
    stp_error->f32_e = 0.0f;
    stp_error->f32_sum = 0.0f;
    stp_error->f32_w = 0.0f;
    stp_error->f32_past = 0.0f;
}

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
