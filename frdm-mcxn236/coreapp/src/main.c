/*
 * Copyright (c) 2026 Sudharshan Reddy Godi
 * SPDX-License-Identifier: MIT
 *
 * @file main.c
 * @brief LED blink sample application using the Zephyr GPIO API.
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

/*
 * This sample drives the board's LED through the Zephyr GPIO API.
 * The DTS alias `led0` resolves to the hardware GPIO used by the board.
 */
#define LED0_NODE DT_ALIAS(led0)

/* Access the GPIO pin described by the `led0` devicetree alias. */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void)
{
    int ret;

    /* Verify that the GPIO controller for the LED is available before use. */
    if (!device_is_ready(led.port)) {
        printk("LED device is not ready\n");
        return 0;
    }

    /* Configure the LED pin as an active-low or active-high output according to DT. */
    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Failed to configure LED GPIO (%d)\n", ret);
        return ret;
    }

    printk("Hello from Zephyr! LED blink demo started.\n");

    /* Blink the LED forever: turn it on for 500 ms, then off for 500 ms. */
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
