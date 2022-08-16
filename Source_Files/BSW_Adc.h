/*
                             *******************
******************************* C HEADER FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : FDC_LLC                                                     **
**  Filename  : BSW_Adc.h                                                   **
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

#ifndef BSW_ADC_INCLUDED
#define BSW_ADC_INCLUDED

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "F28x_Project.h"
#include "F2837xS_SWPrioritizedIsrLevels.h"
#include "ASW_Config.h"

/****************************************************************************/
/**                                                                        **/
/**                      DEFINITIONS AND MACROS                            **/
/**                                                                        **/
/****************************************************************************/
#define MAX_SAMPLES    ( 7U )
#define TEMP_CH        ( 12U )

/****************************************************************************/
/**                                                                        **/
/**                      TYPEDEFS AND STRUCTURES                           **/
/**                                                                        **/
/****************************************************************************/
typedef enum
{
    TMP_CH1 = 0U,
    TMP_CH2,
    TMP_CH3,
    TMP_CH4,
    TMP_CH5,
    TMP_CH6,
    TMP_CH7,
    TMP_CH8,
    TMP_CH9,
    TMP_CH10,
    TMP_CH11,
    TMP_CH12
}en_ADC_TEMP_CH_DEF;

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/

# ifndef BSW_ADC_C_SRC
# endif
extern single f32g_LLC_Iout_LPF;
extern single f32g_LLC_IoutA_LPF;
extern single f32g_LLC_IoutB_LPF;
extern single f32g_LLC_IoutC_LPF;
extern single f32g_LLC_ILinkA_LPF;
extern single f32g_LLC_ILinkB_LPF;
extern single f32g_LLC_ILinkC_LPF;

extern single f32g_LLC_Vout_LPF;
extern single f32g_LLC_VLink_LPF;
extern single f32g_LLC_TMP_LPF[ TEMP_CH ];

extern single f32g_LLC_Power;

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
extern void BSW_Adc_Init ( void );
extern void BSW_Adc_Update ( void );
extern interrupt void adca_isr ( void );
extern interrupt void adcb_isr ( void );
extern interrupt void adcc_isr ( void );

#endif

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
