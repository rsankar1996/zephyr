#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/devicetree.h>

// Check for the device tree aliases
#if (!DT_HAS_ALIAS(led0))
	#error missing device tree alias for led0
#endif

#if (!DT_HAS_ALIAS(led1))
	#error missing device tree alias for led1
#endif

//Get node identifier for parent led node
#define LED0_NODE_ID		DT_ALIAS(led0)
#define LED1_NODE_ID		DT_ALIAS(led1)
#define LEDS_NODE_ID		DT_PARENT(DT_DRV_INST(LED0_NODE_ID))

//Get the blink period from the device tree
#define DELAY_MS			DT_PROP_OR(LEDS_NODE_ID, blink_period_ms, 5000)

struct gpio_dt_spec  led1 = GPIO_DT_SPEC_GET(LED0_NODE_ID, gpios);
struct gpio_dt_spec  led2 = GPIO_DT_SPEC_GET(LED1_NODE_ID, gpios);

int main()
{
	// verify if the device is ready
	if (!gpio_is_ready_dt(&led1))
	{
		return 0;
	}

	if (!gpio_is_ready_dt(&led2))
	{
		return 0;
	}
	
	// configure the LED pin as gpio output device
	if (gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE) < 0)
	{
		return 0;
	}

	if (gpio_pin_configure_dt(&led2, GPIO_OUTPUT_INACTIVE) < 0)
	{
		return 0;
	}
	
	while (1)
	{
		if (gpio_pin_toggle_dt(&led1) < 0)
		{
			return 0;
		}

		if (gpio_pin_toggle_dt(&led2) < 0)
		{
			return 0;
		}
		
		k_msleep(DELAY_MS); 
	}

	return 0;
}
