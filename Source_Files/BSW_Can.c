/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : FDC_LLC                                                     **
**  Filename  : BSW_Can.c                                                   **
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

#define BSW_CAN_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "F28x_Project.h"
#include <stdint.h>
#include <stdbool.h>
#include "ASW_Ctrl.h"
#include "ASW_LLCState.h"
#include "BSW_Can.h"
#include "BSW_Timer.h"
#include "BSW_Adc.h"
#include "BSW_Gpio.h"

/****************************************************************************/
/**                                                                        **/
/**                      DEFINITIONS AND MACROS                            **/
/**                                                                        **/
/****************************************************************************/
#define CAN_MSG_TRANS_ID_1              ( 0x10 )
#define CAN_MSG_TRANS_ID_2              ( 0x11 )
#define CAN_MSG_TRANS_ID_3              ( 0x12 )
#define CAN_MSG_TRANS_ID_4              ( 0x13 )
#define CAN_MSG_TRANS_ID_5              ( 0x14 )

#define CAN_MSG_RECV_ID_1               ( 0x20 )
#define CAN_TX_MSG_OBJ_1                ( 1 )
#define CAN_TX_MSG_OBJ_2                ( 2 )
#define CAN_TX_MSG_OBJ_3                ( 3 )
#define CAN_TX_MSG_OBJ_4                ( 4 )
#define CAN_TX_MSG_OBJ_5                ( 5 )
#define CAN_RX_MSG_OBJ_1                ( 10 )
#define CAN_MAX_BIT_DIVISOR             ( 13 )   /* The maximum CAN bit timing divisor  */
#define CAN_MIN_BIT_DIVISOR             ( 5 )    /* The minimum CAN bit timing divisor   */
#define CAN_MAX_PRE_DIVISOR             ( 1024 ) /* The maximum CAN pre-divisor   */
#define CAN_MIN_PRE_DIVISOR             ( 1 )    /* The minimum CAN pre-divisor   */
#define CAN_BTR_BRP_M                   ( 0x3F )
#define CAN_BTR_BRPE_M                  ( 0xF0000 )
#define CAN_MSG_ID_SHIFT                ( 18 )

typedef enum
{
    MSG_OBJ_TYPE_TRANSMIT,
    MSG_OBJ_TYPE_RECEIVE
}msgObjType;
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
static uint32_t BSW_setCANBitRate ( uint32_t sourceClock, uint32_t bitRate );
static void BSW_setupMessageObject ( uint32_t objID, uint32_t msgID, msgObjType msgType );
static void BSW_sendCANTxMessage ( uint32_t objID, byte ucTXMsgData[8] );
static bool BSW_getCANRxMessage ( uint32_t objID );
static void BSW_CANTxMsg_ID_1 ( void );
static void BSW_CANTxMsg_ID_2 ( void );
static void BSW_CANTxMsg_ID_3 ( void );
static void BSW_CANTxMsg_ID_4 ( void );
static void BSW_CANTxMsg_ID_5 ( void );

static void BSW_CANRx_Get_Data ( void );

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/
unsigned char ucRXMsgData[ 8 ] =  { 0, 0, 0, 0, 0, 0, 0, 0 };
byte u8_previous_mode;

float f16g_test_frequency = 30000.0;
float f16g_LLC_Deadtime = 550.0;
byte u8g_CAN_transmit = 1;

byte u8g_operationMode;
byte u8g_Close_Loop;
byte u8g_IG_ON = 0U;
byte u8g_resetFault = 0U;
byte u8g_LLC_LayerA = 0U;
byte u8g_LLC_LayerB = 0U;
byte u8g_LLC_LayerC = 0U;
float f32g_LLC_Target_V = 0.0F;
en_STATE_DEF u8g_LLC_CanTimeout = STATE_NORMAL;

/****************************************************************************/
/**                                                                        **/
/**                      GLOBAL VARIABLES                                  **/
/**                                                                        **/
/****************************************************************************/

static word u16g_LLC_CanTimeoutCnt = 0;

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
void BSW_Can_Init ( void )
{
    GPIO_SetupPinMux(36, GPIO_MUX_CPU1, 6);     /* GPIO36 -  CANRXA */
    GPIO_SetupPinOptions(36, GPIO_INPUT, GPIO_ASYNC);
    GPIO_SetupPinMux(37, GPIO_MUX_CPU1, 6);     /* GPIO37 - CANTXA */
    GPIO_SetupPinOptions(37, GPIO_OUTPUT, GPIO_PUSHPULL);

    InitCAN();

    ClkCfgRegs.CLKSRCCTL2.bit.CANABCLKSEL = 0;
    uint32_t status = BSW_setCANBitRate(200000000, 500000);

    BSW_setupMessageObject ( CAN_TX_MSG_OBJ_1, CAN_MSG_TRANS_ID_1, MSG_OBJ_TYPE_TRANSMIT );
    BSW_setupMessageObject ( CAN_TX_MSG_OBJ_2, CAN_MSG_TRANS_ID_2, MSG_OBJ_TYPE_TRANSMIT );
    BSW_setupMessageObject ( CAN_TX_MSG_OBJ_3, CAN_MSG_TRANS_ID_3, MSG_OBJ_TYPE_TRANSMIT );
    BSW_setupMessageObject ( CAN_TX_MSG_OBJ_4, CAN_MSG_TRANS_ID_4, MSG_OBJ_TYPE_TRANSMIT );
    BSW_setupMessageObject ( CAN_TX_MSG_OBJ_5, CAN_MSG_TRANS_ID_5, MSG_OBJ_TYPE_TRANSMIT );

    BSW_setupMessageObject ( CAN_RX_MSG_OBJ_1, CAN_MSG_RECV_ID_1, MSG_OBJ_TYPE_RECEIVE );

    CanaRegs.CAN_CTL.bit.Init = 0;

    u8_previous_mode = 1;

    return;
}

/*--------------------------------------------------------------------------*/
/* Function  | CAN_Transmit                                                 */
/* Name      | CAN Transmit                                                 */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void BSW_Can_TxRx ( void )
{
    BSW_CANTxMsg_ID_1 ();
    BSW_CANTxMsg_ID_2 ();
    BSW_CANTxMsg_ID_3 ();
    BSW_CANTxMsg_ID_4 ();
    BSW_CANTxMsg_ID_5 ();

    if ( BSW_getCANRxMessage ( CAN_RX_MSG_OBJ_1 ) == true )
    {
        BSW_CANRx_Get_Data ( );
        u8g_LLC_CanTimeout = STATE_NORMAL;
        u16g_LLC_CanTimeoutCnt = 0U;
    }
    else
    {
        if( u16g_LLC_CanTimeoutCnt < 5U )
        {
            u16g_LLC_CanTimeoutCnt++;
        }
        else
        {
            u8g_LLC_CanTimeout = STATE_FAULT;
        }
    }
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
en_STATE_DEF Bsw_GET_LLC_CanTimeout ( void )
{
    return u8g_LLC_CanTimeout; /* 1 : ok / 0 : false */
}

/****************************************************************************/
/**                                                                        **/
/**                      LOCAL FUNCTIONS                                   **/
/**                                                                        **/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Function  | sendCANMsg_ID_1                                              */
/* Name      | CAN ID1 Transmit                                             */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void BSW_CANTxMsg_ID_1 ( void )
{
    word u16_data = 0U ;
    byte ucTXMsgData[ 8 ] = { 0, };

    u16_data = ( word ) ( ( f32g_LLC_IoutA_LPF * 10.0f ) );
    ucTXMsgData[ 0 ] = Get16BitLoByte( u16_data );
    ucTXMsgData[ 1 ] = Get16BitHiByte( u16_data );

    u16_data = ( word ) ( ( f32g_LLC_IoutB_LPF * 10.0f ) );
    ucTXMsgData[ 2 ] = Get16BitLoByte( u16_data );
    ucTXMsgData[ 3 ] = Get16BitHiByte( u16_data );

    u16_data = ( word ) ( ( f32g_LLC_IoutC_LPF * 10.0f ) );
    ucTXMsgData[ 4 ] = Get16BitLoByte( u16_data );
    ucTXMsgData[ 5 ] = Get16BitHiByte( u16_data );

    u16_data = ( word ) ( ( f32g_LLC_Iout_LPF * 10.0f ) );
    ucTXMsgData[ 6 ] = Get16BitLoByte( u16_data );
    ucTXMsgData[ 7 ] = Get16BitHiByte( u16_data );

    BSW_sendCANTxMessage ( CAN_TX_MSG_OBJ_1, ucTXMsgData );
}

/*--------------------------------------------------------------------------*/
/* Function  | sendCANMsg_ID_2                                              */
/* Name      | CAN ID2 Transmit                                             */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void BSW_CANTxMsg_ID_2 ( void )
{
    word u16_data = 0U ;
    byte ucTXMsgData[ 8 ] = { 0, };

    u16_data = ( word ) ( ( f32g_LLC_ILinkA_LPF * 10.0f ) );
    ucTXMsgData[ 0 ] = Get16BitLoByte( u16_data );
    ucTXMsgData[ 1 ] = Get16BitHiByte( u16_data );

    u16_data = ( word ) ( ( f32g_LLC_ILinkB_LPF * 10.0f ) );
    ucTXMsgData[ 2 ] = Get16BitLoByte ( u16_data );
    ucTXMsgData[ 3 ] = Get16BitHiByte ( u16_data );

    u16_data = ( word ) ( ( f32g_LLC_ILinkC_LPF * 10.0f ) );
    ucTXMsgData[ 4 ] = Get16BitLoByte ( u16_data );
    ucTXMsgData[ 5 ] = Get16BitHiByte ( u16_data );

    u16_data = ( word ) ( ( f32g_LLC_Power * 10.0f ) );
    ucTXMsgData[ 6 ] = Get16BitLoByte ( u16_data );
    ucTXMsgData[ 7 ] = Get16BitHiByte ( u16_data );

    BSW_sendCANTxMessage ( CAN_TX_MSG_OBJ_2, ucTXMsgData );
}

/*--------------------------------------------------------------------------*/
/* Function  | sendCANMsg_ID_2                                              */
/* Name      | CAN ID2 Transmit                                             */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void BSW_CANTxMsg_ID_3 ( void )
{
    word u16_data = 0U ;
    byte ucTXMsgData[ 8 ] = { 0, };

    u16_data = ( word ) ( f32g_LLC_TMP_LPF[ TMP_CH1 ] );
    ucTXMsgData[ 0 ] = Get16BitLoByte( u16_data );

    u16_data = ( word ) ( f32g_LLC_TMP_LPF[ TMP_CH2 ] );
    ucTXMsgData[ 1 ] = Get16BitLoByte( u16_data );

    u16_data = ( word ) ( f32g_LLC_TMP_LPF[ TMP_CH3 ] );
    ucTXMsgData[ 2 ] = Get16BitLoByte( u16_data );

    u16_data = ( word ) ( f32g_LLC_TMP_LPF[ TMP_CH4 ] );
    ucTXMsgData[ 3 ] = Get16BitLoByte( u16_data );

    u16_data = ( word ) ( f32g_LLC_TMP_LPF[ TMP_CH5 ] );
    ucTXMsgData[ 4 ] = Get16BitLoByte( u16_data );

    u16_data = ( word ) ( f32g_LLC_TMP_LPF[ TMP_CH6 ] );
    ucTXMsgData[ 5 ] = Get16BitLoByte( u16_data );

    u16_data = ( word ) ( f32g_LLC_TMP_LPF[ TMP_CH7 ] );
    ucTXMsgData[ 6 ] = Get16BitLoByte( u16_data );

    u16_data = ( word ) ( f32g_LLC_TMP_LPF[ TMP_CH8 ] );
    ucTXMsgData[ 7 ] = Get16BitLoByte( u16_data );

    BSW_sendCANTxMessage ( CAN_TX_MSG_OBJ_3, ucTXMsgData );
}

/*--------------------------------------------------------------------------*/
/* Function  | sendCANMsg_ID_2                                              */
/* Name      | CAN ID2 Transmit                                             */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void BSW_CANTxMsg_ID_4 ( void )
{
    word u16_data = 0U ;
    byte ucTXMsgData[ 8 ] = { 0, };

    u16_data = ( word ) ( f32g_LLC_TMP_LPF[ TMP_CH9 ] );
    ucTXMsgData[ 0 ] = Get16BitLoByte( u16_data );

    u16_data = ( word ) ( f32g_LLC_TMP_LPF[ TMP_CH10 ] );
    ucTXMsgData[ 1 ] = Get16BitLoByte( u16_data );

    u16_data = ( word ) ( f32g_LLC_TMP_LPF[ TMP_CH11 ] );
    ucTXMsgData[ 2 ] = Get16BitLoByte( u16_data );

    u16_data = ( word ) ( f32g_LLC_TMP_LPF[ TMP_CH12 ] );
    ucTXMsgData[ 3 ] = Get16BitLoByte( u16_data );

    u16_data = ( word ) ( f32g_LLC_VLink_LPF * 10.0F );
    ucTXMsgData[ 4 ] =  Get16BitLoByte ( u16_data );
    ucTXMsgData[ 5 ] =  Get16BitHiByte ( u16_data );

    u16_data = ( word ) ( f32g_LLC_Vout_LPF * 10.0F );
    ucTXMsgData[ 6 ] = Get16BitLoByte ( u16_data );
    ucTXMsgData[ 7 ] = Get16BitHiByte ( u16_data );

    BSW_sendCANTxMessage ( CAN_TX_MSG_OBJ_4, ucTXMsgData );
}

/*--------------------------------------------------------------------------*/
/* Function  | sendCANMsg_ID_3                                              */
/* Name      | CAN ID3 Transmit                                             */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void BSW_CANTxMsg_ID_5 ( void )
{
    byte ucTXMsgData[ 8 ] = {0, };
    byte u8_VLink = 0U;
    byte u8_ILinkA = 0U;
    byte u8_ILinkB = 0U;
    byte u8_ILinkC = 0U;

    byte u8_IoutA = 0U;
    byte u8_IoutB = 0U;
    byte u8_IoutC = 0U;
    byte u8_Vout = 0U;

    byte u8_TMP_CH1 = 0U;
    byte u8_TMP_CH2 = 0U;
    byte u8_TMP_CH3 = 0U;
    byte u8_TMP_CH4 = 0U;
    byte u8_TMP_CH5 = 0U;
    byte u8_TMP_CH6 = 0U;
    byte u8_TMP_CH7 = 0U;
    byte u8_TMP_CH8 = 0U;
    byte u8_TMP_CH9 = 0U;
    byte u8_TMP_CH10 = 0U;
    byte u8_TMP_CH11 = 0U;
    byte u8_TMP_CH12 = 0U;


    byte u8_OverCur_IC = 0U;
    byte u8_OverVol_IC = 0U;
    byte u8_Gate_IC = 0U;

    if( stg_AswLLCDiagFlag.u8_VLink != 0U ){ u8_VLink = 1U; }
    if( stg_AswLLCDiagFlag.u8_ILinkA!= 0U ){ u8_ILinkA = 1U; }
    if( stg_AswLLCDiagFlag.u8_ILinkB!= 0U ){ u8_ILinkB = 1U; }
    if( stg_AswLLCDiagFlag.u8_ILinkC!= 0U ){ u8_ILinkC = 1U; }

    if( stg_AswLLCDiagFlag.u8_IoutA != 0U ){ u8_IoutA = 1U; }
    if( stg_AswLLCDiagFlag.u8_IoutB != 0U ){ u8_IoutB = 1U; }
    if( stg_AswLLCDiagFlag.u8_IoutC != 0U ){ u8_IoutC = 1U; }

    if( stg_AswLLCDiagFlag.u8_TMP_CH1 != 0U ){ u8_TMP_CH1 = 1U; }
    if( stg_AswLLCDiagFlag.u8_TMP_CH2 != 0U ){ u8_TMP_CH2 = 1U; }
    if( stg_AswLLCDiagFlag.u8_TMP_CH3 != 0U ){ u8_TMP_CH3 = 1U; }
    if( stg_AswLLCDiagFlag.u8_TMP_CH4 != 0U ){ u8_TMP_CH4 = 1U; }
    if( stg_AswLLCDiagFlag.u8_TMP_CH5 != 0U ){ u8_TMP_CH5 = 1U; }
    if( stg_AswLLCDiagFlag.u8_TMP_CH6 != 0U ){ u8_TMP_CH6 = 1U; }
    if( stg_AswLLCDiagFlag.u8_TMP_CH7 != 0U ){ u8_TMP_CH7 = 1U; }
    if( stg_AswLLCDiagFlag.u8_TMP_CH8 != 0U ){ u8_TMP_CH8 = 1U; }
    if( stg_AswLLCDiagFlag.u8_TMP_CH9 != 0U ){ u8_TMP_CH9 = 1U; }
    if( stg_AswLLCDiagFlag.u8_TMP_CH10 != 0U ){ u8_TMP_CH10 = 1U; }
    if( stg_AswLLCDiagFlag.u8_TMP_CH11 != 0U ){ u8_TMP_CH11 = 1U; }
    if( stg_AswLLCDiagFlag.u8_TMP_CH12 != 0U ){ u8_TMP_CH12 = 1U; }

    if( stg_AswLLCDiagFlag.u8_Vout != 0U ){ u8_Vout = 1U; }
    if( stg_AswLLCDiagFlag.u8_OverCur_IC != 0U ){ u8_OverCur_IC = 1U; }
    if( stg_AswLLCDiagFlag.u8_OverVol_IC != 0U ){ u8_OverVol_IC = 1U; }
    if( stg_AswLLCDiagFlag.u8_Gate_IC != 0U ){ u8_Gate_IC = 1U; }

    ucTXMsgData[ 0 ] = ( byte ) ( ( u8_IoutC<< 5U)|( u8_IoutB<< 4U)
                                 |( u8_IoutA<< 3U)|( u8_ILinkC<< 2U)
                                 |( u8_ILinkB<< 1U)|( u8_ILinkA ) );

    ucTXMsgData[ 1 ] = ( byte ) ( ( u8_TMP_CH8 << 7U )|( u8_TMP_CH7 << 6U )
                                 |( u8_TMP_CH6 << 5U )|( u8_TMP_CH5 << 4U )
                                 |( u8_TMP_CH4 << 3U )|( u8_TMP_CH3 << 2U )
                                 |( u8_TMP_CH2 << 1U )|( u8_TMP_CH1 ) );
    ucTXMsgData[ 2 ] = ( byte ) ( ( u8_TMP_CH12<< 3U)|( u8_TMP_CH11<< 2U)
                                 |( u8_TMP_CH10<< 1U)|( u8_TMP_CH9 ) );

    ucTXMsgData[ 3 ] = ( byte ) ( ( u8_Vout<< 1U)|( u8_VLink ) );
    ucTXMsgData[ 4 ] = ( byte ) ( ( u8_OverCur_IC << 2U )|( u8_OverVol_IC << 1U )|( u8_Gate_IC ) );
    ucTXMsgData[ 5 ] = 0;
    ucTXMsgData[ 6 ] = 0;
    ucTXMsgData[ 7 ] = 0;

    BSW_sendCANTxMessage ( CAN_TX_MSG_OBJ_5, ucTXMsgData );
}

/*--------------------------------------------------------------------------*/
/* Function  | Update_CAN_Get_Data                                          */
/* Name      | CAN Receive                                                  */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void BSW_CANRx_Get_Data ( void )
{
    word u16_data = 0U;

    u8g_IG_ON = ( byte )ucRXMsgData [ 0 ] & 0x01U;
    u8g_resetFault = ( byte ) ( ( ucRXMsgData [ 0 ] & 0x02U ) >> 1U );
    u8g_Close_Loop = ( byte ) ( ( ucRXMsgData [ 0 ] & 0x04U ) >> 2U );
    u8g_LLC_LayerA = ( byte ) ( ( ucRXMsgData [ 0 ] & 0x08U ) >> 3U );
    u8g_LLC_LayerB = ( byte ) ( ( ucRXMsgData [ 0 ] & 0x10U ) >> 4U );
    u8g_LLC_LayerC = ( byte ) ( ( ucRXMsgData [ 0 ] & 0x20U ) >> 5U );

    f16g_test_frequency = ucRXMsgData [ 2 ]<< 8U;
    f16g_test_frequency = (float)f16g_test_frequency + ucRXMsgData [ 1 ];

    u16_data = ucRXMsgData [ 4 ] << 8U;
    f32g_LLC_Target_V = ( single ) u16_data + ucRXMsgData [ 3 ];
 }

/*--------------------------------------------------------------------------*/
/* Function  | setCANBitRate                                                */
/* Name      | set CAN Bit Rate                                             */
/*--------------------------------------------------------------------------*/
/* Parameter | sourceClock ,   bitRate                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static uint32_t BSW_setCANBitRate ( uint32_t sourceClock, uint32_t bitRate )
{
    uint32_t desiredRatio;
    uint32_t canBits;
    uint32_t preDivide;
    uint32_t regValue;
    uint16_t canControlValue;
    uint16_t canBitValues[] =
    {
        0x1100,     /* TSEG2 2, TSEG1 2, SJW 1, Divide 5  */
        0x1200,     /*  TSEG2 2, TSEG1 3, SJW 1, Divide 6  */
        0x2240,     /*  TSEG2 3, TSEG1 3, SJW 2, Divide 7  */
        0x2340,     /*  TSEG2 3, TSEG1 4, SJW 2, Divide 8  */
        0x3340,     /*  TSEG2 4, TSEG1 4, SJW 2, Divide 9  */
        0x3440,     /*  TSEG2 4, TSEG1 5, SJW 2, Divide 10  */
        0x3540,     /*  TSEG2 4, TSEG1 6, SJW 2, Divide 11  */
        0x3640,     /*  TSEG2 4, TSEG1 7, SJW 2, Divide 12  */
        0x3740      /*  TSEG2 4, TSEG1 8, SJW 2, Divide 13  */
    };

    desiredRatio = sourceClock / bitRate;

    if((sourceClock / desiredRatio) > bitRate) { desiredRatio += 1; }

    while(desiredRatio <= CAN_MAX_PRE_DIVISOR * CAN_MAX_BIT_DIVISOR)
    {
        for(canBits = CAN_MAX_BIT_DIVISOR;
                canBits >= CAN_MIN_BIT_DIVISOR;
                canBits--)
        {

            preDivide = desiredRatio / canBits;

            if((preDivide * canBits) == desiredRatio)
            {
                regValue = canBitValues[canBits - CAN_MIN_BIT_DIVISOR];
                canControlValue = CanaRegs.CAN_CTL.all;
                CanaRegs.CAN_CTL.bit.Init = 1;
                CanaRegs.CAN_CTL.bit.CCE = 1;
                regValue |= ((preDivide - 1) & CAN_BTR_BRP_M) |
                                        (((preDivide - 1) << 10) & CAN_BTR_BRPE_M);

                CanaRegs.CAN_BTR.all = regValue;
                CanaRegs.CAN_CTL.all = canControlValue;
                return(sourceClock / ( preDivide * canBits));
            }
        }

        desiredRatio++;
    }

    return 0;
}

/*--------------------------------------------------------------------------*/
/* Function  | setupMessageObject                                           */
/* Name      | send CAN Msg Object                                          */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void BSW_setupMessageObject ( uint32_t objID, uint32_t msgID, msgObjType msgType )
{

    union CAN_IF1CMD_REG CAN_IF1CMD_SHADOW;

    while(CanaRegs.CAN_IF1CMD.bit.Busy)
    {
        /* Nothing */
    }

    CAN_IF1CMD_SHADOW.all = 0;
    CanaRegs.CAN_IF1MSK.all = 0;
    CanaRegs.CAN_IF1ARB.all = 0;
    CanaRegs.CAN_IF1MCTL.all = 0;
    CAN_IF1CMD_SHADOW.bit.Control = 1;
    CAN_IF1CMD_SHADOW.bit.Arb = 1;
    CAN_IF1CMD_SHADOW.bit.Mask = 1;
    CAN_IF1CMD_SHADOW.bit.DIR = 1;

    if(msgType == MSG_OBJ_TYPE_TRANSMIT)
    {
        CanaRegs.CAN_IF1ARB.bit.Dir = 1;
    }

    CanaRegs.CAN_IF1ARB.bit.ID = (msgID << CAN_MSG_ID_SHIFT);
    CanaRegs.CAN_IF1ARB.bit.MsgVal = 1;
    CanaRegs.CAN_IF1MCTL.bit.DLC = 8U;
    CanaRegs.CAN_IF1MCTL.bit.EoB = 1;
    CAN_IF1CMD_SHADOW.bit.MSG_NUM = objID;
    CanaRegs.CAN_IF1CMD.all = CAN_IF1CMD_SHADOW.all;
}

/*--------------------------------------------------------------------------*/
/* Function  | sendCANMessage                                               */
/* Name      | send CAN Msg                                                 */
/*--------------------------------------------------------------------------*/
/* Parameter | objID                                                        */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void BSW_sendCANTxMessage ( uint32_t objID, byte ucTXMsgData[8] )
{
    uint16_t index;
    union CAN_IF1CMD_REG CAN_IF1CMD_SHADOW;

    while(CanaRegs.CAN_IF1CMD.bit.Busy)
    {
        /* Nothing */
    }

    for(index = 0; index < 8U; index++)
    {
        switch(index)
        {
            case 0:
                    CanaRegs.CAN_IF1DATA.bit.Data_0 = ucTXMsgData[index];
                    break;
            case 1:
                    CanaRegs.CAN_IF1DATA.bit.Data_1 = ucTXMsgData[index];
                    break;
            case 2:
                    CanaRegs.CAN_IF1DATA.bit.Data_2 = ucTXMsgData[index];
                    break;
            case 3:
                    CanaRegs.CAN_IF1DATA.bit.Data_3 = ucTXMsgData[index];
                    break;
            case 4:
                    CanaRegs.CAN_IF1DATB.bit.Data_4 = ucTXMsgData[index];
                    break;
            case 5:
                    CanaRegs.CAN_IF1DATB.bit.Data_5 = ucTXMsgData[index];
                    break;
            case 6:
                    CanaRegs.CAN_IF1DATB.bit.Data_6 = ucTXMsgData[index];
                    break;
            case 7:
                    CanaRegs.CAN_IF1DATB.bit.Data_7 = ucTXMsgData[index];
                    break;
        }
    }

    CAN_IF1CMD_SHADOW.all = 0;
    CAN_IF1CMD_SHADOW.bit.DIR = 1;
    CAN_IF1CMD_SHADOW.bit.DATA_A = 1;
    CAN_IF1CMD_SHADOW.bit.DATA_B = 1;
    CAN_IF1CMD_SHADOW.bit.TXRQST = 1;
    CAN_IF1CMD_SHADOW.bit.MSG_NUM = objID;
    CanaRegs.CAN_IF1CMD.all = CAN_IF1CMD_SHADOW.all;
}

/*--------------------------------------------------------------------------*/
/* Function  | getCANMessage                                                */
/* Name      | Get CAN Msg                                                  */
/*--------------------------------------------------------------------------*/
/* Parameter | objID                                                        */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static bool BSW_getCANRxMessage ( uint32_t objID )
{
    bool status;
    uint16_t index;
    union CAN_IF2CMD_REG CAN_IF2CMD_SHADOW;

    CAN_IF2CMD_SHADOW.all = 0;
    CAN_IF2CMD_SHADOW.bit.Control = 1;
    CAN_IF2CMD_SHADOW.bit.DATA_A = 1;
    CAN_IF2CMD_SHADOW.bit.DATA_B = 1;
    CAN_IF2CMD_SHADOW.bit.MSG_NUM = objID;
    CanaRegs.CAN_IF2CMD.all = CAN_IF2CMD_SHADOW.all;

    while(CanaRegs.CAN_IF2CMD.bit.Busy)
    {
        /* Nothing  */
    }

    if(CanaRegs.CAN_IF2MCTL.bit.NewDat == 1)
    {
        for(index = 0; index < 8U; index++)
        {
            switch(index)
            {
                case 0:
                        ucRXMsgData[index] = CanaRegs.CAN_IF2DATA.bit.Data_0;
                break;
                case 1:
                        ucRXMsgData[index] = CanaRegs.CAN_IF2DATA.bit.Data_1;
                break;
                case 2:
                        ucRXMsgData[index] = CanaRegs.CAN_IF2DATA.bit.Data_2;
                break;
                case 3:
                        ucRXMsgData[index] = CanaRegs.CAN_IF2DATA.bit.Data_3;
                break;
                case 4:
                        ucRXMsgData[index] = CanaRegs.CAN_IF2DATB.bit.Data_4;
                break;
                case 5:
                        ucRXMsgData[index] = CanaRegs.CAN_IF2DATB.bit.Data_5;
                break;
                case 6:
                        ucRXMsgData[index] = CanaRegs.CAN_IF2DATB.bit.Data_6;
                break;
                case 7:
                        ucRXMsgData[index] = CanaRegs.CAN_IF2DATB.bit.Data_7;
                break;
            }
        }

        CAN_IF2CMD_SHADOW.all = CanaRegs.CAN_IF2CMD.all;
        CAN_IF2CMD_SHADOW.bit.TxRqst = 1;
        CAN_IF2CMD_SHADOW.bit.MSG_NUM = objID;
        CanaRegs.CAN_IF2CMD.all = CAN_IF2CMD_SHADOW.all;
        status = true;
    }
    else
    {
        status = false;
    }

    return(status);

}
/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
