#include "button.h"

static void button_isr (const struct device *port, struct gpio_callback *cb, \ 
                               gpio_port_pins_t pins)
{
	printk("Button irq\n");	
}

int button_init (struct button * button)
{
	int ret;

	if (button == NULL)
	{
		printk("ERR: Null button pointer\n");
		return -EINVAL;
	}

	// verify if the device is ready
	if (!gpio_is_ready_dt(button->button_spec))
	{
		printk("ERR: failed to get device ready\n");
		return -ENODEV;
	}

	ret = gpio_pin_configure_dt(button->button_spec, GPIO_INPUT);
	if (ret < 0)
	{
		printk("ERR: failed to configure button\n");
		return ret;
	}
	
	// init gpio callback structure
	gpio_init_callback(&button->button_cb, button_isr, BIT(button->button_spec->pin));

	// add the isr
	ret = gpio_add_callback_dt(button->button_spec, &button->button_cb);
	if (ret < 0)
	{
		printk("ERR: failed to add isr : %d\n", ret);
		return ret;
	}

	// configure the interrupt
	return gpio_pin_interrupt_configure_dt(button->button_spec, GPIO_INT_EDGE_TO_ACTIVE);
}

