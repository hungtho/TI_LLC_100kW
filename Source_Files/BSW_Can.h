/*
                             *******************
******************************* C HEADER FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : FDC_LLC                                                     **
**  Filename  : BSW_Can.h                                                   **
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

#ifndef BSW_CAN_INCLUDED
#define BSW_CAN_INCLUDED

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "ASW_Config.h"
#include "BSW_Defines.h"

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
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/

# ifndef BSW_CAN_C_SRC
# endif
extern float f16g_test_frequency;
extern byte u8g_CAN_transmit;

extern float f32g_LLC_Target_V;
extern byte u8g_IG_ON;
extern byte u8g_Close_Loop;
extern byte u8g_resetFault;
extern byte u8g_LLC_LayerA;
extern byte u8g_LLC_LayerB;
extern byte u8g_LLC_LayerC;
extern en_STATE_DEF u8g_LLC_CanTimeout;

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
extern void BSW_Can_Init ( void );
extern void BSW_Can_TxRx ( void );
extern en_STATE_DEF Bsw_GET_LLC_CanTimeout ( void );
#endif

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
