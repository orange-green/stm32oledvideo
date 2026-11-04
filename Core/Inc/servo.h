#ifndef __SERVO_H
#define __SERVO_H

#include "main.h"

// 脉宽范围（单位：微秒，对应ARR=19999时的CCR值）
#define SERVO_MIN_PULSE 1000  // 实测0°对应的脉宽
#define SERVO_MAX_PULSE 2000  // 实测90°对应的脉宽
#define SERVO_MAX_ANGLE 90    

void Servo_Init(void);
void Servo_SetAngle(uint16_t angle);

#endif