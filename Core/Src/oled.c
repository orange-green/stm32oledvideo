#include "oled.h"
#include <string.h>
#include "math.h"


uint8_t ssd1306_buf[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

static void SSD1306_WriteCmd(uint8_t cmd)
{
    uint8_t buf[2] = {0x00, cmd};
    HAL_I2C_Mem_Write(&hi2c1, SSD1306_ADDR, 0x00, I2C_MEMADD_SIZE_8BIT, buf+1, 1, 100);
}

static void SSD1306_WriteData(uint8_t dat)
{
    uint8_t buf[2] = {0x40, dat};
    HAL_I2C_Mem_Write(&hi2c1, SSD1306_ADDR, 0x40, I2C_MEMADD_SIZE_8BIT, buf+1, 1, 100);
}

void SSD1306_Init(void)
{
    HAL_Delay(100);
    SSD1306_WriteCmd(0xAE); //关闭显示
    SSD1306_WriteCmd(0xD5);
    SSD1306_WriteCmd(0x80);
    SSD1306_WriteCmd(0xA8);
    SSD1306_WriteCmd(0x3F);
    SSD1306_WriteCmd(0xD3);
    SSD1306_WriteCmd(0x00);
    SSD1306_WriteCmd(0x40);
    SSD1306_WriteCmd(0xA1);
    SSD1306_WriteCmd(0xC8);
    SSD1306_WriteCmd(0xDA);
    SSD1306_WriteCmd(0x12);
    SSD1306_WriteCmd(0x81);
    SSD1306_WriteCmd(0xCF);
    SSD1306_WriteCmd(0xD9);
    SSD1306_WriteCmd(0xF1);
    SSD1306_WriteCmd(0xDB);
    SSD1306_WriteCmd(0x30);
    SSD1306_WriteCmd(0xA4);
    SSD1306_WriteCmd(0xA6);
    SSD1306_WriteCmd(0x8D);
    SSD1306_WriteCmd(0x14);
    SSD1306_WriteCmd(0xAF); //开启显示
    SSD1306_Clear();
    SSD1306_Refresh();
}

void SSD1306_Clear(void)
{
    memset(ssd1306_buf,0,sizeof(ssd1306_buf));
}

void SSD1306_Refresh(void)
{
    uint8_t page,col;
    for(page=0;page<8;page++)
    {
        SSD1306_WriteCmd(0xB0 + page);
        SSD1306_WriteCmd(0x00);
        SSD1306_WriteCmd(0x10);
        for(col=0;col<128;col++)
        {
            SSD1306_WriteData(ssd1306_buf[page*128 + col]);
        }
    }
}

void SSD1306_DrawPoint(uint8_t x,uint8_t y,uint8_t set)
{
    if(x>=128 || y>=64) return;
    uint8_t page = y / 8;
    uint8_t bit = y % 8;
    if(set){
        ssd1306_buf[page*128 + x] |= (1<<bit);
    }
        
    else {
        ssd1306_buf[page*128 + x] &= ~(1<<bit);
    }
        
}





void SSD1306_DrawHeart(void)
{
    float t;
    int x,y;
    float scale_x = 1.0f;   // 横向
    float scale_y = 0.8f;   // 纵向压得更扁一点
    for(t = 0; t < 2*3.1415926f; t += 0.015f)
    {
        float ox = 16*pow(sin(t),3);
        float oy = 13*cos(t) - 5*cos(2*t) - 2*cos(3*t) - cos(4*t);
        
        x = 64 + ox * scale_x;
        y = 33 - oy * scale_y;
        
        if(x >= 0 && x < 128 && y >= 0 && y < 64)
        {
            SSD1306_DrawPoint(x,y,1);
        }
    }
    SSD1306_Refresh();
}



void SSD1306_DrawPic(uint8_t *buf)
{
    memcpy(ssd1306_buf, buf, 1024);
}




