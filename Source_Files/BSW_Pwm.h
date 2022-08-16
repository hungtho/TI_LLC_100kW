/*
                             *******************
******************************* C HEADER FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : FDC_LLC                                                     **
**  Filename  : BSW_Pwm.h                                                   **
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

#ifndef BSW_PWM_INCLUDED
#define BSW_PWM_INCLUDED

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "F28x_Project.h"
#include "Rte_ApiIn.h"
#include "Rte_ApiOut.h"
#include "ASW_Config.h"

/****************************************************************************/
/**                                                                        **/
/**                      DEFINITIONS AND MACROS                            **/
/**                                                                        **/
/****************************************************************************/
#define CPU_SPD              200E6
#define DEGREE_SCALE_360     ( 1 )
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

# ifndef BSW_PWM_C_SRC
# endif

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
extern void BSW_Pwm_Init ( void );
extern void BSW_Pwm_Freq_Update ( const st_RteIn_LLC *stp_rteIn, st_RteOut_LLC *stp_rteOut );
extern void BSW_Pwm ( byte u8_ch, word u8_state );

extern void BSW_SET_Duty ( byte u8_ch, single f32_duty );
extern void BSW_SET_Freq ( byte u8_ch, single f32_freq );

__interrupt void epwm1_isr(void);
__interrupt void epwm2_isr(void);
__interrupt void epwm3_isr(void);
__interrupt void epwm4_isr(void);
__interrupt void epwm5_isr(void);

#endif

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
