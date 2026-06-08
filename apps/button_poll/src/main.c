#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include "led.h"
#include "button.h"

// Check for the device tree aliases
#if (!DT_HAS_ALIAS(led0))
	#error missing device tree alias for led0
#endif

#if (!DT_HAS_ALIAS(sw0))
	#error missing device tree alias for sw0
#endif

static struct button user_button;

const struct gpio_dt_spec  button_spec = GPIO_DT_SPEC_GET(SW0_NODE_ID, gpios);
const struct gpio_dt_spec  led_spec = GPIO_DT_SPEC_GET(LED0_NODE_ID, gpios);

int main()
{
	printk("Zephyr IRQ example\n");

	user_button.button_spec = &button_spec;

	if (led_init(&led_spec) < 0)
	{
		printk("ERR: led init failed\n");
		return 0;
	}

	if (button_init(&user_button) < 0)
	{
		printk("ERR: button init failed\n");
		return 0;
	}
	
	printk("all init suceessful\n");

	while (1)
	{
		if (true == button_read(&user_button))
		{
			gpio_pin_set_dt (&led_spec, 1);
		}
		else
		{
			gpio_pin_set_dt (&led_spec, 0);
		}
	}

	return 0;
}
