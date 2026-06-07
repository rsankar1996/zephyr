#ifndef BUTTON_H
#define BUTTON_H

#include <zephyr/drivers/gpio.h>

//Get node identifier for parent sw node
#define SW0_NODE_ID		DT_ALIAS(sw0)

struct button
{
	const struct gpio_dt_spec * button_spec;
	struct gpio_callback button_cb;
	// user callback
	// user data
};

int button_init (struct button * button);

#endif /* BUTTON_H */
