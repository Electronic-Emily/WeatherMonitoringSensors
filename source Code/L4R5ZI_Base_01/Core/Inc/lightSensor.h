/*
 * lightSensor.h
 *
 *  Created on: Sep 19, 2021
 *      Author: emily
 */

#ifndef INC_LIGHTSENSOR_H_
#define INC_LIGHTSENSOR_H_

#include "stdint.h"

#define VEML6035_ADD 0x52

//VEML6035 Command Registers
#define VEML_CMD__CONFIG_REG	0x00
#define VEML_CMD__WINDOW_HIGH	0x01
#define VEML_CMD__WINDOW_LOW	0x02
#define VEML_CMD__PSM			0x03
#define VEML_CMD__ALS_VAL		0x04
#define VEML_CMD__WHITE_VAL		0x05
#define VEML_CMD__INT_THLD		0x06

//Config Register 0x00 MASKs
#define VEML__SENS_Pos		12
#define VEML__SENS_Msk		0b1 << VEML__SENS_Pos
#define VEML__DG_Pos		11
#define VEML__DG_Msk		0b1 << VEML__DG_Pos
#define VEML__GAIN_Pos		10
#define VEML__GAIN_Msk		0b1 << VEML__GAIN_Pos
#define VEML__ALS_IT_Pos	6
#define VEML__ALS_IT_Msk	0b1111 << VEML__ALS_IT_Pos
#define VEML__ALS_PERS_Pos	4
#define VEML__ALS_PERS_Msk	0b11 << VEML__ALS_PERS_Pos
#define VEML__INT_CH_Pos	3
#define VEML__INT_CH_Msk	0b1 << VEML__INT_CH_Pos
#define VEML__CH_EN_Pos		2
#define VEML__CH_EN_Msk		0b1 << VEML__CH_EN_Pos
#define VEML__INT_EN_Pos	1
#define VEML__INT_EN_Msk	0b1 << VEML__INT_EN_Pos
#define VEML__SD_Pos		0
#define VEML__SD_Msk		0b1 << VEML__SD_Pos

//Power Safe Mode Reg. 0x03
#define VEML__PSM_WAIT_Pos	1
#define VEML__PSM_WAIT_Msk	0b11 << VEML__PSM_WAIT_Pos

#define VEML__PSM_EN_Pos	0
#define VEML__PSM_EN_Msk	0b1 << VEML__PSM_EN_Pos

//Interrupt Status Reg. 0x06
#define VEML__LOW_THLD_Pos	15
#define VEML__LOW_THLD_Msk	0b1 << VEML__LOW_THLD_Pos
#define VEML__HIGH_THLD_Pos	14
#define VEML__HIGH_THLD_MSK	0b1 << VEML__HIGH_THLD_Pos



void Init_LightSensor();
void Get_Brightness(uint16_t* value);

#endif /* INC_LIGHTSENSOR_H_ */
