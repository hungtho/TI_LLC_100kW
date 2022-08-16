/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : FDC_LLC                                                      **
**  Filename  : Rte_ApiIn.c                                                 **
**  Version   : -.- (PCB : )                                                **
**  Date      : 2020.07.29                                                  **
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

#define RTE_APIIN_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "Rte_ApiIn.h"
#include "BSW_Adc.h"
#include "BSW_Can.h"

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
st_RteIn_LLC stg_rteLLCIn;

/****************************************************************************/
/**                                                                        **/
/**                      GLOBAL VARIABLES                                  **/
/**                                                                        **/
/****************************************************************************/
#if TEST_LLC_VARIABLE
single testIin = 0;
single testVin = 400;
single testIout = 0;
single testVout = 14;
single testTemp = 26 + 40;
single testBplus = 14;
#endif

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
void RTE_LLC_IN ( void )
{

#if TEST_LLC_VARIABLE
	stg_rteLLCIn.st_RealValue.f32_InputCurrent = testIin;
	stg_rteLLCIn.st_RealValue.f32_InputVoltage = testVin;
	stg_rteLLCIn.st_RealValue.f32_OutputCurrent = testIout;
	stg_rteLLCIn.st_RealValue.f32_OutputVoltage = testVout;
	stg_rteLLCIn.st_RealValue.f32_Temperature = testTemp;
	stg_rteLLCIn.st_RealValue.f32_BatteryVoltage = testBplus;

	stg_rteLLCIn.st_CANValue.u8_VcuCmdLLC_Enable = Bsw_GET_VcuCmdEnLLC ();
	stg_rteLLCIn.st_CANValue.f32_VcuCmdLLC_TargetVolt = Bsw_GET_VcuCmdLLCTargetVolt();

	stg_rteLLCIn.st_RealValue.f32_InputVoltage = Bsw_GET_LLC_DCInputVolt();
#else
	/* update LLC Real values */
	byte u8_i;

	stg_rteLLCIn.st_RealValue.f32_VLink = f32g_LLC_VLink_LPF;
	stg_rteLLCIn.st_RealValue.f32_ILinkA = f32g_LLC_ILinkA_LPF;
	stg_rteLLCIn.st_RealValue.f32_ILinkB = f32g_LLC_ILinkB_LPF;
	stg_rteLLCIn.st_RealValue.f32_ILinkC = f32g_LLC_ILinkC_LPF;

	stg_rteLLCIn.st_RealValue.f32_Vout = f32g_LLC_Vout_LPF;
	stg_rteLLCIn.st_RealValue.f32_IoutA = f32g_LLC_IoutA_LPF;
	stg_rteLLCIn.st_RealValue.f32_IoutB = f32g_LLC_IoutA_LPF;
	stg_rteLLCIn.st_RealValue.f32_IoutC = f32g_LLC_IoutA_LPF;

	for ( u8_i = 0; u8_i < 12U; u8_i ++ )
	{
	    stg_rteLLCIn.st_RealValue.f32_TMP_CH[ u8_i ] = f32g_LLC_TMP_LPF [ u8_i ];
	}

	stg_rteLLCIn.st_CANValue.u8_LayerA = u8g_LLC_LayerA;
	stg_rteLLCIn.st_CANValue.u8_LayerB = u8g_LLC_LayerB;
	stg_rteLLCIn.st_CANValue.u8_LayerC = u8g_LLC_LayerC;

	stg_rteLLCIn.st_CANValue.u8_ClosedLoop = u8g_Close_Loop;
	stg_rteLLCIn.st_CANValue.u8_IG_Enable = u8g_IG_ON;
	stg_rteLLCIn.st_CANValue.u8_Reset = u8g_resetFault;
	stg_rteLLCIn.st_CANValue.f32_CmdLLC_TargetVolt = f32g_LLC_Target_V;

//	stg_rteLLCIn.st_CANValue.u8_canBusoffStatus = Bsw_GET_CanBusOff ();
	stg_rteLLCIn.st_CANValue.u8_canTimeoutStatus = Bsw_GET_LLC_CanTimeout ();
#endif
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
