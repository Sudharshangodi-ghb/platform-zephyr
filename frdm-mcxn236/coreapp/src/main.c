#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

#define LED0_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void)
{
    int ret;

    if (!device_is_ready(led.port)) {
        printk("LED device is not ready\n");
        return;
    }

    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Failed to configure LED GPIO (%d)\n", ret);
        return;
    }

    printk("Hello from Zephyr! Core app LED blink demo started.\n");

    while (1) {
        gpio_pin_set_dt(&led, 0);
        printk("LED ON\n");
        k_sleep(K_MSEC(500));

        gpio_pin_set_dt(&led, 1);
        printk("LED OFF\n");
        k_sleep(K_MSEC(500));
    }

    return ret;
}
