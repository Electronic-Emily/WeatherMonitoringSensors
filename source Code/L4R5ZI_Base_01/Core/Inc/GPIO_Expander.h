/*
 * GPIO_Expander.h
 *
 *  Created on: Aug 21, 2021
 *      Author: emily
 */

#ifndef INC_GPIO_EXPANDER_H_
#define INC_GPIO_EXPANDER_H_

#include "stdint.h"

#define SX1502_ADD			0x20
#define GPIO_IC_ADD			(SX1502_ADD << 1)

#define REG_DATA 			0x00
#define	REG_DIR				0x01
#define	REG_PULLUP			0x02
#define	REG_PULLDOWN		0x03
#define	REG_INTER_MASK		0x05
#define	REG_SENSE_HIGH		0x06
#define	REG_SENSE_LOW		0x07
#define	REG_INTER_SOURCE	0x08
#define REG_EVENT_STAT		0x09
#define	REG_PLD_MODE		0x10
#define	REG_PLD_TABLE_0		0x11
#define	REG_PLD_TABLE_1		0x12
#define	REG_PLD_TABLE_2		0x13
#define	REG_PLD_TABLE_3		0x14
#define	REG_PLD_TABLE_4		0x15
#define REG_ADVANCED		0xAB


#define COMPASS_N	0x10
#define	COMPASS_NE	0x20
#define COMPASS_E	0x40
#define COMPASS_SE	0x80
#define COMPASS_S	0x01
#define COMPASS_SW	0x02
#define COMPASS_W	0x04
#define COMPASS_NW	0x08

void Init_External_GPIO();
void ClearINT();
uint8_t ReadPinStatus();

#endif /* INC_GPIO_EXPANDER_H_ */
