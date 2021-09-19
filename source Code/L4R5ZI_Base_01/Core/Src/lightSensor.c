/*
 * lightSensor.c
 *
 *  Created on: Sep 19, 2021
 *      Author: emily
 *
 *      VEML6035 Light Sensor
 */

#include "lightSensor.h"
#include "main.h"

extern I2C_HandleTypeDef hi2c1;

void Init_LightSensor(){
	//Turn ON Light Sensor
	uint16_t tx = 0x0000;
	HAL_I2C_Mem_Write(&hi2c1, VEML6035_ADD, VEML_CMD__CONFIG_REG, 1, (uint8_t*)&tx, 2, 100);
}


//Read in brightness value from sensor
//TODO convert lux value
void Get_Brightness(uint16_t* value){
	uint8_t data[3] = {};
	//get Brightness from Light Sensor
	HAL_I2C_Mem_Read(&hi2c1, VEML6035_ADD, VEML_CMD__ALS_VAL, 1, (uint8_t*)&data, 2, 100);
	*value = (uint16_t)((data[1]<<8) | data[0]);
}



