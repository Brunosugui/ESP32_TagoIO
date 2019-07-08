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
#include "freertos/semphr.h"

#include "esp_pthread.h"
#include "pthread.h"
#include "esp_log.h"
#include "stddef.h"
#include "stdint.h"

#define TICK_TO_MS(ms)					ms/portTICK_PERIOD_MS
#define TAGO_TASK_DELAY					TICK_TO_MS(2000)
#define TAGO_TASK_TAG					"::TAGO TASK::"

#define SEMAPHORE_BLOCK_TIME			TICK_TO_MS(50)

static tago_states_t tago_state;
static SemaphoreHandle_t xSemaphore;
static char device_token[] = CONFIG_ESP_DEVICE_TOKEN;
static char server_url[] = CONFIG_ESP_HTTP_SERVER_ADDR;

void* tago_transmit()
{
	printf("Hi from thread!!\n");
	//todo send http post
	pthread_exit(NULL);
	return NULL;
}

void transmit()
{
    pthread_t transmit_thread;

    esp_pthread_cfg_t cfg = esp_pthread_get_default_config();
    cfg.stack_size = (4 * 1024);
    esp_pthread_set_cfg(&cfg);

    pthread_create(&transmit_thread, NULL, tago_transmit, NULL);
    /**< maybe get data and send it to the thread as argument */
}

void tago_set_state(tago_states_t state)
{
	xSemaphoreTake(xSemaphore, SEMAPHORE_BLOCK_TIME);
	tago_state = state;
	xSemaphoreGive(xSemaphore);
}

void tago_get_state(tago_states_t *state)
{
	xSemaphoreTake(xSemaphore, SEMAPHORE_BLOCK_TIME);
	*state = tago_state;
	xSemaphoreGive(xSemaphore);
}

void tago_task()
{
	tago_states_t state;

	ESP_LOGI(TAGO_TASK_TAG, "Tago Task started\n");
	ESP_LOGI(TAGO_TASK_TAG, "Device Token = \"%s\"\n", (char*) device_token);
	ESP_LOGI(TAGO_TASK_TAG, "Server = \"%s\"\n", (char*) server_url);

   // Semaphore cannot be used before a call to xSemaphoreCreateMutex().
   // This is a macro so pass the variable in directly.
   xSemaphore = xSemaphoreCreateBinary();


   if( xSemaphore != NULL )
   {
	   // The semaphore was created successfully.
	   // The semaphore can now be used.
	   ESP_LOGI(TAGO_TASK_TAG, "Semaphore created successfully!\n");
	   xSemaphoreTake(xSemaphore, SEMAPHORE_BLOCK_TIME);
	   xSemaphoreGive(xSemaphore);
   }
   else
   {
	   ESP_LOGI(TAGO_TASK_TAG, "Failed to create Semaphore!\n");
   }

	while(1)
	{
		tago_get_state(&state);
		switch(state)
		{
		case TAGO_IDLE:
		   ESP_LOGI(TAGO_TASK_TAG, "Tago TASK state: IDLE\n");
		   //todo reconect wifi routine
			break;
		case TAGO_TRANSMIT:
			ESP_LOGI(TAGO_TASK_TAG, "Tago TASK state: TRANSMIT\n");
			transmit();
			break;
		default:
			break;
		}
		vTaskDelay(TAGO_TASK_DELAY);
	}

	//vTaskDelete(NULL);
}
