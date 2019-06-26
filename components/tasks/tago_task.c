/*
 * tago_task.c
 *
 *  Created on: Jun 20, 2019
 *      Author: Bruno
 */

#include "tago_task.h"
#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"
#include "freertos/task.h"
#include "stddef.h"
#include "stdint.h"

#define TASK_DELAY_MS(ms)				ms/portTICK_PERIOD_MS
#define TAGO_TASK_DELAY				TASK_DELAY_MS(500)

static char device_token[] = CONFIG_ESP_DEVICE_TOKEN;
static char server_url[] = CONFIG_ESP_HTTP_SERVER_ADDR;


void tago_task()
{
	while(1)
	{
		printf("%s", (char*) device_token);
		printf("%s", (char*) server_url);
		vTaskDelay(TAGO_TASK_DELAY);
	}

	//vTaskDelete(NULL);
}
