#include <led_buzzer.h>
#include "em_gpio.h"
#include "em_cmu.h"

void led_buzzer_init(void)
{
    CMU_ClockEnable(cmuClock_GPIO, true);
    GPIO_PinModeSet(red_LED_port, red_LED_pin, gpioModePushPull, 0);      // red
    GPIO_PinModeSet(green_LED_port, green_LED_pin, gpioModePushPull, 0);  // green
    GPIO_PinModeSet(blue_LED_port, blue_LED_pin, gpioModePushPull, 0);    // blue
    GPIO_PinModeSet(buzzer_port, buzzer_pin, gpioModePushPull, 1);        // buzzer
    GPIO_PinModeSet(button_port, button_pin, gpioModeInput, 0);           // button
    GPIO_PinModeSet(gpioPortA, 4, gpioModePushPull, 0);
}
void blynk(void)
{
  if (!GPIO_PinInGet(button_port, button_pin))
  {
      setLED('w');
      setBuzzer(true);
      GPIO_PinOutSet(gpioPortA, 4);
  }
  else
  {
      setLED('c');
      setBuzzer(false);
      GPIO_PinOutClear(gpioPortA, 4);
  }
}

void setBuzzer(bool set)
{
    if(set)
       GPIO_PinOutClear(buzzer_port, buzzer_pin);
    else
       GPIO_PinOutSet(buzzer_port, buzzer_pin);
}

void setLED(char ch)
{
    switch (ch)
    {
        case 'r':    // red
            GPIO_PinOutSet(red_LED_port, red_LED_pin);
            GPIO_PinOutClear(green_LED_port, green_LED_pin);
            GPIO_PinOutClear(blue_LED_port, blue_LED_pin);
            break;
        case 'g':    // green
            GPIO_PinOutClear(red_LED_port, red_LED_pin);
            GPIO_PinOutSet(green_LED_port, green_LED_pin);
            GPIO_PinOutClear(blue_LED_port, blue_LED_pin);
            break;
        case 'b':    // blue
            GPIO_PinOutClear(red_LED_port, red_LED_pin);
            GPIO_PinOutClear(green_LED_port, green_LED_pin);
            GPIO_PinOutSet(blue_LED_port, blue_LED_pin);
            break;
        case 'w':    // white
            GPIO_PinOutSet(red_LED_port, red_LED_pin);
            GPIO_PinOutSet(green_LED_port, green_LED_pin);
            GPIO_PinOutSet(blue_LED_port, blue_LED_pin);
            break;
        case 'c':    // clear
            GPIO_PinOutClear(red_LED_port, red_LED_pin);
            GPIO_PinOutClear(green_LED_port, green_LED_pin);
            GPIO_PinOutClear(blue_LED_port, blue_LED_pin);
            break;
        default:
            GPIO_PinOutClear(red_LED_port, red_LED_pin);
            GPIO_PinOutClear(green_LED_port, green_LED_pin);
            GPIO_PinOutClear(blue_LED_port, blue_LED_pin);
            break;
    }
}
