/*
 * Display_LCD.h
 *
 *  Created on: Sep 3, 2021
 *      Author: emily
 */
/*
PINOUT
CLK		-->
MISO	-->
MOSI	-->
CS		-->	ChipSelect
D/C		--> DATA/CMD
Lite	--> Backlight

Pull Lite line low to turn off the backlight
//COMMAND is 0
//Parameter is 1

*/
#ifndef INC_DISPLAY_LCD_H_
#define INC_DISPLAY_LCD_H_

#include "stdint.h"
#include "main.h"

#define HOR_PIXEL 480
#define VER_PIXEL 320

//-----------------------------------------------------------------------
#define NOP 			0x00	//Empty CMD
#define SW_RESET		0x01	//Software Reset
#define RD_D_IDIF		0x04	//Read Disp. ID Information
#define RD_NUMPE		0x05	//Read Number of the Errors on DSI
#define RD_RED			0x06	//Read Red Color
#define RD_GREEN		0x07	//Read Green Color
#define RD_BLUE			0x08	//Read Blue Color
#define RD_DPM			0x0A	//Read Disp. Power Mode
#define RD_MADCTL		0x0B	//Read Disp. Page/Column/Line order (Top/bottom Left/Right)
#define RD_DCOLMOD		0x0C	//Read Disp. DPI and DBI interface Pixel Format
#define RD_DIM			0x0D	//Read Disp. Image Mode
#define RD_DSM			0x0E	//Read Disp. Signal Mode
#define RD_DSDR			0x0F	//Read Disp. Self-Diagnostic Result
#define SLEEP_IN		0x10	//Sleep In
#define SLEEP_OUT		0x11	//Sleep Out
#define PARTIAL_ON		0x12	//Partial Mode On
#define NOR_ON			0x13	//Normal Display Mode ON
#define INV_OFF			0x20	//Disp. Inversion Off
#define INV_ON			0x21	//Disp. Inversion ON
#define ALL_PIXEL_OFF	0x22	//All Pixel Off
#define ALL_PIXEL_ON	0x23	//All Pixel On
#define GAMMA_SET		0x26	//Gamma Set
#define DISP_OFF		0x28	//Display Off
#define DISP_ON			0x29	//Display On
#define COL_ADD_SET		0x2A	//Column Address Set
#define PAGE_ADD_SET	0x2B	//Page Address Set
#define RAM_WRITE		0x2C	//Memory Write
#define RAM_READ		0x2E	//Memory Read
#define PARTIAL_AREA	0x30	//Partial Area
#define VERT_SCROLL		0x33	//Vertical Scrolling Definition
#define TEAR_LINE_OFF	0x34	//Tearing Effect Line OFF
#define TEAR_LINE_ON	0x35	//Learing Effect Line ON
#define MEM_ACC_CTRL	0x36	//Memory Access Control
#define VERT_SCROLL_ST	0x37	//Vertical Scrolling Start Address
#define IDLE_MODE_OFF	0x38	//Idle Mode Off
#define IDLE_MODE_ON	0x39	//Idle Mode On
#define INTR_PIX_FORM	0x3A	//Interface Pixel Format
#define WRITE_MEM_CONT	0x3C	//Write Memory Continue
#define READ_MEM_CONT	0x3E	//Read Memory Continue
#define SET_TEAR_LINE	0x44	//Set tear scan line
#define GET_SCAN_LINE	0x45	//Mipi new get scan lines
#define SET_DISP_BRIGHT	0x51	//Write Display Brightness Value
#define GET_DISP_BRIGHT	0x52	//Read Display Brightness Value
#define WRITE_CTRL_DISP	0x53	//Write Control Display
#define READ_CTRL_DISP	0x54	//Read Control Display
#define WRITE_CONT_BRI	0x55	//Write content adaptive brightness control
#define READ_CONT_ABC	0x56	//Read Content adaptive Brightness control
#define WRITE_CABC_MIN	0x5E	//Write CABC minimum Brightness
#define READ_CABC_MIN	0x5F	//Read CABC minimum brightness
#define READ_ABC_SDR	0x68	//Read automatic brightness control self-diagnostic
#define READ_B_W_LOW	0x70	//Read Black/White Low Bits
#define READ_B_K_X		0x71	//
#define READ_B_K_Y		0x72	//
#define READ_W_X		0x73	//
#define	READ_W_Y		0x74	//
#define	READ_RED_GR_LOW	0x75	//
#define	READ_R_X		0x76	//
#define	READ_R_Y		0x77	//
#define	READ_G_X		0x78	//
#define	READ_G_Y		0x79	//
#define	RD_BLUE_AC_LOW	0x7A	//
#define	READ_B_X		0x7B	//
#define	READ_B_Y		0x7C	//
#define	READ_A_X		0x7D	//
#define	READ_A_Y		0x7E	//
#define	READ_DDB_START	0xA1	//
#define	READ_DDB_CONT	0xA8	//
#define	RD_FIRST_CK_SUM	0xAA	//
#define	RD_CONT_CK_SUM	0xAF	//
#define	READ_ID_1		0xDA	//
#define	READ_ID_2		0xDB	//
#define	READ_ID_3		0xDC	//
#define	SET_OSC			0xB0	//
#define	SET_PWR_CTRL	0xB1	//
#define	SET_DISP_REG	0xB2	//
#define	SET_RGB_INTER	0xB3	//
#define	SET_DISP_CYCLE	0xB4	//
#define	SET_BGP_VOLT	0xB5	//
#define	SET_VCOM		0xB6	//
#define	SET_OTP			0xB7	//
#define	SET_EXT_CMD		0xB9	//
#define	SET_SOURCE_OPT	0xC0	//
#define	SET_DIG_GAMMA	0xC1	//Digital Gamma Correction
#define	SET_ID			0xC3	//ID OTP
#define	SET_DDB			0xC4	//
#define	SET_CABC		0xC9	//
#define	SET_PANEL		0xCC	//Set Panel Characteristics
#define	SET_GAMMA_CURV	0xE0	//Set Gamma Curve
#define	SET_IMG_FUNC	0xE9	//Set Image Function
#define	SET_CMD_TYPE	0xEA	//Set Command Type
#define	SET_COLOR		0xEB	//
#define	SET_SPI_INDEX	0xFE	//Set SPI read index
#define	SPI_READ_CMD	0xFF	//SPI read command Data

#define	IC_READ_CMD		0xD0

#define COLOR_RED		0x1F00
#define COLOR_GREEN		0xE007
#define COLOR_LIGHTBLUE	0x07FF
#define COLOR_PINK		0xFFE0
#define COLOR_BLUE		0x07E0

#define BACKGROUND_COLOR COLOR_LIGHTBLUE

typedef enum
{
	NORTH,
	NORTH_EAST,
	EAST,
	SOUTH_EAST,
	SOUTH,
	SOUTH_WEST,
	WEST,
	NORTH_WEST,
	NONE
}Direction;



//-------------------------------------------------------------------------------------

void SendCommand(uint8_t value);
void SendData(uint8_t* data, uint8_t length);
void SendData_NoCS_8(uint8_t* data, uint16_t length);
void SendData_NoCS_16(uint16_t* data, uint16_t length);

void Fill_Display(uint16_t color);
void PartialFill(uint16_t color, uint16_t x_min, uint16_t x_length, uint16_t y_min, uint16_t y_length);

void Draw_Picture(uint16_t color, uint16_t x, uint16_t x_length, uint16_t y, uint16_t y_length, uint8_t* array);
void SetDarw_Coordates(uint16_t x_min, uint16_t y_min);
void Draw_Line(uint16_t x1, uint16_t y1, uint16_t color, uint16_t x2,uint16_t y2, uint16_t width);

void Update_Dir_Display(uint8_t dir);
void Test_All_Arrows();
void Arrow_Demo();
void Draw_Arrow(Direction dir);
void Delete_Arrow(Direction dir);
void Print_Arrow(Direction dir, uint16_t color);
void InitSystem_Display();

#endif /* INC_DISPLAY_LCD_H_ */
