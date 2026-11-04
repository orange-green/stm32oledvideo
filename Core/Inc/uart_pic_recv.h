#ifndef __UART_PIC_RECV_H
#define __UART_PIC_RECV_H

#include "stdint.h"

#define PIC_DATA_LEN    1024
#define PIC_ACK_OK      0x06

typedef struct
{
    uint16_t dataCnt;
} UartPicHandle_t;

void UartPic_Init(UartPicHandle_t *h);
void UartPic_ProcessByte(UartPicHandle_t *h, uint8_t dat);

#endif
