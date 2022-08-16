/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : Edison                                                      **
**  Filename  : ASW_LLCSequence.c                                           **
**  Version   : -.- (PCB : )                                                **
**  Date      : 2020.05.14                                                  **
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

#define ASW_LLCSEQUENCE_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "Rte_Typedef.h"
#include "Rte_ApiIn.h"
#include "Rte_ApiOut.h"
#include "ASW_Config.h"
#include "ASW_LLCState.h"
#include "ASW_Ctrl.h"
#include "ASW_LLCStateTrans.h"
#include <ASW_Diag.h>

#include "Bsw_Pwm.h"
#include "Bsw_Can.h"


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
static void Asw_RunReady ( void );
static void Asw_RunNormal ( byte u8_cmdLLCEnable, single f32_cmdTargetVolt, single f32_cmdTargetCur );
static void Asw_RunFault ( void );
static void Asw_RunFailure ( void );

static void Asw_Control_LLCRun ( byte u8_cmdLLCEnable, single f32_cmdTargetVolt, single f32_cmdTargetCur );
static void Asw_PowerOffLayerA ( void );
static void Asw_PowerOffLayerB ( void );
static void Asw_PowerOffLayerC ( void );

static void Asw_PowerOnLayerA ( void );
static void Asw_PowerOnLayerB ( void );
static void Asw_PowerOnLayerC ( void );

static single Asw_SoftStop ( single f32_rteFre );
static single Asw_GetIref( single f32_power );

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/
byte u8g_SoftStartEnd = 0U;

single f32g_cmdTargetCur_SS = 0.0f;
st_DiagnosisType stg_AswLLCDiagFlag = { STATE_NORMAL, };

/****************************************************************************/
/**                                                                        **/
/**                      GLOBAL VARIABLES                                  **/
/**                                                                        **/
/****************************************************************************/
static en_LLC_STATE u8s_LLCPWMCtrl = EN_LLC_Off;

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Function  |            											                            */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void Asw_LLC_Init ( void )
{
	Asw_LLC_PiInit ();
	Asw_LLC_PiCofficient ();
	Asw_LLC_AdcInit ();

	stg_rteLLCOut.st_PwmValue.f32_fre[ LAYER_A ]  = LLC_FRE_MAX;
	stg_rteLLCOut.st_PwmValue.f32_fre[ LAYER_B ]  = LLC_FRE_MAX;
	stg_rteLLCOut.st_PwmValue.f32_fre[ LAYER_C ]  = LLC_FRE_MAX;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void Asw_LLC_Mode ( void )
{
	en_LLC_MODE_DEF u8_LLCModeState = Asw_GET_LLC_Mode (); /* Updated LLC mode */

	byte u8_LLC_IG_Enable = 0U;
	single f32_refVolVal = 0.0F;
	single f32_refCurVal = 0.0F;

    if( ( stg_rteLLCIn.st_CANValue.u8_LayerA == 1U )
      ||( stg_rteLLCIn.st_CANValue.u8_LayerB == 1U )
      ||( stg_rteLLCIn.st_CANValue.u8_LayerC == 1U ) )
    {
        u8_LLC_IG_Enable = stg_rteLLCIn.st_CANValue.u8_IG_Enable;
    }
    else{ u8_LLC_IG_Enable = 0U; }

	f32_refVolVal = stg_rteLLCIn.st_CANValue.f32_CmdLLC_TargetVolt;
	f32_refCurVal = Asw_GetIref ( LLC_POWER_MAX );

	switch( u8_LLCModeState )
	{
	case LLC_MODE_READY :
	    Asw_RunReady ();
		break;

	case LLC_MODE_NORMAL :
	    Asw_RunNormal ( u8_LLC_IG_Enable, f32_refVolVal, f32_refCurVal );
		break;

	case LLC_MODE_FAULT :
	    Asw_RunFault ();
		break;

	case LLC_MODE_FAILURE :
	    Asw_RunFailure ();
		break;

	default :
	    Asw_RunReady ();
		break;
	}
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
en_LLC_STATE Asw_GET_LLC_PwmCtrl ( void )
{
	return u8s_LLCPWMCtrl;
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
static void Asw_RunReady ( void )
{
    Asw_LLC_Init ();
    Asw_Control_LLCRun ( 0U, 0.0F, 0.0F );
}

/*--------------------------------------------------------------------------*/
/* Function  |            											       										  */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Asw_RunNormal ( byte u8_cmdLLCEnable, single f32_cmdTargetVolt, single f32_cmdTargetCur )
{
	if( f32_cmdTargetVolt > LLC_CMD_REFVOLT_MIN )
	{
	    Asw_Control_LLCRun ( u8_cmdLLCEnable, f32_cmdTargetVolt, f32_cmdTargetCur );
	}
	else
	{
	    Asw_Control_LLCRun ( 0U, 0.0F, 0.0F );
	}
}

/*--------------------------------------------------------------------------*/
/* Function  |            											        */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Asw_RunFault ( void )
{
    Asw_Control_LLCRun ( 0U, 0.0F, 0.0F );
}

/*--------------------------------------------------------------------------*/
/* Function  |            											        */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Asw_RunFailure ( void )
{
    Asw_Control_LLCRun ( 0U, 0.0F, 0.0F );
}

/*--------------------------------------------------------------------------*/
/* Function  |            											        */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Asw_Control_LLCRun ( byte u8_cmdLLCEnable, single f32_cmdTargetVolt, single f32_cmdTargetCur )
{
	if( ( u8_cmdLLCEnable == 1U ) && ( f32_cmdTargetVolt >= LLC_CMD_REFVOLT_MIN ) ) /* LLC_RUN_POWERON */
	{
		f32g_cmdTargetCur_SS = Asw_SoftStart ( f32_cmdTargetCur, f32g_cmdTargetCur_SS, SOFTSTART_3S );  /* 2s for soft start */

		if( f32g_cmdTargetCur_SS >= f32_cmdTargetCur )
		{
			u8g_SoftStartEnd = 1U;
		}

	    u8s_LLCPWMCtrl = EN_LLC_On;

//	    if( stg_rteLLCIn.st_CANValue.u8_LayerA == 1U ){ Asw_PowerOnLayerA (); }
//	    else{ Asw_PowerOffLayerA (); }
//
//        if( stg_rteLLCIn.st_CANValue.u8_LayerB == 1U ){ Asw_PowerOnLayerB (); }
//        else{ Asw_PowerOffLayerB (); }
//
//        if( stg_rteLLCIn.st_CANValue.u8_LayerC == 1U ){ Asw_PowerOnLayerC (); }
//        else{ Asw_PowerOffLayerC (); }
	}
	else /* LLC_RUN_STANDBY */
	{
	    u8s_LLCPWMCtrl = EN_LLC_Off;
        f32g_cmdTargetCur_SS = 0.0F;
        u8g_SoftStartEnd = 0U;

//	    Asw_PowerOffLayerA ();
//	    Asw_PowerOffLayerB ();
//	    Asw_PowerOffLayerC ();
	    Asw_LLC_PiInit ();
	}
}

/*--------------------------------------------------------------------------*/
/* Function  |            											        */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Asw_PowerOffLayerA ( void )
{
    stg_rteLLCOut.st_PwmValue.f32_fre[ LAYER_A ] = Asw_SoftStop ( stg_rteLLCOut.st_PwmValue.f32_fre[ LAYER_A ] );
    if( stg_rteLLCOut.st_PwmValue.f32_fre[ LAYER_A ] >= LLC_FRE_MAX )
    {
        DISABLE_RDY1;
    }
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Asw_PowerOffLayerB ( void )
{
    stg_rteLLCOut.st_PwmValue.f32_fre[ LAYER_B ] = Asw_SoftStop ( stg_rteLLCOut.st_PwmValue.f32_fre[ LAYER_B ] );
    if( stg_rteLLCOut.st_PwmValue.f32_fre[ LAYER_B ] >= LLC_FRE_MAX )
    {
        DISABLE_BUFF1;
        DISABLE_BUFF2;
        DISABLE_RDY2;
    }
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Asw_PowerOffLayerC ( void )
{
    stg_rteLLCOut.st_PwmValue.f32_fre[ LAYER_C ] = Asw_SoftStop ( stg_rteLLCOut.st_PwmValue.f32_fre[ LAYER_C ] );
    if( stg_rteLLCOut.st_PwmValue.f32_fre[ LAYER_C ] >= LLC_FRE_MAX )
    {
        DISABLE_RDY3;
    }
}

/*--------------------------------------------------------------------------*/
/* Function  |            											        */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Asw_PowerOnLayerA ( void )
{

    BSW_Pwm ( 1U, EN_PWM_On );
    BSW_Pwm ( 2U, EN_PWM_On );

    ENABLE_RDY1;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Asw_PowerOnLayerB ( void )
{

    BSW_Pwm ( 3U, EN_PWM_On );
    BSW_Pwm ( 4U, EN_PWM_On );
    ENABLE_BUFF1;
    ENABLE_BUFF2;

    ENABLE_RDY2;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Asw_PowerOnLayerC ( void )
{
    BSW_Pwm ( 5U, EN_PWM_On );
    BSW_Pwm ( 6U, EN_PWM_On );

    ENABLE_RDY3;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static single Asw_SoftStop ( single f32_rteFre )
{
	single f32_Fre = 0U;

	if( f32_rteFre < LLC_FRE_MAX )
	{
	    f32_Fre = f32_rteFre + LLC_FRE_MAX / SOFTSTOP_3S;   /* 3s for soft stop */
	}
	else
	{
	    f32_Fre = LLC_FRE_MAX;
	}

	return ( f32_Fre );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static single Asw_GetIref( single f32_power )
{
    single f32_rtn;

    f32_rtn = f32_power / ( f32g_LLC_Target_V * ( u8g_LLC_LayerA + u8g_LLC_LayerB + u8g_LLC_LayerB ) );

    if( f32_rtn > LLC_IOUT_MAX )
    {
        f32_rtn = LLC_IOUT_MAX;
    }

    return f32_rtn;
}

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
