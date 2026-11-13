/*
 * Copyright (c) 2026 Sudharshan Reddy Godi
 * SPDX-License-Identifier: MIT
 *
 * @file main.c
 * @brief Silicon temperature sensor sample application.
 *
 * This sample initializes the silicon temperature sensor attached via the
 * silicon_temp0 alias, fetches the sensor data, reads the die temperature,
 * and logs the value once every second.
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main_silicontemp, LOG_LEVEL_INF);

int main(void)
{
  /* Get the configured silicon temperature sensor instance. */
  const struct device *const silicon_temp = DEVICE_DT_GET(DT_ALIAS(silicon_temp0));

  if (!device_is_ready(silicon_temp)) {
    LOG_ERR("Device is not ready");
    return -1;
  }

  LOG_INF("Device %s is initialized successfully", silicon_temp->name);

  while (1) {
    struct sensor_value adc_temperature;

    /* Fetch the latest sensor data from the device before reading the die temp. */
    if (sensor_sample_fetch(silicon_temp) < 0) {
      LOG_ERR("Failed to fetch sensor data");
      k_msleep(1000);
      continue;
    }

    if (sensor_channel_get(silicon_temp, SENSOR_CHAN_DIE_TEMP, &adc_temperature) < 0) {
      LOG_ERR("Failed to get sensor channel");
      return -1;
    }

    double temp_c = sensor_value_to_double(&adc_temperature);

    LOG_INF("Silicon Temperature: %.2f C", temp_c);

    k_msleep(1000);
  }

  return 0;
}
