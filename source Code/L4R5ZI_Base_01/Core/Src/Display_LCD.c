/*
 * Display_LCD.c
 *
 *  Created on: Sep 3, 2021
 *      Author: emily
 */

#include "Display_LCD.h"
#include "GPIO_Expander.h"
#include <string.h>
#include "math.h"
#include "stdlib.h"
extern SPI_HandleTypeDef hspi1;
extern Direction g_Disp_Direction;

#define X_MIN 0x0000
#define X_MAX 0x01DF
#define Y_MIN 0x0000
#define Y_MAX 0x013F

#define INT32_FLIP(number) ((number&0xFF)<<24)|((number&0xFF00)<<8)|((number&0xFF0000)>>8)|((number&0xFF000000)>>24)
#define ARROW_DELAY 500


#define ARROW_COLOR 	COLOR_BLUE
#define X_WINDOW 		160
#define X__MAX			X_ORG + X_WINDOW
#define X_WIND_CENT 	X_ORG + ( X_WINDOW/2 )
#define Y_WINDOW 		160
#define Y__MAX 			Y_ORG + Y_WINDOW
#define Y_WIND_CENT		Y_ORG + ( Y_WINDOW /2 )

#define X_ORG 			60
#define Y_ORG 			(320-Y_WINDOW)/2
#define LINE_THICK 		10


void InitSystem_Display(){
	//Set up CS and C/D pin in unactive state
	HAL_GPIO_WritePin(GPIOE, LCD_CS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, DATA_CMD_LCD_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	//-----------------------------------------------------

	SendCommand(SW_RESET);

	uint8_t ext_array[3] = {0xFF,0x83,0x57};
	SendCommand(SET_EXT_CMD);
	SendData(&ext_array[0],3);

	uint8_t inter_array[4] = {0x80,0x00,0x06,0x06};
	SendCommand(SET_RGB_INTER);
	SendData(&inter_array[0],4);

	uint8_t vcom_array[1] = {0x25};
	SendCommand(SET_VCOM);
	SendData(&vcom_array[0],1);

	uint8_t osc_array[1] = {0x68};
	SendCommand(SET_OSC);
	SendData(&osc_array[0],1);

	uint8_t panel_array[1] = {0x05};
	SendCommand(SET_PANEL);
	SendData(&panel_array[0],1);

	uint8_t pwr_ctrl_array[6] = {0x00, 0x15, 0x1C, 0x1C, 0x83, 0xAA};
	SendCommand(SET_PWR_CTRL);
	SendData(&pwr_ctrl_array[0],6);

	uint8_t source_array[6] = {0x50, 0x50, 0x01, 0x3C, 0x1E, 0x08};
	SendCommand(SET_SOURCE_OPT);
	SendData(&source_array[0],6);

	uint8_t disp_cycle_array[7] = {0x02, 0x40, 0x00, 0x2A, 0x2A, 0x0D, 0x78};
	SendCommand(SET_DISP_CYCLE);
	SendData(&disp_cycle_array[0],7);

	uint8_t gamma_array[34] =
	{0x02,0x0A,0x11,0x1D,0x23,0x35,0x41,0x4B,0x4B,0x42,0x3A,0x27,0x1B,0x08,0x09,0x03,0x02,0x0A,0x11,0x1D,0x23,0x35,0x41,0x4B,0x4B,0x42,0x3A,0x27,0x1B,0x08,0x09,0x03,0x00,0x01};
	SendCommand(SET_GAMMA_CURV);
	SendData(&gamma_array[0],34);

	uint8_t pixel_inter_array[1] = {0x55};
	SendCommand(INTR_PIX_FORM);
	SendData(&pixel_inter_array[0],1);

	uint8_t mem_acc_array[1] = {0xC0};
	SendCommand(MEM_ACC_CTRL);
	SendData(&mem_acc_array[0],1);

	uint8_t line_t_array[1] = {0x00};
	SendCommand(TEAR_LINE_ON);
	SendData(&line_t_array[0],1);

	uint8_t set_tear_array[2] = {0x00,0x02};
	SendCommand(SET_TEAR_LINE);
	SendData(&set_tear_array[0],2);
	HAL_Delay(10);
	SendCommand(SLEEP_OUT);
	HAL_Delay(10);
	SendCommand(DISP_ON);
	HAL_Delay(10);
	uint8_t mem_array[1] = {0xA0};
	SendCommand(MEM_ACC_CTRL);
	SendData(&mem_array[0],1);

	//-------------------------------------------
	HAL_Delay(4);
	Fill_Display(COLOR_LIGHTBLUE);
	//PartialFill(YELLOW,10,100,10,2);
	//Draw_Picture(GREEN,100,24,100,24,&NORTH_COMP_24[0][0]);
	//Draw_Line(YELLOW, 10, 10, 300,300,5);


	Test_All_Arrows();


	//Draw_Mag_Pic(2, GREEN, 200, 12, 200, 12, &NORTH_COMP[0][0]);
	//Draw_Mag_Pic(2, GREEN, 200, 5, 200, 5, &SQUR_LINE[0][0]);
	//-----------------------------------------------------
}


void Update_Dir_Display(uint8_t dir){

	Delete_Arrow(g_Disp_Direction);
	g_Disp_Direction = NONE;

	switch(dir){
	case (uint8_t)COMPASS_N:
		g_Disp_Direction = NORTH;
		break;
	case COMPASS_NE:
		g_Disp_Direction = NORTH_EAST;
		break;
	case COMPASS_E:
		g_Disp_Direction = EAST;
		break;
	case COMPASS_SE:
		g_Disp_Direction = SOUTH_EAST;
		break;
	case COMPASS_S:
		g_Disp_Direction = SOUTH;
		break;
	case COMPASS_SW:
		g_Disp_Direction = SOUTH_WEST;
		break;
	case COMPASS_W:
		g_Disp_Direction = WEST;
		break;
	case COMPASS_NW:
		g_Disp_Direction = NORTH_WEST;
		break;
	}
	Draw_Arrow(g_Disp_Direction);
}

void Arrow_Demo(){
	Draw_Arrow(NORTH);
	HAL_Delay(ARROW_DELAY);
	Delete_Arrow(NORTH);

	Draw_Arrow(NORTH_EAST);
	HAL_Delay(ARROW_DELAY);
	Delete_Arrow(NORTH_EAST);

	Draw_Arrow(EAST);
	HAL_Delay(ARROW_DELAY);
	Delete_Arrow(EAST);

	Draw_Arrow(SOUTH_EAST);
	HAL_Delay(ARROW_DELAY);
	Delete_Arrow(SOUTH_EAST);

	Draw_Arrow(SOUTH);
	HAL_Delay(ARROW_DELAY);
	Delete_Arrow(SOUTH);

	Draw_Arrow(SOUTH_WEST);
	HAL_Delay(ARROW_DELAY);
	Delete_Arrow(SOUTH_WEST);

	Draw_Arrow(WEST);
	HAL_Delay(ARROW_DELAY);
	Delete_Arrow(WEST);

	Draw_Arrow(NORTH_WEST);
	HAL_Delay(ARROW_DELAY);
	Delete_Arrow(NORTH_WEST);
}



//Print all arrows at the same time then erase them
//used as start-up demo
void Test_All_Arrows(){
	Draw_Arrow(NORTH);
	Draw_Arrow(NORTH_EAST);
	Draw_Arrow(EAST);
	Draw_Arrow(SOUTH_EAST);
	Draw_Arrow(SOUTH);
	Draw_Arrow(SOUTH_WEST);
	Draw_Arrow(WEST);
	Draw_Arrow(NORTH_WEST);
	HAL_Delay(1000);
	Delete_Arrow(NORTH);
	Delete_Arrow(NORTH_EAST);
	Delete_Arrow(EAST);
	Delete_Arrow(SOUTH_EAST);
	Delete_Arrow(SOUTH);
	Delete_Arrow(SOUTH_WEST);
	Delete_Arrow(WEST);
	Delete_Arrow(NORTH_WEST);
}

//Draw an arrow in the color not equal to the background.
void Draw_Arrow(Direction dir){
	Print_Arrow(dir, ARROW_COLOR);
}

//Erase arrow by re-drawing it but using the background color
void Delete_Arrow(Direction dir){
	Print_Arrow(dir, BACKGROUND_COLOR);
}



//Function that will draw an arrow
//Can be used to erase or draw one, based on what color you use.
void Print_Arrow(Direction dir, uint16_t color){
switch(dir){
case NORTH:
	//MAIN
	PartialFill(color, X_WIND_CENT-(LINE_THICK/2), LINE_THICK, Y_ORG ,Y_WINDOW);
	Draw_Line(X_WIND_CENT-30, Y__MAX-30, color,  X_WIND_CENT, Y__MAX, 8);
	Draw_Line(X_WIND_CENT+30, Y__MAX-30, color,  X_WIND_CENT, Y__MAX, 8);
	break;
case NORTH_EAST:
	Draw_Line(X_ORG+25, Y_ORG+25, color,  X__MAX-25, Y__MAX-25, 8);
	//Horizontal
	PartialFill(color,X__MAX-25-40 , 40 , Y__MAX-25 -(LINE_THICK/2), LINE_THICK);
	//Vertical
	PartialFill(color,X__MAX-25 -(LINE_THICK/2) , LINE_THICK , Y__MAX-25-40 , 40);
	break;
case EAST:
	PartialFill(color, X_ORG, X_WINDOW, Y_WIND_CENT-(LINE_THICK/2), LINE_THICK);
	Draw_Line(X__MAX, Y_WIND_CENT, color, X__MAX-30, Y_WIND_CENT+30, 8);
	Draw_Line(X__MAX, Y_WIND_CENT, color, X__MAX-30, Y_WIND_CENT-30, 8);
	break;
case SOUTH_EAST:
	Draw_Line(X_ORG+25, Y__MAX-25, color,  X__MAX-25, Y_ORG+25, 8);
	//Horizontal
	PartialFill(color,X__MAX-25-40, 40 , Y_ORG+25 -(LINE_THICK/2), LINE_THICK);
	//Vertical
	PartialFill(color,X__MAX-25 -(LINE_THICK/2) , LINE_THICK , Y_ORG+25, 40);
	break;
case SOUTH:
	PartialFill(color, X_WIND_CENT-(LINE_THICK/2), LINE_THICK, Y_ORG ,Y_WINDOW);
	Draw_Line(X_WIND_CENT-30, Y_ORG+30, color,  X_WIND_CENT, Y_ORG, 8);
	Draw_Line(X_WIND_CENT+30, Y_ORG+30, color,  X_WIND_CENT, Y_ORG, 8);
	break;
case SOUTH_WEST:
	Draw_Line(X_ORG+25, Y_ORG+25, color,  X__MAX-25, Y__MAX-25, 8);
	PartialFill(color,X_ORG+25 , 40 , Y_ORG+25 - (LINE_THICK/2)-1, LINE_THICK);
	PartialFill(color,X_ORG+25-(LINE_THICK/2)-1,LINE_THICK ,Y_ORG+25, 40);// LINE_THICK , Y__MAX-25-40 , 40);
	break;
case WEST:
	PartialFill(color, X_ORG, X_WINDOW, Y_WIND_CENT-(LINE_THICK/2), LINE_THICK);
	Draw_Line(X_ORG, Y_WIND_CENT, color, X_ORG+30, Y_WIND_CENT+30, 8);
	Draw_Line(X_ORG, Y_WIND_CENT, color, X_ORG+30, Y_WIND_CENT-30, 8);
	break;
case NORTH_WEST:
	Draw_Line(X_ORG+25, Y__MAX-25, color,  X__MAX-25, Y_ORG+25, 8);
	PartialFill(color, X_ORG+25-(LINE_THICK/2)-1, LINE_THICK ,Y__MAX-25-40, 40);
	PartialFill(color,X_ORG+25 , 40 , Y__MAX-25 - (LINE_THICK/2)+1, LINE_THICK);
	break;
default:
	break;
}
}



//Draw a line with two points
void Draw_Line( uint16_t x1, uint16_t y1, uint16_t color, uint16_t x2,uint16_t y2, uint16_t width){
	int16_t x_range = x2-x1;
	int16_t y_range = y2-y1;

	float slope = y_range/x_range;
	float B = -(slope*x1) + y1;

	x_range = abs(x_range);
	y_range = abs(y_range);

	for(int i = 0; i < x_range; i++){
		//SET Coordinates
		uint16_t YY;
		if(x1<x2){
			YY = (x1+i)*slope + B;
			PartialFill(color, (x1+i)-(width/2) , width, YY-(width/2) , width);
		}
		else{
			YY = (x2+i)*slope + B;
			PartialFill(color, (x2+i)-(width/2) , width, YY-(width/2) , width);
		}
	}
}




//Set the Min for both X and Y coordinates on the Display.
//the Max for each axis is the display's MAX value
void SetDarw_Coordates(uint16_t x_min, uint16_t y_min){
	uint32_t columnVal,pageVal;
	columnVal 	= (uint32_t)INT32_FLIP( (uint32_t)((x_min<<16)|(X_MAX)) );
	pageVal 	= (uint32_t)INT32_FLIP( (uint32_t)((y_min<<16)|(Y_MAX)) );

	SendCommand(COL_ADD_SET);
	SendData_NoCS_8((uint8_t*)&columnVal,4);

	SendCommand(PAGE_ADD_SET);
	SendData_NoCS_8((uint8_t*)&pageVal,4);
}


//Pointing to the Bottom Left of the Rectangle
void PartialFill(uint16_t color, uint16_t x_min, uint16_t x_length, uint16_t y_min, uint16_t y_length){
	uint32_t columnVal,pageVal;

	uint16_t pic_size = (x_length)*(y_length);
	uint16_t pic_array[pic_size];

	//Verify bounds
	if((x_min + x_length)-1 > X_MAX){
		return; // Error Out of Bounds
	}
	if((y_min + y_length)-1 > Y_MAX){
		return; // Error Out of Bounds
	}

	columnVal 	= (uint32_t)INT32_FLIP( (uint32_t)((x_min<<16)|(x_min + x_length-1)) );
	pageVal 	= (uint32_t)INT32_FLIP( (uint32_t)((y_min<<16)|(y_min + y_length-1)) );


	for(int i = 0; i < pic_size; i++){
			pic_array[i] =  color;
	}

	SendCommand(COL_ADD_SET);
	SendData_NoCS_8((uint8_t*)&columnVal,4);

	SendCommand(PAGE_ADD_SET);
	SendData_NoCS_8((uint8_t*)&pageVal,4);

	SendCommand(RAM_WRITE);
	SendData_NoCS_16(&pic_array[0], pic_size);

	HAL_GPIO_WritePin(GPIOE, LCD_CS_Pin, GPIO_PIN_SET);
}

void Fill_Display(uint16_t color){
	//320 x 480
	uint8_t col_array[4] = {0x00,0x00,0x01,0xDF};
	uint8_t page_array[4] = {0x00,0x00,0x01,0x3F};

	uint16_t second_Array[HOR_PIXEL];
	for(int i = 0; i < HOR_PIXEL; i++){
		second_Array[i] = color;
	}

	SendCommand(COL_ADD_SET);
	SendData_NoCS_8(&col_array[0],4);

	HAL_Delay(1);

	SendCommand(PAGE_ADD_SET);
	SendData_NoCS_8(&page_array[0],4);

	HAL_Delay(1);

	SendCommand(RAM_WRITE);
	for(int y = 0; y < VER_PIXEL; y++){
			SendData_NoCS_16(&second_Array[0], HOR_PIXEL);
	}
	HAL_GPIO_WritePin(GPIOE, LCD_CS_Pin, GPIO_PIN_SET);
}

//Send SPI uint8_t and RESET C/D pin (indicate that its a cmd)
void SendCommand(uint8_t value){
	uint8_t stuff = value;
	HAL_GPIO_WritePin(GPIOE, LCD_CS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, DATA_CMD_LCD_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, &stuff, 1, 100);
	HAL_GPIO_WritePin(GPIOE, DATA_CMD_LCD_Pin, GPIO_PIN_SET);
}



//Send SPI uint8_t data without the Chip Select at the end of transmission
void SendData_NoCS_8(uint8_t* data, uint16_t length){
	HAL_SPI_Transmit(&hspi1, data, length, 100);
	HAL_GPIO_WritePin(GPIOE, DATA_CMD_LCD_Pin, GPIO_PIN_SET);
}


//Send SPI uint16_t data without the Chip Select at the end of transmission
void SendData_NoCS_16(uint16_t* data, uint16_t length){
	HAL_SPI_Transmit(&hspi1, (uint8_t*)data, length*2, 100);
	//HAL_GPIO_WritePin(GPIOE, DATA_CMD_LCD_Pin, GPIO_PIN_SET);
}

//Send SPI data then SET Chip Select pin high
void SendData(uint8_t* data, uint8_t length){
	HAL_SPI_Transmit(&hspi1, data, length, 100);
	HAL_GPIO_WritePin(GPIOE, DATA_CMD_LCD_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, LCD_CS_Pin, GPIO_PIN_SET);
}



//===========================================================================

//Draw a picture based on a bitmap
void Draw_Picture(uint16_t color, uint16_t x, uint16_t x_length, uint16_t y, uint16_t y_length, uint8_t* array){
	uint32_t columnVal,pageVal;

	uint16_t pic_size = (x_length)*(y_length);
	uint16_t pic_array[pic_size];

	//Verify bounds
	if((x + x_length)-1 > X_MAX){
		return; // Error Out of Bounds
	}
	if((y + y_length)-1 > Y_MAX){
		return; // Error Out of Bounds
	}

	columnVal 	= (uint32_t)INT32_FLIP( (uint32_t)((x<<16) | (x + x_length-1)) );
	pageVal 	= (uint32_t)INT32_FLIP( (uint32_t)((y<<16) | (y + y_length-1)) );

	for(int i = 0; i < pic_size; i++){
			if( *(array+i) == 1){
				pic_array[i] =  BACKGROUND_COLOR;
			}else{
				pic_array[i] =  color;
			}
	}

	SendCommand(COL_ADD_SET);
	SendData_NoCS_8((uint8_t*)&columnVal,4);

	SendCommand(PAGE_ADD_SET);
	SendData_NoCS_8((uint8_t*)&pageVal,4);

	SendCommand(RAM_WRITE);
	SendData_NoCS_16(&pic_array[0], pic_size);

	HAL_GPIO_WritePin(GPIOE, LCD_CS_Pin, GPIO_PIN_SET);
}
