/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <peripheral_io.h>

#include "log.h"

static peripheral_gpio_h g_sensor_h[3] = {NULL,};
static int g_pin_num[3] = {-1,};
static int gpio_count=0;

void resource_close_led(void)
{
	int i=0;
	_I("LED is finishing...");
	for(i=0;i<gpio_count;i++)
	{
		peripheral_gpio_close(g_sensor_h[i]);
		g_sensor_h[i] = NULL;
		g_pin_num[i] = -1;
	}
}

int resource_write_led(int pin_num, int write_value)
{
	int ret = PERIPHERAL_ERROR_NONE;
	int i=0;
	int index=-1;
	for(i=0;i<gpio_count;i++)
	{
		if(pin_num==g_pin_num[i])
			{
				index=i;
				break;
			}
	}


	if (index==-1) {
		peripheral_gpio_h temp = NULL;

		ret = peripheral_gpio_open(pin_num, &temp);
		retv_if(ret, -1);

		ret = peripheral_gpio_set_direction(temp, PERIPHERAL_GPIO_DIRECTION_OUT_INITIALLY_LOW);
		if (ret) {
			peripheral_gpio_close(temp);
			return -1;
		}

		g_sensor_h[gpio_count] = temp;
		g_pin_num[gpio_count] = pin_num;
		index=gpio_count;
		gpio_count++;
	}

	ret = peripheral_gpio_write(g_sensor_h[index], write_value);
	retv_if(ret < 0, -1);


	return 0;
}
