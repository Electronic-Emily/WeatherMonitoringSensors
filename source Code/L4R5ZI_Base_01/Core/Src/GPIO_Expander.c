/*
 * GPIO_Expander.c
 *
 *  Created on: Aug 21, 2021
 *      Author: emily
 */

#include "GPIO_Expander.h"
#include "main.h"

extern I2C_HandleTypeDef hi2c2;

void Init_External_GPIO(){
	//Set Pins as INPUT
	uint8_t RX_data = 0xFF;
	HAL_I2C_Mem_Write(&hi2c2, GPIO_IC_ADD, REG_DIR ,1,&RX_data,1,100);

	//Pull-Up Disabled
	RX_data = 0x00;
	HAL_I2C_Mem_Write(&hi2c2, GPIO_IC_ADD, REG_PULLUP ,1,&RX_data,1,100);

	//PUll-Down Disabled
	RX_data = 0x00;
	HAL_I2C_Mem_Write(&hi2c2, GPIO_IC_ADD, REG_PULLDOWN ,1,&RX_data,1,100);

	//Disable the ISRs
	RX_data = 0x00; //Enable ISR on all pins//0xFF;
	HAL_I2C_Mem_Write(&hi2c2, GPIO_IC_ADD, REG_INTER_MASK ,1,&RX_data,1,100);

	//No Edge Sense (Rising/Falling/Both)
	RX_data = 0x55;//All Rising  //0x00;
	HAL_I2C_Mem_Write(&hi2c2, GPIO_IC_ADD, REG_SENSE_HIGH ,1,&RX_data,1,100);

	//No Edge Sense (Rising/Falling/Both)
	RX_data = 0x55;//All rising//0x00;
	HAL_I2C_Mem_Write(&hi2c2, GPIO_IC_ADD, REG_SENSE_LOW ,1,&RX_data,1,100);

	//RX_data =
	//HAL_I2C_Mem_Write(&hi2c2, GPIO_IC_ADD, REG_INTER_SOURCE ,1,&RX_data,1,100);

	//RX_data =
	//HAL_I2C_Mem_Write(&hi2c2, GPIO_IC_ADD, REG_INTER_SOURCE ,1,&RX_data,1,100);

	//RX_data =
	//HAL_I2C_Mem_Write(&hi2c2, GPIO_IC_ADD, REG_EVENT_STAT ,1,&RX_data,1,100);

	//RX_data =
	//HAL_I2C_Mem_Write(&hi2c2, GPIO_IC_ADD, REG_PLD_MODE ,1,&RX_data,1,100);

	ClearINT();
}

//Write to reg to clear all Interrupts
void ClearINT(){
	uint8_t RX_data = 0xFF;
	HAL_I2C_Mem_Write(&hi2c2, GPIO_IC_ADD, REG_INTER_SOURCE ,1,&RX_data,1,100);
}

//Read the status of each of the 8 pins
uint8_t ReadPinStatus(){
	uint8_t pins = 0;
	HAL_I2C_Mem_Read(&hi2c2, (0x20 << 1), 0x00, 1, &pins, 1, 20);
	return pins;
}


