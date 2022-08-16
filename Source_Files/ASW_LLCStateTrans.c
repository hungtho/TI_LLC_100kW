/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : Edison                                                      **
**  Filename  : ASW_LLCStateTrans.c                                         **
**  Version   : -.- (PCB : )                                                **
**  Date      : 2020.07.28                                                  **
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

#define ASW_LLCSTATETRANS_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "Rte_ApiIn.h"
#include "ASW_Config.h"
#include "ASW_LLCStateTrans.h"
#include <ASW_LLCState.h>

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
static byte IsChangeModeReady ( const st_DiagnosisType *stp_DetectedFlag );
static byte IsChangeModeNormal ( const st_DiagnosisType *stp_DetectedFlag );
static byte IsChangeModeFault ( const st_DiagnosisType *stp_DetectedFlag );
static byte IsChangeModeFailure ( const st_DiagnosisType *stp_DetectedFlag );
static void LLC_SET_ModeStatus ( en_LLC_MODE_DEF u8_val );

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
static word u16g_CheckReady_Cnt = 0U;
static en_LLC_MODE_DEF u8g_LLCMode = LLC_MODE_READY;

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Function  |            											        */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void Asw_LLC_ModeUpdate ( const st_DiagnosisType *stp_faultDetectedResult )
{
	switch( Asw_GET_LLC_Mode () )
	{
	case LLC_MODE_READY:
		if( IsChangeModeFailure ( stp_faultDetectedResult ) == uTRUE )
		{
			LLC_SET_ModeStatus ( LLC_MODE_FAILURE );
		}
		else if( IsChangeModeReady ( stp_faultDetectedResult ) == uTRUE )
		{
			LLC_SET_ModeStatus ( LLC_MODE_NORMAL );
		}
		else
		{
			LLC_SET_ModeStatus ( LLC_MODE_READY );
		}
		break;
	case LLC_MODE_NORMAL:
		if( IsChangeModeFailure ( stp_faultDetectedResult ) == uTRUE )
		{
			LLC_SET_ModeStatus ( LLC_MODE_FAILURE );
		}
		else if( IsChangeModeFault ( stp_faultDetectedResult ) == uTRUE )
		{
			LLC_SET_ModeStatus ( LLC_MODE_FAULT );
		}
		else
		{
			LLC_SET_ModeStatus ( LLC_MODE_NORMAL );
		}
		break;

	case LLC_MODE_FAULT:
		if( IsChangeModeFailure ( stp_faultDetectedResult ) == uTRUE )
		{
			LLC_SET_ModeStatus ( LLC_MODE_FAILURE );
		}
		else if( IsChangeModeNormal ( stp_faultDetectedResult ) == uTRUE )
		{
			LLC_SET_ModeStatus ( LLC_MODE_READY );
		}
		else
		{
			LLC_SET_ModeStatus( LLC_MODE_FAULT );
		}
		break;
	case LLC_MODE_FAILURE:
		if( IsChangeModeNormal ( stp_faultDetectedResult ) == uTRUE )
		{
		    if( stg_rteLLCIn.st_CANValue.u8_Reset == 1U )
		    {
		        LLC_SET_ModeStatus ( LLC_MODE_READY );

		        stg_AswLLCDiagFlag.u8_OverVol_IC = STATE_NORMAL;
		        stg_AswLLCDiagFlag.u8_OverCur_IC = STATE_NORMAL;
		        stg_AswLLCDiagFlag.u8_Gate_IC = STATE_NORMAL;
		    }
		    else
		    {
		        LLC_SET_ModeStatus ( LLC_MODE_FAILURE );
		    }
		}
		else
		{
			LLC_SET_ModeStatus ( LLC_MODE_FAILURE );
		}
		break;
	default:
			LLC_SET_ModeStatus ( LLC_MODE_READY );
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
en_LLC_MODE_DEF Asw_GET_LLC_Mode ( void )
{
	return u8g_LLCMode;
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
static byte IsChangeModeReady ( const st_DiagnosisType *stp_DetectedFlag )
{
	byte rtnVal = uFALSE;

	if( ( stp_DetectedFlag->u8_Vout == STATE_NORMAL )
	 && ( stp_DetectedFlag->u8_TMP_CH1 == STATE_NORMAL )
	 && ( stp_DetectedFlag->u8_TMP_CH2 == STATE_NORMAL )
	 && ( stp_DetectedFlag->u8_TMP_CH3 == STATE_NORMAL )
	 && ( stp_DetectedFlag->u8_TMP_CH4 == STATE_NORMAL )
	 && ( stp_DetectedFlag->u8_TMP_CH5 == STATE_NORMAL )
	 && ( stp_DetectedFlag->u8_TMP_CH6 == STATE_NORMAL )
	 && ( stp_DetectedFlag->u8_TMP_CH7 == STATE_NORMAL )
	 && ( stp_DetectedFlag->u8_TMP_CH8 == STATE_NORMAL )
	 && ( stp_DetectedFlag->u8_TMP_CH9 == STATE_NORMAL )
	 && ( stp_DetectedFlag->u8_TMP_CH10 == STATE_NORMAL )
	 && ( stp_DetectedFlag->u8_TMP_CH11 == STATE_NORMAL )
	 && ( stp_DetectedFlag->u8_TMP_CH12 == STATE_NORMAL )
	 && ( stp_DetectedFlag->u8_CanBusOffSts == STATE_NORMAL )
	 && ( stp_DetectedFlag->u8_CanTimeoutSts == STATE_NORMAL ) )
	{
		if( u16g_CheckReady_Cnt >= LLC_READY_DELAY_TIME ){ rtnVal = uTRUE; }
		else{ u16g_CheckReady_Cnt++; }
	}
	else
	{
		u16g_CheckReady_Cnt = 0U;
	}

	return rtnVal;
}

/*--------------------------------------------------------------------------*/
/* Function  |            											        										*/
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static byte IsChangeModeNormal ( const st_DiagnosisType *stp_DetectedFlag )
{
	byte rtnVal = uFALSE;

	if(	( stp_DetectedFlag->u8_VLink == STATE_NORMAL )
	 && ( stp_DetectedFlag->u8_ILinkA == STATE_NORMAL )
	 && ( stp_DetectedFlag->u8_ILinkB == STATE_NORMAL )
	 && ( stp_DetectedFlag->u8_ILinkC == STATE_NORMAL )
	 && ( stp_DetectedFlag->u8_Vout == STATE_NORMAL )
	 && ( stp_DetectedFlag->u8_IoutA == STATE_NORMAL )
	 && ( stp_DetectedFlag->u8_IoutB == STATE_NORMAL )
	 && ( stp_DetectedFlag->u8_IoutC == STATE_NORMAL )
     && ( stp_DetectedFlag->u8_TMP_CH1 == STATE_NORMAL )
     && ( stp_DetectedFlag->u8_TMP_CH2 == STATE_NORMAL )
     && ( stp_DetectedFlag->u8_TMP_CH3 == STATE_NORMAL )
     && ( stp_DetectedFlag->u8_TMP_CH4 == STATE_NORMAL )
     && ( stp_DetectedFlag->u8_TMP_CH5 == STATE_NORMAL )
     && ( stp_DetectedFlag->u8_TMP_CH6 == STATE_NORMAL )
     && ( stp_DetectedFlag->u8_TMP_CH7 == STATE_NORMAL )
     && ( stp_DetectedFlag->u8_TMP_CH8 == STATE_NORMAL )
     && ( stp_DetectedFlag->u8_TMP_CH9 == STATE_NORMAL )
     && ( stp_DetectedFlag->u8_TMP_CH10 == STATE_NORMAL )
     && ( stp_DetectedFlag->u8_TMP_CH11 == STATE_NORMAL )
     && ( stp_DetectedFlag->u8_TMP_CH12 == STATE_NORMAL )
	 && ( stp_DetectedFlag->u8_CanBusOffSts == STATE_NORMAL ) )
	{
		rtnVal = uTRUE;
	}

	return rtnVal;
}

/*--------------------------------------------------------------------------*/
/* Function  |            											        										*/
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static  byte IsChangeModeFault ( const st_DiagnosisType *stp_DetectedFlag )
{
	byte rtnVal = uFALSE;

	if( ( stp_DetectedFlag->u8_VLink != STATE_NORMAL )
	 || ( stp_DetectedFlag->u8_ILinkA != STATE_NORMAL )
	 || ( stp_DetectedFlag->u8_ILinkB != STATE_NORMAL )
	 || ( stp_DetectedFlag->u8_ILinkC != STATE_NORMAL )
	 || ( stp_DetectedFlag->u8_Vout != STATE_NORMAL )
	 || ( stp_DetectedFlag->u8_IoutA != STATE_NORMAL )
	 || ( stp_DetectedFlag->u8_IoutB != STATE_NORMAL )
	 || ( stp_DetectedFlag->u8_IoutC != STATE_NORMAL )
	 || ( stp_DetectedFlag->u8_TMP_CH1 != STATE_NORMAL )
	 || ( stp_DetectedFlag->u8_TMP_CH2 != STATE_NORMAL )
	 || ( stp_DetectedFlag->u8_TMP_CH3 != STATE_NORMAL )
	 || ( stp_DetectedFlag->u8_TMP_CH4 != STATE_NORMAL )
	 || ( stp_DetectedFlag->u8_TMP_CH5 != STATE_NORMAL )
	 || ( stp_DetectedFlag->u8_TMP_CH6 != STATE_NORMAL )
	 || ( stp_DetectedFlag->u8_TMP_CH7 != STATE_NORMAL )
	 || ( stp_DetectedFlag->u8_TMP_CH8 != STATE_NORMAL )
	 || ( stp_DetectedFlag->u8_TMP_CH9 != STATE_NORMAL )
	 || ( stp_DetectedFlag->u8_TMP_CH10 != STATE_NORMAL )
	 || ( stp_DetectedFlag->u8_TMP_CH11 != STATE_NORMAL )
	 || ( stp_DetectedFlag->u8_TMP_CH12 != STATE_NORMAL )
     )
	{
		rtnVal = uTRUE; /* Stay to mode fault */
		u16g_CheckReady_Cnt = 0U;
	}

	return rtnVal;
}

/*--------------------------------------------------------------------------*/
/* Function  |            											        */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static byte IsChangeModeFailure ( const st_DiagnosisType *stp_DetectedFlag )
{
	byte rtnVal = uFALSE;

	if( ( stp_DetectedFlag->u8_OverCur_IC == STATE_FAULT )
   || ( stp_DetectedFlag->u8_OverVol_IC == STATE_FAULT )
   || ( stp_DetectedFlag->u8_Gate_IC == STATE_FAULT ) )
	{
		rtnVal = uTRUE; /* entry to mode Failure */
		u16g_CheckReady_Cnt = 0U;
	}

	return rtnVal;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void LLC_SET_ModeStatus ( en_LLC_MODE_DEF u8_val )
{
	u8g_LLCMode = u8_val;
}

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/


/****************************************************************************/
/**                                                                        **/
/**                      LOCAL FUNCTIONS                                   **/
/**                                                                        **/
/****************************************************************************/

