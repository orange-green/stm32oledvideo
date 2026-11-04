#ifndef LED_H
#define LED_H

void init_pwm_led(void);
void handle_button(void);
void led_task(void);
void led_on(void);
void led_off(void);

#endif