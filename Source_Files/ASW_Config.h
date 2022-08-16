/*
                             *******************
******************************* C HEADER FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : FDC_LLC                                                     **
**  Filename  : ASW_Config.h                                                **
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

#ifndef ASW_CONFIG_INCLUDED
#define ASW_CONFIG_INCLUDED

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "Rte_Typedef.h"
#include "BSW_Defines.h"

/****************************************************************************/
/**                                                                        **/
/**                      DEFINITIONS AND MACROS                            **/
/**                                                                        **/
/****************************************************************************/
#define TEST_LLC_VARIABLE      ( 0U )

#define DIAG_LLC_INVOLT_ON     ( 0U )
#define DIAG_LLC_INCURR_ON     ( 0U )
#define DIAG_LLC_OUTVOLT_ON    ( 0U )
#define DIAG_LLC_OUTCURR_ON    ( 0U )
#define DIAG_LLC_TEMP_ON       ( 0U )

#define CPU_CLK                ( 200e6 )
#define FREQ_SWITCHING         ( 20e3f )
#define FREQ_SAMPLING          ( 10e3 )
#define SAMPLING_TIME          ( 1.0f/FREQ_SAMPLING )     /*  = 1/FREQ_SAMPLING */
#define LLC_DEADTIME           ( 550.0f )     /* nano sec */

#define LLC_IOUT_MAX            ( 90.0f )    /* 90 A */
#define LLC_POWER_MAX          ( 120000.0f )   /* 120 kW */
#define LLC_CMD_REFVOLT_MIN    ( 200.0f )
#define LLC_READY_DELAY_TIME   ( 500U ) /* ms */

#define SOFTSTART_3S           ( 3000 ) /* 3000 * 1ms = 3s */
#define SOFTSTOP_3S            ( 3000 ) /* 3000 * 1ms = 3s */
#define OPENLOOP_SLEW_1S       ( 10000 ) /* 10000 * 100us = 1s */

#define TOGGLE_TP18            ( GpioDataRegs.GPATOGGLE.bit.GPIO8 = 1 )
#define SET_TP18               ( GpioDataRegs.GPASET.bit.GPIO8 = 1 )
#define CLEAR_TP18             ( GpioDataRegs.GPACLEAR.bit.GPIO8 = 1 )
#define TOGGLE_TP64            ( GpioDataRegs.GPATOGGLE.bit.GPIO28 = 1 )

#define TWOPI                  ( 6.2831853071795864 )

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

# ifndef ASW_CONFIG_C_SRC
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
