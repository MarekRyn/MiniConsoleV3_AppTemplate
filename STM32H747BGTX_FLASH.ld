/*******************************************************************/
/* MiniConsole V3 - Application - Linker script                    */
/*                                                                 */
/* Author: Marek Ryn                                               */
/* Version: 0.1b                                                   */
/*                                                                 */
/* Changelog:                                                      */
/*                                                                 */
/* - 0.1b	- Development version                                  */
/*******************************************************************/


/* Entry Point */
ENTRY(app_entry)

/* All stack parameteres are handled by firmware. App is sharing stack with firmware */


_Min_Heap_Size = 0x200; /* required for complier to check if enough APP_RAM is available */
_max_heap =  ORIGIN(APP_RAM) + LENGTH(APP_RAM); /* heap can extend up to end of APP_RAM */

/* Memories definition */
MEMORY
{
  ITCMRAM	(xrw)	: ORIGIN = 0x00000000, 	LENGTH = 64K	/* Fast memory for CM7 Core - Instructions */
  DTCMRAM 	(rw)  	: ORIGIN = 0x20000000, 	LENGTH = 128K   /* Fast memory for CM7 Core - Data */
  
  APP_FLASH (rx)	: ORIGIN = 0x90000000, 	LENGTH = 16M    /* Application code */
  APP_RAM	(xrw)	: ORIGIN = 0x24020000, 	LENGTH = 384K   /* Application data */
  
  SH0_RAM	(rw)	: ORIGIN = 0x30040000, 	LENGTH = 32K    /* Shared memory for Sound System */
  SH1_RAM	(rw)	: ORIGIN = 0x38008000, 	LENGTH = 32K    /* Shared memory for Application */
}

/* Sections */
SECTIONS
{
  /* The startup code into "APP_FLASH" memory */
  .app_config :
  {
    . = ALIGN(4);
    KEEP(*(.app_config)) /* Startup code */
    . = ALIGN(4);
  } >APP_FLASH


  /* The program code and other data into "OS_FLASH" memory */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } >APP_FLASH


  /* Used by the startup to initialize copy routine*/
  _siitcmram = LOADADDR(.itc_mram);

  /* The program routines to be located in ITCMRAM and executed from this memory */
  .itc_mram : {
  	. = ALIGN(4);
  	_sitcmram = .;        /* create a global symbol at data start */
  	*(.itc_mram)			  /* program routines to copy to ITCMRAM */
    . = ALIGN(4);
    _eitcmram = .;        /* define a global symbol at data end */
  } >ITCMRAM AT> APP_FLASH 

  /* Constant data into "APP_FLASH" memory */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >APP_FLASH

  .ARM.extab   : { 
    . = ALIGN(4);
    *(.ARM.extab* .gnu.linkonce.armextab.*)
    . = ALIGN(4);
  } >APP_FLASH
  
  .ARM : {
    . = ALIGN(4);
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
    . = ALIGN(4);
  } >APP_FLASH

  .preinit_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
    . = ALIGN(4);
  } >APP_FLASH
  
  .init_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
    . = ALIGN(4);
  } >APP_FLASH
  
  .fini_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
    . = ALIGN(4);
  } >APP_FLASH

  /* Used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections into "OS_RAM" memory */
  .data : 
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */
    *(.RamFunc)        /* .RamFunc sections */
    *(.RamFunc*)       /* .RamFunc* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >APP_RAM AT> APP_FLASH
  
  
  /* Used by the startup to initialize copy routine*/
  _sidtcmram = LOADADDR(.dtc_mram);

  /* The program data to be located in DTCMRAM and accessed from this memory */
  .dtc_mram : {
  	. = ALIGN(4);
  	_sdtcmram = .;        /* create a global symbol at data start */
  	*(.dtc_mram)			  /* program routines to copy to DTCMRAM */
    . = ALIGN(4);
    _edtcmram = .;        /* define a global symbol at data end */
  } >DTCMRAM AT> APP_FLASH 

  /* Uninitialized data section into "OS_RAM" memory */
  . = ALIGN(4);
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss section */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >APP_RAM

  /* User_heap_stack section, used to check that there is enough "OS_RAM" memory left */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = ALIGN(8);
  } >APP_RAM

  /* Uninitialized data section into "SH0_RAM" shared memory */
  .sh0_ram :
  {
  	. = ALIGN(4);
  	*(.sh0_ram)
  	. = ALIGN(4);
  } >SH0_RAM
  
  /* Uninitialized data section into "SH1_RAM" shared memory */
  .sh1_ram :
  {
  	. = ALIGN(4);
  	*(.sh1_ram)
  	. = ALIGN(4);
  } >SH1_RAM 
  
  /* Remove information from the compiler libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
