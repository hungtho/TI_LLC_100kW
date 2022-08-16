
MEMORY
{
PAGE 0 :
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */

//   BEGIN           	: origin = 0x000000, length = 0x000002
   BEGIN           	: origin = 0x080000, length = 0x000002
   RAMM0           	: origin = 0x000122, length = 0x0002DE
   RAMD0           	: origin = 0x00B000, length = 0x000800
//   RAMLS0          	: origin = 0x008000, length = 0x000800
//   RAMLS1          	: origin = 0x008800, length = 0x000800
//   RAMLS2      		: origin = 0x009000, length = 0x000800
//   RAMLS3      		: origin = 0x009800, length = 0x000800
//   RAMLS4      		: origin = 0x00A000, length = 0x000800
   RAMLS01234		: origin = 0x008000, length = 0x003000
   RESET           	: origin = 0x3FFFC0, length = 0x000002

   /* Flash sectors */
   FLASHA           : origin = 0x080002, length = 0x001FFE	/* on-chip Flash */
   FLASHB           : origin = 0x082000, length = 0x002000	/* on-chip Flash */
   FLASHC           : origin = 0x084000, length = 0x002000	/* on-chip Flash */
   FLASHD           : origin = 0x086000, length = 0x002000	/* on-chip Flash */
  // FLASHE           : origin = 0x088000, length = 0x008000	/* on-chip Flash */
   FLASHE           : origin = 0x088000, length = 0x030000	/* on-chip Flash */
   //FLASHF           : origin = 0x090000, length = 0x008000	/* on-chip Flash */
   //FLASHG           : origin = 0x098000, length = 0x008000	/* on-chip Flash */
  // FLASHH           : origin = 0x0A0000, length = 0x008000	/* on-chip Flash */
  // FLASHI           : origin = 0x0A8000, length = 0x008000	/* on-chip Flash */
  // FLASHJ           : origin = 0x0B0000, length = 0x008000	/* on-chip Flash */
   FLASHK           : origin = 0x0B8000, length = 0x002000	/* on-chip Flash */
   FLASHL           : origin = 0x0BA000, length = 0x002000	/* on-chip Flash */
   FLASHM           : origin = 0x0BC000, length = 0x002000	/* on-chip Flash */
   FLASHN           : origin = 0x0BE000, length = 0x002000	/* on-chip Flash */
   FLASHO           : origin = 0x0C0000, length = 0x002000	/* on-chip Flash */
   FLASHP           : origin = 0x0C2000, length = 0x002000	/* on-chip Flash */
   FLASHQ           : origin = 0x0C4000, length = 0x002000	/* on-chip Flash */
   FLASHR           : origin = 0x0C6000, length = 0x002000	/* on-chip Flash */
   FLASHS           : origin = 0x0C8000, length = 0x008000	/* on-chip Flash */
   FLASHT           : origin = 0x0D0000, length = 0x008000	/* on-chip Flash */
   FLASHU           : origin = 0x0D8000, length = 0x008000	/* on-chip Flash */
   FLASHV           : origin = 0x0E0000, length = 0x008000	/* on-chip Flash */
   FLASHW           : origin = 0x0E8000, length = 0x008000	/* on-chip Flash */
   FLASHX           : origin = 0x0F0000, length = 0x008000	/* on-chip Flash */
   FLASHY           : origin = 0x0F8000, length = 0x002000	/* on-chip Flash */
   FLASHZ           : origin = 0x0FA000, length = 0x002000	/* on-chip Flash */
   FLASHAA          : origin = 0x0FC000, length = 0x002000	/* on-chip Flash */
   FLASHAB          : origin = 0x0FE000, length = 0x002000	/* on-chip Flash */

PAGE 1 :

   BOOT_RSVD       : origin = 0x000002, length = 0x000120     /* Part of M0, BOOT rom will use this for stack */
   RAMM1           : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
   RAMD1           : origin = 0x00B800, length = 0x000800

   RAMLS5      : origin = 0x00A800, length = 0x000800

   RAMGS0      : origin = 0x00C000, length = 0x001000
   RAMGS1      : origin = 0x00D000, length = 0x001000
   RAMGS2      : origin = 0x00E000, length = 0x001000
   RAMGS3      : origin = 0x00F000, length = 0x001000
   RAMGS4      : origin = 0x010000, length = 0x001000
 //  RAMGS5      : origin = 0x011000, length = 0x001000
//   RAMGS6      : origin = 0x012000, length = 0x001000
   RAMGS_F   : origin = 0x011000, length = 0x007000 // abk
//   RAMGS7      : origin = 0x013000, length = 0x001000
//   RAMGS8_11   : origin = 0x014000, length = 0x004000
//   RAMGS8      : origin = 0x014000, length = 0x001000
//   RAMGS9      : origin = 0x015000, length = 0x001000
//   RAMGS10     : origin = 0x016000, length = 0x001000
//   RAMGS11     : origin = 0x017000, length = 0x001000

   CANA_MSG_RAM     : origin = 0x049000, length = 0x000800
   CANB_MSG_RAM     : origin = 0x04B000, length = 0x000800
}


SECTIONS
{
   codestart        : > BEGIN,     PAGE = 0

   wddisable		: > FLASHB,		PAGE = 0
   copysections 	: > FLASHB, 	PAGE = 0

//   .text            : > FLASHA,    PAGE = 0
//   .cinit           : > FLASHA,    PAGE = 0
//   .pinit           : > FLASHA,    PAGE = 0
//   .switch          : > FLASHA,    PAGE = 0
//////////////////////////////////////////////////////////////////////
   .text        	: LOAD = FLASHE,     PAGE = 0
					  RUN = RAMGS_F, PAGE = 1
					  LOAD_START(_text_loadstart),
					  RUN_START(_text_runstart),
					  SIZE(_text_size)

   .cinit           : LOAD = FLASHA,     PAGE = 0
					  RUN = RAMM0 | RAMD0, PAGE = 0
					  LOAD_START(_cinit_loadstart),
					  RUN_START(_cinit_runstart),
					  SIZE(_cinit_size)

   .pinit           : LOAD = FLASHA,     PAGE = 0
					  RUN = RAMM0, PAGE = 0
					  LOAD_START(_pinit_loadstart),
					  RUN_START(_pinit_runstart),
					  SIZE(_pinit_size)

   .econst          : LOAD = FLASHA,     PAGE = 0
					  RUN = RAMLS5, PAGE = 1
					  LOAD_START(_econst_loadstart),
					  RUN_START(_econst_runstart),
					  SIZE(_econst_size)

   .switch          : LOAD = FLASHA,     PAGE = 0
					  RUN = RAMM0, PAGE = 0
					  LOAD_START(_switch_loadstart),
					  RUN_START(_switch_runstart),
					  SIZE(_switch_size)
//////////////////////////////////////////////////////////////////////
   .reset           : > RESET,     PAGE = 0, TYPE = DSECT /* not used, */

   .stack           : > RAMD1,     PAGE = 1
   .ebss            : > RAMLS5,    PAGE = 1
//   .econst          : > FLASHA,    PAGE = 0
   .esysmem         : > RAMLS5,    PAGE = 1
   Filter_RegsFile  : > RAMGS0,	   PAGE = 1  // leegy

   ramgs0           : > RAMGS0,    PAGE = 1
   ramgs1           : > RAMGS1,    PAGE = 1

#ifdef __TI_COMPILER_VERSION__
   #if __TI_COMPILER_VERSION__ >= 15009000
    .TI.ramfunc : {} > RAMM0,      PAGE = 0
   #else
   ramfuncs         : > RAMM0      PAGE = 0   
   #endif
#endif

   /* The following section definitions are for SDFM examples */
   Filter1_RegsFile : > RAMGS1,	PAGE = 1, fill=0x1111
   Filter2_RegsFile : > RAMGS2,	PAGE = 1, fill=0x2222
   Filter3_RegsFile : > RAMGS3,	PAGE = 1, fill=0x3333
   Filter4_RegsFile : > RAMGS4,	PAGE = 1, fill=0x4444
 //  Difference_RegsFile : >RAMGS5, 	PAGE = 1, fill=0x3333
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
