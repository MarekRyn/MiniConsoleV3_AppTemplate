/**
  ******************************************************************************
  * @file      startup_stm32h747xx.s
  ******************************************************************************
  */

  .syntax unified
  .cpu cortex-m7
  .fpu softvfp
  .thumb


  .section  .text.app_entry
  .weak  app_entry
  .type  app_entry, %function

app_entry:

/* Copy the data segment initializers from flash to SRAM */
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  movs r3, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r4, [r2, r3]
  str r4, [r0, r3]
  adds r3, r3, #4

LoopCopyDataInit:
  adds r4, r0, r3
  cmp r4, r1
  bcc CopyDataInit
/* Zero fill the bss segment. */
  ldr r2, =_sbss
  ldr r4, =_ebss
  movs r3, #0
  b LoopFillZerobss

FillZerobss:
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  cmp r2, r4
  bcc FillZerobss


/* Call static constructors */
  PUSH {lr}
  bl __libc_init_array

/* Call the application's entry point.*/
  bl  app_init
  POP {LR}
  bx  lr

  .size  app_entry, .-app_entry


/******************************************************************************
*
* Application configuration section
*
*******************************************************************************/

  .section  .app_config,"a",%progbits
  .type  appConfig, %object
  .size  appConfig, .-appConfig

appConfig:
  .word  app_entry	// application entry (initialization)
  .word	 app_main	// application main
  .space 128		// 128 bytes for additional parameters updated during flashing process (ie home directorey)







