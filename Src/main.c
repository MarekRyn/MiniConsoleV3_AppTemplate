/*****************************************************************
 * MiniConsole V3 - Application Template
 *
 * Author: Marek Ryn
 * Version: 0.1b
 *
 * Changelog:
 *
 * - 0.1b	- Development version
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
	BSP->SetHomeDir("0:/Game00/");

	// Initializing graphical interface
	BSP->LCD_Init(LCD_COLOR_MODE_RGB888, LCD_BUFFER_MODE_TRIPLE, BSP->G2D_Color(C_BLACK, 255), NULL);

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
		BSP->G2D_DrawBitmapC((uint32_t)RES_THUMB, 400, 240, 320, 200);
		BSP->LCD_FrameReady();

		// Routines in this section will be executed once per frame
		frametime = BSP->LCD_GetFrameTime();
	}
}
