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
/*
#include <peripheral_io.h>
#include <stdio.h>
#include "log.h"

static peripheral_gpio_h g_sensor_h = NULL;
static int g_pin_num = -1;

void resource_close_infrared_motion_sensor(void)
{
	if (!g_sensor_h) return;

	_I("Infrared Motion Sensor is finishing...");

	peripheral_gpio_close(g_sensor_h);

	g_sensor_h = NULL;
	g_pin_num = -1;
}

int resource_read_infrared_motion_sensor(int pin_num, uint32_t *out_value)
{
	int ret = PERIPHERAL_ERROR_NONE;

	if (!g_sensor_h) {
		peripheral_gpio_h temp = NULL;

		ret = peripheral_gpio_open(pin_num, &temp);
		retv_if(ret, -1);

		ret = peripheral_gpio_set_direction(temp, PERIPHERAL_GPIO_DIRECTION_IN);
		if (ret) {
			peripheral_gpio_close(temp);
			_E("peripheral_gpio_set_direction failed.");
			return -1;
		}

		g_sensor_h = temp;
		g_pin_num = pin_num;
	}

	if (g_pin_num != pin_num) {
		_E("Invalid pin number.");
		return -1;
	}

	ret = peripheral_gpio_read(g_sensor_h, out_value);
	retv_if(ret < 0, -1);

	return 0;
}
*/

#include <peripheral_io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "stdio.h"

int read_tracking_data(const char* path, int *out_value, int *pin_numb, int *pin_numb2)
{
	int i = 4;
	char buf[1000];
	char result[100];
	FILE *fp;

	fp = fopen("/opt/usr/home/owner/apps_rw/org.tizen.smart-surveillance-camera/shared/data/lhy.txt", "r");

	if(fp==NULL)
		return -1;

	fgets(buf, sizeof(buf), fp);
	fclose(fp);

	while (1) {
		if (buf[i] == ',') {
			result[i - 4] = NULL;
			break;
		}
		result[i - 4] = buf[i];
		i++;
	}



	if (strcmp(result, "water bottle")==0) {
		*pin_numb = 130;
		*pin_numb2 = 0;
		*out_value = 1;
		return 0;
	} else if (strcmp(result, "computer keyboard")==0) {
		*pin_numb = 0;
		*pin_numb2 = 46;
		*out_value = 1;
		return 0;
	} else if (strcmp(result, "rubber eraser")==0) {
		*pin_numb = 130;
		*pin_numb2 = 46;
		*out_value = 1;
		return 0;
	} else
		return 0;
	return 0;
}
