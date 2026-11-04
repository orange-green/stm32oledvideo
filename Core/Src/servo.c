#include "servo.h"

extern TIM_HandleTypeDef htim2; // CubeMX生成的TIM2句柄

void Servo_Init(void) {
    // 启动TIM2通道2的PWM输出
    // 注意：CubeMX中建议将TIM2 CH2的初始Pulse设为1500，防止上电猛转
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
}

void Servo_SetAngle(uint16_t angle) {
    if (angle > 180) angle = 180;
    
    // 线性映射 0~180° → 500~2500
    uint32_t pulse = SERVO_MIN_PULSE + (uint32_t)((uint32_t)(SERVO_MAX_PULSE - SERVO_MIN_PULSE) * angle / 180);
    
    // 修改TIM2 CH2的比较值
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, pulse);
}