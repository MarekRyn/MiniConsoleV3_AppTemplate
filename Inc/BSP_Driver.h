/*
 * BSP_Driver.h
 *
 *  Created on: May 29, 2024
 *      Author: marek
 */

#ifndef BSP_DRIVER_H_
#define BSP_DRIVER_H_

#define NULL ((void *)0)

#include <stdint.h>

// Driver constants
#define BSP_DRIVER	__attribute__((section(".dtc_mram")))

#define BSP_OK		0
#define BSP_ERROR	1
#define BSP_BUSY	2
#define BSP_TIMEOUT	3
#define BSP_SUSPEND	4

// BSP structures - LCD

// Screen size
#define LCD_WIDTH	800
#define LCD_HEIGHT	480

// Mode definitions
#define LCD_COLOR_MODE_ARGB8888			6
#define LCD_COLOR_MODE_ARGB4444			5
#define LCD_COLOR_MODE_ARGB1555			4
#define LCD_COLOR_MODE_RGB888			3
#define LCD_COLOR_MODE_AL88				2
#define LCD_COLOR_MODE_L8				1

#define LCD_BUFFER_MODE_DOUBLE		2
#define LCD_BUFFER_MODE_TRIPLE		3

// Color Definitions - Valid only for ARGB and RGB modes
#define C_BLUE          0x0000FF
#define C_GREEN         0x00FF00
#define C_RED           0xFF0000
#define C_CYAN          0x00FFFF
#define C_MAGENTA       0xFF00FF
#define C_YELLOW        0xFFFF00
#define C_LIGHTBLUE     0x8080FF
#define C_LIGHTGREEN    0x80FF80
#define C_LIGHTRED      0xFF8080
#define C_LIGHTCYAN     0x80FFFF
#define C_LIGHTMAGENTA  0xFF80FF
#define C_LIGHTYELLOW   0xFFFF80
#define C_DARKBLUE      0x000080
#define C_DARKGREEN     0x008000
#define C_DARKRED       0x800000
#define C_DARKCYAN      0x008080
#define C_DARKMAGENTA   0x800080
#define C_DARKYELLOW    0x808000
#define C_WHITE         0xFFFFFF
#define C_LIGHTGRAY     0xD3D3D3
#define C_GRAY          0x808080
#define C_DARKGRAY      0x404040
#define C_BLACK         0x000000
#define C_BROWN         0xA52A2A
#define C_ORANGE        0xFFA500




// BSP structures - LCD Touch Panel

#define LCD_TP_GEST_NONE			0x00
#define LCD_TP_GEST_CLICK_DOWN		0x01
#define LCD_TP_GEST_CLICK_UP		0x02
#define LCD_TP_GEST_SWIPE_UP		0x04
#define LCD_TP_GEST_SWIPE_DOWN		0x08
#define LCD_TP_GEST_SWIPE_LEFT		0x10
#define LCD_TP_GEST_SWIPE_RIGHT		0x20
#define LCD_TP_GEST_DRAG			0x40
#define LCD_TP_GEST_ZOOM			0x80

#define LCD_TP_REG_TOTAL_LENGTH		0x1F					// Total length of registers in bytes
#define LCD_TP_DATA_NO				5
#define LCD_TP_AREA_NO				32

typedef struct {
	uint16_t	x;
	uint16_t	y;
	uint8_t		status;
	uint8_t		pstatus;
	uint8_t		id;
} TP_DATA;

typedef struct {
	int16_t		x;
	int16_t		y;
	uint16_t	w;
	uint16_t	h;
	void *		callback;
	uint8_t		active;
} TP_AREA;

typedef struct {
	uint8_t		area;
	uint32_t	gest;
	uint16_t	start_x;
	uint16_t	start_y;
	uint32_t	start_t;
	uint16_t	stop_x;
	uint16_t	stop_y;
	uint32_t	stop_t;
	int16_t		delta_x;
	int16_t		delta_y;
	uint32_t	delta_t;
	float		speed_x;
	float		speed_y;
} TP_GEST;

typedef struct {
	uint8_t		raw_data[LCD_TP_REG_TOTAL_LENGTH];
	uint8_t		touch_count;
	TP_DATA		touch_data[LCD_TP_DATA_NO];
	TP_AREA		touch_areas[LCD_TP_AREA_NO];
	TP_GEST		gest_data;
} LCD_TP_HandleTypeDef;


// BSP structures - IMU IC

typedef struct _IMU_DATA {
	float		ox;		// deg/s around X axis
	float		oy;		// deg/s around Y axis
	float		oz;		// deg/s around Z axis
	float		x;		// g acceleration along X axis
	float		y;		// g acceleration along Y axis
	float		z;		// g acceleration along Z axis
	float		t;		// temperature in C deg
} IMU_DATA;

typedef struct _IMU_POS {
	float		pitch;		// device angle around X axis
	float		roll;		// device angle around Y axis
	float		yaw;		// device angle around Z axis
} IMU_POS;

typedef struct _IMU_CAL {
	int32_t		c_ox;
	int32_t		c_oy;
	int32_t		c_oz;
	int32_t		c_x;
	int32_t		c_y;
	int32_t		c_z;
	uint32_t	progress;
	uint32_t	sampleno;
} IMU_CAL;

typedef struct _IMU {
	uint8_t			raw_data[14];
	IMU_CAL			cal;
	IMU_DATA		data;
	IMU_POS			pos;
	uint32_t		timestamp;
} IMU_HandleTypeDef;

// BSP structures - Inputs (Buttons and Joystick)

typedef struct _INPUTS_JOY_CAL {
	uint16_t		x_center_min;
	uint16_t		x_center_max;
	uint16_t		y_center_min;
	uint16_t		y_center_max;
	uint16_t		x_min;
	uint16_t		x_max;
	uint16_t		y_min;
	uint16_t		y_max;
} INPUTS_JOY_CAL;

typedef struct _INPUTS_JOY {
	int16_t			joy_X;		// range from -512 to +512 (0 means center)
	int16_t			joy_Y;		// range from -512 to +512 (0 means center)
} INPUTS_JOY;

typedef struct _INPUTS_BTNS {
	uint8_t			btn_A;
	uint8_t			btn_B;
	uint8_t			btn_C;
	uint8_t			btn_D;
	uint8_t			btn_X_U;
	uint8_t			btn_X_D;
	uint8_t			btn_X_L;
	uint8_t			btn_X_R;
	uint8_t			btn_JOY;
	uint8_t			btn_MENU;
	uint8_t			btn_PWR;
} INPUTS_BTNS;

typedef struct _INPUTS {
	uint16_t		raw_data_joy[2];
	INPUTS_JOY_CAL	joy_cal;
	INPUTS_JOY		joy;
	INPUTS_BTNS		buttons;
	uint8_t			mode;
	uint32_t		timestamp;
} INPUTS_HandleTypeDef;


// BSP structures - Audio

enum AUDIO_STATUS {
	AUDIO_STATUS_NONE,
	AUDIO_STATUS_READY,
	AUDIO_STATUS_BUF_UNDERRUN,
	AUDIO_STATUS_CH_REPEAT,
	AUDIO_STATUS_CH_STOP,
	AUDIO_STATUS_COUNT				// Not a real status, just counter how many status values are defined
};



/*********************************************************/
/* DRIVER API                                            */
/*********************************************************/

typedef struct {

	// Placeholder for app init and main
	/* 0000 */		uint32_t *	reserved0000;
	/* 0001 */		uint32_t *	reserved0001;
	/* 0002 */		uint32_t *	reserved0002;
	/* 0003 */		uint32_t *	reserved0003;
	/* 0004 */		uint32_t *	reserved0004;
	/* 0005 */		uint32_t *	reserved0005;
	/* 0006 */		uint32_t *	reserved0006;
	/* 0007 */		uint32_t *	reserved0007;

	// BSP Structures for accessing various data
	/* 0008 */		LCD_TP_HandleTypeDef * hlcdtp;
	/* 0009 */		IMU_HandleTypeDef *	himu;
	/* 0010 */		INPUTS_HandleTypeDef * hinputs;
	/* 0011 */		uint32_t *	reserved0011;
	/* 0012 */		uint32_t *	reserved0012;
	/* 0013 */		uint32_t *	reserved0013;
	/* 0014 */		uint32_t *	reserved0014;
	/* 0015 */		uint32_t *	reserved0015;

	// System functions
	/* 0016 */		uint8_t (* PWR_Restart)(void);
	/* 0017 */		uint8_t (* PWR_ShutDown)(void);
	/* 0018 */		void (* Delay)(uint32_t delay);
	/* 0019 */		uint32_t (* GetTick)(void);
	/* 0020 */		uint8_t (* SetHomeDir)(char * homeDir);
	/* 0021 */		uint8_t (* RTC_GetDate)(uint16_t * pyear, uint8_t * pmonth, uint8_t * pday, uint8_t * pweekday);
	/* 0022 */		uint8_t (* RTC_GetTime)(uint8_t * phour, uint8_t * pminute, uint8_t * psecond);
	/* 0023 */		int32_t (* RTC_GetUnixTimestamp)(void);
	/* 0024 */		uint32_t *	reserved0024;
	/* 0025 */		uint32_t *	reserved0025;
	/* 0026 */		uint32_t *	reserved0026;
	/* 0027 */		uint32_t *	reserved0027;
	/* 0028 */		uint32_t *	reserved0028;
	/* 0029 */		uint32_t *	reserved0029;
	/* 0030 */		uint32_t *	reserved0030;
	/* 0031 */		uint32_t *	reserved0031;

	// LCD & Touch Panel Library
	/* 0032 */		void (* LCD_Init)(uint8_t color_mode, uint8_t buffer_mode, uint32_t bgcolor, uint32_t *clut);
	/* 0033 */		void (* LCD_FrameReady)(void);
	/* 0034 */		uint8_t (* LCD_GetEditPermission)(void);
	/* 0035 */		void (* LCD_SetBackLight)(uint8_t value, uint8_t dimspeed);
	/* 0036 */		uint8_t (* LCD_GetBackLight)(void);
	/* 0037 */		void (* LCD_BacklLightOff)(void);
	/* 0038 */		void (* LCD_BackLightOn)(void);
	/* 0039 */		uint32_t (* LCD_GetFrameTime)(void);
	/* 0040 */		uint32_t *	reserved0040;
	/* 0041 */		uint32_t *	reserved0041;
	/* 0042 */		uint32_t *	reserved0042;
	/* 0043 */		uint32_t *	reserved0043;
	/* 0044 */		uint32_t *	reserved0044;
	/* 0045 */		uint32_t *	reserved0045;
	/* 0046 */		uint32_t *	reserved0046;
	/* 0047 */		uint32_t *	reserved0047;
	/* 0048 */		uint32_t *	reserved0048;
	/* 0049 */		uint32_t *	reserved0049;
	/* 0050 */		uint32_t *	reserved0050;
	/* 0051 */		uint32_t *	reserved0051;
	/* 0052 */		uint32_t *	reserved0052;
	/* 0053 */		uint32_t *	reserved0053;
	/* 0054 */		uint32_t *	reserved0054;
	/* 0055 */		uint32_t *	reserved0055;
	/* 0056 */		uint32_t *	reserved0056;
	/* 0057 */		uint32_t *	reserved0057;
	/* 0058 */		uint32_t *	reserved0058;
	/* 0059 */		uint32_t *	reserved0059;
	/* 0060 */		uint32_t *	reserved0060;
	/* 0061 */		uint32_t *	reserved0061;
	/* 0062 */		uint32_t *	reserved0062;
	/* 0063 */		uint32_t *	reserved0063;
	/* 0064 */		uint32_t *	reserved0064;
	/* 0065 */		uint32_t *	reserved0065;
	/* 0066 */		uint32_t *	reserved0066;
	/* 0067 */		uint32_t *	reserved0067;
	/* 0068 */		uint32_t *	reserved0068;
	/* 0069 */		uint32_t *	reserved0069;
	/* 0070 */		uint32_t *	reserved0070;
	/* 0071 */		uint32_t *	reserved0071;
	/* 0072 */		uint32_t *	reserved0072;
	/* 0073 */		uint32_t *	reserved0073;
	/* 0074 */		uint32_t *	reserved0074;
	/* 0075 */		uint32_t *	reserved0075;
	/* 0076 */		uint32_t *	reserved0076;
	/* 0077 */		uint32_t *	reserved0077;
	/* 0078 */		uint32_t *	reserved0078;
	/* 0079 */		uint32_t *	reserved0079;
	/* 0080 */		uint32_t *	reserved0080;
	/* 0081 */		uint32_t *	reserved0081;
	/* 0082 */		uint32_t *	reserved0082;
	/* 0083 */		uint32_t *	reserved0083;
	/* 0084 */		uint32_t *	reserved0084;
	/* 0085 */		uint32_t *	reserved0085;
	/* 0086 */		uint32_t *	reserved0086;
	/* 0087 */		uint32_t *	reserved0087;
	/* 0088 */		uint32_t *	reserved0088;
	/* 0089 */		uint32_t *	reserved0089;
	/* 0090 */		uint32_t *	reserved0090;
	/* 0091 */		uint32_t *	reserved0091;
	/* 0092 */		uint32_t *	reserved0092;
	/* 0093 */		uint32_t *	reserved0093;
	/* 0094 */		uint32_t *	reserved0094;
	/* 0095 */		uint32_t *	reserved0095;
	/* 0096 */		uint32_t *	reserved0096;
	/* 0097 */		uint32_t *	reserved0097;
	/* 0098 */		uint32_t *	reserved0098;
	/* 0099 */		uint32_t *	reserved0099;
	/* 0100 */		uint32_t *	reserved0100;
	/* 0101 */		uint32_t *	reserved0101;
	/* 0102 */		uint32_t *	reserved0102;
	/* 0103 */		uint32_t *	reserved0103;
	/* 0104 */		uint32_t *	reserved0104;
	/* 0105 */		uint32_t *	reserved0105;
	/* 0106 */		uint32_t *	reserved0106;
	/* 0107 */		uint32_t *	reserved0107;
	/* 0108 */		uint32_t *	reserved0108;
	/* 0109 */		uint32_t *	reserved0109;
	/* 0110 */		uint32_t *	reserved0110;
	/* 0111 */		uint32_t *	reserved0111;
	/* 0112 */		uint32_t *	reserved0112;
	/* 0113 */		uint32_t *	reserved0113;
	/* 0114 */		uint32_t *	reserved0114;
	/* 0115 */		uint32_t *	reserved0115;
	/* 0116 */		uint32_t *	reserved0116;
	/* 0117 */		uint32_t *	reserved0117;
	/* 0118 */		uint32_t *	reserved0118;
	/* 0119 */		uint32_t *	reserved0119;
	/* 0120 */		uint32_t *	reserved0120;
	/* 0121 */		uint32_t *	reserved0121;
	/* 0122 */		uint32_t *	reserved0122;
	/* 0123 */		uint32_t *	reserved0123;
	/* 0124 */		uint32_t *	reserved0124;
	/* 0125 */		uint32_t *	reserved0125;
	/* 0126 */		uint32_t *	reserved0126;
	/* 0127 */		uint32_t *	reserved0127;

	// G2D Library
	/* 0128 */		void (* G2D_ClearFrame)(void);
	/* 0129 */		void (* G2D_FillFrame)(uint32_t color);
	/* 0130 */		void (* G2D_CopyPrevFrame)(void);
	/* 0131 */		void (* G2D_CopyScrollPrevFrame)(int16_t dx, int16_t dy);
	/* 0132 */		void (* G2D_DrawPixel)(int16_t x, int16_t y, uint32_t color);
	/* 0133 */		void (* G2D_DrawHLine)(int16_t x, int16_t y, int16_t length, uint32_t color);
	/* 0134 */		void (* G2D_DrawHLineBlend)(int16_t x, int16_t y, int16_t length, uint32_t color);
	/* 0135 */		void (* G2D_DrawVLine)(int16_t x, int16_t y, int16_t length, uint32_t color);
	/* 0136 */		void (* G2D_DrawVLineBlend)(int16_t x, int16_t y, int16_t length, uint32_t color);
	/* 0137 */		void (* G2D_DrawLine)(int16_t X1, int16_t Y1, int16_t X2, int16_t Y2, uint32_t color);
	/* 0138 */		void (* G2D_DrawRect)(int16_t x, int16_t y, uint16_t width, uint16_t height, uint32_t color);
	/* 0139 */		void (* G2D_DrawFillRect)(int16_t x, int16_t y, uint16_t width, uint16_t height, uint32_t color);
	/* 0140 */		void (* G2D_DrawFillRectBlend)(int16_t x, int16_t y, uint16_t width, uint16_t height, uint32_t color);
	/* 0141 */		void (* G2D_DrawCircle)(int16_t x, int16_t y, uint16_t r, uint32_t color);
	/* 0142 */		void (* G2D_DrawFillCircle)(int16_t x, int16_t y, uint16_t r, uint32_t color);
	/* 0143 */		void (* G2D_DrawFillCircleBlend)(int16_t x, int16_t y, uint16_t r, uint32_t color);
	/* 0144 */		void (* G2D_DrawRoundRect)(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t radius, uint32_t color);
	/* 0145 */		void (* G2D_DrawFillRoundRect)(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t radius, uint32_t color);
	/* 0146 */		void (* G2D_DrawFillRoundRectBlend)(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t radius, uint32_t color);
	/* 0147 */		uint16_t (* G2D_Text)(int16_t x, int16_t y, const uint8_t *font, char *str, uint32_t color, uint32_t bgcolor);
	/* 0148 */		uint16_t (* G2D_TextBlend)(int16_t x, int16_t y, const uint8_t *font, char *str, uint32_t color);
	/* 0149 */		uint8_t (* G2D_GetTextHeight)(const uint8_t *font);
	/* 0150 */		void (* G2D_DrawBitmapBlend)(uint32_t sourcedata, int16_t x, int16_t y, int16_t width, int16_t height, uint8_t alpha);
	/* 0151 */		void (* G2D_DrawBitmapBlendC)(uint32_t sourcedata, int16_t x, int16_t y, int16_t width, int16_t height, uint8_t alpha);
	/* 0152 */		void (* G2D_DrawBitmap)(uint32_t sourcedata, int16_t x, int16_t y, int16_t width, int16_t height);
	/* 0153 */		void (* G2D_DrawBitmapC)(uint32_t sourcedata, int16_t x, int16_t y, int16_t width, int16_t height);
	/* 0154 */		void (* G2D_DrawBitmapRotate)(uint32_t sourcedata, int16_t x, int16_t y, int16_t width, int16_t height, float angle);
	/* 0155 */		void (* G2D_DrawBitmapRotateC)(uint32_t sourcedata, int16_t x, int16_t y, int16_t width, int16_t height, float angle);
	/* 0156 */		void (* G2D_DrawIcon)(uint32_t iconsource, int16_t x, int16_t y, uint32_t color, uint32_t bgcolor);
	/* 0157 */		void (* G2D_DrawIconC)(uint32_t iconsource, int16_t x, int16_t y, uint32_t color, uint32_t bgcolor);
	/* 0158 */		void (* G2D_DrawIconBlend)(uint32_t iconsource, int16_t x, int16_t y, uint32_t color);
	/* 0159 */		void (* G2D_DrawIconBlendC)(uint32_t iconsource, int16_t x, int16_t y, uint32_t color);
	/* 0160 */		uint16_t (* G2D_GetIconHeight)(uint32_t iconsource);
	/* 0161 */		uint16_t (* G2D_GetIconWidth)(uint32_t iconsource);
	/* 0162 */		void (* G2D_DrawJPEG)(uint32_t jpeg_addr, uint32_t jpeg_size, int16_t x, int16_t y);
	/* 0163 */		void (* G2D_DrawJPEGC)(uint32_t jpeg_addr, uint32_t jpeg_size, int16_t x, int16_t y);
	/* 0164 */		void (* G2D_DrawLastJPEG)(int16_t x, int16_t y);
	/* 0165 */		void (* G2D_DrawLastJPEGC)(int16_t x, int16_t y);
	/* 0166 */		void (* G2D_DecodeJPEG)(uint32_t jpeg_addr, uint32_t jpeg_size);
	/* 0167 */		void (* G2D_DrawTile)(uint32_t tileset_addr, uint32_t tileset_cols, uint32_t tile_width, uint32_t tile_height, uint32_t tile_col, uint32_t tile_row, int16_t x, int16_t y);
	/* 0168 */		void (* G2D_DrawTileC)(uint32_t tileset_addr, uint32_t tileset_cols, uint32_t tile_width, uint32_t tile_height, uint32_t tile_col, uint32_t tile_row, int16_t x, int16_t y);
	/* 0169 */		void (* G2D_DrawTileBlend)(uint32_t tileset_addr, uint32_t tileset_cols, uint32_t tile_width, uint32_t tile_height, uint32_t tile_col, uint32_t tile_row, int16_t x, int16_t y);
	/* 0170 */		void (* G2D_DrawTileBlendC)(uint32_t tileset_addr, uint32_t tileset_cols, uint32_t tile_width, uint32_t tile_height, uint32_t tile_col, uint32_t tile_row, int16_t x, int16_t y);
	/* 0171 */		uint32_t (* G2D_Color)(uint32_t color, uint8_t alpha);
	/* 0172 */		uint32_t (* G2D_Alpha)(uint32_t color, uint8_t alpha);
	/* 0173 */		void (* G2D_CopyBuf)(uint32_t src_addr, uint16_t offsline_src, uint16_t x_dest, uint16_t y_dest, uint16_t width, uint16_t height);
	/* 0174 */		void (* G2D_CopyBufBlend)(uint32_t src_addr, uint16_t offsline_src, uint16_t x_dest, uint16_t y_dest, uint16_t width, uint16_t height, uint8_t alpha);
	/* 0175 */		void (* G2D_CacheFrame)(void);
	/* 0176 */		void (* G2D_RestoreFrame)(void);
	/* 0177 */		uint32_t *	reserved0177;
	/* 0178 */		uint32_t *	reserved0178;
	/* 0179 */		uint32_t *	reserved0179;
	/* 0180 */		uint32_t *	reserved0180;
	/* 0181 */		uint32_t *	reserved0181;
	/* 0182 */		uint32_t *	reserved0182;
	/* 0183 */		uint32_t *	reserved0183;
	/* 0184 */		uint32_t *	reserved0184;
	/* 0185 */		uint32_t *	reserved0185;
	/* 0186 */		uint32_t *	reserved0186;
	/* 0187 */		uint32_t *	reserved0187;
	/* 0188 */		uint32_t *	reserved0188;
	/* 0189 */		uint32_t *	reserved0189;
	/* 0190 */		uint32_t *	reserved0190;
	/* 0191 */		uint32_t *	reserved0191;
	/* 0192 */		uint32_t *	reserved0192;
	/* 0193 */		uint32_t *	reserved0193;
	/* 0194 */		uint32_t *	reserved0194;
	/* 0195 */		uint32_t *	reserved0195;
	/* 0196 */		uint32_t *	reserved0196;
	/* 0197 */		uint32_t *	reserved0197;
	/* 0198 */		uint32_t *	reserved0198;
	/* 0199 */		uint32_t *	reserved0199;
	/* 0200 */		uint32_t *	reserved0200;
	/* 0201 */		uint32_t *	reserved0201;
	/* 0202 */		uint32_t *	reserved0202;
	/* 0203 */		uint32_t *	reserved0203;
	/* 0204 */		uint32_t *	reserved0204;
	/* 0205 */		uint32_t *	reserved0205;
	/* 0206 */		uint32_t *	reserved0206;
	/* 0207 */		uint32_t *	reserved0207;
	/* 0208 */		uint32_t *	reserved0208;
	/* 0209 */		uint32_t *	reserved0209;
	/* 0210 */		uint32_t *	reserved0210;
	/* 0211 */		uint32_t *	reserved0211;
	/* 0212 */		uint32_t *	reserved0212;
	/* 0213 */		uint32_t *	reserved0213;
	/* 0214 */		uint32_t *	reserved0214;
	/* 0215 */		uint32_t *	reserved0215;
	/* 0216 */		uint32_t *	reserved0216;
	/* 0217 */		uint32_t *	reserved0217;
	/* 0218 */		uint32_t *	reserved0218;
	/* 0219 */		uint32_t *	reserved0219;
	/* 0220 */		uint32_t *	reserved0220;
	/* 0221 */		uint32_t *	reserved0221;
	/* 0222 */		uint32_t *	reserved0222;
	/* 0223 */		uint32_t *	reserved0223;
	/* 0224 */		uint32_t *	reserved0224;
	/* 0225 */		uint32_t *	reserved0225;
	/* 0226 */		uint32_t *	reserved0226;
	/* 0227 */		uint32_t *	reserved0227;
	/* 0228 */		uint32_t *	reserved0228;
	/* 0229 */		uint32_t *	reserved0229;
	/* 0230 */		uint32_t *	reserved0230;
	/* 0231 */		uint32_t *	reserved0231;
	/* 0232 */		uint32_t *	reserved0232;
	/* 0233 */		uint32_t *	reserved0233;
	/* 0234 */		uint32_t *	reserved0234;
	/* 0235 */		uint32_t *	reserved0235;
	/* 0236 */		uint32_t *	reserved0236;
	/* 0237 */		uint32_t *	reserved0237;
	/* 0238 */		uint32_t *	reserved0238;
	/* 0239 */		uint32_t *	reserved0239;
	/* 0240 */		uint32_t *	reserved0240;
	/* 0241 */		uint32_t *	reserved0241;
	/* 0242 */		uint32_t *	reserved0242;
	/* 0243 */		uint32_t *	reserved0243;
	/* 0244 */		uint32_t *	reserved0244;
	/* 0245 */		uint32_t *	reserved0245;
	/* 0246 */		uint32_t *	reserved0246;
	/* 0247 */		uint32_t *	reserved0247;
	/* 0248 */		uint32_t *	reserved0248;
	/* 0249 */		uint32_t *	reserved0249;
	/* 0250 */		uint32_t *	reserved0250;
	/* 0251 */		uint32_t *	reserved0251;
	/* 0252 */		uint32_t *	reserved0252;
	/* 0253 */		uint32_t *	reserved0253;
	/* 0254 */		uint32_t *	reserved0254;
	/* 0255 */		uint32_t *	reserved0255;

	// Audio Library
	/* 0256 */		uint8_t (* Audio_SetMasterVolume)(uint8_t volume);
	/* 0257 */		uint8_t (* Audio_GetMasterVolume)(void);
	/* 0258 */		uint8_t (* Audio_GetMasterVolumeL)(void);
	/* 0259 */		uint8_t (* Audio_GetMasterVolumeR)(void);
	/* 0260 */		uint8_t (* Audio_SetMasterVolumeLR)(uint8_t volume_L, uint8_t volume_R);
	/* 0261 */		uint8_t (* Audio_IncMasterVolume)(uint8_t delta);
	/* 0262 */		uint8_t (* Audio_DecMasterVolume)(uint8_t delta);
	/* 0263 */		uint8_t (* Audio_SetChannelVolume)(uint8_t chno, uint8_t volume);
	/* 0264 */		uint8_t (* Audio_SetChannelVolumeLR)(uint8_t chno, uint8_t volume_L, uint8_t volume_R);
	/* 0265 */		uint8_t (* Audio_IncChannelVolume)(uint8_t chno, uint8_t delta);
	/* 0266 */		uint8_t (* Audio_DecChannelVolume)(uint8_t chno, uint8_t delta);
	/* 0267 */		uint32_t *	reserved0267;
	/* 0268 */		uint8_t (* Audio_LinkSourceMP3)(uint8_t chno, void * addr, uint32_t size);
	/* 0269 */		uint8_t (* Audio_LinkSourceMOD)(uint8_t chno, void * addr, uint32_t size);
	/* 0270 */		uint8_t (* Audio_LinkSourceRAW)(uint8_t chno, void * addr, uint32_t size);
	/* 0271 */		uint8_t (* Audio_ChannelPLay)(uint8_t chno, uint8_t repeat);
	/* 0272 */		uint8_t (* Audio_ChannelStop)(uint8_t chno);
	/* 0273 */		uint8_t (* Audio_ChannelPause)(uint8_t chno);
	/* 0274 */		uint8_t (* Audio_RegisterStatusCallback)(uint8_t status, void* callback);
	/* 0275 */		uint32_t (* Audio_GetStatusParam)(uint8_t index);
	/* 0276 */		uint8_t (* Audio_GetFreeChannel)(void);
	/* 0277 */		uint32_t *	reserved0277;
	/* 0278 */		uint32_t *	reserved0278;
	/* 0279 */		uint32_t *	reserved0279;
	/* 0280 */		uint32_t *	reserved0280;
	/* 0281 */		uint32_t *	reserved0281;
	/* 0282 */		uint32_t *	reserved0282;
	/* 0283 */		uint32_t *	reserved0283;
	/* 0284 */		uint32_t *	reserved0284;
	/* 0285 */		uint32_t *	reserved0285;
	/* 0286 */		uint32_t *	reserved0286;
	/* 0287 */		uint32_t *	reserved0287;
	/* 0288 */		uint32_t *	reserved0288;
	/* 0289 */		uint32_t *	reserved0289;
	/* 0290 */		uint32_t *	reserved0290;
	/* 0291 */		uint32_t *	reserved0291;
	/* 0292 */		uint32_t *	reserved0292;
	/* 0293 */		uint32_t *	reserved0293;
	/* 0294 */		uint32_t *	reserved0294;
	/* 0295 */		uint32_t *	reserved0295;
	/* 0296 */		uint32_t *	reserved0296;
	/* 0297 */		uint32_t *	reserved0297;
	/* 0298 */		uint32_t *	reserved0298;
	/* 0299 */		uint32_t *	reserved0299;
	/* 0300 */		uint32_t *	reserved0300;
	/* 0301 */		uint32_t *	reserved0301;
	/* 0302 */		uint32_t *	reserved0302;
	/* 0303 */		uint32_t *	reserved0303;
	/* 0304 */		uint32_t *	reserved0304;
	/* 0305 */		uint32_t *	reserved0305;
	/* 0306 */		uint32_t *	reserved0306;
	/* 0307 */		uint32_t *	reserved0307;
	/* 0308 */		uint32_t *	reserved0308;
	/* 0309 */		uint32_t *	reserved0309;
	/* 0310 */		uint32_t *	reserved0310;
	/* 0311 */		uint32_t *	reserved0311;
	/* 0312 */		uint32_t *	reserved0312;
	/* 0313 */		uint32_t *	reserved0313;
	/* 0314 */		uint32_t *	reserved0314;
	/* 0315 */		uint32_t *	reserved0315;
	/* 0316 */		uint32_t *	reserved0316;
	/* 0317 */		uint32_t *	reserved0317;
	/* 0318 */		uint32_t *	reserved0318;
	/* 0319 */		uint32_t *	reserved0319;
	/* 0320 */		uint32_t *	reserved0320;
	/* 0321 */		uint32_t *	reserved0321;
	/* 0322 */		uint32_t *	reserved0322;
	/* 0323 */		uint32_t *	reserved0323;
	/* 0324 */		uint32_t *	reserved0324;
	/* 0325 */		uint32_t *	reserved0325;
	/* 0326 */		uint32_t *	reserved0326;
	/* 0327 */		uint32_t *	reserved0327;
	/* 0328 */		uint32_t *	reserved0328;
	/* 0329 */		uint32_t *	reserved0329;
	/* 0330 */		uint32_t *	reserved0330;
	/* 0331 */		uint32_t *	reserved0331;
	/* 0332 */		uint32_t *	reserved0332;
	/* 0333 */		uint32_t *	reserved0333;
	/* 0334 */		uint32_t *	reserved0334;
	/* 0335 */		uint32_t *	reserved0335;
	/* 0336 */		uint32_t *	reserved0336;
	/* 0337 */		uint32_t *	reserved0337;
	/* 0338 */		uint32_t *	reserved0338;
	/* 0339 */		uint32_t *	reserved0339;
	/* 0340 */		uint32_t *	reserved0340;
	/* 0341 */		uint32_t *	reserved0341;
	/* 0342 */		uint32_t *	reserved0342;
	/* 0343 */		uint32_t *	reserved0343;
	/* 0344 */		uint32_t *	reserved0344;
	/* 0345 */		uint32_t *	reserved0345;
	/* 0346 */		uint32_t *	reserved0346;
	/* 0347 */		uint32_t *	reserved0347;
	/* 0348 */		uint32_t *	reserved0348;
	/* 0349 */		uint32_t *	reserved0349;
	/* 0350 */		uint32_t *	reserved0350;
	/* 0351 */		uint32_t *	reserved0351;
	/* 0352 */		uint32_t *	reserved0352;
	/* 0353 */		uint32_t *	reserved0353;
	/* 0354 */		uint32_t *	reserved0354;
	/* 0355 */		uint32_t *	reserved0355;
	/* 0356 */		uint32_t *	reserved0356;
	/* 0357 */		uint32_t *	reserved0357;
	/* 0358 */		uint32_t *	reserved0358;
	/* 0359 */		uint32_t *	reserved0359;
	/* 0360 */		uint32_t *	reserved0360;
	/* 0361 */		uint32_t *	reserved0361;
	/* 0362 */		uint32_t *	reserved0362;
	/* 0363 */		uint32_t *	reserved0363;
	/* 0364 */		uint32_t *	reserved0364;
	/* 0365 */		uint32_t *	reserved0365;
	/* 0366 */		uint32_t *	reserved0366;
	/* 0367 */		uint32_t *	reserved0367;
	/* 0368 */		uint32_t *	reserved0368;
	/* 0369 */		uint32_t *	reserved0369;
	/* 0370 */		uint32_t *	reserved0370;
	/* 0371 */		uint32_t *	reserved0371;
	/* 0372 */		uint32_t *	reserved0372;
	/* 0373 */		uint32_t *	reserved0373;
	/* 0374 */		uint32_t *	reserved0374;
	/* 0375 */		uint32_t *	reserved0375;
	/* 0376 */		uint32_t *	reserved0376;
	/* 0377 */		uint32_t *	reserved0377;
	/* 0378 */		uint32_t *	reserved0378;
	/* 0379 */		uint32_t *	reserved0379;
	/* 0380 */		uint32_t *	reserved0380;
	/* 0381 */		uint32_t *	reserved0381;
	/* 0382 */		uint32_t *	reserved0382;
	/* 0383 */		uint32_t *	reserved0383;

	// Resources
	/* 0384 */		uint8_t (* Res_Init)(void * resAddr, uint32_t resSize);
	/* 0385 */		void* (* Res_Alloc)(uint32_t resSize);
	/* 0386 */		uint8_t (* Res_Free)(void * objAddr);
	/* 0387 */		void* (* Res_Load)(char *filename);
	/* 0388 */		uint32_t (* Res_GetSize)(void * objAddr);
	/* 0389 */		uint32_t *	reserved0389;
	/* 0390 */		uint32_t *	reserved0390;
	/* 0391 */		uint32_t *	reserved0391;
	/* 0392 */		uint32_t *	reserved0392;
	/* 0393 */		uint32_t *	reserved0393;
	/* 0394 */		uint32_t *	reserved0394;
	/* 0395 */		uint32_t *	reserved0395;
	/* 0396 */		uint32_t *	reserved0396;
	/* 0397 */		uint32_t *	reserved0397;
	/* 0398 */		uint32_t *	reserved0398;
	/* 0399 */		uint32_t *	reserved0399;
	/* 0400 */		uint32_t *	reserved0400;
	/* 0401 */		uint32_t *	reserved0401;
	/* 0402 */		uint32_t *	reserved0402;
	/* 0403 */		uint32_t *	reserved0403;
	/* 0404 */		uint32_t *	reserved0404;
	/* 0405 */		uint32_t *	reserved0405;
	/* 0406 */		uint32_t *	reserved0406;
	/* 0407 */		uint32_t *	reserved0407;
	/* 0408 */		uint32_t *	reserved0408;
	/* 0409 */		uint32_t *	reserved0409;
	/* 0410 */		uint32_t *	reserved0410;
	/* 0411 */		uint32_t *	reserved0411;
	/* 0412 */		uint32_t *	reserved0412;
	/* 0413 */		uint32_t *	reserved0413;
	/* 0414 */		uint32_t *	reserved0414;
	/* 0415 */		uint32_t *	reserved0415;
	/* 0416 */		uint32_t *	reserved0416;
	/* 0417 */		uint32_t *	reserved0417;
	/* 0418 */		uint32_t *	reserved0418;
	/* 0419 */		uint32_t *	reserved0419;
	/* 0420 */		uint32_t *	reserved0420;
	/* 0421 */		uint32_t *	reserved0421;
	/* 0422 */		uint32_t *	reserved0422;
	/* 0423 */		uint32_t *	reserved0423;
	/* 0424 */		uint32_t *	reserved0424;
	/* 0425 */		uint32_t *	reserved0425;
	/* 0426 */		uint32_t *	reserved0426;
	/* 0427 */		uint32_t *	reserved0427;
	/* 0428 */		uint32_t *	reserved0428;
	/* 0429 */		uint32_t *	reserved0429;
	/* 0430 */		uint32_t *	reserved0430;
	/* 0431 */		uint32_t *	reserved0431;
	/* 0432 */		uint32_t *	reserved0432;
	/* 0433 */		uint32_t *	reserved0433;
	/* 0434 */		uint32_t *	reserved0434;
	/* 0435 */		uint32_t *	reserved0435;
	/* 0436 */		uint32_t *	reserved0436;
	/* 0437 */		uint32_t *	reserved0437;
	/* 0438 */		uint32_t *	reserved0438;
	/* 0439 */		uint32_t *	reserved0439;
	/* 0440 */		uint32_t *	reserved0440;
	/* 0441 */		uint32_t *	reserved0441;
	/* 0442 */		uint32_t *	reserved0442;
	/* 0443 */		uint32_t *	reserved0443;
	/* 0444 */		uint32_t *	reserved0444;
	/* 0445 */		uint32_t *	reserved0445;
	/* 0446 */		uint32_t *	reserved0446;
	/* 0447 */		uint32_t *	reserved0447;
	/* 0448 */		uint32_t *	reserved0448;
	/* 0449 */		uint32_t *	reserved0449;
	/* 0450 */		uint32_t *	reserved0450;
	/* 0451 */		uint32_t *	reserved0451;
	/* 0452 */		uint32_t *	reserved0452;
	/* 0453 */		uint32_t *	reserved0453;
	/* 0454 */		uint32_t *	reserved0454;
	/* 0455 */		uint32_t *	reserved0455;
	/* 0456 */		uint32_t *	reserved0456;
	/* 0457 */		uint32_t *	reserved0457;
	/* 0458 */		uint32_t *	reserved0458;
	/* 0459 */		uint32_t *	reserved0459;
	/* 0460 */		uint32_t *	reserved0460;
	/* 0461 */		uint32_t *	reserved0461;
	/* 0462 */		uint32_t *	reserved0462;
	/* 0463 */		uint32_t *	reserved0463;
	/* 0464 */		uint32_t *	reserved0464;
	/* 0465 */		uint32_t *	reserved0465;
	/* 0466 */		uint32_t *	reserved0466;
	/* 0467 */		uint32_t *	reserved0467;
	/* 0468 */		uint32_t *	reserved0468;
	/* 0469 */		uint32_t *	reserved0469;
	/* 0470 */		uint32_t *	reserved0470;
	/* 0471 */		uint32_t *	reserved0471;
	/* 0472 */		uint32_t *	reserved0472;
	/* 0473 */		uint32_t *	reserved0473;
	/* 0474 */		uint32_t *	reserved0474;
	/* 0475 */		uint32_t *	reserved0475;
	/* 0476 */		uint32_t *	reserved0476;
	/* 0477 */		uint32_t *	reserved0477;
	/* 0478 */		uint32_t *	reserved0478;
	/* 0479 */		uint32_t *	reserved0479;
	/* 0480 */		uint32_t *	reserved0480;
	/* 0481 */		uint32_t *	reserved0481;
	/* 0482 */		uint32_t *	reserved0482;
	/* 0483 */		uint32_t *	reserved0483;
	/* 0484 */		uint32_t *	reserved0484;
	/* 0485 */		uint32_t *	reserved0485;
	/* 0486 */		uint32_t *	reserved0486;
	/* 0487 */		uint32_t *	reserved0487;
	/* 0488 */		uint32_t *	reserved0488;
	/* 0489 */		uint32_t *	reserved0489;
	/* 0490 */		uint32_t *	reserved0490;
	/* 0491 */		uint32_t *	reserved0491;
	/* 0492 */		uint32_t *	reserved0492;
	/* 0493 */		uint32_t *	reserved0493;
	/* 0494 */		uint32_t *	reserved0494;
	/* 0495 */		uint32_t *	reserved0495;
	/* 0496 */		uint32_t *	reserved0496;
	/* 0497 */		uint32_t *	reserved0497;
	/* 0498 */		uint32_t *	reserved0498;
	/* 0499 */		uint32_t *	reserved0499;
	/* 0500 */		uint32_t *	reserved0500;
	/* 0501 */		uint32_t *	reserved0501;
	/* 0502 */		uint32_t *	reserved0502;
	/* 0503 */		uint32_t *	reserved0503;
	/* 0504 */		uint32_t *	reserved0504;
	/* 0505 */		uint32_t *	reserved0505;
	/* 0506 */		uint32_t *	reserved0506;
	/* 0507 */		uint32_t *	reserved0507;
	/* 0508 */		uint32_t *	reserved0508;
	/* 0509 */		uint32_t *	reserved0509;
	/* 0510 */		uint32_t *	reserved0510;
	/* 0511 */		uint32_t *	reserved0511;

	// Remaining pointers
	/* 0512 */		uint32_t *	reserved0512;
	/* 0513 */		uint32_t *	reserved0513;
	/* 0514 */		uint32_t *	reserved0514;
	/* 0515 */		uint32_t *	reserved0515;
	/* 0516 */		uint32_t *	reserved0516;
	/* 0517 */		uint32_t *	reserved0517;
	/* 0518 */		uint32_t *	reserved0518;
	/* 0519 */		uint32_t *	reserved0519;

	/* 0520 */		uint32_t *	reserved0520;
	/* 0521 */		uint32_t *	reserved0521;
	/* 0522 */		uint32_t *	reserved0522;
	/* 0523 */		uint32_t *	reserved0523;
	/* 0524 */		uint32_t *	reserved0524;
	/* 0525 */		uint32_t *	reserved0525;
	/* 0526 */		uint32_t *	reserved0526;
	/* 0527 */		uint32_t *	reserved0527;
	/* 0528 */		uint32_t *	reserved0528;
	/* 0529 */		uint32_t *	reserved0529;

	/* 0530 */		uint32_t *	reserved0530;
	/* 0531 */		uint32_t *	reserved0531;
	/* 0532 */		uint32_t *	reserved0532;
	/* 0533 */		uint32_t *	reserved0533;
	/* 0534 */		uint32_t *	reserved0534;
	/* 0535 */		uint32_t *	reserved0535;
	/* 0536 */		uint32_t *	reserved0536;
	/* 0537 */		uint32_t *	reserved0537;
	/* 0538 */		uint32_t *	reserved0538;
	/* 0539 */		uint32_t *	reserved0539;

	/* 0540 */		uint32_t *	reserved0540;
	/* 0541 */		uint32_t *	reserved0541;
	/* 0542 */		uint32_t *	reserved0542;
	/* 0543 */		uint32_t *	reserved0543;
	/* 0544 */		uint32_t *	reserved0544;
	/* 0545 */		uint32_t *	reserved0545;
	/* 0546 */		uint32_t *	reserved0546;
	/* 0547 */		uint32_t *	reserved0547;
	/* 0548 */		uint32_t *	reserved0548;
	/* 0549 */		uint32_t *	reserved0549;

	/* 0550 */		uint32_t *	reserved0550;
	/* 0551 */		uint32_t *	reserved0551;
	/* 0552 */		uint32_t *	reserved0552;
	/* 0553 */		uint32_t *	reserved0553;
	/* 0554 */		uint32_t *	reserved0554;
	/* 0555 */		uint32_t *	reserved0555;
	/* 0556 */		uint32_t *	reserved0556;
	/* 0557 */		uint32_t *	reserved0557;
	/* 0558 */		uint32_t *	reserved0558;
	/* 0559 */		uint32_t *	reserved0559;

	/* 0560 */		uint32_t *	reserved0560;
	/* 0561 */		uint32_t *	reserved0561;
	/* 0562 */		uint32_t *	reserved0562;
	/* 0563 */		uint32_t *	reserved0563;
	/* 0564 */		uint32_t *	reserved0564;
	/* 0565 */		uint32_t *	reserved0565;
	/* 0566 */		uint32_t *	reserved0566;
	/* 0567 */		uint32_t *	reserved0567;
	/* 0568 */		uint32_t *	reserved0568;
	/* 0569 */		uint32_t *	reserved0569;

	/* 0570 */		uint32_t *	reserved0570;
	/* 0571 */		uint32_t *	reserved0571;
	/* 0572 */		uint32_t *	reserved0572;
	/* 0573 */		uint32_t *	reserved0573;
	/* 0574 */		uint32_t *	reserved0574;
	/* 0575 */		uint32_t *	reserved0575;
	/* 0576 */		uint32_t *	reserved0576;
	/* 0577 */		uint32_t *	reserved0577;
	/* 0578 */		uint32_t *	reserved0578;
	/* 0579 */		uint32_t *	reserved0579;

	/* 0580 */		uint32_t *	reserved0580;
	/* 0581 */		uint32_t *	reserved0581;
	/* 0582 */		uint32_t *	reserved0582;
	/* 0583 */		uint32_t *	reserved0583;
	/* 0584 */		uint32_t *	reserved0584;
	/* 0585 */		uint32_t *	reserved0585;
	/* 0586 */		uint32_t *	reserved0586;
	/* 0587 */		uint32_t *	reserved0587;
	/* 0588 */		uint32_t *	reserved0588;
	/* 0589 */		uint32_t *	reserved0589;

	/* 0590 */		uint32_t *	reserved0590;
	/* 0591 */		uint32_t *	reserved0591;
	/* 0592 */		uint32_t *	reserved0592;
	/* 0593 */		uint32_t *	reserved0593;
	/* 0594 */		uint32_t *	reserved0594;
	/* 0595 */		uint32_t *	reserved0595;
	/* 0596 */		uint32_t *	reserved0596;
	/* 0597 */		uint32_t *	reserved0597;
	/* 0598 */		uint32_t *	reserved0598;
	/* 0599 */		uint32_t *	reserved0599;

	/* 0600 */		uint32_t *	reserved0600;
	/* 0601 */		uint32_t *	reserved0601;
	/* 0602 */		uint32_t *	reserved0602;
	/* 0603 */		uint32_t *	reserved0603;
	/* 0604 */		uint32_t *	reserved0604;
	/* 0605 */		uint32_t *	reserved0605;
	/* 0606 */		uint32_t *	reserved0606;
	/* 0607 */		uint32_t *	reserved0607;
	/* 0608 */		uint32_t *	reserved0608;
	/* 0609 */		uint32_t *	reserved0609;

	/* 0610 */		uint32_t *	reserved0610;
	/* 0611 */		uint32_t *	reserved0611;
	/* 0612 */		uint32_t *	reserved0612;
	/* 0613 */		uint32_t *	reserved0613;
	/* 0614 */		uint32_t *	reserved0614;
	/* 0615 */		uint32_t *	reserved0615;
	/* 0616 */		uint32_t *	reserved0616;
	/* 0617 */		uint32_t *	reserved0617;
	/* 0618 */		uint32_t *	reserved0618;
	/* 0619 */		uint32_t *	reserved0619;

	/* 0620 */		uint32_t *	reserved0620;
	/* 0621 */		uint32_t *	reserved0621;
	/* 0622 */		uint32_t *	reserved0622;
	/* 0623 */		uint32_t *	reserved0623;
	/* 0624 */		uint32_t *	reserved0624;
	/* 0625 */		uint32_t *	reserved0625;
	/* 0626 */		uint32_t *	reserved0626;
	/* 0627 */		uint32_t *	reserved0627;
	/* 0628 */		uint32_t *	reserved0628;
	/* 0629 */		uint32_t *	reserved0629;

	/* 0630 */		uint32_t *	reserved0630;
	/* 0631 */		uint32_t *	reserved0631;
	/* 0632 */		uint32_t *	reserved0632;
	/* 0633 */		uint32_t *	reserved0633;
	/* 0634 */		uint32_t *	reserved0634;
	/* 0635 */		uint32_t *	reserved0635;
	/* 0636 */		uint32_t *	reserved0636;
	/* 0637 */		uint32_t *	reserved0637;
	/* 0638 */		uint32_t *	reserved0638;
	/* 0639 */		uint32_t *	reserved0639;

	/* 0640 */		uint32_t *	reserved0640;
	/* 0641 */		uint32_t *	reserved0641;
	/* 0642 */		uint32_t *	reserved0642;
	/* 0643 */		uint32_t *	reserved0643;
	/* 0644 */		uint32_t *	reserved0644;
	/* 0645 */		uint32_t *	reserved0645;
	/* 0646 */		uint32_t *	reserved0646;
	/* 0647 */		uint32_t *	reserved0647;
	/* 0648 */		uint32_t *	reserved0648;
	/* 0649 */		uint32_t *	reserved0649;

	/* 0650 */		uint32_t *	reserved0650;
	/* 0651 */		uint32_t *	reserved0651;
	/* 0652 */		uint32_t *	reserved0652;
	/* 0653 */		uint32_t *	reserved0653;
	/* 0654 */		uint32_t *	reserved0654;
	/* 0655 */		uint32_t *	reserved0655;
	/* 0656 */		uint32_t *	reserved0656;
	/* 0657 */		uint32_t *	reserved0657;
	/* 0658 */		uint32_t *	reserved0658;
	/* 0659 */		uint32_t *	reserved0659;

	/* 0660 */		uint32_t *	reserved0660;
	/* 0661 */		uint32_t *	reserved0661;
	/* 0662 */		uint32_t *	reserved0662;
	/* 0663 */		uint32_t *	reserved0663;
	/* 0664 */		uint32_t *	reserved0664;
	/* 0665 */		uint32_t *	reserved0665;
	/* 0666 */		uint32_t *	reserved0666;
	/* 0667 */		uint32_t *	reserved0667;
	/* 0668 */		uint32_t *	reserved0668;
	/* 0669 */		uint32_t *	reserved0669;

	/* 0670 */		uint32_t *	reserved0670;
	/* 0671 */		uint32_t *	reserved0671;
	/* 0672 */		uint32_t *	reserved0672;
	/* 0673 */		uint32_t *	reserved0673;
	/* 0674 */		uint32_t *	reserved0674;
	/* 0675 */		uint32_t *	reserved0675;
	/* 0676 */		uint32_t *	reserved0676;
	/* 0677 */		uint32_t *	reserved0677;
	/* 0678 */		uint32_t *	reserved0678;
	/* 0679 */		uint32_t *	reserved0679;

	/* 0680 */		uint32_t *	reserved0680;
	/* 0681 */		uint32_t *	reserved0681;
	/* 0682 */		uint32_t *	reserved0682;
	/* 0683 */		uint32_t *	reserved0683;
	/* 0684 */		uint32_t *	reserved0684;
	/* 0685 */		uint32_t *	reserved0685;
	/* 0686 */		uint32_t *	reserved0686;
	/* 0687 */		uint32_t *	reserved0687;
	/* 0688 */		uint32_t *	reserved0688;
	/* 0689 */		uint32_t *	reserved0689;

	/* 0690 */		uint32_t *	reserved0690;
	/* 0691 */		uint32_t *	reserved0691;
	/* 0692 */		uint32_t *	reserved0692;
	/* 0693 */		uint32_t *	reserved0693;
	/* 0694 */		uint32_t *	reserved0694;
	/* 0695 */		uint32_t *	reserved0695;
	/* 0696 */		uint32_t *	reserved0696;
	/* 0697 */		uint32_t *	reserved0697;
	/* 0698 */		uint32_t *	reserved0698;
	/* 0699 */		uint32_t *	reserved0699;

	/* 0700 */		uint32_t *	reserved0700;
	/* 0701 */		uint32_t *	reserved0701;
	/* 0702 */		uint32_t *	reserved0702;
	/* 0703 */		uint32_t *	reserved0703;
	/* 0704 */		uint32_t *	reserved0704;
	/* 0705 */		uint32_t *	reserved0705;
	/* 0706 */		uint32_t *	reserved0706;
	/* 0707 */		uint32_t *	reserved0707;
	/* 0708 */		uint32_t *	reserved0708;
	/* 0709 */		uint32_t *	reserved0709;

	/* 0710 */		uint32_t *	reserved0710;
	/* 0711 */		uint32_t *	reserved0711;
	/* 0712 */		uint32_t *	reserved0712;
	/* 0713 */		uint32_t *	reserved0713;
	/* 0714 */		uint32_t *	reserved0714;
	/* 0715 */		uint32_t *	reserved0715;
	/* 0716 */		uint32_t *	reserved0716;
	/* 0717 */		uint32_t *	reserved0717;
	/* 0718 */		uint32_t *	reserved0718;
	/* 0719 */		uint32_t *	reserved0719;

	/* 0720 */		uint32_t *	reserved0720;
	/* 0721 */		uint32_t *	reserved0721;
	/* 0722 */		uint32_t *	reserved0722;
	/* 0723 */		uint32_t *	reserved0723;
	/* 0724 */		uint32_t *	reserved0724;
	/* 0725 */		uint32_t *	reserved0725;
	/* 0726 */		uint32_t *	reserved0726;
	/* 0727 */		uint32_t *	reserved0727;
	/* 0728 */		uint32_t *	reserved0728;
	/* 0729 */		uint32_t *	reserved0729;

	/* 0730 */		uint32_t *	reserved0730;
	/* 0731 */		uint32_t *	reserved0731;
	/* 0732 */		uint32_t *	reserved0732;
	/* 0733 */		uint32_t *	reserved0733;
	/* 0734 */		uint32_t *	reserved0734;
	/* 0735 */		uint32_t *	reserved0735;
	/* 0736 */		uint32_t *	reserved0736;
	/* 0737 */		uint32_t *	reserved0737;
	/* 0738 */		uint32_t *	reserved0738;
	/* 0739 */		uint32_t *	reserved0739;

	/* 0740 */		uint32_t *	reserved0740;
	/* 0741 */		uint32_t *	reserved0741;
	/* 0742 */		uint32_t *	reserved0742;
	/* 0743 */		uint32_t *	reserved0743;
	/* 0744 */		uint32_t *	reserved0744;
	/* 0745 */		uint32_t *	reserved0745;
	/* 0746 */		uint32_t *	reserved0746;
	/* 0747 */		uint32_t *	reserved0747;
	/* 0748 */		uint32_t *	reserved0748;
	/* 0749 */		uint32_t *	reserved0749;

	/* 0750 */		uint32_t *	reserved0750;
	/* 0751 */		uint32_t *	reserved0751;
	/* 0752 */		uint32_t *	reserved0752;
	/* 0753 */		uint32_t *	reserved0753;
	/* 0754 */		uint32_t *	reserved0754;
	/* 0755 */		uint32_t *	reserved0755;
	/* 0756 */		uint32_t *	reserved0756;
	/* 0757 */		uint32_t *	reserved0757;
	/* 0758 */		uint32_t *	reserved0758;
	/* 0759 */		uint32_t *	reserved0759;

	/* 0760 */		uint32_t *	reserved0760;
	/* 0761 */		uint32_t *	reserved0761;
	/* 0762 */		uint32_t *	reserved0762;
	/* 0763 */		uint32_t *	reserved0763;
	/* 0764 */		uint32_t *	reserved0764;
	/* 0765 */		uint32_t *	reserved0765;
	/* 0766 */		uint32_t *	reserved0766;
	/* 0767 */		uint32_t *	reserved0767;
	/* 0768 */		uint32_t *	reserved0768;
	/* 0769 */		uint32_t *	reserved0769;

	/* 0770 */		uint32_t *	reserved0770;
	/* 0771 */		uint32_t *	reserved0771;
	/* 0772 */		uint32_t *	reserved0772;
	/* 0773 */		uint32_t *	reserved0773;
	/* 0774 */		uint32_t *	reserved0774;
	/* 0775 */		uint32_t *	reserved0775;
	/* 0776 */		uint32_t *	reserved0776;
	/* 0777 */		uint32_t *	reserved0777;
	/* 0778 */		uint32_t *	reserved0778;
	/* 0779 */		uint32_t *	reserved0779;

	/* 0780 */		uint32_t *	reserved0780;
	/* 0781 */		uint32_t *	reserved0781;
	/* 0782 */		uint32_t *	reserved0782;
	/* 0783 */		uint32_t *	reserved0783;
	/* 0784 */		uint32_t *	reserved0784;
	/* 0785 */		uint32_t *	reserved0785;
	/* 0786 */		uint32_t *	reserved0786;
	/* 0787 */		uint32_t *	reserved0787;
	/* 0788 */		uint32_t *	reserved0788;
	/* 0789 */		uint32_t *	reserved0789;

	/* 0790 */		uint32_t *	reserved0790;
	/* 0791 */		uint32_t *	reserved0791;
	/* 0792 */		uint32_t *	reserved0792;
	/* 0793 */		uint32_t *	reserved0793;
	/* 0794 */		uint32_t *	reserved0794;
	/* 0795 */		uint32_t *	reserved0795;
	/* 0796 */		uint32_t *	reserved0796;
	/* 0797 */		uint32_t *	reserved0797;
	/* 0798 */		uint32_t *	reserved0798;
	/* 0799 */		uint32_t *	reserved0799;

	/* 0800 */		uint32_t *	reserved0800;
	/* 0801 */		uint32_t *	reserved0801;
	/* 0802 */		uint32_t *	reserved0802;
	/* 0803 */		uint32_t *	reserved0803;
	/* 0804 */		uint32_t *	reserved0804;
	/* 0805 */		uint32_t *	reserved0805;
	/* 0806 */		uint32_t *	reserved0806;
	/* 0807 */		uint32_t *	reserved0807;
	/* 0808 */		uint32_t *	reserved0808;
	/* 0809 */		uint32_t *	reserved0809;

	/* 0810 */		uint32_t *	reserved0810;
	/* 0811 */		uint32_t *	reserved0811;
	/* 0812 */		uint32_t *	reserved0812;
	/* 0813 */		uint32_t *	reserved0813;
	/* 0814 */		uint32_t *	reserved0814;
	/* 0815 */		uint32_t *	reserved0815;
	/* 0816 */		uint32_t *	reserved0816;
	/* 0817 */		uint32_t *	reserved0817;
	/* 0818 */		uint32_t *	reserved0818;
	/* 0819 */		uint32_t *	reserved0819;

	/* 0820 */		uint32_t *	reserved0820;
	/* 0821 */		uint32_t *	reserved0821;
	/* 0822 */		uint32_t *	reserved0822;
	/* 0823 */		uint32_t *	reserved0823;
	/* 0824 */		uint32_t *	reserved0824;
	/* 0825 */		uint32_t *	reserved0825;
	/* 0826 */		uint32_t *	reserved0826;
	/* 0827 */		uint32_t *	reserved0827;
	/* 0828 */		uint32_t *	reserved0828;
	/* 0829 */		uint32_t *	reserved0829;

	/* 0830 */		uint32_t *	reserved0830;
	/* 0831 */		uint32_t *	reserved0831;
	/* 0832 */		uint32_t *	reserved0832;
	/* 0833 */		uint32_t *	reserved0833;
	/* 0834 */		uint32_t *	reserved0834;
	/* 0835 */		uint32_t *	reserved0835;
	/* 0836 */		uint32_t *	reserved0836;
	/* 0837 */		uint32_t *	reserved0837;
	/* 0838 */		uint32_t *	reserved0838;
	/* 0839 */		uint32_t *	reserved0839;

	/* 0840 */		uint32_t *	reserved0840;
	/* 0841 */		uint32_t *	reserved0841;
	/* 0842 */		uint32_t *	reserved0842;
	/* 0843 */		uint32_t *	reserved0843;
	/* 0844 */		uint32_t *	reserved0844;
	/* 0845 */		uint32_t *	reserved0845;
	/* 0846 */		uint32_t *	reserved0846;
	/* 0847 */		uint32_t *	reserved0847;
	/* 0848 */		uint32_t *	reserved0848;
	/* 0849 */		uint32_t *	reserved0849;

	/* 0850 */		uint32_t *	reserved0850;
	/* 0851 */		uint32_t *	reserved0851;
	/* 0852 */		uint32_t *	reserved0852;
	/* 0853 */		uint32_t *	reserved0853;
	/* 0854 */		uint32_t *	reserved0854;
	/* 0855 */		uint32_t *	reserved0855;
	/* 0856 */		uint32_t *	reserved0856;
	/* 0857 */		uint32_t *	reserved0857;
	/* 0858 */		uint32_t *	reserved0858;
	/* 0859 */		uint32_t *	reserved0859;

	/* 0860 */		uint32_t *	reserved0860;
	/* 0861 */		uint32_t *	reserved0861;
	/* 0862 */		uint32_t *	reserved0862;
	/* 0863 */		uint32_t *	reserved0863;
	/* 0864 */		uint32_t *	reserved0864;
	/* 0865 */		uint32_t *	reserved0865;
	/* 0866 */		uint32_t *	reserved0866;
	/* 0867 */		uint32_t *	reserved0867;
	/* 0868 */		uint32_t *	reserved0868;
	/* 0869 */		uint32_t *	reserved0869;

	/* 0870 */		uint32_t *	reserved0870;
	/* 0871 */		uint32_t *	reserved0871;
	/* 0872 */		uint32_t *	reserved0872;
	/* 0873 */		uint32_t *	reserved0873;
	/* 0874 */		uint32_t *	reserved0874;
	/* 0875 */		uint32_t *	reserved0875;
	/* 0876 */		uint32_t *	reserved0876;
	/* 0877 */		uint32_t *	reserved0877;
	/* 0878 */		uint32_t *	reserved0878;
	/* 0879 */		uint32_t *	reserved0879;

	/* 0880 */		uint32_t *	reserved0880;
	/* 0881 */		uint32_t *	reserved0881;
	/* 0882 */		uint32_t *	reserved0882;
	/* 0883 */		uint32_t *	reserved0883;
	/* 0884 */		uint32_t *	reserved0884;
	/* 0885 */		uint32_t *	reserved0885;
	/* 0886 */		uint32_t *	reserved0886;
	/* 0887 */		uint32_t *	reserved0887;
	/* 0888 */		uint32_t *	reserved0888;
	/* 0889 */		uint32_t *	reserved0889;

	/* 0890 */		uint32_t *	reserved0890;
	/* 0891 */		uint32_t *	reserved0891;
	/* 0892 */		uint32_t *	reserved0892;
	/* 0893 */		uint32_t *	reserved0893;
	/* 0894 */		uint32_t *	reserved0894;
	/* 0895 */		uint32_t *	reserved0895;
	/* 0896 */		uint32_t *	reserved0896;
	/* 0897 */		uint32_t *	reserved0897;
	/* 0898 */		uint32_t *	reserved0898;
	/* 0899 */		uint32_t *	reserved0899;

	/* 0900 */		uint32_t *	reserved0900;
	/* 0901 */		uint32_t *	reserved0901;
	/* 0902 */		uint32_t *	reserved0902;
	/* 0903 */		uint32_t *	reserved0903;
	/* 0904 */		uint32_t *	reserved0904;
	/* 0905 */		uint32_t *	reserved0905;
	/* 0906 */		uint32_t *	reserved0906;
	/* 0907 */		uint32_t *	reserved0907;
	/* 0908 */		uint32_t *	reserved0908;
	/* 0909 */		uint32_t *	reserved0909;

	/* 0910 */		uint32_t *	reserved0910;
	/* 0911 */		uint32_t *	reserved0911;
	/* 0912 */		uint32_t *	reserved0912;
	/* 0913 */		uint32_t *	reserved0913;
	/* 0914 */		uint32_t *	reserved0914;
	/* 0915 */		uint32_t *	reserved0915;
	/* 0916 */		uint32_t *	reserved0916;
	/* 0917 */		uint32_t *	reserved0917;
	/* 0918 */		uint32_t *	reserved0918;
	/* 0919 */		uint32_t *	reserved0919;

	/* 0920 */		uint32_t *	reserved0920;
	/* 0921 */		uint32_t *	reserved0921;
	/* 0922 */		uint32_t *	reserved0922;
	/* 0923 */		uint32_t *	reserved0923;
	/* 0924 */		uint32_t *	reserved0924;
	/* 0925 */		uint32_t *	reserved0925;
	/* 0926 */		uint32_t *	reserved0926;
	/* 0927 */		uint32_t *	reserved0927;
	/* 0928 */		uint32_t *	reserved0928;
	/* 0929 */		uint32_t *	reserved0929;

	/* 0930 */		uint32_t *	reserved0930;
	/* 0931 */		uint32_t *	reserved0931;
	/* 0932 */		uint32_t *	reserved0932;
	/* 0933 */		uint32_t *	reserved0933;
	/* 0934 */		uint32_t *	reserved0934;
	/* 0935 */		uint32_t *	reserved0935;
	/* 0936 */		uint32_t *	reserved0936;
	/* 0937 */		uint32_t *	reserved0937;
	/* 0938 */		uint32_t *	reserved0938;
	/* 0939 */		uint32_t *	reserved0939;

	/* 0940 */		uint32_t *	reserved0940;
	/* 0941 */		uint32_t *	reserved0941;
	/* 0942 */		uint32_t *	reserved0942;
	/* 0943 */		uint32_t *	reserved0943;
	/* 0944 */		uint32_t *	reserved0944;
	/* 0945 */		uint32_t *	reserved0945;
	/* 0946 */		uint32_t *	reserved0946;
	/* 0947 */		uint32_t *	reserved0947;
	/* 0948 */		uint32_t *	reserved0948;
	/* 0949 */		uint32_t *	reserved0949;

	/* 0950 */		uint32_t *	reserved0950;
	/* 0951 */		uint32_t *	reserved0951;
	/* 0952 */		uint32_t *	reserved0952;
	/* 0953 */		uint32_t *	reserved0953;
	/* 0954 */		uint32_t *	reserved0954;
	/* 0955 */		uint32_t *	reserved0955;
	/* 0956 */		uint32_t *	reserved0956;
	/* 0957 */		uint32_t *	reserved0957;
	/* 0958 */		uint32_t *	reserved0958;
	/* 0959 */		uint32_t *	reserved0959;

	/* 0960 */		uint32_t *	reserved0960;
	/* 0961 */		uint32_t *	reserved0961;
	/* 0962 */		uint32_t *	reserved0962;
	/* 0963 */		uint32_t *	reserved0963;
	/* 0964 */		uint32_t *	reserved0964;
	/* 0965 */		uint32_t *	reserved0965;
	/* 0966 */		uint32_t *	reserved0966;
	/* 0967 */		uint32_t *	reserved0967;
	/* 0968 */		uint32_t *	reserved0968;
	/* 0969 */		uint32_t *	reserved0969;

	/* 0970 */		uint32_t *	reserved0970;
	/* 0971 */		uint32_t *	reserved0971;
	/* 0972 */		uint32_t *	reserved0972;
	/* 0973 */		uint32_t *	reserved0973;
	/* 0974 */		uint32_t *	reserved0974;
	/* 0975 */		uint32_t *	reserved0975;
	/* 0976 */		uint32_t *	reserved0976;
	/* 0977 */		uint32_t *	reserved0977;
	/* 0978 */		uint32_t *	reserved0978;
	/* 0979 */		uint32_t *	reserved0979;

	/* 0980 */		uint32_t *	reserved0980;
	/* 0981 */		uint32_t *	reserved0981;
	/* 0982 */		uint32_t *	reserved0982;
	/* 0983 */		uint32_t *	reserved0983;
	/* 0984 */		uint32_t *	reserved0984;
	/* 0985 */		uint32_t *	reserved0985;
	/* 0986 */		uint32_t *	reserved0986;
	/* 0987 */		uint32_t *	reserved0987;
	/* 0988 */		uint32_t *	reserved0988;
	/* 0989 */		uint32_t *	reserved0989;

	/* 0990 */		uint32_t *	reserved0990;
	/* 0991 */		uint32_t *	reserved0991;
	/* 0992 */		uint32_t *	reserved0992;
	/* 0993 */		uint32_t *	reserved0993;
	/* 0994 */		uint32_t *	reserved0994;
	/* 0995 */		uint32_t *	reserved0995;
	/* 0996 */		uint32_t *	reserved0996;
	/* 0997 */		uint32_t *	reserved0997;
	/* 0998 */		uint32_t *	reserved0998;
	/* 0999 */		uint32_t *	reserved0999;

	/* 1000 */		uint32_t *	reserved1000;
	/* 1001 */		uint32_t *	reserved1001;
	/* 1002 */		uint32_t *	reserved1002;
	/* 1003 */		uint32_t *	reserved1003;
	/* 1004 */		uint32_t *	reserved1004;
	/* 1005 */		uint32_t *	reserved1005;
	/* 1006 */		uint32_t *	reserved1006;
	/* 1007 */		uint32_t *	reserved1007;
	/* 1008 */		uint32_t *	reserved1008;
	/* 1009 */		uint32_t *	reserved1009;

	/* 1010 */		uint32_t *	reserved1010;
	/* 1011 */		uint32_t *	reserved1011;
	/* 1012 */		uint32_t *	reserved1012;
	/* 1013 */		uint32_t *	reserved1013;
	/* 1014 */		uint32_t *	reserved1014;
	/* 1015 */		uint32_t *	reserved1015;
	/* 1016 */		uint32_t *	reserved1016;
	/* 1017 */		uint32_t *	reserved1017;
	/* 1018 */		uint32_t *	reserved1018;
	/* 1019 */		uint32_t *	reserved1019;

	/* 1020 */		uint32_t *	reserved1020;
	/* 1021 */		uint32_t *	reserved1021;
	/* 1022 */		uint32_t *	reserved1022;
	/* 1023 */		uint32_t *	reserved1023;

} BSP_Driver_TypeDef;

extern BSP_DRIVER BSP_Driver_TypeDef	BSP;


#endif /* BSP_DRIVER_H_ */
