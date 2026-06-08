#ifndef LED_H
#define LED_H

#include <stdbool.h>
#include <stdint.h>
#include <errno.h>
#include <zephyr/drivers/gpio.h>

//Get node identifier for parent led node
#define LED0_NODE_ID		DT_ALIAS(led0)
#define LEDS_NODE_ID		DT_PARENT(LED0_NODE_ID)

int led_init(const struct gpio_dt_spec * led);
int led_toggle(const struct gpio_dt_spec * led);
bool led_get_state(void);
uint32_t led_get_period_ms(void);
const char * led_get_label(void);

#endif /* LED_H */
