/*
 * Copyright (c) 2026 Sudharshan Reddy Godi
 * SPDX-License-Identifier: MIT
 *
 * @file main.c
 * @brief FRDM-MCXN236 accelerometer tilt indicator sample application.
 *
 * This sample initializes the on-board FXLS8974 accelerometer, reads the
 * acceleration values along the X, Y, and Z axes, and updates the RGB LED to
 * indicate the current board orientation.
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main_accelerometer, LOG_LEVEL_DBG);

#define ACCEL_NODE DT_NODELABEL(fxls8974)

#define LED0_NODE  DT_ALIAS(led0)
#define LED1_NODE  DT_ALIAS(led1)
#define LED2_NODE  DT_ALIAS(led2)

static const struct device *accel = DEVICE_DT_GET(ACCEL_NODE);

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);

/* Set the RGB LED to the requested on/off state for each channel. */
static void set_rgb(bool r, bool g, bool b)
{
  gpio_pin_set_dt(&led0, r);
  gpio_pin_set_dt(&led1, g);
  gpio_pin_set_dt(&led2, b);
}

int main(void)
{
  struct sensor_value x, y, z;

  LOG_INF("Accelerometer tilt indicator using the on-board FXLS8974 sensor");

  if (!device_is_ready(accel)) {
    LOG_ERR("FXLS8974 is not ready");
    return -1;
  }

  gpio_pin_configure_dt(&led0, GPIO_OUTPUT_INACTIVE);
  gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);
  gpio_pin_configure_dt(&led2, GPIO_OUTPUT_INACTIVE);

  while (1) {
    sensor_sample_fetch(accel);

    sensor_channel_get(accel, SENSOR_CHAN_ACCEL_X, &x);
    sensor_channel_get(accel, SENSOR_CHAN_ACCEL_Y, &y);
    sensor_channel_get(accel, SENSOR_CHAN_ACCEL_Z, &z);

    LOG_INF("X=%d.%02d  Y=%d.%02d  Z=%d.%02d", x.val1, x.val2, y.val1, y.val2, z.val1, z.val2);

    double xg = sensor_value_to_double(&x);
    double yg = sensor_value_to_double(&y);
    double zg = sensor_value_to_double(&z);

    /* Board is upside down: strong negative acceleration along Z. */
    if (zg < -8.0) {
      set_rgb(true, true, true);   /* White */
    }

    /* Board is tilted to the right on the X axis. */
    else if (xg > 3.0) {
      set_rgb(false, false, true); /* Blue */
    }

    /* Board is tilted to the left on the X axis. */
    else if (xg < -3.0) {
      set_rgb(true, false, false); /* Red */
    }

    /* Board is tilted forward on the Y axis. */
    else if (yg > 3.0) {
      set_rgb(true, true, false); /* Yellow */
    }

    /* Board is tilted backward on the Y axis. */
    else if (yg < -3.0) {
      set_rgb(false, true, true); /* Cyan */
    }

    /* Board is level. */
    else {
      set_rgb(false, true, false); /* Green */
    }

    k_msleep(100);
  }

  return 0;
}
