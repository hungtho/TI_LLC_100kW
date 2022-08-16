/*
                             *******************
******************************* C HEADER FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : FDC_LLC                                                     **
**  Filename  : ASW_Ctrl.h                                                  **
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

#ifndef ASW_CTRL_INCLUDED
#define ASW_CTRL_INCLUDED

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "ASW_Config.h"
#include "BSW_Timer.h"
#include "BSW_Pwm.h"
/****************************************************************************/
/**                                                                        **/
/**                      DEFINITIONS AND MACROS                            **/
/**                                                                        **/
/****************************************************************************/
#define  ENABLE_BUFF1               ( GpioDataRegs.GPASET.bit.GPIO26 = 1 )
#define  DISABLE_BUFF1              ( GpioDataRegs.GPACLEAR.bit.GPIO26 = 1 )
#define  ENABLE_BUFF2               ( GpioDataRegs.GPDSET.bit.GPIO99 = 1 )
#define  DISABLE_BUFF2              ( GpioDataRegs.GPDCLEAR.bit.GPIO99 = 1 )

#define  DISABLE_RDY1              ( GpioDataRegs.GPCCLEAR.bit.GPIO77 = 1 )
#define  DISABLE_RDY2              ( GpioDataRegs.GPCCLEAR.bit.GPIO78 = 1 )
#define  DISABLE_RDY3              ( GpioDataRegs.GPCCLEAR.bit.GPIO79 = 1 )

#define  ENABLE_RDY1               ( GpioDataRegs.GPCSET.bit.GPIO77 = 1 )
#define  ENABLE_RDY2               ( GpioDataRegs.GPCSET.bit.GPIO78 = 1 )
#define  ENABLE_RDY3               ( GpioDataRegs.GPCSET.bit.GPIO79 = 1 )

#define SYS_FRE                 ( 200000000.0F ) /* SysFre = 100000000 Hz*/
#define LLC_FRE_MAX             ( 100000.0F ) /* MaxFre = 100 kHz*/
#define LLC_FRE_MIN             ( 30000.0F ) /* MinFre = 30 kHz*/
#define LLC_DUTY_MAX            ( SYS_FRE/LLC_FRE_MIN )
#define LLC_DUTY_MIN            ( SYS_FRE/LLC_FRE_MAX )

/****************************************************************************/
/**                                                                        **/
/**                      TYPEDEFS AND STRUCTURES                           **/
/**                                                                        **/
/****************************************************************************/
typedef struct
{
    float32 P;
    float32 I;
    float32 D;
    float32 a;  /* anti windup gain*/
}st_PID_GAINS;

typedef struct
{
    float32 f32_e;
    float32 f32_sum;
    float32 f32_past;
    float32 f32_w;
}st_PID_ERRORS;

typedef struct {

    float32 a0;
    float32 a1;
    float32 b0;
    float32 b1;
}st_COEF_1;

typedef struct {
    float32 in;
    float32 out;
}st_Z_1;

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/

# ifndef ASW_CTRL_C_SRC
# endif

extern byte  u8g_operationMode;

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
extern void Asw_LLC_PiInit ( void );
extern void Asw_LLC_PiCofficient ( void );

extern void Asw_LLC_PiCtrl ( const st_CANRxValuesType_LLC *stp_canValues, single f32_Ioref, const st_RealValuesType *stp_adcValues );
extern single Asw_SoftStart ( single f32_CmdTarget, single f32_RefTemp, single f32_scale );
extern st_COEF_1 Asw_Get1stLPFcoef ( single cutoff, single freqSampling );
extern single Asw_FirstLPF ( single in, st_Z_1 *Zn1, st_COEF_1 coef );


#endif

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
