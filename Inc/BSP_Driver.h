/*
 * BSP_Driver.h
 *
 *  Created on: May 29, 2024
 *      Author: marek
 */

#ifndef BSP_DRIVER_H_
#define BSP_DRIVER_H_

#define NULL ((void *)0)


// Driver memory region macro
#define BSP_DRIVER	volatile __attribute__((section(".dtc_mram")))

// BSP structures - LCD

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

// Placeholder for app init and main
/* 0000 */	BSP_DRIVER	uint32_t *	reserved0000;
/* 0001 */	BSP_DRIVER	uint32_t *	reserved0001;
/* 0002 */	BSP_DRIVER	uint32_t *	reserved0002;
/* 0003 */	BSP_DRIVER	uint32_t *	reserved0003;
/* 0004 */	BSP_DRIVER	uint32_t *	reserved0004;
/* 0005 */	BSP_DRIVER	uint32_t *	reserved0005;
/* 0006 */	BSP_DRIVER	uint32_t *	reserved0006;
/* 0007 */	BSP_DRIVER	uint32_t *	reserved0007;

// BSP Structures for accessing various data
/* 0008 */	BSP_DRIVER	LCD_TP_HandleTypeDef *	BSP_hlcdtp;
/* 0009 */	BSP_DRIVER	IMU_HandleTypeDef *	BSP_himu;
/* 0010 */	BSP_DRIVER	INPUTS_HandleTypeDef *	BSP_hinputs;
/* 0011 */	BSP_DRIVER	uint32_t *	reserved0011;
/* 0012 */	BSP_DRIVER	uint32_t *	reserved0012;
/* 0013 */	BSP_DRIVER	uint32_t *	reserved0013;
/* 0014 */	BSP_DRIVER	uint32_t *	reserved0014;
/* 0015 */	BSP_DRIVER	uint32_t *	reserved0015;

// System functions
/* 0016 */	BSP_DRIVER	uint8_t (* BSP_PWR_Restart)(void);
/* 0017 */	BSP_DRIVER	uint8_t (* BSP_PWR_ShutDown)(void);
/* 0018 */	BSP_DRIVER	uint32_t *	reserved0018;
/* 0019 */	BSP_DRIVER	uint32_t *	reserved0019;
/* 0020 */	BSP_DRIVER	uint32_t *	reserved0020;
/* 0021 */	BSP_DRIVER	uint32_t *	reserved0021;
/* 0022 */	BSP_DRIVER	uint32_t *	reserved0022;
/* 0023 */	BSP_DRIVER	uint32_t *	reserved0023;
/* 0024 */	BSP_DRIVER	uint32_t *	reserved0024;
/* 0025 */	BSP_DRIVER	uint32_t *	reserved0025;
/* 0026 */	BSP_DRIVER	uint32_t *	reserved0026;
/* 0027 */	BSP_DRIVER	uint32_t *	reserved0027;
/* 0028 */	BSP_DRIVER	uint32_t *	reserved0028;
/* 0029 */	BSP_DRIVER	uint32_t *	reserved0029;
/* 0030 */	BSP_DRIVER	uint32_t *	reserved0030;
/* 0031 */	BSP_DRIVER	uint32_t *	reserved0031;

// LCD & Touch Panel Library
/* 0032 */	BSP_DRIVER	void (* BSP_LCD_Init)(uint8_t color_mode, uint8_t buffer_mode, uint32_t bgcolor, uint32_t *clut);
/* 0033 */	BSP_DRIVER	void (* BSP_LCD_FrameReady)(void);
/* 0034 */	BSP_DRIVER	uint8_t (* BSP_LCD_GetEditPermission)(void);
/* 0035 */	BSP_DRIVER	void (* BSP_LCD_SetBackLight)(uint8_t value, uint8_t dimspeed);
/* 0036 */	BSP_DRIVER	uint8_t (* BSP_LCD_GetBackLight)(void);
/* 0037 */	BSP_DRIVER	void (* BSP_LCD_BacklLightOff)(void);
/* 0038 */	BSP_DRIVER	void (* BSP_LCD_BackLightOn)(void);
/* 0039 */	BSP_DRIVER	uint32_t (* BSP_LCD_GetFrameTime)(void);
/* 0040 */	BSP_DRIVER	uint32_t *	reserved0040;
/* 0041 */	BSP_DRIVER	uint32_t *	reserved0041;
/* 0042 */	BSP_DRIVER	uint32_t *	reserved0042;
/* 0043 */	BSP_DRIVER	uint32_t *	reserved0043;
/* 0044 */	BSP_DRIVER	uint32_t *	reserved0044;
/* 0045 */	BSP_DRIVER	uint32_t *	reserved0045;
/* 0046 */	BSP_DRIVER	uint32_t *	reserved0046;
/* 0047 */	BSP_DRIVER	uint32_t *	reserved0047;
/* 0048 */	BSP_DRIVER	uint32_t *	reserved0048;
/* 0049 */	BSP_DRIVER	uint32_t *	reserved0049;
/* 0050 */	BSP_DRIVER	uint32_t *	reserved0050;
/* 0051 */	BSP_DRIVER	uint32_t *	reserved0051;
/* 0052 */	BSP_DRIVER	uint32_t *	reserved0052;
/* 0053 */	BSP_DRIVER	uint32_t *	reserved0053;
/* 0054 */	BSP_DRIVER	uint32_t *	reserved0054;
/* 0055 */	BSP_DRIVER	uint32_t *	reserved0055;
/* 0056 */	BSP_DRIVER	uint32_t *	reserved0056;
/* 0057 */	BSP_DRIVER	uint32_t *	reserved0057;
/* 0058 */	BSP_DRIVER	uint32_t *	reserved0058;
/* 0059 */	BSP_DRIVER	uint32_t *	reserved0059;
/* 0060 */	BSP_DRIVER	uint32_t *	reserved0060;
/* 0061 */	BSP_DRIVER	uint32_t *	reserved0061;
/* 0062 */	BSP_DRIVER	uint32_t *	reserved0062;
/* 0063 */	BSP_DRIVER	uint32_t *	reserved0063;
/* 0064 */	BSP_DRIVER	uint32_t *	reserved0064;
/* 0065 */	BSP_DRIVER	uint32_t *	reserved0065;
/* 0066 */	BSP_DRIVER	uint32_t *	reserved0066;
/* 0067 */	BSP_DRIVER	uint32_t *	reserved0067;
/* 0068 */	BSP_DRIVER	uint32_t *	reserved0068;
/* 0069 */	BSP_DRIVER	uint32_t *	reserved0069;
/* 0070 */	BSP_DRIVER	uint32_t *	reserved0070;
/* 0071 */	BSP_DRIVER	uint32_t *	reserved0071;
/* 0072 */	BSP_DRIVER	uint32_t *	reserved0072;
/* 0073 */	BSP_DRIVER	uint32_t *	reserved0073;
/* 0074 */	BSP_DRIVER	uint32_t *	reserved0074;
/* 0075 */	BSP_DRIVER	uint32_t *	reserved0075;
/* 0076 */	BSP_DRIVER	uint32_t *	reserved0076;
/* 0077 */	BSP_DRIVER	uint32_t *	reserved0077;
/* 0078 */	BSP_DRIVER	uint32_t *	reserved0078;
/* 0079 */	BSP_DRIVER	uint32_t *	reserved0079;
/* 0080 */	BSP_DRIVER	uint32_t *	reserved0080;
/* 0081 */	BSP_DRIVER	uint32_t *	reserved0081;
/* 0082 */	BSP_DRIVER	uint32_t *	reserved0082;
/* 0083 */	BSP_DRIVER	uint32_t *	reserved0083;
/* 0084 */	BSP_DRIVER	uint32_t *	reserved0084;
/* 0085 */	BSP_DRIVER	uint32_t *	reserved0085;
/* 0086 */	BSP_DRIVER	uint32_t *	reserved0086;
/* 0087 */	BSP_DRIVER	uint32_t *	reserved0087;
/* 0088 */	BSP_DRIVER	uint32_t *	reserved0088;
/* 0089 */	BSP_DRIVER	uint32_t *	reserved0089;
/* 0090 */	BSP_DRIVER	uint32_t *	reserved0090;
/* 0091 */	BSP_DRIVER	uint32_t *	reserved0091;
/* 0092 */	BSP_DRIVER	uint32_t *	reserved0092;
/* 0093 */	BSP_DRIVER	uint32_t *	reserved0093;
/* 0094 */	BSP_DRIVER	uint32_t *	reserved0094;
/* 0095 */	BSP_DRIVER	uint32_t *	reserved0095;
/* 0096 */	BSP_DRIVER	uint32_t *	reserved0096;
/* 0097 */	BSP_DRIVER	uint32_t *	reserved0097;
/* 0098 */	BSP_DRIVER	uint32_t *	reserved0098;
/* 0099 */	BSP_DRIVER	uint32_t *	reserved0099;
/* 0100 */	BSP_DRIVER	uint32_t *	reserved0100;
/* 0101 */	BSP_DRIVER	uint32_t *	reserved0101;
/* 0102 */	BSP_DRIVER	uint32_t *	reserved0102;
/* 0103 */	BSP_DRIVER	uint32_t *	reserved0103;
/* 0104 */	BSP_DRIVER	uint32_t *	reserved0104;
/* 0105 */	BSP_DRIVER	uint32_t *	reserved0105;
/* 0106 */	BSP_DRIVER	uint32_t *	reserved0106;
/* 0107 */	BSP_DRIVER	uint32_t *	reserved0107;
/* 0108 */	BSP_DRIVER	uint32_t *	reserved0108;
/* 0109 */	BSP_DRIVER	uint32_t *	reserved0109;
/* 0110 */	BSP_DRIVER	uint32_t *	reserved0110;
/* 0111 */	BSP_DRIVER	uint32_t *	reserved0111;
/* 0112 */	BSP_DRIVER	uint32_t *	reserved0112;
/* 0113 */	BSP_DRIVER	uint32_t *	reserved0113;
/* 0114 */	BSP_DRIVER	uint32_t *	reserved0114;
/* 0115 */	BSP_DRIVER	uint32_t *	reserved0115;
/* 0116 */	BSP_DRIVER	uint32_t *	reserved0116;
/* 0117 */	BSP_DRIVER	uint32_t *	reserved0117;
/* 0118 */	BSP_DRIVER	uint32_t *	reserved0118;
/* 0119 */	BSP_DRIVER	uint32_t *	reserved0119;
/* 0120 */	BSP_DRIVER	uint32_t *	reserved0120;
/* 0121 */	BSP_DRIVER	uint32_t *	reserved0121;
/* 0122 */	BSP_DRIVER	uint32_t *	reserved0122;
/* 0123 */	BSP_DRIVER	uint32_t *	reserved0123;
/* 0124 */	BSP_DRIVER	uint32_t *	reserved0124;
/* 0125 */	BSP_DRIVER	uint32_t *	reserved0125;
/* 0126 */	BSP_DRIVER	uint32_t *	reserved0126;
/* 0127 */	BSP_DRIVER	uint32_t *	reserved0127;

// G2D Library
/* 0128 */	BSP_DRIVER	void (* G2D_ClearFrame)(void);
/* 0129 */	BSP_DRIVER	void (* G2D_FillFrame)(uint32_t color);
/* 0130 */	BSP_DRIVER	void (* G2D_CopyPrevFrame)(void);
/* 0131 */	BSP_DRIVER	void (* G2D_CopyScrollPrevFrame)(int16_t dx, int16_t dy);
/* 0132 */	BSP_DRIVER	void (* G2D_DrawPixel)(int16_t x, int16_t y, uint32_t color);
/* 0133 */	BSP_DRIVER	void (* G2D_DrawHLine)(int16_t x, int16_t y, int16_t length, uint32_t color);
/* 0134 */	BSP_DRIVER	void (* G2D_DrawHLineBlend)(int16_t x, int16_t y, int16_t length, uint32_t color);
/* 0135 */	BSP_DRIVER	void (* G2D_DrawVLine)(int16_t x, int16_t y, int16_t length, uint32_t color);
/* 0136 */	BSP_DRIVER	void (* G2D_DrawVLineBlend)(int16_t x, int16_t y, int16_t length, uint32_t color);
/* 0137 */	BSP_DRIVER	void (* G2D_DrawLine)(int16_t X1, int16_t Y1, int16_t X2, int16_t Y2, uint32_t color);
/* 0138 */	BSP_DRIVER	void (* G2D_DrawRect)(int16_t x, int16_t y, uint16_t width, uint16_t height, uint32_t color);
/* 0139 */	BSP_DRIVER	void (* G2D_DrawFillRect)(int16_t x, int16_t y, uint16_t width, uint16_t height, uint32_t color);
/* 0140 */	BSP_DRIVER	void (* G2D_DrawFillRectBlend)(int16_t x, int16_t y, uint16_t width, uint16_t height, uint32_t color);
/* 0141 */	BSP_DRIVER	void (* G2D_DrawCircle)(int16_t x, int16_t y, uint16_t r, uint32_t color);
/* 0142 */	BSP_DRIVER	void (* G2D_DrawFillCircle)(int16_t x, int16_t y, uint16_t r, uint32_t color);
/* 0143 */	BSP_DRIVER	void (* G2D_DrawFillCircleBlend)(int16_t x, int16_t y, uint16_t r, uint32_t color);
/* 0144 */	BSP_DRIVER	void (* G2D_DrawRoundRect)(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t radius, uint32_t color);
/* 0145 */	BSP_DRIVER	void (* G2D_DrawFillRoundRect)(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t radius, uint32_t color);
/* 0146 */	BSP_DRIVER	void (* G2D_DrawFillRoundRectBlend)(int16_t x, int16_t y, uint16_t width, uint16_t height, uint16_t radius, uint32_t color);
/* 0147 */	BSP_DRIVER	uint16_t (* G2D_Text)(int16_t x, int16_t y, const uint8_t *font, char *str, uint32_t color, uint32_t bgcolor);
/* 0148 */	BSP_DRIVER	uint16_t (* G2D_TextBlend)(int16_t x, int16_t y, const uint8_t *font, char *str, uint32_t color);
/* 0149 */	BSP_DRIVER	uint8_t (* G2D_GetTextHeight)(const uint8_t *font);
/* 0150 */	BSP_DRIVER	void (* G2D_DrawBitmapBlend)(uint32_t sourcedata, int16_t x, int16_t y, int16_t width, int16_t height, uint8_t alpha);
/* 0151 */	BSP_DRIVER	void (* G2D_DrawBitmapBlendC)(uint32_t sourcedata, int16_t x, int16_t y, int16_t width, int16_t height, uint8_t alpha);
/* 0152 */	BSP_DRIVER	void (* G2D_DrawBitmap)(uint32_t sourcedata, int16_t x, int16_t y, int16_t width, int16_t height);
/* 0153 */	BSP_DRIVER	void (* G2D_DrawBitmapC)(uint32_t sourcedata, int16_t x, int16_t y, int16_t width, int16_t height);
/* 0154 */	BSP_DRIVER	void (* G2D_DrawBitmapRotate)(uint32_t sourcedata, int16_t x, int16_t y, int16_t width, int16_t height, float angle);
/* 0155 */	BSP_DRIVER	void (* G2D_DrawBitmapRotateC)(uint32_t sourcedata, int16_t x, int16_t y, int16_t width, int16_t height, float angle);
/* 0156 */	BSP_DRIVER	void (* G2D_DrawIcon)(uint32_t iconsource, int16_t x, int16_t y, uint32_t color, uint32_t bgcolor);
/* 0157 */	BSP_DRIVER	void (* G2D_DrawIconC)(uint32_t iconsource, int16_t x, int16_t y, uint32_t color, uint32_t bgcolor);
/* 0158 */	BSP_DRIVER	void (* G2D_DrawIconBlend)(uint32_t iconsource, int16_t x, int16_t y, uint32_t color);
/* 0159 */	BSP_DRIVER	void (* G2D_DrawIconBlendC)(uint32_t iconsource, int16_t x, int16_t y, uint32_t color);
/* 0160 */	BSP_DRIVER	uint16_t (* G2D_GetIconHeight)(uint32_t iconsource);
/* 0161 */	BSP_DRIVER	uint16_t (* G2D_GetIconWidth)(uint32_t iconsource);
/* 0162 */	BSP_DRIVER	void (* G2D_DrawJPEG)(uint32_t jpeg_addr, uint32_t jpeg_size, int16_t x, int16_t y);
/* 0163 */	BSP_DRIVER	void (* G2D_DrawJPEGC)(uint32_t jpeg_addr, uint32_t jpeg_size, int16_t x, int16_t y);
/* 0164 */	BSP_DRIVER	void (* G2D_DrawLastJPEG)(int16_t x, int16_t y);
/* 0165 */	BSP_DRIVER	void (* G2D_DrawLastJPEGC)(int16_t x, int16_t y);
/* 0166 */	BSP_DRIVER	void (* G2D_DecodeJPEG)(uint32_t jpeg_addr, uint32_t jpeg_size);
/* 0167 */	BSP_DRIVER	void (* G2D_DrawTile)(uint32_t tileset_addr, uint32_t tileset_cols, uint32_t tile_width, uint32_t tile_height, uint32_t tile_col, uint32_t tile_row, int16_t x, int16_t y);
/* 0168 */	BSP_DRIVER	void (* G2D_DrawTileC)(uint32_t tileset_addr, uint32_t tileset_cols, uint32_t tile_width, uint32_t tile_height, uint32_t tile_col, uint32_t tile_row, int16_t x, int16_t y);
/* 0169 */	BSP_DRIVER	void (* G2D_DrawTileBlend)(uint32_t tileset_addr, uint32_t tileset_cols, uint32_t tile_width, uint32_t tile_height, uint32_t tile_col, uint32_t tile_row, int16_t x, int16_t y);
/* 0170 */	BSP_DRIVER	void (* G2D_DrawTileBlendC)(uint32_t tileset_addr, uint32_t tileset_cols, uint32_t tile_width, uint32_t tile_height, uint32_t tile_col, uint32_t tile_row, int16_t x, int16_t y);
/* 0171 */	BSP_DRIVER	uint32_t (* G2D_Color)(uint32_t color, uint8_t alpha);
/* 0172 */	BSP_DRIVER	uint32_t (* G2D_Alpha)(uint32_t color, uint8_t alpha);
/* 0173 */	BSP_DRIVER	uint32_t *	reserved0173;
/* 0174 */	BSP_DRIVER	uint32_t *	reserved0174;
/* 0175 */	BSP_DRIVER	uint32_t *	reserved0175;
/* 0176 */	BSP_DRIVER	uint32_t *	reserved0176;
/* 0177 */	BSP_DRIVER	uint32_t *	reserved0177;
/* 0178 */	BSP_DRIVER	uint32_t *	reserved0178;
/* 0179 */	BSP_DRIVER	uint32_t *	reserved0179;
/* 0180 */	BSP_DRIVER	uint32_t *	reserved0180;
/* 0181 */	BSP_DRIVER	uint32_t *	reserved0181;
/* 0182 */	BSP_DRIVER	uint32_t *	reserved0182;
/* 0183 */	BSP_DRIVER	uint32_t *	reserved0183;
/* 0184 */	BSP_DRIVER	uint32_t *	reserved0184;
/* 0185 */	BSP_DRIVER	uint32_t *	reserved0185;
/* 0186 */	BSP_DRIVER	uint32_t *	reserved0186;
/* 0187 */	BSP_DRIVER	uint32_t *	reserved0187;
/* 0188 */	BSP_DRIVER	uint32_t *	reserved0188;
/* 0189 */	BSP_DRIVER	uint32_t *	reserved0189;
/* 0190 */	BSP_DRIVER	uint32_t *	reserved0190;
/* 0191 */	BSP_DRIVER	uint32_t *	reserved0191;
/* 0192 */	BSP_DRIVER	uint32_t *	reserved0192;
/* 0193 */	BSP_DRIVER	uint32_t *	reserved0193;
/* 0194 */	BSP_DRIVER	uint32_t *	reserved0194;
/* 0195 */	BSP_DRIVER	uint32_t *	reserved0195;
/* 0196 */	BSP_DRIVER	uint32_t *	reserved0196;
/* 0197 */	BSP_DRIVER	uint32_t *	reserved0197;
/* 0198 */	BSP_DRIVER	uint32_t *	reserved0198;
/* 0199 */	BSP_DRIVER	uint32_t *	reserved0199;
/* 0200 */	BSP_DRIVER	uint32_t *	reserved0200;
/* 0201 */	BSP_DRIVER	uint32_t *	reserved0201;
/* 0202 */	BSP_DRIVER	uint32_t *	reserved0202;
/* 0203 */	BSP_DRIVER	uint32_t *	reserved0203;
/* 0204 */	BSP_DRIVER	uint32_t *	reserved0204;
/* 0205 */	BSP_DRIVER	uint32_t *	reserved0205;
/* 0206 */	BSP_DRIVER	uint32_t *	reserved0206;
/* 0207 */	BSP_DRIVER	uint32_t *	reserved0207;
/* 0208 */	BSP_DRIVER	uint32_t *	reserved0208;
/* 0209 */	BSP_DRIVER	uint32_t *	reserved0209;
/* 0210 */	BSP_DRIVER	uint32_t *	reserved0210;
/* 0211 */	BSP_DRIVER	uint32_t *	reserved0211;
/* 0212 */	BSP_DRIVER	uint32_t *	reserved0212;
/* 0213 */	BSP_DRIVER	uint32_t *	reserved0213;
/* 0214 */	BSP_DRIVER	uint32_t *	reserved0214;
/* 0215 */	BSP_DRIVER	uint32_t *	reserved0215;
/* 0216 */	BSP_DRIVER	uint32_t *	reserved0216;
/* 0217 */	BSP_DRIVER	uint32_t *	reserved0217;
/* 0218 */	BSP_DRIVER	uint32_t *	reserved0218;
/* 0219 */	BSP_DRIVER	uint32_t *	reserved0219;
/* 0220 */	BSP_DRIVER	uint32_t *	reserved0220;
/* 0221 */	BSP_DRIVER	uint32_t *	reserved0221;
/* 0222 */	BSP_DRIVER	uint32_t *	reserved0222;
/* 0223 */	BSP_DRIVER	uint32_t *	reserved0223;
/* 0224 */	BSP_DRIVER	uint32_t *	reserved0224;
/* 0225 */	BSP_DRIVER	uint32_t *	reserved0225;
/* 0226 */	BSP_DRIVER	uint32_t *	reserved0226;
/* 0227 */	BSP_DRIVER	uint32_t *	reserved0227;
/* 0228 */	BSP_DRIVER	uint32_t *	reserved0228;
/* 0229 */	BSP_DRIVER	uint32_t *	reserved0229;
/* 0230 */	BSP_DRIVER	uint32_t *	reserved0230;
/* 0231 */	BSP_DRIVER	uint32_t *	reserved0231;
/* 0232 */	BSP_DRIVER	uint32_t *	reserved0232;
/* 0233 */	BSP_DRIVER	uint32_t *	reserved0233;
/* 0234 */	BSP_DRIVER	uint32_t *	reserved0234;
/* 0235 */	BSP_DRIVER	uint32_t *	reserved0235;
/* 0236 */	BSP_DRIVER	uint32_t *	reserved0236;
/* 0237 */	BSP_DRIVER	uint32_t *	reserved0237;
/* 0238 */	BSP_DRIVER	uint32_t *	reserved0238;
/* 0239 */	BSP_DRIVER	uint32_t *	reserved0239;
/* 0240 */	BSP_DRIVER	uint32_t *	reserved0240;
/* 0241 */	BSP_DRIVER	uint32_t *	reserved0241;
/* 0242 */	BSP_DRIVER	uint32_t *	reserved0242;
/* 0243 */	BSP_DRIVER	uint32_t *	reserved0243;
/* 0244 */	BSP_DRIVER	uint32_t *	reserved0244;
/* 0245 */	BSP_DRIVER	uint32_t *	reserved0245;
/* 0246 */	BSP_DRIVER	uint32_t *	reserved0246;
/* 0247 */	BSP_DRIVER	uint32_t *	reserved0247;
/* 0248 */	BSP_DRIVER	uint32_t *	reserved0248;
/* 0249 */	BSP_DRIVER	uint32_t *	reserved0249;
/* 0250 */	BSP_DRIVER	uint32_t *	reserved0250;
/* 0251 */	BSP_DRIVER	uint32_t *	reserved0251;
/* 0252 */	BSP_DRIVER	uint32_t *	reserved0252;
/* 0253 */	BSP_DRIVER	uint32_t *	reserved0253;
/* 0254 */	BSP_DRIVER	uint32_t *	reserved0254;
/* 0255 */	BSP_DRIVER	uint32_t *	reserved0255;

// Audio Library
/* 0256 */	BSP_DRIVER	uint8_t (* BSP_Audio_SetMasterVolume)(uint8_t volume);
/* 0257 */	BSP_DRIVER	uint8_t (* BSP_Audio_GetMasterVolume)(void);
/* 0258 */	BSP_DRIVER	uint8_t (* BSP_Audio_GetMasterVolumeL)(void);
/* 0259 */	BSP_DRIVER	uint8_t (* BSP_Audio_GetMasterVolumeR)(void);
/* 0260 */	BSP_DRIVER	uint8_t (* BSP_Audio_SetMasterVolumeLR)(uint8_t volume_L, uint8_t volume_R);
/* 0261 */	BSP_DRIVER	uint8_t (* BSP_Audio_IncMasterVolume)(uint8_t delta);
/* 0262 */	BSP_DRIVER	uint8_t (* BSP_Audio_DecMasterVolume)(uint8_t delta);
/* 0263 */	BSP_DRIVER	uint8_t (* BSP_Audio_SetChannelVolume)(uint8_t chno, uint8_t volume);
/* 0264 */	BSP_DRIVER	uint8_t (* BSP_Audio_SetChannelVolumeLR)(uint8_t chno, uint8_t volume_L, uint8_t volume_R);
/* 0265 */	BSP_DRIVER	uint8_t (* BSP_Audio_IncChannelVolume)(uint8_t chno, uint8_t delta);
/* 0266 */	BSP_DRIVER	uint8_t (* BSP_Audio_DecChannelVolume)(uint8_t chno, uint8_t delta);
/* 0267 */	BSP_DRIVER	uint32_t *	reserved0267;
/* 0268 */	BSP_DRIVER	uint8_t (* BSP_Audio_LinkSourceMP3)(uint8_t chno, void * addr, uint32_t size);
/* 0269 */	BSP_DRIVER	uint8_t (* BSP_Audio_LinkSourceMOD)(uint8_t chno, void * addr, uint32_t size);
/* 0270 */	BSP_DRIVER	uint8_t (* BSP_Audio_LinkSourceRAW)(uint8_t chno, void * addr, uint32_t size);
/* 0271 */	BSP_DRIVER	uint8_t (* BSP_Audio_ChannelPLay)(uint8_t chno, uint8_t repeat);
/* 0272 */	BSP_DRIVER	uint8_t (* BSP_Audio_ChannelStop)(uint8_t chno);
/* 0273 */	BSP_DRIVER	uint8_t (* BSP_Audio_ChannelPause)(uint8_t chno);
/* 0274 */	BSP_DRIVER	uint8_t (* BSP_Audio_RegisterStatusCallback)(uint8_t status, void* callback);
/* 0275 */	BSP_DRIVER	uint32_t (* BSP_Audio_GetStatusParam)(uint8_t index);
/* 0276 */	BSP_DRIVER	uint32_t *	reserved0276;
/* 0277 */	BSP_DRIVER	uint32_t *	reserved0277;
/* 0278 */	BSP_DRIVER	uint32_t *	reserved0278;
/* 0279 */	BSP_DRIVER	uint32_t *	reserved0279;
/* 0280 */	BSP_DRIVER	uint32_t *	reserved0280;
/* 0281 */	BSP_DRIVER	uint32_t *	reserved0281;
/* 0282 */	BSP_DRIVER	uint32_t *	reserved0282;
/* 0283 */	BSP_DRIVER	uint32_t *	reserved0283;
/* 0284 */	BSP_DRIVER	uint32_t *	reserved0284;
/* 0285 */	BSP_DRIVER	uint32_t *	reserved0285;
/* 0286 */	BSP_DRIVER	uint32_t *	reserved0286;
/* 0287 */	BSP_DRIVER	uint32_t *	reserved0287;
/* 0288 */	BSP_DRIVER	uint32_t *	reserved0288;
/* 0289 */	BSP_DRIVER	uint32_t *	reserved0289;
/* 0290 */	BSP_DRIVER	uint32_t *	reserved0290;
/* 0291 */	BSP_DRIVER	uint32_t *	reserved0291;
/* 0292 */	BSP_DRIVER	uint32_t *	reserved0292;
/* 0293 */	BSP_DRIVER	uint32_t *	reserved0293;
/* 0294 */	BSP_DRIVER	uint32_t *	reserved0294;
/* 0295 */	BSP_DRIVER	uint32_t *	reserved0295;
/* 0296 */	BSP_DRIVER	uint32_t *	reserved0296;
/* 0297 */	BSP_DRIVER	uint32_t *	reserved0297;
/* 0298 */	BSP_DRIVER	uint32_t *	reserved0298;
/* 0299 */	BSP_DRIVER	uint32_t *	reserved0299;
/* 0300 */	BSP_DRIVER	uint32_t *	reserved0300;
/* 0301 */	BSP_DRIVER	uint32_t *	reserved0301;
/* 0302 */	BSP_DRIVER	uint32_t *	reserved0302;
/* 0303 */	BSP_DRIVER	uint32_t *	reserved0303;
/* 0304 */	BSP_DRIVER	uint32_t *	reserved0304;
/* 0305 */	BSP_DRIVER	uint32_t *	reserved0305;
/* 0306 */	BSP_DRIVER	uint32_t *	reserved0306;
/* 0307 */	BSP_DRIVER	uint32_t *	reserved0307;
/* 0308 */	BSP_DRIVER	uint32_t *	reserved0308;
/* 0309 */	BSP_DRIVER	uint32_t *	reserved0309;
/* 0310 */	BSP_DRIVER	uint32_t *	reserved0310;
/* 0311 */	BSP_DRIVER	uint32_t *	reserved0311;
/* 0312 */	BSP_DRIVER	uint32_t *	reserved0312;
/* 0313 */	BSP_DRIVER	uint32_t *	reserved0313;
/* 0314 */	BSP_DRIVER	uint32_t *	reserved0314;
/* 0315 */	BSP_DRIVER	uint32_t *	reserved0315;
/* 0316 */	BSP_DRIVER	uint32_t *	reserved0316;
/* 0317 */	BSP_DRIVER	uint32_t *	reserved0317;
/* 0318 */	BSP_DRIVER	uint32_t *	reserved0318;
/* 0319 */	BSP_DRIVER	uint32_t *	reserved0319;
/* 0320 */	BSP_DRIVER	uint32_t *	reserved0320;
/* 0321 */	BSP_DRIVER	uint32_t *	reserved0321;
/* 0322 */	BSP_DRIVER	uint32_t *	reserved0322;
/* 0323 */	BSP_DRIVER	uint32_t *	reserved0323;
/* 0324 */	BSP_DRIVER	uint32_t *	reserved0324;
/* 0325 */	BSP_DRIVER	uint32_t *	reserved0325;
/* 0326 */	BSP_DRIVER	uint32_t *	reserved0326;
/* 0327 */	BSP_DRIVER	uint32_t *	reserved0327;
/* 0328 */	BSP_DRIVER	uint32_t *	reserved0328;
/* 0329 */	BSP_DRIVER	uint32_t *	reserved0329;
/* 0330 */	BSP_DRIVER	uint32_t *	reserved0330;
/* 0331 */	BSP_DRIVER	uint32_t *	reserved0331;
/* 0332 */	BSP_DRIVER	uint32_t *	reserved0332;
/* 0333 */	BSP_DRIVER	uint32_t *	reserved0333;
/* 0334 */	BSP_DRIVER	uint32_t *	reserved0334;
/* 0335 */	BSP_DRIVER	uint32_t *	reserved0335;
/* 0336 */	BSP_DRIVER	uint32_t *	reserved0336;
/* 0337 */	BSP_DRIVER	uint32_t *	reserved0337;
/* 0338 */	BSP_DRIVER	uint32_t *	reserved0338;
/* 0339 */	BSP_DRIVER	uint32_t *	reserved0339;
/* 0340 */	BSP_DRIVER	uint32_t *	reserved0340;
/* 0341 */	BSP_DRIVER	uint32_t *	reserved0341;
/* 0342 */	BSP_DRIVER	uint32_t *	reserved0342;
/* 0343 */	BSP_DRIVER	uint32_t *	reserved0343;
/* 0344 */	BSP_DRIVER	uint32_t *	reserved0344;
/* 0345 */	BSP_DRIVER	uint32_t *	reserved0345;
/* 0346 */	BSP_DRIVER	uint32_t *	reserved0346;
/* 0347 */	BSP_DRIVER	uint32_t *	reserved0347;
/* 0348 */	BSP_DRIVER	uint32_t *	reserved0348;
/* 0349 */	BSP_DRIVER	uint32_t *	reserved0349;
/* 0350 */	BSP_DRIVER	uint32_t *	reserved0350;
/* 0351 */	BSP_DRIVER	uint32_t *	reserved0351;
/* 0352 */	BSP_DRIVER	uint32_t *	reserved0352;
/* 0353 */	BSP_DRIVER	uint32_t *	reserved0353;
/* 0354 */	BSP_DRIVER	uint32_t *	reserved0354;
/* 0355 */	BSP_DRIVER	uint32_t *	reserved0355;
/* 0356 */	BSP_DRIVER	uint32_t *	reserved0356;
/* 0357 */	BSP_DRIVER	uint32_t *	reserved0357;
/* 0358 */	BSP_DRIVER	uint32_t *	reserved0358;
/* 0359 */	BSP_DRIVER	uint32_t *	reserved0359;
/* 0360 */	BSP_DRIVER	uint32_t *	reserved0360;
/* 0361 */	BSP_DRIVER	uint32_t *	reserved0361;
/* 0362 */	BSP_DRIVER	uint32_t *	reserved0362;
/* 0363 */	BSP_DRIVER	uint32_t *	reserved0363;
/* 0364 */	BSP_DRIVER	uint32_t *	reserved0364;
/* 0365 */	BSP_DRIVER	uint32_t *	reserved0365;
/* 0366 */	BSP_DRIVER	uint32_t *	reserved0366;
/* 0367 */	BSP_DRIVER	uint32_t *	reserved0367;
/* 0368 */	BSP_DRIVER	uint32_t *	reserved0368;
/* 0369 */	BSP_DRIVER	uint32_t *	reserved0369;
/* 0370 */	BSP_DRIVER	uint32_t *	reserved0370;
/* 0371 */	BSP_DRIVER	uint32_t *	reserved0371;
/* 0372 */	BSP_DRIVER	uint32_t *	reserved0372;
/* 0373 */	BSP_DRIVER	uint32_t *	reserved0373;
/* 0374 */	BSP_DRIVER	uint32_t *	reserved0374;
/* 0375 */	BSP_DRIVER	uint32_t *	reserved0375;
/* 0376 */	BSP_DRIVER	uint32_t *	reserved0376;
/* 0377 */	BSP_DRIVER	uint32_t *	reserved0377;
/* 0378 */	BSP_DRIVER	uint32_t *	reserved0378;
/* 0379 */	BSP_DRIVER	uint32_t *	reserved0379;
/* 0380 */	BSP_DRIVER	uint32_t *	reserved0380;
/* 0381 */	BSP_DRIVER	uint32_t *	reserved0381;
/* 0382 */	BSP_DRIVER	uint32_t *	reserved0382;
/* 0383 */	BSP_DRIVER	uint32_t *	reserved0383;

// Resources
/* 0384 */	BSP_DRIVER	uint8_t (* BSP_Res_Init)(void * resAddr, uint32_t resSize);
/* 0385 */	BSP_DRIVER	void* (* BSP_Res_Alloc)(uint32_t resSize);
/* 0386 */	BSP_DRIVER	uint8_t (* BSP_Res_Free)(void * objAddr);
/* 0387 */	BSP_DRIVER	void* (* BSP_Res_Load)(char *filename);
/* 0388 */	BSP_DRIVER	uint32_t (* BSP_Res_GetSize)(void * objAddr);
/* 0389 */	BSP_DRIVER	uint32_t *	reserved0389;
/* 0390 */	BSP_DRIVER	uint32_t *	reserved0390;
/* 0391 */	BSP_DRIVER	uint32_t *	reserved0391;
/* 0392 */	BSP_DRIVER	uint32_t *	reserved0392;
/* 0393 */	BSP_DRIVER	uint32_t *	reserved0393;
/* 0394 */	BSP_DRIVER	uint32_t *	reserved0394;
/* 0395 */	BSP_DRIVER	uint32_t *	reserved0395;
/* 0396 */	BSP_DRIVER	uint32_t *	reserved0396;
/* 0397 */	BSP_DRIVER	uint32_t *	reserved0397;
/* 0398 */	BSP_DRIVER	uint32_t *	reserved0398;
/* 0399 */	BSP_DRIVER	uint32_t *	reserved0399;
/* 0400 */	BSP_DRIVER	uint32_t *	reserved0400;
/* 0401 */	BSP_DRIVER	uint32_t *	reserved0401;
/* 0402 */	BSP_DRIVER	uint32_t *	reserved0402;
/* 0403 */	BSP_DRIVER	uint32_t *	reserved0403;
/* 0404 */	BSP_DRIVER	uint32_t *	reserved0404;
/* 0405 */	BSP_DRIVER	uint32_t *	reserved0405;
/* 0406 */	BSP_DRIVER	uint32_t *	reserved0406;
/* 0407 */	BSP_DRIVER	uint32_t *	reserved0407;
/* 0408 */	BSP_DRIVER	uint32_t *	reserved0408;
/* 0409 */	BSP_DRIVER	uint32_t *	reserved0409;
/* 0410 */	BSP_DRIVER	uint32_t *	reserved0410;
/* 0411 */	BSP_DRIVER	uint32_t *	reserved0411;
/* 0412 */	BSP_DRIVER	uint32_t *	reserved0412;
/* 0413 */	BSP_DRIVER	uint32_t *	reserved0413;
/* 0414 */	BSP_DRIVER	uint32_t *	reserved0414;
/* 0415 */	BSP_DRIVER	uint32_t *	reserved0415;
/* 0416 */	BSP_DRIVER	uint32_t *	reserved0416;
/* 0417 */	BSP_DRIVER	uint32_t *	reserved0417;
/* 0418 */	BSP_DRIVER	uint32_t *	reserved0418;
/* 0419 */	BSP_DRIVER	uint32_t *	reserved0419;
/* 0420 */	BSP_DRIVER	uint32_t *	reserved0420;
/* 0421 */	BSP_DRIVER	uint32_t *	reserved0421;
/* 0422 */	BSP_DRIVER	uint32_t *	reserved0422;
/* 0423 */	BSP_DRIVER	uint32_t *	reserved0423;
/* 0424 */	BSP_DRIVER	uint32_t *	reserved0424;
/* 0425 */	BSP_DRIVER	uint32_t *	reserved0425;
/* 0426 */	BSP_DRIVER	uint32_t *	reserved0426;
/* 0427 */	BSP_DRIVER	uint32_t *	reserved0427;
/* 0428 */	BSP_DRIVER	uint32_t *	reserved0428;
/* 0429 */	BSP_DRIVER	uint32_t *	reserved0429;
/* 0430 */	BSP_DRIVER	uint32_t *	reserved0430;
/* 0431 */	BSP_DRIVER	uint32_t *	reserved0431;
/* 0432 */	BSP_DRIVER	uint32_t *	reserved0432;
/* 0433 */	BSP_DRIVER	uint32_t *	reserved0433;
/* 0434 */	BSP_DRIVER	uint32_t *	reserved0434;
/* 0435 */	BSP_DRIVER	uint32_t *	reserved0435;
/* 0436 */	BSP_DRIVER	uint32_t *	reserved0436;
/* 0437 */	BSP_DRIVER	uint32_t *	reserved0437;
/* 0438 */	BSP_DRIVER	uint32_t *	reserved0438;
/* 0439 */	BSP_DRIVER	uint32_t *	reserved0439;
/* 0440 */	BSP_DRIVER	uint32_t *	reserved0440;
/* 0441 */	BSP_DRIVER	uint32_t *	reserved0441;
/* 0442 */	BSP_DRIVER	uint32_t *	reserved0442;
/* 0443 */	BSP_DRIVER	uint32_t *	reserved0443;
/* 0444 */	BSP_DRIVER	uint32_t *	reserved0444;
/* 0445 */	BSP_DRIVER	uint32_t *	reserved0445;
/* 0446 */	BSP_DRIVER	uint32_t *	reserved0446;
/* 0447 */	BSP_DRIVER	uint32_t *	reserved0447;
/* 0448 */	BSP_DRIVER	uint32_t *	reserved0448;
/* 0449 */	BSP_DRIVER	uint32_t *	reserved0449;
/* 0450 */	BSP_DRIVER	uint32_t *	reserved0450;
/* 0451 */	BSP_DRIVER	uint32_t *	reserved0451;
/* 0452 */	BSP_DRIVER	uint32_t *	reserved0452;
/* 0453 */	BSP_DRIVER	uint32_t *	reserved0453;
/* 0454 */	BSP_DRIVER	uint32_t *	reserved0454;
/* 0455 */	BSP_DRIVER	uint32_t *	reserved0455;
/* 0456 */	BSP_DRIVER	uint32_t *	reserved0456;
/* 0457 */	BSP_DRIVER	uint32_t *	reserved0457;
/* 0458 */	BSP_DRIVER	uint32_t *	reserved0458;
/* 0459 */	BSP_DRIVER	uint32_t *	reserved0459;
/* 0460 */	BSP_DRIVER	uint32_t *	reserved0460;
/* 0461 */	BSP_DRIVER	uint32_t *	reserved0461;
/* 0462 */	BSP_DRIVER	uint32_t *	reserved0462;
/* 0463 */	BSP_DRIVER	uint32_t *	reserved0463;
/* 0464 */	BSP_DRIVER	uint32_t *	reserved0464;
/* 0465 */	BSP_DRIVER	uint32_t *	reserved0465;
/* 0466 */	BSP_DRIVER	uint32_t *	reserved0466;
/* 0467 */	BSP_DRIVER	uint32_t *	reserved0467;
/* 0468 */	BSP_DRIVER	uint32_t *	reserved0468;
/* 0469 */	BSP_DRIVER	uint32_t *	reserved0469;
/* 0470 */	BSP_DRIVER	uint32_t *	reserved0470;
/* 0471 */	BSP_DRIVER	uint32_t *	reserved0471;
/* 0472 */	BSP_DRIVER	uint32_t *	reserved0472;
/* 0473 */	BSP_DRIVER	uint32_t *	reserved0473;
/* 0474 */	BSP_DRIVER	uint32_t *	reserved0474;
/* 0475 */	BSP_DRIVER	uint32_t *	reserved0475;
/* 0476 */	BSP_DRIVER	uint32_t *	reserved0476;
/* 0477 */	BSP_DRIVER	uint32_t *	reserved0477;
/* 0478 */	BSP_DRIVER	uint32_t *	reserved0478;
/* 0479 */	BSP_DRIVER	uint32_t *	reserved0479;
/* 0480 */	BSP_DRIVER	uint32_t *	reserved0480;
/* 0481 */	BSP_DRIVER	uint32_t *	reserved0481;
/* 0482 */	BSP_DRIVER	uint32_t *	reserved0482;
/* 0483 */	BSP_DRIVER	uint32_t *	reserved0483;
/* 0484 */	BSP_DRIVER	uint32_t *	reserved0484;
/* 0485 */	BSP_DRIVER	uint32_t *	reserved0485;
/* 0486 */	BSP_DRIVER	uint32_t *	reserved0486;
/* 0487 */	BSP_DRIVER	uint32_t *	reserved0487;
/* 0488 */	BSP_DRIVER	uint32_t *	reserved0488;
/* 0489 */	BSP_DRIVER	uint32_t *	reserved0489;
/* 0490 */	BSP_DRIVER	uint32_t *	reserved0490;
/* 0491 */	BSP_DRIVER	uint32_t *	reserved0491;
/* 0492 */	BSP_DRIVER	uint32_t *	reserved0492;
/* 0493 */	BSP_DRIVER	uint32_t *	reserved0493;
/* 0494 */	BSP_DRIVER	uint32_t *	reserved0494;
/* 0495 */	BSP_DRIVER	uint32_t *	reserved0495;
/* 0496 */	BSP_DRIVER	uint32_t *	reserved0496;
/* 0497 */	BSP_DRIVER	uint32_t *	reserved0497;
/* 0498 */	BSP_DRIVER	uint32_t *	reserved0498;
/* 0499 */	BSP_DRIVER	uint32_t *	reserved0499;
/* 0500 */	BSP_DRIVER	uint32_t *	reserved0500;
/* 0501 */	BSP_DRIVER	uint32_t *	reserved0501;
/* 0502 */	BSP_DRIVER	uint32_t *	reserved0502;
/* 0503 */	BSP_DRIVER	uint32_t *	reserved0503;
/* 0504 */	BSP_DRIVER	uint32_t *	reserved0504;
/* 0505 */	BSP_DRIVER	uint32_t *	reserved0505;
/* 0506 */	BSP_DRIVER	uint32_t *	reserved0506;
/* 0507 */	BSP_DRIVER	uint32_t *	reserved0507;
/* 0508 */	BSP_DRIVER	uint32_t *	reserved0508;
/* 0509 */	BSP_DRIVER	uint32_t *	reserved0509;
/* 0510 */	BSP_DRIVER	uint32_t *	reserved0510;
/* 0511 */	BSP_DRIVER	uint32_t *	reserved0511;

// Remaining pointers
/* 0512 */	BSP_DRIVER	uint32_t *	reserved0512;
/* 0513 */	BSP_DRIVER	uint32_t *	reserved0513;
/* 0514 */	BSP_DRIVER	uint32_t *	reserved0514;
/* 0515 */	BSP_DRIVER	uint32_t *	reserved0515;
/* 0516 */	BSP_DRIVER	uint32_t *	reserved0516;
/* 0517 */	BSP_DRIVER	uint32_t *	reserved0517;
/* 0518 */	BSP_DRIVER	uint32_t *	reserved0518;
/* 0519 */	BSP_DRIVER	uint32_t *	reserved0519;

/* 0520 */	BSP_DRIVER	uint32_t *	reserved0520;
/* 0521 */	BSP_DRIVER	uint32_t *	reserved0521;
/* 0522 */	BSP_DRIVER	uint32_t *	reserved0522;
/* 0523 */	BSP_DRIVER	uint32_t *	reserved0523;
/* 0524 */	BSP_DRIVER	uint32_t *	reserved0524;
/* 0525 */	BSP_DRIVER	uint32_t *	reserved0525;
/* 0526 */	BSP_DRIVER	uint32_t *	reserved0526;
/* 0527 */	BSP_DRIVER	uint32_t *	reserved0527;
/* 0528 */	BSP_DRIVER	uint32_t *	reserved0528;
/* 0529 */	BSP_DRIVER	uint32_t *	reserved0529;

/* 0530 */	BSP_DRIVER	uint32_t *	reserved0530;
/* 0531 */	BSP_DRIVER	uint32_t *	reserved0531;
/* 0532 */	BSP_DRIVER	uint32_t *	reserved0532;
/* 0533 */	BSP_DRIVER	uint32_t *	reserved0533;
/* 0534 */	BSP_DRIVER	uint32_t *	reserved0534;
/* 0535 */	BSP_DRIVER	uint32_t *	reserved0535;
/* 0536 */	BSP_DRIVER	uint32_t *	reserved0536;
/* 0537 */	BSP_DRIVER	uint32_t *	reserved0537;
/* 0538 */	BSP_DRIVER	uint32_t *	reserved0538;
/* 0539 */	BSP_DRIVER	uint32_t *	reserved0539;

/* 0540 */	BSP_DRIVER	uint32_t *	reserved0540;
/* 0541 */	BSP_DRIVER	uint32_t *	reserved0541;
/* 0542 */	BSP_DRIVER	uint32_t *	reserved0542;
/* 0543 */	BSP_DRIVER	uint32_t *	reserved0543;
/* 0544 */	BSP_DRIVER	uint32_t *	reserved0544;
/* 0545 */	BSP_DRIVER	uint32_t *	reserved0545;
/* 0546 */	BSP_DRIVER	uint32_t *	reserved0546;
/* 0547 */	BSP_DRIVER	uint32_t *	reserved0547;
/* 0548 */	BSP_DRIVER	uint32_t *	reserved0548;
/* 0549 */	BSP_DRIVER	uint32_t *	reserved0549;

/* 0550 */	BSP_DRIVER	uint32_t *	reserved0550;
/* 0551 */	BSP_DRIVER	uint32_t *	reserved0551;
/* 0552 */	BSP_DRIVER	uint32_t *	reserved0552;
/* 0553 */	BSP_DRIVER	uint32_t *	reserved0553;
/* 0554 */	BSP_DRIVER	uint32_t *	reserved0554;
/* 0555 */	BSP_DRIVER	uint32_t *	reserved0555;
/* 0556 */	BSP_DRIVER	uint32_t *	reserved0556;
/* 0557 */	BSP_DRIVER	uint32_t *	reserved0557;
/* 0558 */	BSP_DRIVER	uint32_t *	reserved0558;
/* 0559 */	BSP_DRIVER	uint32_t *	reserved0559;

/* 0560 */	BSP_DRIVER	uint32_t *	reserved0560;
/* 0561 */	BSP_DRIVER	uint32_t *	reserved0561;
/* 0562 */	BSP_DRIVER	uint32_t *	reserved0562;
/* 0563 */	BSP_DRIVER	uint32_t *	reserved0563;
/* 0564 */	BSP_DRIVER	uint32_t *	reserved0564;
/* 0565 */	BSP_DRIVER	uint32_t *	reserved0565;
/* 0566 */	BSP_DRIVER	uint32_t *	reserved0566;
/* 0567 */	BSP_DRIVER	uint32_t *	reserved0567;
/* 0568 */	BSP_DRIVER	uint32_t *	reserved0568;
/* 0569 */	BSP_DRIVER	uint32_t *	reserved0569;

/* 0570 */	BSP_DRIVER	uint32_t *	reserved0570;
/* 0571 */	BSP_DRIVER	uint32_t *	reserved0571;
/* 0572 */	BSP_DRIVER	uint32_t *	reserved0572;
/* 0573 */	BSP_DRIVER	uint32_t *	reserved0573;
/* 0574 */	BSP_DRIVER	uint32_t *	reserved0574;
/* 0575 */	BSP_DRIVER	uint32_t *	reserved0575;
/* 0576 */	BSP_DRIVER	uint32_t *	reserved0576;
/* 0577 */	BSP_DRIVER	uint32_t *	reserved0577;
/* 0578 */	BSP_DRIVER	uint32_t *	reserved0578;
/* 0579 */	BSP_DRIVER	uint32_t *	reserved0579;

/* 0580 */	BSP_DRIVER	uint32_t *	reserved0580;
/* 0581 */	BSP_DRIVER	uint32_t *	reserved0581;
/* 0582 */	BSP_DRIVER	uint32_t *	reserved0582;
/* 0583 */	BSP_DRIVER	uint32_t *	reserved0583;
/* 0584 */	BSP_DRIVER	uint32_t *	reserved0584;
/* 0585 */	BSP_DRIVER	uint32_t *	reserved0585;
/* 0586 */	BSP_DRIVER	uint32_t *	reserved0586;
/* 0587 */	BSP_DRIVER	uint32_t *	reserved0587;
/* 0588 */	BSP_DRIVER	uint32_t *	reserved0588;
/* 0589 */	BSP_DRIVER	uint32_t *	reserved0589;

/* 0590 */	BSP_DRIVER	uint32_t *	reserved0590;
/* 0591 */	BSP_DRIVER	uint32_t *	reserved0591;
/* 0592 */	BSP_DRIVER	uint32_t *	reserved0592;
/* 0593 */	BSP_DRIVER	uint32_t *	reserved0593;
/* 0594 */	BSP_DRIVER	uint32_t *	reserved0594;
/* 0595 */	BSP_DRIVER	uint32_t *	reserved0595;
/* 0596 */	BSP_DRIVER	uint32_t *	reserved0596;
/* 0597 */	BSP_DRIVER	uint32_t *	reserved0597;
/* 0598 */	BSP_DRIVER	uint32_t *	reserved0598;
/* 0599 */	BSP_DRIVER	uint32_t *	reserved0599;

/* 0600 */	BSP_DRIVER	uint32_t *	reserved0600;
/* 0601 */	BSP_DRIVER	uint32_t *	reserved0601;
/* 0602 */	BSP_DRIVER	uint32_t *	reserved0602;
/* 0603 */	BSP_DRIVER	uint32_t *	reserved0603;
/* 0604 */	BSP_DRIVER	uint32_t *	reserved0604;
/* 0605 */	BSP_DRIVER	uint32_t *	reserved0605;
/* 0606 */	BSP_DRIVER	uint32_t *	reserved0606;
/* 0607 */	BSP_DRIVER	uint32_t *	reserved0607;
/* 0608 */	BSP_DRIVER	uint32_t *	reserved0608;
/* 0609 */	BSP_DRIVER	uint32_t *	reserved0609;

/* 0610 */	BSP_DRIVER	uint32_t *	reserved0610;
/* 0611 */	BSP_DRIVER	uint32_t *	reserved0611;
/* 0612 */	BSP_DRIVER	uint32_t *	reserved0612;
/* 0613 */	BSP_DRIVER	uint32_t *	reserved0613;
/* 0614 */	BSP_DRIVER	uint32_t *	reserved0614;
/* 0615 */	BSP_DRIVER	uint32_t *	reserved0615;
/* 0616 */	BSP_DRIVER	uint32_t *	reserved0616;
/* 0617 */	BSP_DRIVER	uint32_t *	reserved0617;
/* 0618 */	BSP_DRIVER	uint32_t *	reserved0618;
/* 0619 */	BSP_DRIVER	uint32_t *	reserved0619;

/* 0620 */	BSP_DRIVER	uint32_t *	reserved0620;
/* 0621 */	BSP_DRIVER	uint32_t *	reserved0621;
/* 0622 */	BSP_DRIVER	uint32_t *	reserved0622;
/* 0623 */	BSP_DRIVER	uint32_t *	reserved0623;
/* 0624 */	BSP_DRIVER	uint32_t *	reserved0624;
/* 0625 */	BSP_DRIVER	uint32_t *	reserved0625;
/* 0626 */	BSP_DRIVER	uint32_t *	reserved0626;
/* 0627 */	BSP_DRIVER	uint32_t *	reserved0627;
/* 0628 */	BSP_DRIVER	uint32_t *	reserved0628;
/* 0629 */	BSP_DRIVER	uint32_t *	reserved0629;

/* 0630 */	BSP_DRIVER	uint32_t *	reserved0630;
/* 0631 */	BSP_DRIVER	uint32_t *	reserved0631;
/* 0632 */	BSP_DRIVER	uint32_t *	reserved0632;
/* 0633 */	BSP_DRIVER	uint32_t *	reserved0633;
/* 0634 */	BSP_DRIVER	uint32_t *	reserved0634;
/* 0635 */	BSP_DRIVER	uint32_t *	reserved0635;
/* 0636 */	BSP_DRIVER	uint32_t *	reserved0636;
/* 0637 */	BSP_DRIVER	uint32_t *	reserved0637;
/* 0638 */	BSP_DRIVER	uint32_t *	reserved0638;
/* 0639 */	BSP_DRIVER	uint32_t *	reserved0639;

/* 0640 */	BSP_DRIVER	uint32_t *	reserved0640;
/* 0641 */	BSP_DRIVER	uint32_t *	reserved0641;
/* 0642 */	BSP_DRIVER	uint32_t *	reserved0642;
/* 0643 */	BSP_DRIVER	uint32_t *	reserved0643;
/* 0644 */	BSP_DRIVER	uint32_t *	reserved0644;
/* 0645 */	BSP_DRIVER	uint32_t *	reserved0645;
/* 0646 */	BSP_DRIVER	uint32_t *	reserved0646;
/* 0647 */	BSP_DRIVER	uint32_t *	reserved0647;
/* 0648 */	BSP_DRIVER	uint32_t *	reserved0648;
/* 0649 */	BSP_DRIVER	uint32_t *	reserved0649;

/* 0650 */	BSP_DRIVER	uint32_t *	reserved0650;
/* 0651 */	BSP_DRIVER	uint32_t *	reserved0651;
/* 0652 */	BSP_DRIVER	uint32_t *	reserved0652;
/* 0653 */	BSP_DRIVER	uint32_t *	reserved0653;
/* 0654 */	BSP_DRIVER	uint32_t *	reserved0654;
/* 0655 */	BSP_DRIVER	uint32_t *	reserved0655;
/* 0656 */	BSP_DRIVER	uint32_t *	reserved0656;
/* 0657 */	BSP_DRIVER	uint32_t *	reserved0657;
/* 0658 */	BSP_DRIVER	uint32_t *	reserved0658;
/* 0659 */	BSP_DRIVER	uint32_t *	reserved0659;

/* 0660 */	BSP_DRIVER	uint32_t *	reserved0660;
/* 0661 */	BSP_DRIVER	uint32_t *	reserved0661;
/* 0662 */	BSP_DRIVER	uint32_t *	reserved0662;
/* 0663 */	BSP_DRIVER	uint32_t *	reserved0663;
/* 0664 */	BSP_DRIVER	uint32_t *	reserved0664;
/* 0665 */	BSP_DRIVER	uint32_t *	reserved0665;
/* 0666 */	BSP_DRIVER	uint32_t *	reserved0666;
/* 0667 */	BSP_DRIVER	uint32_t *	reserved0667;
/* 0668 */	BSP_DRIVER	uint32_t *	reserved0668;
/* 0669 */	BSP_DRIVER	uint32_t *	reserved0669;

/* 0670 */	BSP_DRIVER	uint32_t *	reserved0670;
/* 0671 */	BSP_DRIVER	uint32_t *	reserved0671;
/* 0672 */	BSP_DRIVER	uint32_t *	reserved0672;
/* 0673 */	BSP_DRIVER	uint32_t *	reserved0673;
/* 0674 */	BSP_DRIVER	uint32_t *	reserved0674;
/* 0675 */	BSP_DRIVER	uint32_t *	reserved0675;
/* 0676 */	BSP_DRIVER	uint32_t *	reserved0676;
/* 0677 */	BSP_DRIVER	uint32_t *	reserved0677;
/* 0678 */	BSP_DRIVER	uint32_t *	reserved0678;
/* 0679 */	BSP_DRIVER	uint32_t *	reserved0679;

/* 0680 */	BSP_DRIVER	uint32_t *	reserved0680;
/* 0681 */	BSP_DRIVER	uint32_t *	reserved0681;
/* 0682 */	BSP_DRIVER	uint32_t *	reserved0682;
/* 0683 */	BSP_DRIVER	uint32_t *	reserved0683;
/* 0684 */	BSP_DRIVER	uint32_t *	reserved0684;
/* 0685 */	BSP_DRIVER	uint32_t *	reserved0685;
/* 0686 */	BSP_DRIVER	uint32_t *	reserved0686;
/* 0687 */	BSP_DRIVER	uint32_t *	reserved0687;
/* 0688 */	BSP_DRIVER	uint32_t *	reserved0688;
/* 0689 */	BSP_DRIVER	uint32_t *	reserved0689;

/* 0690 */	BSP_DRIVER	uint32_t *	reserved0690;
/* 0691 */	BSP_DRIVER	uint32_t *	reserved0691;
/* 0692 */	BSP_DRIVER	uint32_t *	reserved0692;
/* 0693 */	BSP_DRIVER	uint32_t *	reserved0693;
/* 0694 */	BSP_DRIVER	uint32_t *	reserved0694;
/* 0695 */	BSP_DRIVER	uint32_t *	reserved0695;
/* 0696 */	BSP_DRIVER	uint32_t *	reserved0696;
/* 0697 */	BSP_DRIVER	uint32_t *	reserved0697;
/* 0698 */	BSP_DRIVER	uint32_t *	reserved0698;
/* 0699 */	BSP_DRIVER	uint32_t *	reserved0699;

/* 0700 */	BSP_DRIVER	uint32_t *	reserved0700;
/* 0701 */	BSP_DRIVER	uint32_t *	reserved0701;
/* 0702 */	BSP_DRIVER	uint32_t *	reserved0702;
/* 0703 */	BSP_DRIVER	uint32_t *	reserved0703;
/* 0704 */	BSP_DRIVER	uint32_t *	reserved0704;
/* 0705 */	BSP_DRIVER	uint32_t *	reserved0705;
/* 0706 */	BSP_DRIVER	uint32_t *	reserved0706;
/* 0707 */	BSP_DRIVER	uint32_t *	reserved0707;
/* 0708 */	BSP_DRIVER	uint32_t *	reserved0708;
/* 0709 */	BSP_DRIVER	uint32_t *	reserved0709;

/* 0710 */	BSP_DRIVER	uint32_t *	reserved0710;
/* 0711 */	BSP_DRIVER	uint32_t *	reserved0711;
/* 0712 */	BSP_DRIVER	uint32_t *	reserved0712;
/* 0713 */	BSP_DRIVER	uint32_t *	reserved0713;
/* 0714 */	BSP_DRIVER	uint32_t *	reserved0714;
/* 0715 */	BSP_DRIVER	uint32_t *	reserved0715;
/* 0716 */	BSP_DRIVER	uint32_t *	reserved0716;
/* 0717 */	BSP_DRIVER	uint32_t *	reserved0717;
/* 0718 */	BSP_DRIVER	uint32_t *	reserved0718;
/* 0719 */	BSP_DRIVER	uint32_t *	reserved0719;

/* 0720 */	BSP_DRIVER	uint32_t *	reserved0720;
/* 0721 */	BSP_DRIVER	uint32_t *	reserved0721;
/* 0722 */	BSP_DRIVER	uint32_t *	reserved0722;
/* 0723 */	BSP_DRIVER	uint32_t *	reserved0723;
/* 0724 */	BSP_DRIVER	uint32_t *	reserved0724;
/* 0725 */	BSP_DRIVER	uint32_t *	reserved0725;
/* 0726 */	BSP_DRIVER	uint32_t *	reserved0726;
/* 0727 */	BSP_DRIVER	uint32_t *	reserved0727;
/* 0728 */	BSP_DRIVER	uint32_t *	reserved0728;
/* 0729 */	BSP_DRIVER	uint32_t *	reserved0729;

/* 0730 */	BSP_DRIVER	uint32_t *	reserved0730;
/* 0731 */	BSP_DRIVER	uint32_t *	reserved0731;
/* 0732 */	BSP_DRIVER	uint32_t *	reserved0732;
/* 0733 */	BSP_DRIVER	uint32_t *	reserved0733;
/* 0734 */	BSP_DRIVER	uint32_t *	reserved0734;
/* 0735 */	BSP_DRIVER	uint32_t *	reserved0735;
/* 0736 */	BSP_DRIVER	uint32_t *	reserved0736;
/* 0737 */	BSP_DRIVER	uint32_t *	reserved0737;
/* 0738 */	BSP_DRIVER	uint32_t *	reserved0738;
/* 0739 */	BSP_DRIVER	uint32_t *	reserved0739;

/* 0740 */	BSP_DRIVER	uint32_t *	reserved0740;
/* 0741 */	BSP_DRIVER	uint32_t *	reserved0741;
/* 0742 */	BSP_DRIVER	uint32_t *	reserved0742;
/* 0743 */	BSP_DRIVER	uint32_t *	reserved0743;
/* 0744 */	BSP_DRIVER	uint32_t *	reserved0744;
/* 0745 */	BSP_DRIVER	uint32_t *	reserved0745;
/* 0746 */	BSP_DRIVER	uint32_t *	reserved0746;
/* 0747 */	BSP_DRIVER	uint32_t *	reserved0747;
/* 0748 */	BSP_DRIVER	uint32_t *	reserved0748;
/* 0749 */	BSP_DRIVER	uint32_t *	reserved0749;

/* 0750 */	BSP_DRIVER	uint32_t *	reserved0750;
/* 0751 */	BSP_DRIVER	uint32_t *	reserved0751;
/* 0752 */	BSP_DRIVER	uint32_t *	reserved0752;
/* 0753 */	BSP_DRIVER	uint32_t *	reserved0753;
/* 0754 */	BSP_DRIVER	uint32_t *	reserved0754;
/* 0755 */	BSP_DRIVER	uint32_t *	reserved0755;
/* 0756 */	BSP_DRIVER	uint32_t *	reserved0756;
/* 0757 */	BSP_DRIVER	uint32_t *	reserved0757;
/* 0758 */	BSP_DRIVER	uint32_t *	reserved0758;
/* 0759 */	BSP_DRIVER	uint32_t *	reserved0759;

/* 0760 */	BSP_DRIVER	uint32_t *	reserved0760;
/* 0761 */	BSP_DRIVER	uint32_t *	reserved0761;
/* 0762 */	BSP_DRIVER	uint32_t *	reserved0762;
/* 0763 */	BSP_DRIVER	uint32_t *	reserved0763;
/* 0764 */	BSP_DRIVER	uint32_t *	reserved0764;
/* 0765 */	BSP_DRIVER	uint32_t *	reserved0765;
/* 0766 */	BSP_DRIVER	uint32_t *	reserved0766;
/* 0767 */	BSP_DRIVER	uint32_t *	reserved0767;
/* 0768 */	BSP_DRIVER	uint32_t *	reserved0768;
/* 0769 */	BSP_DRIVER	uint32_t *	reserved0769;

/* 0770 */	BSP_DRIVER	uint32_t *	reserved0770;
/* 0771 */	BSP_DRIVER	uint32_t *	reserved0771;
/* 0772 */	BSP_DRIVER	uint32_t *	reserved0772;
/* 0773 */	BSP_DRIVER	uint32_t *	reserved0773;
/* 0774 */	BSP_DRIVER	uint32_t *	reserved0774;
/* 0775 */	BSP_DRIVER	uint32_t *	reserved0775;
/* 0776 */	BSP_DRIVER	uint32_t *	reserved0776;
/* 0777 */	BSP_DRIVER	uint32_t *	reserved0777;
/* 0778 */	BSP_DRIVER	uint32_t *	reserved0778;
/* 0779 */	BSP_DRIVER	uint32_t *	reserved0779;

/* 0780 */	BSP_DRIVER	uint32_t *	reserved0780;
/* 0781 */	BSP_DRIVER	uint32_t *	reserved0781;
/* 0782 */	BSP_DRIVER	uint32_t *	reserved0782;
/* 0783 */	BSP_DRIVER	uint32_t *	reserved0783;
/* 0784 */	BSP_DRIVER	uint32_t *	reserved0784;
/* 0785 */	BSP_DRIVER	uint32_t *	reserved0785;
/* 0786 */	BSP_DRIVER	uint32_t *	reserved0786;
/* 0787 */	BSP_DRIVER	uint32_t *	reserved0787;
/* 0788 */	BSP_DRIVER	uint32_t *	reserved0788;
/* 0789 */	BSP_DRIVER	uint32_t *	reserved0789;

/* 0790 */	BSP_DRIVER	uint32_t *	reserved0790;
/* 0791 */	BSP_DRIVER	uint32_t *	reserved0791;
/* 0792 */	BSP_DRIVER	uint32_t *	reserved0792;
/* 0793 */	BSP_DRIVER	uint32_t *	reserved0793;
/* 0794 */	BSP_DRIVER	uint32_t *	reserved0794;
/* 0795 */	BSP_DRIVER	uint32_t *	reserved0795;
/* 0796 */	BSP_DRIVER	uint32_t *	reserved0796;
/* 0797 */	BSP_DRIVER	uint32_t *	reserved0797;
/* 0798 */	BSP_DRIVER	uint32_t *	reserved0798;
/* 0799 */	BSP_DRIVER	uint32_t *	reserved0799;

/* 0800 */	BSP_DRIVER	uint32_t *	reserved0800;
/* 0801 */	BSP_DRIVER	uint32_t *	reserved0801;
/* 0802 */	BSP_DRIVER	uint32_t *	reserved0802;
/* 0803 */	BSP_DRIVER	uint32_t *	reserved0803;
/* 0804 */	BSP_DRIVER	uint32_t *	reserved0804;
/* 0805 */	BSP_DRIVER	uint32_t *	reserved0805;
/* 0806 */	BSP_DRIVER	uint32_t *	reserved0806;
/* 0807 */	BSP_DRIVER	uint32_t *	reserved0807;
/* 0808 */	BSP_DRIVER	uint32_t *	reserved0808;
/* 0809 */	BSP_DRIVER	uint32_t *	reserved0809;

/* 0810 */	BSP_DRIVER	uint32_t *	reserved0810;
/* 0811 */	BSP_DRIVER	uint32_t *	reserved0811;
/* 0812 */	BSP_DRIVER	uint32_t *	reserved0812;
/* 0813 */	BSP_DRIVER	uint32_t *	reserved0813;
/* 0814 */	BSP_DRIVER	uint32_t *	reserved0814;
/* 0815 */	BSP_DRIVER	uint32_t *	reserved0815;
/* 0816 */	BSP_DRIVER	uint32_t *	reserved0816;
/* 0817 */	BSP_DRIVER	uint32_t *	reserved0817;
/* 0818 */	BSP_DRIVER	uint32_t *	reserved0818;
/* 0819 */	BSP_DRIVER	uint32_t *	reserved0819;

/* 0820 */	BSP_DRIVER	uint32_t *	reserved0820;
/* 0821 */	BSP_DRIVER	uint32_t *	reserved0821;
/* 0822 */	BSP_DRIVER	uint32_t *	reserved0822;
/* 0823 */	BSP_DRIVER	uint32_t *	reserved0823;
/* 0824 */	BSP_DRIVER	uint32_t *	reserved0824;
/* 0825 */	BSP_DRIVER	uint32_t *	reserved0825;
/* 0826 */	BSP_DRIVER	uint32_t *	reserved0826;
/* 0827 */	BSP_DRIVER	uint32_t *	reserved0827;
/* 0828 */	BSP_DRIVER	uint32_t *	reserved0828;
/* 0829 */	BSP_DRIVER	uint32_t *	reserved0829;

/* 0830 */	BSP_DRIVER	uint32_t *	reserved0830;
/* 0831 */	BSP_DRIVER	uint32_t *	reserved0831;
/* 0832 */	BSP_DRIVER	uint32_t *	reserved0832;
/* 0833 */	BSP_DRIVER	uint32_t *	reserved0833;
/* 0834 */	BSP_DRIVER	uint32_t *	reserved0834;
/* 0835 */	BSP_DRIVER	uint32_t *	reserved0835;
/* 0836 */	BSP_DRIVER	uint32_t *	reserved0836;
/* 0837 */	BSP_DRIVER	uint32_t *	reserved0837;
/* 0838 */	BSP_DRIVER	uint32_t *	reserved0838;
/* 0839 */	BSP_DRIVER	uint32_t *	reserved0839;

/* 0840 */	BSP_DRIVER	uint32_t *	reserved0840;
/* 0841 */	BSP_DRIVER	uint32_t *	reserved0841;
/* 0842 */	BSP_DRIVER	uint32_t *	reserved0842;
/* 0843 */	BSP_DRIVER	uint32_t *	reserved0843;
/* 0844 */	BSP_DRIVER	uint32_t *	reserved0844;
/* 0845 */	BSP_DRIVER	uint32_t *	reserved0845;
/* 0846 */	BSP_DRIVER	uint32_t *	reserved0846;
/* 0847 */	BSP_DRIVER	uint32_t *	reserved0847;
/* 0848 */	BSP_DRIVER	uint32_t *	reserved0848;
/* 0849 */	BSP_DRIVER	uint32_t *	reserved0849;

/* 0850 */	BSP_DRIVER	uint32_t *	reserved0850;
/* 0851 */	BSP_DRIVER	uint32_t *	reserved0851;
/* 0852 */	BSP_DRIVER	uint32_t *	reserved0852;
/* 0853 */	BSP_DRIVER	uint32_t *	reserved0853;
/* 0854 */	BSP_DRIVER	uint32_t *	reserved0854;
/* 0855 */	BSP_DRIVER	uint32_t *	reserved0855;
/* 0856 */	BSP_DRIVER	uint32_t *	reserved0856;
/* 0857 */	BSP_DRIVER	uint32_t *	reserved0857;
/* 0858 */	BSP_DRIVER	uint32_t *	reserved0858;
/* 0859 */	BSP_DRIVER	uint32_t *	reserved0859;

/* 0860 */	BSP_DRIVER	uint32_t *	reserved0860;
/* 0861 */	BSP_DRIVER	uint32_t *	reserved0861;
/* 0862 */	BSP_DRIVER	uint32_t *	reserved0862;
/* 0863 */	BSP_DRIVER	uint32_t *	reserved0863;
/* 0864 */	BSP_DRIVER	uint32_t *	reserved0864;
/* 0865 */	BSP_DRIVER	uint32_t *	reserved0865;
/* 0866 */	BSP_DRIVER	uint32_t *	reserved0866;
/* 0867 */	BSP_DRIVER	uint32_t *	reserved0867;
/* 0868 */	BSP_DRIVER	uint32_t *	reserved0868;
/* 0869 */	BSP_DRIVER	uint32_t *	reserved0869;

/* 0870 */	BSP_DRIVER	uint32_t *	reserved0870;
/* 0871 */	BSP_DRIVER	uint32_t *	reserved0871;
/* 0872 */	BSP_DRIVER	uint32_t *	reserved0872;
/* 0873 */	BSP_DRIVER	uint32_t *	reserved0873;
/* 0874 */	BSP_DRIVER	uint32_t *	reserved0874;
/* 0875 */	BSP_DRIVER	uint32_t *	reserved0875;
/* 0876 */	BSP_DRIVER	uint32_t *	reserved0876;
/* 0877 */	BSP_DRIVER	uint32_t *	reserved0877;
/* 0878 */	BSP_DRIVER	uint32_t *	reserved0878;
/* 0879 */	BSP_DRIVER	uint32_t *	reserved0879;

/* 0880 */	BSP_DRIVER	uint32_t *	reserved0880;
/* 0881 */	BSP_DRIVER	uint32_t *	reserved0881;
/* 0882 */	BSP_DRIVER	uint32_t *	reserved0882;
/* 0883 */	BSP_DRIVER	uint32_t *	reserved0883;
/* 0884 */	BSP_DRIVER	uint32_t *	reserved0884;
/* 0885 */	BSP_DRIVER	uint32_t *	reserved0885;
/* 0886 */	BSP_DRIVER	uint32_t *	reserved0886;
/* 0887 */	BSP_DRIVER	uint32_t *	reserved0887;
/* 0888 */	BSP_DRIVER	uint32_t *	reserved0888;
/* 0889 */	BSP_DRIVER	uint32_t *	reserved0889;

/* 0890 */	BSP_DRIVER	uint32_t *	reserved0890;
/* 0891 */	BSP_DRIVER	uint32_t *	reserved0891;
/* 0892 */	BSP_DRIVER	uint32_t *	reserved0892;
/* 0893 */	BSP_DRIVER	uint32_t *	reserved0893;
/* 0894 */	BSP_DRIVER	uint32_t *	reserved0894;
/* 0895 */	BSP_DRIVER	uint32_t *	reserved0895;
/* 0896 */	BSP_DRIVER	uint32_t *	reserved0896;
/* 0897 */	BSP_DRIVER	uint32_t *	reserved0897;
/* 0898 */	BSP_DRIVER	uint32_t *	reserved0898;
/* 0899 */	BSP_DRIVER	uint32_t *	reserved0899;

/* 0900 */	BSP_DRIVER	uint32_t *	reserved0900;
/* 0901 */	BSP_DRIVER	uint32_t *	reserved0901;
/* 0902 */	BSP_DRIVER	uint32_t *	reserved0902;
/* 0903 */	BSP_DRIVER	uint32_t *	reserved0903;
/* 0904 */	BSP_DRIVER	uint32_t *	reserved0904;
/* 0905 */	BSP_DRIVER	uint32_t *	reserved0905;
/* 0906 */	BSP_DRIVER	uint32_t *	reserved0906;
/* 0907 */	BSP_DRIVER	uint32_t *	reserved0907;
/* 0908 */	BSP_DRIVER	uint32_t *	reserved0908;
/* 0909 */	BSP_DRIVER	uint32_t *	reserved0909;

/* 0910 */	BSP_DRIVER	uint32_t *	reserved0910;
/* 0911 */	BSP_DRIVER	uint32_t *	reserved0911;
/* 0912 */	BSP_DRIVER	uint32_t *	reserved0912;
/* 0913 */	BSP_DRIVER	uint32_t *	reserved0913;
/* 0914 */	BSP_DRIVER	uint32_t *	reserved0914;
/* 0915 */	BSP_DRIVER	uint32_t *	reserved0915;
/* 0916 */	BSP_DRIVER	uint32_t *	reserved0916;
/* 0917 */	BSP_DRIVER	uint32_t *	reserved0917;
/* 0918 */	BSP_DRIVER	uint32_t *	reserved0918;
/* 0919 */	BSP_DRIVER	uint32_t *	reserved0919;

/* 0920 */	BSP_DRIVER	uint32_t *	reserved0920;
/* 0921 */	BSP_DRIVER	uint32_t *	reserved0921;
/* 0922 */	BSP_DRIVER	uint32_t *	reserved0922;
/* 0923 */	BSP_DRIVER	uint32_t *	reserved0923;
/* 0924 */	BSP_DRIVER	uint32_t *	reserved0924;
/* 0925 */	BSP_DRIVER	uint32_t *	reserved0925;
/* 0926 */	BSP_DRIVER	uint32_t *	reserved0926;
/* 0927 */	BSP_DRIVER	uint32_t *	reserved0927;
/* 0928 */	BSP_DRIVER	uint32_t *	reserved0928;
/* 0929 */	BSP_DRIVER	uint32_t *	reserved0929;

/* 0930 */	BSP_DRIVER	uint32_t *	reserved0930;
/* 0931 */	BSP_DRIVER	uint32_t *	reserved0931;
/* 0932 */	BSP_DRIVER	uint32_t *	reserved0932;
/* 0933 */	BSP_DRIVER	uint32_t *	reserved0933;
/* 0934 */	BSP_DRIVER	uint32_t *	reserved0934;
/* 0935 */	BSP_DRIVER	uint32_t *	reserved0935;
/* 0936 */	BSP_DRIVER	uint32_t *	reserved0936;
/* 0937 */	BSP_DRIVER	uint32_t *	reserved0937;
/* 0938 */	BSP_DRIVER	uint32_t *	reserved0938;
/* 0939 */	BSP_DRIVER	uint32_t *	reserved0939;

/* 0940 */	BSP_DRIVER	uint32_t *	reserved0940;
/* 0941 */	BSP_DRIVER	uint32_t *	reserved0941;
/* 0942 */	BSP_DRIVER	uint32_t *	reserved0942;
/* 0943 */	BSP_DRIVER	uint32_t *	reserved0943;
/* 0944 */	BSP_DRIVER	uint32_t *	reserved0944;
/* 0945 */	BSP_DRIVER	uint32_t *	reserved0945;
/* 0946 */	BSP_DRIVER	uint32_t *	reserved0946;
/* 0947 */	BSP_DRIVER	uint32_t *	reserved0947;
/* 0948 */	BSP_DRIVER	uint32_t *	reserved0948;
/* 0949 */	BSP_DRIVER	uint32_t *	reserved0949;

/* 0950 */	BSP_DRIVER	uint32_t *	reserved0950;
/* 0951 */	BSP_DRIVER	uint32_t *	reserved0951;
/* 0952 */	BSP_DRIVER	uint32_t *	reserved0952;
/* 0953 */	BSP_DRIVER	uint32_t *	reserved0953;
/* 0954 */	BSP_DRIVER	uint32_t *	reserved0954;
/* 0955 */	BSP_DRIVER	uint32_t *	reserved0955;
/* 0956 */	BSP_DRIVER	uint32_t *	reserved0956;
/* 0957 */	BSP_DRIVER	uint32_t *	reserved0957;
/* 0958 */	BSP_DRIVER	uint32_t *	reserved0958;
/* 0959 */	BSP_DRIVER	uint32_t *	reserved0959;

/* 0960 */	BSP_DRIVER	uint32_t *	reserved0960;
/* 0961 */	BSP_DRIVER	uint32_t *	reserved0961;
/* 0962 */	BSP_DRIVER	uint32_t *	reserved0962;
/* 0963 */	BSP_DRIVER	uint32_t *	reserved0963;
/* 0964 */	BSP_DRIVER	uint32_t *	reserved0964;
/* 0965 */	BSP_DRIVER	uint32_t *	reserved0965;
/* 0966 */	BSP_DRIVER	uint32_t *	reserved0966;
/* 0967 */	BSP_DRIVER	uint32_t *	reserved0967;
/* 0968 */	BSP_DRIVER	uint32_t *	reserved0968;
/* 0969 */	BSP_DRIVER	uint32_t *	reserved0969;

/* 0970 */	BSP_DRIVER	uint32_t *	reserved0970;
/* 0971 */	BSP_DRIVER	uint32_t *	reserved0971;
/* 0972 */	BSP_DRIVER	uint32_t *	reserved0972;
/* 0973 */	BSP_DRIVER	uint32_t *	reserved0973;
/* 0974 */	BSP_DRIVER	uint32_t *	reserved0974;
/* 0975 */	BSP_DRIVER	uint32_t *	reserved0975;
/* 0976 */	BSP_DRIVER	uint32_t *	reserved0976;
/* 0977 */	BSP_DRIVER	uint32_t *	reserved0977;
/* 0978 */	BSP_DRIVER	uint32_t *	reserved0978;
/* 0979 */	BSP_DRIVER	uint32_t *	reserved0979;

/* 0980 */	BSP_DRIVER	uint32_t *	reserved0980;
/* 0981 */	BSP_DRIVER	uint32_t *	reserved0981;
/* 0982 */	BSP_DRIVER	uint32_t *	reserved0982;
/* 0983 */	BSP_DRIVER	uint32_t *	reserved0983;
/* 0984 */	BSP_DRIVER	uint32_t *	reserved0984;
/* 0985 */	BSP_DRIVER	uint32_t *	reserved0985;
/* 0986 */	BSP_DRIVER	uint32_t *	reserved0986;
/* 0987 */	BSP_DRIVER	uint32_t *	reserved0987;
/* 0988 */	BSP_DRIVER	uint32_t *	reserved0988;
/* 0989 */	BSP_DRIVER	uint32_t *	reserved0989;

/* 0990 */	BSP_DRIVER	uint32_t *	reserved0990;
/* 0991 */	BSP_DRIVER	uint32_t *	reserved0991;
/* 0992 */	BSP_DRIVER	uint32_t *	reserved0992;
/* 0993 */	BSP_DRIVER	uint32_t *	reserved0993;
/* 0994 */	BSP_DRIVER	uint32_t *	reserved0994;
/* 0995 */	BSP_DRIVER	uint32_t *	reserved0995;
/* 0996 */	BSP_DRIVER	uint32_t *	reserved0996;
/* 0997 */	BSP_DRIVER	uint32_t *	reserved0997;
/* 0998 */	BSP_DRIVER	uint32_t *	reserved0998;
/* 0999 */	BSP_DRIVER	uint32_t *	reserved0999;

/* 1000 */	BSP_DRIVER	uint32_t *	reserved1000;
/* 1001 */	BSP_DRIVER	uint32_t *	reserved1001;
/* 1002 */	BSP_DRIVER	uint32_t *	reserved1002;
/* 1003 */	BSP_DRIVER	uint32_t *	reserved1003;
/* 1004 */	BSP_DRIVER	uint32_t *	reserved1004;
/* 1005 */	BSP_DRIVER	uint32_t *	reserved1005;
/* 1006 */	BSP_DRIVER	uint32_t *	reserved1006;
/* 1007 */	BSP_DRIVER	uint32_t *	reserved1007;
/* 1008 */	BSP_DRIVER	uint32_t *	reserved1008;
/* 1009 */	BSP_DRIVER	uint32_t *	reserved1009;

/* 1010 */	BSP_DRIVER	uint32_t *	reserved1010;
/* 1011 */	BSP_DRIVER	uint32_t *	reserved1011;
/* 1012 */	BSP_DRIVER	uint32_t *	reserved1012;
/* 1013 */	BSP_DRIVER	uint32_t *	reserved1013;
/* 1014 */	BSP_DRIVER	uint32_t *	reserved1014;
/* 1015 */	BSP_DRIVER	uint32_t *	reserved1015;
/* 1016 */	BSP_DRIVER	uint32_t *	reserved1016;
/* 1017 */	BSP_DRIVER	uint32_t *	reserved1017;
/* 1018 */	BSP_DRIVER	uint32_t *	reserved1018;
/* 1019 */	BSP_DRIVER	uint32_t *	reserved1019;

/* 1020 */	BSP_DRIVER	uint32_t *	reserved1020;
/* 1021 */	BSP_DRIVER	uint32_t *	reserved1021;
/* 1022 */	BSP_DRIVER	uint32_t *	reserved1022;
/* 1023 */	BSP_DRIVER	uint32_t *	reserved1023;

#endif /* BSP_DRIVER_H_ */
