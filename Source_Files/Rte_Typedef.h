/*
                             *******************
******************************* C HEADER FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : FDC_LLC                                                      **
**  Filename  : Rte_Typedef.h                                               **
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

#ifndef RTE_TYPEDEF_INCLUDED
#define RTE_TYPEDEF_INCLUDED

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "BSW_Defines.h"

/****************************************************************************/
/**                                                                        **/
/**                      DEFINITIONS AND MACROS                            **/
/**                                                                        **/
/****************************************************************************/
#define uTRUE  														( 1U )
#define uFALSE 														( 0U )

/****************************************************************************/
/**                                                                        **/
/**                      TYPEDEFS AND STRUCTURES                           **/
/**                                                                        **/

/****************************************************************************/
typedef enum
{
	EN_LLC_Off = 0U,
	EN_LLC_On
}en_LLC_STATE;

typedef enum
{
    EN_PWM_Off = 0U,
    EN_PWM_On
}en_PWM_STATE;

typedef enum
{
    NOR_LOWER = 0U,
    NOR_UPPER,
    NOR_RECOVER_LOWER,
    NOR_RECOVER_UPPER,
    FAULT_LOWER,
    FAULT_UPPER
}en_ADC_MODE_DEF;

typedef enum
{
	LLC_MODE_READY = 0U,
	LLC_MODE_NORMAL,
	LLC_MODE_FAULT,
	LLC_MODE_FAILURE
}en_LLC_MODE_DEF;

typedef enum
{
	STATE_NORMAL,
	STATE_UNDER,
	STATE_OVER,
	STATE_FAULT,
}en_STATE_DEF;

typedef enum
{
    LAYER_A,
    LAYER_B,
    LAYER_C,
}en_LAYER_DEF;

typedef struct
{
    en_STATE_DEF u8_VLink;       /* HV V - 입력전압  (250V ~ 420V) */
    en_STATE_DEF u8_HV_I;       /* HV I - 입력전류 (0A ~ 20A) */
    en_STATE_DEF u8_ILinkA;       /* HV I - 입력전류 (0A ~ 20A) */
    en_STATE_DEF u8_ILinkB;       /* HV I - 입력전류 (0A ~ 20A) */
    en_STATE_DEF u8_ILinkC;       /* HV I - 입력전류 (0A ~ 20A) */
    en_STATE_DEF u8_Vout;       /* LV V(Battery)- 출력전압 (6V ~ 16V) */
    en_STATE_DEF u8_IoutA;       /* LV I(Battery)- 출력전류 (0A ~ 128A) */
    en_STATE_DEF u8_IoutB;       /* LV I(Battery)- 출력전류 (0A ~ 128A) */
    en_STATE_DEF u8_IoutC;       /* LV I(Battery)- 출력전류 (0A ~ 128A) */

    en_STATE_DEF u8_TMP_CH1;       /* Temperature (-40 ~ 105)*/
    en_STATE_DEF u8_TMP_CH2;       /* Temperature (-40 ~ 105)*/
    en_STATE_DEF u8_TMP_CH3;       /* Temperature (-40 ~ 105)*/
    en_STATE_DEF u8_TMP_CH4;       /* Temperature (-40 ~ 105)*/
    en_STATE_DEF u8_TMP_CH5;       /* Temperature (-40 ~ 105)*/
    en_STATE_DEF u8_TMP_CH6;       /* Temperature (-40 ~ 105)*/
    en_STATE_DEF u8_TMP_CH7;       /* Temperature (-40 ~ 105)*/
    en_STATE_DEF u8_TMP_CH8;       /* Temperature (-40 ~ 105)*/
    en_STATE_DEF u8_TMP_CH9;       /* Temperature (-40 ~ 105)*/
    en_STATE_DEF u8_TMP_CH10;       /* Temperature (-40 ~ 105)*/
    en_STATE_DEF u8_TMP_CH11;       /* Temperature (-40 ~ 105)*/
    en_STATE_DEF u8_TMP_CH12;       /* Temperature (-40 ~ 105)*/

    en_STATE_DEF u8_OverVol_IC;       /* Temperature (-40 ~ 105)*/
    en_STATE_DEF u8_OverCur_IC;       /* Temperature (-40 ~ 105)*/
    en_STATE_DEF u8_Gate_IC;       /* Temperature (-40 ~ 105)*/

    en_STATE_DEF u8_CanTimeoutSts;
    en_STATE_DEF u8_CanBusOffSts;
}st_DiagnosisType;

typedef struct
{
	single f32_limit[6];
	word u16_DeratingCnt;
	word u16_FaultUnderCnt;
	word u16_FaultOvertCnt;
	en_STATE_DEF u8_SensorState;
}st_AdcLimitValue;

typedef struct
{
    single f32_VLink;
    single f32_ILinkA;
    single f32_ILinkB;
    single f32_ILinkC;

    single f32_IoutA;
    single f32_IoutB;
    single f32_IoutC;
    single f32_Vout;
    single f32_TMP_CH[ 12 ];

}st_RealValuesType;
typedef struct
{
	/* LLC Rx signals */
	byte u8_IG_Enable;
	byte u8_Reset;
	byte u8_ClosedLoop;
	byte u8_LayerA;
	byte u8_LayerB;
	byte u8_LayerC;

	single f32_CmdLLC_TargetVolt;

	en_STATE_DEF u8_canBusoffStatus;
	en_STATE_DEF u8_canTimeoutStatus;

}st_CANRxValuesType_LLC;

typedef struct
{
	en_LLC_MODE_DEF u8_LLC_mode;
}st_CANTxValuesType_LLC;

typedef struct
{
	en_LLC_STATE u8_LLCPWMCtrl;
	single f32_fre[3];
}st_PWMType_LLC;

typedef struct
{
	st_RealValuesType st_RealValue;
	st_CANRxValuesType_LLC st_CANValue;
}st_RteIn_LLC;

typedef struct
{
	st_CANTxValuesType_LLC st_CANValue;
	st_PWMType_LLC st_PwmValue;
}st_RteOut_LLC;

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/

# ifndef RTE_TYPEDEF_C_SRC
# endif

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/

#endif

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
