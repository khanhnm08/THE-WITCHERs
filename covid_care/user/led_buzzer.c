/*
 * led_buzzer.c
 *
 *  Created on: 22 thg 2, 2022
 *      Author: Ngo Minh Khanh
 */

#include "led_buzzer.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "sl_pwm.h"
#include "sl_pwm_instances.h"
#include "sl_simple_rgb_pwm_led_instances.h"

/**
 *  @brief init clock & set mode for led & buzzer
 */
void led_buzzer_init (void)
{
	CMU_ClockEnable (cmuClock_GPIO, true);
	GPIO_PinModeSet (GPIO_GND_PORT, GPIO_GND_PIN, gpioModePushPull, 0);
	GPIO_PinModeSet (red_LED_port, red_LED_pin, gpioModePushPull, 0);     // red
	GPIO_PinModeSet (green_LED_port, green_LED_pin, gpioModePushPull, 0); // green
	GPIO_PinModeSet (blue_LED_port, blue_LED_pin, gpioModePushPull, 0);  // blue
	GPIO_PinModeSet (buzzer_port, buzzer_pin, gpioModePushPull, 0);    // buzzer
	GPIO_PinModeSet (button_port, button_pin, gpioModeInput, 1);       // button
	GPIO_PinModeSet (LED_on_board_port, LED_on_board_pin, gpioModePushPull, 1);
	GPIO_PinOutSet (LED_on_board_port, LED_on_board_pin);
}

/**
 *  @brief set buzzer
 */
void set_Buzzer ()
{
//	GPIO_PinOutSet (buzzer_port, buzzer_pin);
	sl_pwm_start(&sl_pwm_buzzer);
}

/**
 *  @brief clear buzzer
 */
void clear_Buzzer ()
{
//	GPIO_PinOutClear (buzzer_port, buzzer_pin);
	sl_pwm_stop(&sl_pwm_buzzer);
}

/**
 *  @brief set color of led
 */
void set_LED (char ch)
{
	switch (ch)
	{
		case 'R':    // red
//			GPIO_PinOutSet (red_LED_port, red_LED_pin);
//			GPIO_PinOutClear (green_LED_port, green_LED_pin);
//			GPIO_PinOutClear (blue_LED_port, blue_LED_pin);
			sl_app_log(" r \n");
			sl_led_turn_on((sl_led_t *)&sl_rgb_led);
			sl_led_set_rgb_color(&sl_rgb_led, 255, 0, 0);
			break;
		case 'G':    // green
//			GPIO_PinOutClear (red_LED_port, red_LED_pin);
//			GPIO_PinOutSet (green_LED_port, green_LED_pin);
//			GPIO_PinOutClear (blue_LED_port, blue_LED_pin);
			sl_led_turn_on((sl_led_t *)&sl_rgb_led);
			sl_led_set_rgb_color(&sl_rgb_led, 0, 255, 0);
			break;
		case 'B':    // blue
//			GPIO_PinOutClear (red_LED_port, red_LED_pin);
//			GPIO_PinOutClear (green_LED_port, green_LED_pin);
//			GPIO_PinOutSet (blue_LED_port, blue_LED_pin);
			sl_led_turn_on((sl_led_t *)&sl_rgb_led);
			sl_led_set_rgb_color(&sl_rgb_led, 0, 0, 255);
			break;
		case 'O': 	// orange
			sl_led_turn_on((sl_led_t *)&sl_rgb_led);
			sl_led_set_rgb_color(&sl_rgb_led, 255, 10, 0);
			break;
		case 'W':    // white
//			GPIO_PinOutSet (red_LED_port, red_LED_pin);
//			GPIO_PinOutSet (green_LED_port, green_LED_pin);
//			GPIO_PinOutSet (blue_LED_port, blue_LED_pin);
			sl_led_turn_on((sl_led_t *)&sl_rgb_led);
			sl_led_set_rgb_color(&sl_rgb_led, 255, 255, 255);
			break;
	}
}

/**
 *  @brief clear all led
 */
void clear_all_LED ()
{
//	GPIO_PinOutClear (red_LED_port, red_LED_pin);
//	GPIO_PinOutClear (green_LED_port, green_LED_pin);
//	GPIO_PinOutClear (blue_LED_port, blue_LED_pin);
	sl_led_turn_off((sl_led_t *)&sl_rgb_led);
}

void blynk (void)
{
	if (!GPIO_PinInGet (button_port, button_pin))
	{
		GPIO_PinOutSet (LED_on_board_port, LED_on_board_pin);
		sl_app_log("Led on \n");
	}
	else
	{
		GPIO_PinOutClear (LED_on_board_port, LED_on_board_pin);
		sl_app_log("Led off \n");
	}
}

