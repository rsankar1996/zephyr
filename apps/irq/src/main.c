#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include "main.h"

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
	user_button.button_spec = &button_spec;

	if (led_init(&led_spec) < 0)
	{
		return 0;
	}

	if (button_init(&user_button) < 0)
	{
		return 0;
	}

	return 0;
}
