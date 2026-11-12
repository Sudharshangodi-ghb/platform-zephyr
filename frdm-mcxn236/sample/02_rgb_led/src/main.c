/*
 * Copyright (c) 2026 Sudharshan Reddy Godi
 * SPDX-License-Identifier: MIT
 *
 * @file main.c
 * @brief RGB LED blink sample application using the Zephyr GPIO API.
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

/* GPIO aliases for each RGB LED channel. */
#define LED0_NODE  DT_ALIAS(led0)
#define LED1_NODE  DT_ALIAS(led1)
#define LED2_NODE  DT_ALIAS(led2)

/* Board-level LED device definitions for the three color channels. */
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);

LOG_MODULE_REGISTER(rgb_logger, LOG_LEVEL_INF);

int main(void)
{
  LOG_INF("RGB blinky program");

  int ret1 = 0, ret2 = 0, ret3 = 0;

  /* Verify that all RGB LED GPIO controllers are initialized and ready. */
  if (!gpio_is_ready_dt(&led0) ||
      !gpio_is_ready_dt(&led1) ||
      !gpio_is_ready_dt(&led2))
  {
    LOG_ERR("LEDs are not ready");
    return -1;
  }

  /* Configure each LED pin as a push-pull output with an inactive state. */
  ret1 = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_INACTIVE);
  ret2 = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);
  ret3 = gpio_pin_configure_dt(&led2, GPIO_OUTPUT_INACTIVE);

  if ((ret1 < 0) || (ret2 < 0) || (ret3 < 0)) {
    LOG_ERR("Failed to configure LED pin(s)");
    return -1;
  }

  while (1) {
    /* Blink each channel in sequence with a 1-second delay between updates. */
    LOG_INF("Toggling LEDs");

    LOG_INF("LED 0 toggled");
    ret1 = gpio_pin_set_dt(&led0, 1);
    if (ret1 < 0) {
      LOG_ERR("Failed to set LED 0 high");
      return -1;
    }

    k_msleep(1000);
    ret1 = gpio_pin_set_dt(&led0, 0);

    ret2 = gpio_pin_set_dt(&led1, 1);
    if (ret2 < 0) {
      LOG_ERR("Failed to set LED 1 high");
      return -1;
    }

    k_msleep(1000);
    ret2 = gpio_pin_set_dt(&led1, 0);

    ret3 = gpio_pin_set_dt(&led2, 1);
    if (ret3 < 0) {
      LOG_ERR("Failed to set LED 2 high");
      return -1;
    }

    k_msleep(1000);
    ret3 = gpio_pin_set_dt(&led2, 0);
  }

  return 0;
}
