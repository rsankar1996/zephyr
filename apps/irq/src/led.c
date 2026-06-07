#include "led.h"

//Get the blink period from the device tree
#define DELAY_MS			DT_PROP_OR(LEDS_NODE_ID, blink_period_ms, 200)
#define LED_LABEL			DT_PROP_OR(LED0_NODE_ID, label, "USER_LED")

static bool led_state = false;

int led_init(const struct gpio_dt_spec * led)
{
	if (led == NULL)
	{
		return -EINVAL;
	}

	// verify if the device is ready
	if (!gpio_is_ready_dt(led))
	{
		return -ENODEV;
	}

	return gpio_pin_configure_dt(led, GPIO_OUTPUT_INACTIVE);
}

int led_toggle(const struct gpio_dt_spec * led)
{
	int ret;

	if (led == NULL)
	{
		return -EINVAL;
	}
	
	ret = gpio_pin_toggle_dt(led);
	if (ret == 0)
	{
		led_state = !led_state;
	}
	
	return ret;
}

bool led_get_state(void)
{
	return led_state;
}

uint32_t led_get_period_ms(void)
{
	return DELAY_MS;
}

const char * led_get_label(void)
{
	return LED_LABEL;
}
