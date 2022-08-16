/*
                             *******************
******************************* C HEADER FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : BSW_Defines                                          				**
**  Filename  : BSW_Defines.h                                        				**
**  Version   : -.- (PCB : )                                                **
**  Date      : 2019.03.11                                                  **
**                                                                          **
******************************************************************************
**                                                                          **
**  (c) 2019 YOUNG HWA TECH Co., Ltd. All Rights Reserved                   **
**                                                                          **
**                       YOUNG HWA TECH Co., Ltd.                           **
******************************************************************************

VERSION HISTORY:
----------------

Version     : -.-
Date        : ----.--.--
Revised by  : Im, Hong Kyun
Description : Original version.

*/

#ifndef BSW_DEFINES_INCLUDED
#define BSW_DEFINES_INCLUDED

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                      DEFINITIONS AND MACROS                            **/
/**                                                                        **/
/****************************************************************************/
/*****************************************************************************

signed char ----------- s8
signed char* ---------- s8p
static signed char ---- s8s
static signed char* --- s8sp
extern signed char ---- s8g
extern signed char* --- s8gp

unsigned char --------- u8
unsigned char* -------- u8p
static unsigned char -- u8s
static unsigned char* - u8sp
extern unsigned char -- u8g
extern unsigned char* - u8gp

struct ---------------- st
struct* --------------- stp
static struct --------- sts
static struct* -------- stsp
extern struct --------- stg
extern struct* -------- stgp

enum ------------------ en
static enum ----------- ens
extern enum ----------- eng

*****************************************************************************/
/*****************************************************************************
  @ Types definition
*****************************************************************************/
# if defined ( GNU_C_DATA_TYPE )
	typedef volatile signed char sbyte;
	typedef volatile unsigned char byte;

	typedef volatile signed short sword;
	typedef volatile unsigned short word;

	typedef volatile signed int sdword;
	typedef volatile unsigned int dword;

# else
	typedef signed char   sbyte;
	typedef unsigned char byte;

	typedef signed short    sword;
	typedef unsigned short  word;

	typedef signed long   sdword;
	typedef unsigned long dword;

	typedef float single;
# endif
/*
typedef struct
{
  byte b0:1;
  byte b1:1;
  byte b2:1;
  byte b3:1;
  byte b4:1;
  byte b5:1;
  byte b6:1;
  byte b7:1;
}ST_Reg_8Bit;

typedef struct
{
  byte b0	:1;
  byte b1	:1;
  byte b2	:1;
  byte b3	:1;
  byte b4	:1;
  byte b5	:1;
  byte b6	:1;
  byte b7	:1;
  byte b8	:1;
	byte b9	:1;
	byte b10:1;
	byte b11:1;
	byte b12:1;
	byte b13:1;
	byte b14:1;
	byte b15:1;
}ST_Reg_16Bit;

typedef struct
{
  byte b0	:1;
  byte b1	:1;
  byte b2	:1;
  byte b3	:1;
  byte b4	:1;
  byte b5	:1;
  byte b6	:1;
  byte b7	:1;
  byte b8	:1;
	byte b9	:1;
	byte b10:1;
	byte b11:1;
	byte b12:1;
	byte b13:1;
	byte b14:1;
	byte b15:1;
	byte b16:1;
	byte b17:1;
	byte b18:1;
	byte b19:1;
	byte b20:1;
	byte b21:1;
	byte b22:1;
	byte b23:1;
	byte b24:1;
	byte b25:1;
	byte b26:1;
	byte b27:1;
	byte b28:1;
	byte b29:1;
	byte b30:1;
	byte b31:1;
}ST_Reg_32Bit;
*/
/*****************************************************************************
  @ Standard Defines                                                       
*****************************************************************************/
# ifndef NULL
#define NULL    ( ( void * ) 0 )
# endif

/* Bits peripheral register access macros - 8 bit access */  
#define setReg8( RegName, val )                       ( RegName = ( byte )( val ) )
#define getReg8( RegName )                            ( ( byte )RegName )
#define testReg8Bits( RegName, GetMask )              ( RegName & ( GetMask ) )
#define clrReg8Bits( RegName, ClrMask )               ( RegName &= ( byte )( ~ClrMask & 0xFFU ) )
#define setReg8Bits( RegName, SetMask )               ( RegName |= ( byte )( SetMask ) )
#define invertReg8Bits( RegName, InvMask )            ( RegName ^= ( byte )( InvMask ) )
#define clrSetReg8Bits( RegName, ClrMask, SetMask )   ( RegName = ( RegName & ( ( byte )( ~ClrMask & 0xFFU ) ) ) | ( byte )( SetMask ) )

/* Bits peripheral register access macros - 16 bit access */  
#define setReg16( RegName, val )                        ( RegName = ( word )( val ) )                                                                         
#define getReg16( RegName )                             ( ( word )RegName )
#define testReg16Bits( RegName, GetMask )               ( RegName & ( GetMask ) )
#define clrReg16Bits( RegName, ClrMask )                ( RegName &= ( word )( ~ClrMask & 0xFFFFU ) )
#define setReg16Bits( RegName, SetMask )                ( RegName |= ( word )( SetMask ) )
#define invertReg16Bits( RegName, InvMask )             ( RegName ^= ( word )( InvMask ) )
#define clrSetReg16Bits( RegName, ClrMask, SetMask )    ( RegName = ( RegName & ( ( word )( ~ClrMask & 0xFFFFU ) ) ) | ( word )( SetMask ) )

#define setReg32( RegName, val )                        ( RegName = ( dword )( val ) )
#define testReg32Bits( RegName, GetMask )               ( RegName & ( GetMask ) )
#define setReg32Bits( RegName, SetMask )                ( RegName |= ( dword )( SetMask ) )
#define clrReg32Bits( RegName, ClrMask )                ( RegName &= ( dword )( ~ClrMask & 0xFFFFFFFFU ) )
#define clrSetReg32Bits( RegName, ClrMask, SetMask )    ( RegName = ( RegName & ( ( dword )( ~ClrMask & 0xFFFFFFFFU ) ) ) | ( dword )( SetMask ) )

/* Data assemble/deassemble macros */
/* compose from byte stream a 16 bit data */
#define Make16Bit( hiByte, loByte )   ( ( word )( ( ( ( word )( hiByte ) & 0x00FFU ) << 8 ) | ( ( word )( loByte ) ) ) )

/* compose from byte stream a 32 bit data */
#define Make32Bit( hiHiByte, hiLoByte, loHiByte, loLoByte )   ( ( dword )( ( ( ( dword )( hiHiByte ) ) << 24 ) | \
                                                                           ( ( ( dword )( hiLoByte ) ) << 16 ) | \
                                                                           ( ( ( dword )( loHiByte ) ) << 8 )  | \
                                                                             ( ( dword )( loLoByte ) ) ) )
/* decompose 8 bit data in nibble stream */
#define Get8BitHiNibble( data )   ( ( byte )( ( ( data ) & 0xF0U ) >> 4 ) )
#define Get8BitLoNibble( data )   ( ( byte )( ( ( data ) & 0x0FU ) ) )

/* decompose 16 bit data in byte stream */
#define Get16BitHiByte( data )    ( ( byte )( ( ( data ) & 0xFF00U ) >> 8 ) )
#define Get16BitLoByte( data )    ( ( byte )( data ) )

/* decompose 32 bit data in byte stream */
#define Get32BitHiHiByte( data )    ( ( byte )( ( ( dword )( data ) ) >> 24 ) )
#define Get32BitHiLoByte( data )    ( ( byte )( ( ( dword )( data ) ) >> 16 ) )
#define Get32BitLoHiByte( data )    ( ( byte )( ( ( dword )( data ) ) >> 8 ) )
#define Get32BitLoLoByte( data )    ( ( byte )( data ) )

/* decompose 32 bit data in word stream */
#define Get32BitHiWord( data )    ( ( word )( ( ( dword )( data ) ) >> 16 ) )
#define Get32BitLoWord( data )    ( ( word )( data ) )

/* Little endian <==> big endian 32-bit swap macros. */
#define Swap32LittleBig( a ) {                                  \
          dword u32_Tmp;                                        \
          u32_Tmp = a;                                          \
          ( ( byte * )&a )[ 0 ] = ( ( byte * )&u32_Tmp )[ 3 ];  \
          ( ( byte * )&a )[ 1 ] = ( ( byte * )&u32_Tmp )[ 2 ];  \
          ( ( byte * )&a )[ 2 ] = ( ( byte * )&u32_Tmp )[ 1 ];  \
          ( ( byte * )&a )[ 3 ] = ( ( byte * )&u32_Tmp )[ 0 ];  \
        }

/* Little endian <==> big endian 16-bit swap macros. */
#define Swap16LittleBig( a ) {                                  \
          word u16_Tmp;                                         \
          u16_Tmp = ( word )a;                                  \
          ( ( byte * )&a )[ 0 ] = ( ( byte * )&u16_Tmp )[ 1 ];  \
          ( ( byte * )&a )[ 1 ] = ( ( byte * )&u16_Tmp )[ 0 ];  \
        }

#define MAX( a, b )   ( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )
#define MIN( a, b )   ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )

#define ABS( a )    ( ( ( a ) > 0 ) ? ( a ) : ( -( a ) ) )

#define SWAP( a, b )    ( ( a ) ^= ( b ), ( b ) ^= ( a ), ( a ) ^= ( b ) )

#define ASCII2HEX( a )    ( ( a ) - ( ( ( a ) > '9' ) ? ( 'A' - 10 ) : '0' ) )
#define HEX2ASCII( b )    ( ( b ) + ( ( ( b ) >  9  ) ? ( 'A' - 10 ) : '0' ) )

#define UPPERCASE( c )    ( ( c ) - ( ( 'a' <= ( c ) && ( c ) <= 'z' ) ? ( 'a' - 'A' ) : 0 ) )     
#define LOWERCASE( c )    ( ( c ) + ( ( 'A' <= ( c ) && ( c ) <= 'Z' ) ? ( 'a' - 'A' ) : 0 ) )

#define ARRAY_SIZE( array )   ( sizeof( array ) / sizeof( array[ 0 ] ) )

/* Bits mask */
#define u8g_Bit0    ( 0x01U ) /* Bit0 */ 
#define u8g_Bit1    ( 0x02U )	/* Bit1 */ 
#define u8g_Bit2    ( 0x04U )	/* Bit2 */ 
#define u8g_Bit3    ( 0x08U )	/* Bit3 */ 
#define u8g_Bit4    ( 0x10U )	/* Bit4 */ 
#define u8g_Bit5    ( 0x20U )	/* Bit5 */ 
#define u8g_Bit6    ( 0x40U )	/* Bit6 */ 
#define u8g_Bit7    ( 0x80U )	/* Bit7 */

#define u8g_Bit8    ( 0x0100U ) /* Bit8  */ 
#define u8g_Bit9    ( 0x0200U )	/* Bit9  */ 
#define u8g_Bit10   ( 0x0400U )	/* Bit10 */ 
#define u8g_Bit11   ( 0x0800U )	/* Bit11 */ 
#define u8g_Bit12   ( 0x1000U )	/* Bit12 */ 
#define u8g_Bit13   ( 0x2000U )	/* Bit13 */ 
#define u8g_Bit14   ( 0x4000U )	/* Bit14 */ 
#define u8g_Bit15   ( 0x8000U )	/* Bit15 */

/* Bit shift */
#define	SFT00   ( 0U )  /* initial shift value */
#define	SFT01		( 1U )	/* initial shift value */
#define	SFT02		( 2U )	/* initial shift value */
#define	SFT03		( 3U )	/* initial shift value */
#define	SFT04		( 4U )	/* initial shift value */
#define	SFT05		( 5U )	/* initial shift value */
#define	SFT06		( 6U )	/* initial shift value */
#define	SFT07		( 7U )	/* initial shift value */
#define	SFT08		( 8U )	/* initial shift value */
#define	SFT09		( 9U ) /* initial shift value */
#define	SFT10		( 10U ) /* initial shift value */
#define	SFT11		( 11U ) /* initial shift value */
#define	SFT12		( 12U ) /* initial shift value */
#define	SFT13		( 13U ) /* initial shift value */
#define	SFT14		( 14U ) /* initial shift value */
#define	SFT15		( 15U ) /* initial shift value */
#define	SFT16		( 16U ) /* initial shift value */
#define	SFT17		( 17U ) /* initial shift value */
#define	SFT18		( 18U ) /* initial shift value */
#define	SFT19		( 19U ) /* initial shift value */
#define	SFT20		( 20U ) /* initial shift value */
#define	SFT21		( 21U ) /* initial shift value */
#define	SFT22		( 22U ) /* initial shift value */
#define	SFT23		( 23U ) /* initial shift value */
#define	SFT24		( 24U ) /* initial shift value */
#define	SFT25		( 25U ) /* initial shift value */
#define	SFT26		( 26U ) /* initial shift value */
#define	SFT27		( 27U ) /* initial shift value */
#define	SFT28		( 28U ) /* initial shift value */
#define	SFT29		( 29U ) /* initial shift value */
#define	SFT30		( 30U ) /* initial shift value */
#define	SFT31		( 31U ) /* initial shift value */

/* Macros for sleep ready */
#define SLEEP_READY   ( 0x00U ) /* Sleep Available, OK */
#define	SLEEP_NA		  ( 0x01U ) /* bit0 : Appl Sleep Not Available */

/* Macros for control type */
#define LO_TYPE   ( 1U )
#define HI_TYPE		( 2U )

/* Macros for edge state type */
#define NO_EDGE   ( 0U )
#define LO_EDGE   ( 1U )
#define HI_EDGE   ( 2U )

/*****************************************************************************
  @ Macros for unsigned 1bit variable(bit field)                                                    
*****************************************************************************/
#define	big_TRUE    ( 1U )
#define	big_FALSE		( 0U )

#define	big_ON    ( 1U )
#define	big_OFF   ( 0U )

#define	big_NA		( 1U ) /* Not Available */
#define	big_OK		( 0U )

#define	big_HI		( 1U ) /* value high */
#define	big_LO		( 0U )	/* value low  */

#define	big_ENA		( 1U )	/* enable  */
#define	big_DIS   ( 0U )	/* disable */

#define big_ACTIVE      ( 1U )
#define big_INACTIVE    ( 0U )

#define big_EXIST   ( 1U )
#define big_NONE    ( 0U )

#define	big_SET     ( 1U ) /* SET Value = 1   */
#define	big_RESET   ( 0U )	/* RESET Value = 0 */

#define big_FAIL			( 0U )
#define big_SUCCESS		( 1U )

#define u8g_MAX   ( 0xFFU )
#define	u8g_MIN		( 0x00U )

#define	u16g_MAX    ( 0xFFFFU )
#define	u16g_MIN		( 0x0000U )

#define	u32g_MAX		( 0xFFFFFFFFU )
#define	u32g_MIN    ( 0x00000000U )

#define u8g_HI    ( 0x01U ) /* value high */
#define	u8g_LO		( 0x00U ) /* value low */

#define	u8g_ON    ( 0x01U ) /* General On */
#define	u8g_OFF		( 0x00U ) /* General Off */

#define u8g_SET   ( 0x01U )
#define u8g_CLR   ( 0x00U )

#define	u16g_SET		( 0x0001U )
#define	u16g_CLR    ( 0x0000U )

#define	u32g_SET    ( 0x00000001U )
#define	u32g_CLR		( 0x00000000U )

/*****************************************************************************
  @ Internal definitions of the error constants.                           
*****************************************************************************/
#define ERR_OK          ( 0U )  /* OK */
#define ERR_SPEED       ( 1U )  /* This device does not work in the active speed mode. */
#define ERR_RANGE       ( 2U )  /* Parameter out of range. */
#define ERR_VALUE       ( 3U )  /* Parameter of incorrect value. */
#define ERR_OVERFLOW    ( 4U )  /* Timer overflow. */
#define ERR_MATH        ( 5U )  /* Overflow during evaluation. */
#define ERR_ENABLED     ( 6U )  /* Device is enabled. */
#define ERR_DISABLED    ( 7U )  /* Device is disabled. */
#define ERR_BUSY        ( 8U )  /* Device is busy. */
#define ERR_NOTAVAIL    ( 9U )  /* Requested value or method not available. */
#define ERR_RXEMPTY     ( 10U ) /* No data in receiver. */
#define ERR_TXFULL      ( 11U ) /* Transmitter is full. */
#define ERR_BUSOFF      ( 12U ) /* Bus not available. */
#define ERR_OVERRUN     ( 13U ) /* Overrun error is detected. */
#define ERR_FRAMING     ( 14U ) /* Framing error is detected. */
#define ERR_PARITY      ( 15U ) /* Parity error is detected. */
#define ERR_NOISE       ( 16U ) /* Noise error is detected. */
#define ERR_IDLE        ( 17U ) /* Idle error is detected. */
#define ERR_FAULT       ( 18U ) /* Fault error is detected. */
#define ERR_BREAK       ( 19U ) /* Break char is received during communication. */
#define ERR_CRC         ( 20U ) /* CRC error is detected. */
#define ERR_ARBITR      ( 21U ) /* A node losts arbitration. This error occurs if two nodes start transmission at the same time. */
#define ERR_PROTECT     ( 22U ) /* Protection error is detected. */
#define ERR_UNDERFLOW   ( 23U ) /* Underflow error is detected. */
#define ERR_UNDERRUN    ( 24U ) /* Underrun error is detected. */
#define ERR_COMMON      ( 25U ) /* Common error of a device. */
#define ERR_LINSYNC     ( 26U ) /* LIN synchronization error is detected. */

#define ME_PCTL_RUN( n )		( ( ( dword )( n ) ) << 0U )
#define ME_PCTL_LP( n )     ( ( ( dword )( n ) ) << 3U )

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

# ifndef BSW_DEFINES_C_SRC
# endif

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
extern byte U8_CountUp ( byte u8_Count, byte u8_Max );
extern byte U8_CountDown ( byte u8_Count );
extern word U16_CountUp ( word u16_Count, word u16_Max );
extern word U16_CountDown ( word u16_Count );
extern dword U32_CountUp ( dword u32_Count, dword u32_Max );
extern dword U32_CountDown ( dword u32_Count );
extern byte DetectEdgeState ( byte u8_NowValue, byte *u8p_LastValue );

#endif

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
