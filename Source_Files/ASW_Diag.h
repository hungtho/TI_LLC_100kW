/*
                             *******************
******************************* C HEADER FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : FDC_LLC                                                     **
**  Filename  : ASW_Fault.h                                                 **
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

#ifndef ASW_FAULT_INCLUDED
#define ASW_FAULT_INCLUDED

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "Rte_Typedef.h"
/****************************************************************************/
/**                                                                        **/
/**                      DEFINITIONS AND MACROS                            **/
/**                                                                        **/
/****************************************************************************/
#define LLC_VIN_NOR_LOWER                   ( 280.0f )
#define LLC_VIN_NOR_UPPER                   ( 820.0f )
#define LLC_VIN_NOR_RECOVER_LOWER           ( 290.0f )
#define LLC_VIN_NOR_RECOVER_UPPER           ( 815.0f )

#define LLC_IIN_NOR_LOWER                   ( 0.0f )
#define LLC_IIN_NOR_UPPER                   ( 50.0f )
#define LLC_IIN_NOR_RECOVER_LOWER           ( 0.0f )
#define LLC_IIN_NOR_RECOVER_UPPER           ( 1.0f )

#define LLC_VOUT_NOR_LOWER                  ( 200.0f )
#define LLC_VOUT_NOR_UPPER                  ( 420.0f )
#define LLC_VOUT_NOR_RECOVER_LOWER          ( 250.0f )
#define LLC_VOUT_NOR_RECOVER_UPPER          ( 400.0f )

#define LLC_IOUT_NOR_LOWER                  ( 0.0f )
#define LLC_IOUT_NOR_UPPER                  ( 90.0f )
#define LLC_IOUT_NOR_RECOVER_LOWER          ( 0.0f )
#define LLC_IOUT_NOR_RECOVER_UPPER          ( 1.0f )


#define LLC_TEMP_NOR_LOWER                  ( -30.0f ) /* -30C LOW LEVEL NORMAL RECOVERY */
#define LLC_TEMP_NOR_UPPER                  ( 135.0f ) /* 135 HIGH LEVEL NORMAL RECOVERY */
#define LLC_TEMP_NOR_RECOVER_LOWER          ( -25.0f ) /* -25C Degree*/
#define LLC_TEMP_NOR_RECOVER_UPPER          ( 80.0f ) /* 80C Degree*/
#define LLC_TEMP_FAULT_UPPER                ( 115.0f ) /* 115C HIGH LEVEL FAULT  */

#define MAX_FLT_CNT                         ( 500U )
/****************************************************************************/
/**                                                                        **/
/**                      TYPEDEFS AND STRUCTURES                           **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/

# ifndef ASW_FAULT_C_SRC
# endif

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
extern void Asw_LLC_AdcInit ( void );
extern void Asw_LLC_DiagAdcValues ( st_DiagnosisType *stp_DiagFlags, const st_RealValuesType *stp_adcValues );
extern en_STATE_DEF Asw_Adc_NormalMode ( st_AdcLimitValue *stp_Limit, single f32_adcRealValue );
extern en_STATE_DEF Asw_Adc_UnderMode ( st_AdcLimitValue *stp_Limit, single f32_adcRealValue );
extern en_STATE_DEF Asw_Adc_OverMode ( st_AdcLimitValue *stp_Limit, single f32_adcRealValue );
//extern en_STATE_DEF Asw_Adc_TempNormalMode ( st_AdcLimitValue *stp_Limit, single f32_adcRealTemp );
//extern en_STATE_DEF Asw_Adc_TempFaultMode ( st_AdcLimitValue *stp_Limit, single f32_adcRealTemp );

extern void Asw_LLC_DiagCanState ( st_DiagnosisType *stp_DiagFlags, const st_CANRxValuesType_LLC *stp_canSts );

#endif

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
