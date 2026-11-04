#ifndef __SSD1306_H
#define __SSD1306_H
#include "main.h"
#include "i2c.h"

#define SSD1306_ADDR 0x78
#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64


extern uint8_t ssd1306_buf[1024];

extern I2C_HandleTypeDef hi2c1;

void SSD1306_Init(void);
void SSD1306_Clear(void);
void SSD1306_Refresh(void);
void SSD1306_DrawPoint(uint8_t x,uint8_t y,uint8_t set);
void SSD1306_WriteString(uint8_t x,uint8_t y,char *str);

void SSD1306_DrawHeart(void);

void SSD1306_DrawPic(uint8_t *buf);


#endif
