/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : FDC_LLC                                                     **
**  Filename  : BSW_Gpio.c                                                  **
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

#define BSW_GPIO_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "BSW_Gpio.h"
#include "F28x_Project.h"
#include "ASW_Ctrl.h"
#include <ASW_LLCState.h>
#include "BSW_Adc.h"
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
void GPIO_Interrupt_Set ( void );
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
void BSW_Gpio_Init ( void )
{
    EALLOW;

#if LLC_FULL_3LAYERS
    GpioCtrlRegs.GPAGMUX2.bit.GPIO26 = 0;       /* IG_SIG */
    GpioCtrlRegs.GPAGMUX2.bit.GPIO27 = 0;       /* RST_GATE */
    GpioCtrlRegs.GPCGMUX1.bit.GPIO71 = 0;       /* RDY_1 */
    GpioCtrlRegs.GPCGMUX1.bit.GPIO72 = 0;       /* RDY_2 */
    GpioCtrlRegs.GPCGMUX1.bit.GPIO73 = 0;       /* RDY_3 */

    GpioCtrlRegs.GPAGMUX2.bit.GPIO26 = DIR_INPUT;       /* Enable RST_GATE as input */
    GpioCtrlRegs.GPAGMUX2.bit.GPIO27 = DIR_OUTPUT;      /* Enable RST_GATE as output */
    GpioCtrlRegs.GPCDIR.bit.GPIO71 = DIR_OUTPUT;        /* Enable RDY_1 as output */
    GpioCtrlRegs.GPCDIR.bit.GPIO72 = DIR_OUTPUT;        /* Enable RDY_2 as output */
    GpioCtrlRegs.GPCDIR.bit.GPIO73 = DIR_OUTPUT;        /* Enable RDY_3 as output */

    GpioDataRegs.GPASET.bit.GPIO27 = STATE_HIGH;        /* Set RST_GATE HIGH */
    GpioDataRegs.GPCCLEAR.bit.GPIO71 = STATE_HIGH;      /* Clear RDY_1 */
    GpioDataRegs.GPCCLEAR.bit.GPIO72 = STATE_HIGH;      /* Clear RDY_2 */
    GpioDataRegs.GPCCLEAR.bit.GPIO73 = STATE_HIGH;      /* Clear RDY_3 */
#endif
    /***********************************/

    GpioCtrlRegs.GPAGMUX2.bit.GPIO26 = 0;       /* Enable Buffer1 */
    GpioCtrlRegs.GPDGMUX1.bit.GPIO99 = 0;       /* Enable Buffer2 */

    GpioCtrlRegs.GPADIR.bit.GPIO26 = 1;         /* '1' means output : Enable Buffer1 */
    GpioCtrlRegs.GPDDIR.bit.GPIO99 = 1;         /* Enable Buffer2 */

    GpioCtrlRegs.GPAGMUX2.bit.GPIO28 = 0;       /* TP64 */
    GpioCtrlRegs.GPADIR.bit.GPIO28 = 1;
    GpioDataRegs.GPACLEAR.bit.GPIO28 = 0;

//    GpioCtrlRegs.GPAGMUX1.bit.GPIO8 = 0;       /* TP18 */
//    GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;
//    GpioDataRegs.GPACLEAR.bit.GPIO8 = 0;


    /* Fault Signals from GPIO 56 to GPIO 63  */
    GpioCtrlRegs.GPBGMUX2.bit.GPIO56 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO56 = 0;
    GpioDataRegs.GPBSET.bit.GPIO56  = 1;

    GpioCtrlRegs.GPBGMUX2.bit.GPIO57 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO57 = 0;
    GpioDataRegs.GPBSET.bit.GPIO57  = 1;

    GpioCtrlRegs.GPBGMUX2.bit.GPIO58 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO58 = 0;
    GpioDataRegs.GPBSET.bit.GPIO58  = 1;

    GpioCtrlRegs.GPBGMUX2.bit.GPIO59 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO59 = 0;
    GpioDataRegs.GPBSET.bit.GPIO59  = 1;

    GpioCtrlRegs.GPBGMUX2.bit.GPIO60 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO60 = 0;
    GpioDataRegs.GPBSET.bit.GPIO60  = 1;

    GpioCtrlRegs.GPBGMUX2.bit.GPIO61 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO61 = 0;
    GpioDataRegs.GPBSET.bit.GPIO61  = 1;

    GpioCtrlRegs.GPBGMUX2.bit.GPIO62 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO62 = 0;
    GpioDataRegs.GPBSET.bit.GPIO62  = 1;

    GpioCtrlRegs.GPBGMUX2.bit.GPIO63 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO63 = 0;
    GpioDataRegs.GPBSET.bit.GPIO63  = 1;

    /* Ready Signals from GPIO 48 to GPIO 55  */

    GpioCtrlRegs.GPBGMUX2.bit.GPIO48 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO48 = 0;
    GpioCtrlRegs.GPBGMUX2.bit.GPIO49 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO49 = 0;
    GpioCtrlRegs.GPBGMUX2.bit.GPIO50 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO50 = 0;
    GpioCtrlRegs.GPBGMUX2.bit.GPIO51 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO51 = 0;
    GpioCtrlRegs.GPBGMUX2.bit.GPIO52 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO52 = 0;
    GpioCtrlRegs.GPBGMUX2.bit.GPIO53 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO53 = 0;
    GpioCtrlRegs.GPBGMUX2.bit.GPIO54 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO54 = 0;
    GpioCtrlRegs.GPBGMUX2.bit.GPIO55 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO55 = 0;
    EDIS;

    GPIO_Interrupt_Set ( );

    return;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void GPIO_Interrupt_Set ( void )
{
#if LLC_FULL_3LAYERS

    EALLOW;
    GpioCtrlRegs.GPCGMUX1.bit.GPIO77 = 0;       /* GPIO77, for fault Interrupt */
    GpioCtrlRegs.GPCDIR.bit.GPIO77 = DIR_INPUT; /* GPIO77 as input */
    GpioCtrlRegs.GPCPUD.bit.GPIO77 = 0;         /* GPIO77, PULL UP Enable */
    GpioCtrlRegs.GPCQSEL1.bit.GPIO77 = 0;       /* XINT3 Synch to SYSCLKOUT only */

    GpioCtrlRegs.GPCGMUX1.bit.GPIO78 = 0;       /* GPIO78, for fault Interrupt */
    GpioCtrlRegs.GPCDIR.bit.GPIO78 = DIR_INPUT; /* GPIO78 as input */
    GpioCtrlRegs.GPCPUD.bit.GPIO78 = 0;         /* GPIO78, PULL UP Enable */
    GpioCtrlRegs.GPCQSEL1.bit.GPIO78 = 0;       /* XINT3 Synch to SYSCLKOUT only */

    GpioCtrlRegs.GPCGMUX1.bit.GPIO79 = 0;       /* GPIO79, for fault Interrupt */
    GpioCtrlRegs.GPCDIR.bit.GPIO79 = DIR_INPUT; /* GPIO79 as input */
    GpioCtrlRegs.GPCPUD.bit.GPIO79 = 0;         /* GPIO79, PULL UP Enable */
    GpioCtrlRegs.GPCQSEL1.bit.GPIO79 = 0;       /* XINT3 Synch to SYSCLKOUT only */

    EDIS;

    /* GPIO77 is XINT1, GPIO78 is XINT2, GPIO79 is XINT3 */
    GPIO_SetupXINT1Gpio ( 77 );
    GPIO_SetupXINT2Gpio ( 78 );
    GPIO_SetupXINT3Gpio ( 79 );
#else

    EALLOW;
    GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;         /* GPIO39, for Over Voltage Interrupt  */
    GpioCtrlRegs.GPBDIR.bit.GPIO39 = 0;          /* GPIO39 as input  */
    GpioCtrlRegs.GPBPUD.bit.GPIO39 = 1;          /* GPIO39, PULL UP Enable */
    GpioCtrlRegs.GPBQSEL1.bit.GPIO39 = 0;        /* XINT1 Synch to SYSCLKOUT only */


    GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 0;         /* GPIO40, for Over Current Interrupt */
    GpioCtrlRegs.GPBDIR.bit.GPIO40 = 0;          /* GPIO40 as input */
    GpioCtrlRegs.GPBPUD.bit.GPIO40 = 1;                  /* GPIO40, PULL UP Enable */
    GpioCtrlRegs.GPBQSEL1.bit.GPIO40 = 0;        /* XINT2 Synch to SYSCLKOUT only */


    GpioCtrlRegs.GPCGMUX1.bit.GPIO69 = 0;       /* GPIO69, for fault Interrupt */
    GpioCtrlRegs.GPCDIR.bit.GPIO69 = 0;         /* GPIO69 as input */
    GpioCtrlRegs.GPCPUD.bit.GPIO69 = 0;                  /* GPIO69, PULL UP Enable */
    GpioCtrlRegs.GPCQSEL1.bit.GPIO69 = 0;       /* XINT3 Synch to SYSCLKOUT only */

    EDIS;

    /* GPIO39 is XINT1, GPIO69 is XINT2, GPIO40 is XINT3 */
    GPIO_SetupXINT1Gpio ( 39 );
    GPIO_SetupXINT2Gpio ( 69 );
    GPIO_SetupXINT3Gpio ( 40 );
#endif
    /* Configure XINTs */
    XintRegs.XINT1CR.bit.POLARITY = 1;          /* Rising edge interrupt */
    XintRegs.XINT2CR.bit.POLARITY = 0;          /* Falling edge interrupt */
    XintRegs.XINT3CR.bit.POLARITY = 1;          /* Rising edge interrupt */

    /* Enable XINTs */
    XintRegs.XINT1CR.bit.ENABLE = 1;            /* Enable XINT1 */
    XintRegs.XINT2CR.bit.ENABLE = 1;            /* Enable XINT2 */
    XintRegs.XINT3CR.bit.ENABLE = 1;            /* Enable XINT3 */


}

/*--------------------------------------------------------------------------*/
/* Function  | Over_Current_isr                                             */
/* Name      | Over Current Interrupt                                       */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
interrupt void Over_Current_isr ( void )
{
    DISABLE_BUFF1;
    DISABLE_BUFF2;

    DISABLE_RDY1;
    DISABLE_RDY2;
    DISABLE_RDY3;

    stg_AswLLCDiagFlag.u8_OverCur_IC = STATE_FAULT;
    /* Acknowledge this interrupt to get more from group 12  */
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
}

/*--------------------------------------------------------------------------*/
/* Function  | Over_Volt_isr                                                */
/* Name      | Over Voltage Interrupt                                       */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
interrupt void Over_Volt_isr ( void )
{
    DISABLE_BUFF1;
    DISABLE_BUFF2;

    DISABLE_RDY1;
    DISABLE_RDY2;
    DISABLE_RDY3;

    stg_AswLLCDiagFlag.u8_OverVol_IC = STATE_FAULT;
    /* Acknowledge this interrupt to get more from group 1  */
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

/*--------------------------------------------------------------------------*/
/* Function  | Fualt_isr                                                    */
/* Name      | Fault Interrupt                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
interrupt void Fualt_isr ( void )
{
    DISABLE_BUFF1;
    DISABLE_BUFF2;

    DISABLE_RDY1;
    DISABLE_RDY2;
    DISABLE_RDY3;

    stg_AswLLCDiagFlag.u8_Gate_IC = STATE_FAULT;
    /* Acknowledge this interrupt to get more from group 1  */
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
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
