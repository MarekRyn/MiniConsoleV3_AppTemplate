/*****************************************************************
 * MiniConsole V3 - Application Template
 *
 * Author: Marek Ryn
 * Version: 1.0
 *
 * Changelog:
 *
 * - 0.1b	- Development version
 * - 1.0	- First stable release
 *******************************************************************
 * To start new application:
 * 	1) In Project Explorer left click -> copy this project
 * 	2) Paste this project with new name
 * 	3) Open newly created project
 * 	4) Clean project
 * 	5) Delete Debug folder
 * 	6) In Run configuration select new .elf file
 * 	7) In Run configuration -> Debugger add external loader
 * 	8) In Run configuration -> Startup set Specify Vector Table(hex)
 * 		to 0x08000000
 *******************************************************************/


#include "main.h"
#include "fonts.h"

static void * RES_THUMB;
volatile uint32_t frametime;

// Entry point 1 - Initialization function
void app_init(void) {
	// Setting home directory
	// This command is valid only when software is loaded through stlink to easy application development
	// This command is ignored when application is uploaded through bootloader
	BSP->SetHomeDir("0:/Test/");

	// Initializing graphical interface
	BSP->LCD_Init(LCD_COLOR_MODE_RGB888, LCD_BUFFER_MODE_DOUBLE, BSP->G2D_Color(C_BLACK, 255), NULL);

	// Initialize resource memory
	BSP->Res_Init((void *)0xC0000000, 32*1024*1024);

	// Loading resources (thumbnail image)
	RES_THUMB = BSP->Res_Load("thumbnail.bin");
}

// Entry point 2 - Main function
void app_main(void) {

	while (1) {

		// Routines in this section will be executed every time

		while (!BSP->LCD_GetEditPermission()) continue;

		// Generate frame here
		BSP->G2D_ClearFrame();
		BSP->G2D_TextBlend(10, 10, FONT_26_verdana,"EXAMPLE APPLICATION", BSP->G2D_Color(C_WHITE, 255));
		BSP->G2D_DrawBitmapC(RES_THUMB, 400, 240, 320, 200);
		BSP->LCD_FrameReady();

		// Routines in this section will be executed once per frame
		frametime = BSP->LCD_GetFrameTime();

	}
}
