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

void * music = NULL;

void app_init(void) {
	BSP_LCD_Init(LCD_COLOR_MODE_ARGB8888, LCD_BUFFER_MODE_TRIPLE, G2D_Color(C_BLUE, 255), NULL);

	BSP_Res_Init(0xC0000000, 32*1024*1024);
	music = BSP_Res_Load("alex-productions-efficsounds-energetic-rock-hiking-free-music.mp3");
}

void app_main(void) {

	BSP_Audio_LinkSourceMP3(0, music, BSP_Res_GetSize(music));
	BSP_Audio_SetChannelVolume(0, 128);
	BSP_Audio_ChannelPLay(0, 1);

	while (1) {

		if (BSP_LCD_FrameReady == 0) continue;

		G2D_ClearFrame();
		G2D_DrawFillCircle(100, 100, 50, G2D_Color(C_RED, 255));
		BSP_LCD_FrameReady();

	}
}
