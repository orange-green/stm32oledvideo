#include "main.h"
#include "gpio.h"

extern TIM_HandleTypeDef htim2;

typedef enum {
    LED_OFF,
    LED_ON,
    LED_BLINK
} LedMode;

static LedMode current_mode = LED_OFF;

// 闪烁用的私有变量
static uint32_t blink_tick = 0;

void init_pwm_led(void) {
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);
}


void led_on(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);  // 低电平，亮
}

void led_off(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);    // 高电平，灭
}
// ----------------------------------------------------------

void handle_button(void) {
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET) {
        HAL_Delay(20);
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET) {
            while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET);

            current_mode++;
            if (current_mode > LED_BLINK) {
                current_mode = LED_OFF;
            }

            switch (current_mode) {
                case LED_OFF:
                    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 1000);
                    break;
                case LED_ON:
                    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);
                    break;
                case LED_BLINK:
                    break;
            }
        }
    }
}

void led_task(void) {
    if (current_mode == LED_BLINK) {
        blink_tick++;
        if (blink_tick % 60 < 30) {
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);
        } else {
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 1000);
        }
    }
}