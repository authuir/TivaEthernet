/*
 * TFT.h
 *
 *  Created on: 2015-8-6
 *      Author: Authuir
 */

#ifndef TFT_H_
#define TFT_H_

#define TFT_DC_0
#define TFT_DC_1

#define TFT_RST_0
#define TFT_RST_1

#define NUM_SSI_DATA 256

void Init_TFT();
void LCD_WR_REG(uint16_t regval);

#endif /* TFT_H_ */
