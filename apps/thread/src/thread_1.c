#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/devicetree.h>

#define STACK_SIZE 1024
#define PRIORITY 0

static void thread_1_run(void *p1, void *p2, void *p3)
{
	while (1) 
	{
		printk("Thread 1 running\n");
		k_sleep(K_SECONDS(1));
	}
}

K_THREAD_DEFINE(my_tid_1, STACK_SIZE, thread_1_run,
				NULL, NULL, NULL, PRIORITY, 0, 0);
