/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : FDC_LLC                                                      **
**  Filename  : Rte_Interface.c                                             **
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

#define RTE_INTERFACE_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "Rte_ApiIn.h"
#include "Rte_ApiOut.h"
#include "ASW_Ctrl.h"
#include <ASW_LLCState.h>
#include "ASW_LLCStateTrans.h"
#include <ASW_Diag.h>
#include "BSW_Can.h"
#include "BSW_Adc.h"
#include "BSW_Timer.h"
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
static void RTE_Task_100us ( void );
static void RTE_Task_1ms ( void );
static void RTE_Task_50ms ( void );
static void RTE_LLC_CTRL ( void );

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
single f32_openloop_fre = 100000.0f;
/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Function  |            											        										*/
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void RTE_BSW_Init ( void )
{
    BSW_Pwm_Init ( );
    BSW_Adc_Init ( );
    BSW_Gpio_Init ( );
    BSW_Can_Init ( );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void RTE_Task_Run ( void )
{
    RTE_Task_100us ();


	if( --u16g_task_flag_1m == 0U )
	{
//		RTE_Task_1ms ();

		u16g_task_flag_1m = 10U;
	}

    if( --u16g_task_flag_50m == 0U )
    {
//        RTE_Task_50ms ();

        u16g_task_flag_50m = 500U;
    }
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
static void RTE_Task_100us ( void )
{
    BSW_Adc_Update ( );

    RTE_LLC_IN ();
    RTE_LLC_CTRL ();
    RTE_LLC_OUT ();
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void RTE_Task_1ms ( void )
{
    Asw_LLC_DiagAdcValues ( &stg_AswLLCDiagFlag, &stg_rteLLCIn.st_RealValue ); /* Diagnostic of Adc values */
//    Asw_LLC_DiagCanState ( &stg_AswLLCDiagFlag, &stg_rteLLCIn.st_CANValue ); /* Diagnostic of CAN Communication*/

    Asw_LLC_ModeUpdate ( &stg_AswLLCDiagFlag );
    Asw_LLC_Mode ();    /* LLC Sequence control by LLC mode */
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void RTE_Task_50ms ( void )
{
    BSW_Can_TxRx ( );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void RTE_LLC_CTRL ( void )
{
    static byte u8_On = 1;
    if( stg_rteLLCIn.st_CANValue.u8_ClosedLoop == 1U )
    {
        BSW_Pwm ( 1U, EN_PWM_Off );
        BSW_Pwm ( 2U, EN_PWM_Off );

        BSW_Pwm ( 3U, EN_PWM_Off );
        BSW_Pwm ( 4U, EN_PWM_Off );

        Asw_LLC_PiCtrl ( &stg_rteLLCIn.st_CANValue,
                         f32g_cmdTargetCur_SS,
                         &stg_rteLLCIn.st_RealValue );
    }
    else
    {
        if( stg_rteLLCIn.st_CANValue.u8_IG_Enable == ( byte )EN_LLC_On )
        {
            if( u8_On == 1 )
            {
                BSW_Pwm ( 1U, EN_PWM_On );
                BSW_Pwm ( 2U, EN_PWM_On );

                BSW_Pwm ( 3U, EN_PWM_On );
                BSW_Pwm ( 4U, EN_PWM_On );
                u8_On = 0;
            }
            f32_openloop_fre = Asw_SoftStart ( f16g_test_frequency, f32_openloop_fre, OPENLOOP_SLEW_1S );  /* 1s for soft start */
        }
        else
        {
            f32_openloop_fre = 100000.0f;
//            DISABLE_BUFF1;
//            DISABLE_BUFF2;
            u8_On = 1;
            BSW_Pwm ( 1U, EN_PWM_Off );
            BSW_Pwm ( 2U, EN_PWM_Off );

            BSW_Pwm ( 3U, EN_PWM_Off );
            BSW_Pwm ( 4U, EN_PWM_Off );
        }
    }

}

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
