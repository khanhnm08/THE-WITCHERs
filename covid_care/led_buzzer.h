#include "em_gpio.h"

#define  red_LED_port     gpioPortC
#define  red_LED_pin      1

#define  green_LED_port   gpioPortB
#define  green_LED_pin    4

#define  blue_LED_port    gpioPortB
#define  blue_LED_pin     3

#define  buzzer_port      gpioPortC
#define  buzzer_pin       0

#define  button_port      gpioPortC
#define  button_pin       7

void led_buzzer_init(void);
void setBuzzer(bool set);
void setLED(char ch);
void blynk(void);

