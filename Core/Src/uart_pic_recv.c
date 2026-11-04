#include "uart_pic_recv.h"
#include "oled.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

extern UartPicHandle_t hPicRecv;

void UartPic_Init(UartPicHandle_t *h)
{
    h->dataCnt = 0;
}

// 单字节处理：收到就填缓存，写满1024直接刷新
// void UartPic_ProcessByte(UartPicHandle_t *h, uint8_t dat)
// {
//     // ssd1306_buf[h->dataCnt] = dat;
//     // h->dataCnt ++;

//     // if(h->dataCnt >= PIC_DATA_LEN)
//     // {
//     //     SSD1306_Refresh();
//     //     uint8_t ack = PIC_ACK_OK;
//     //     CDC_Transmit_FS(&ack, 1);

//     //     h->dataCnt = 0; // 写完一屏，重置索引，等待下一帧
//     // }


//     ssd1306_buf[h->dataCnt] = dat;
//     h->dataCnt ++;

//     if(h->dataCnt >= PIC_DATA_LEN)
//     {
//         // 测试：全屏点亮，判断通路是否正常
//         //memset(ssd1306_buf,0xFF,1024);
//         SSD1306_Refresh();
//         uint8_t ack = PIC_ACK_OK;
//         CDC_Transmit_FS(&ack, 1);
//         h->dataCnt = 0;
//     }
// }


void UartPic_ProcessByte(UartPicHandle_t *h, uint8_t dat)
{
    // 只要进来就回复06，用来确认函数被调用了
    uint8_t ack = 0x06;
    CDC_Transmit_FS(&ack, 1);
}

