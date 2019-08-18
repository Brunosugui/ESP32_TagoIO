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

#include "http_tago.h"
#include "wifi.h"

#include "esp_log.h"
#include "stddef.h"
#include "stdint.h"

#define TICK_TO_MS(ms)					ms/portTICK_PERIOD_MS
#define TAGO_TASK_DELAY					TICK_TO_MS(5000)
#define TAGO_TASK_TAG					"::TAGO TASK::"

#define SEMAPHORE_BLOCK_TIME			TICK_TO_MS(50)

static tago_states_t tago_state;
static SemaphoreHandle_t tago_state_sem, tago_http_thread_sem;

char test_string[] =
		"{\"variable\" : \"Name\","
		"\"value\" : \"Bruno\"}";

void* tago_transmit()
{
	ESP_LOGI(TAGO_TASK_TAG, "Starting data transmission");
	xSemaphoreTake(tago_http_thread_sem, SEMAPHORE_BLOCK_TIME);
	http_tago_post_data(test_string);
	xSemaphoreGive(tago_http_thread_sem);
	ESP_LOGI(TAGO_TASK_TAG, "Finished data transmission");
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
    /**< todo implement data gather and send it to the thread as argument */

    pthread_join(transmit_thread, NULL);
}

void tago_set_state(tago_states_t state)
{
	xSemaphoreTake(tago_state_sem, SEMAPHORE_BLOCK_TIME);
	tago_state = state;
	xSemaphoreGive(tago_state_sem);
}

void tago_get_state(tago_states_t *state)
{
	xSemaphoreTake(tago_state_sem, SEMAPHORE_BLOCK_TIME);
	*state = tago_state;
	xSemaphoreGive(tago_state_sem);
}



void tago_task()
{
	tago_states_t state;
	//esp_err_t err;
	ESP_LOGI(TAGO_TASK_TAG, "Tago Task started\n");

   tago_state_sem = xSemaphoreCreateBinary();
   tago_http_thread_sem = xSemaphoreCreateBinary();

   if( NULL != tago_state_sem && NULL != tago_http_thread_sem)
   {
	   ESP_LOGI(TAGO_TASK_TAG, "Semaphore created successfully!\n");
	   xSemaphoreTake(tago_state_sem, SEMAPHORE_BLOCK_TIME);
	   xSemaphoreGive(tago_state_sem);
	   xSemaphoreTake(tago_http_thread_sem, SEMAPHORE_BLOCK_TIME);
	   xSemaphoreGive(tago_http_thread_sem);
   }
   else
   {
	   ESP_LOGI(TAGO_TASK_TAG, "Failed to create Semaphore!\n");
   }

	while(1)
	{
		vTaskDelay(TAGO_TASK_DELAY);
		tago_get_state(&state);
		switch(state)
		{
		case TAGO_IDLE:
		   ESP_LOGI(TAGO_TASK_TAG, "Tago TASK state: IDLE\n");
			break;
		case TAGO_WF_CONNECTED:
			ESP_LOGI(TAGO_TASK_TAG, "Tago TASK state: Wifi Connected, initializing http client\n");
			tago_set_state(ESP_OK == http_tago_init_client() ? TAGO_TRANSMIT : TAGO_WF_CONNECTED);
			break;
		case TAGO_TRANSMIT:
			ESP_LOGI(TAGO_TASK_TAG, "Tago TASK state: TRANSMIT\n");
			transmit();
			break;
		case TAGO_WF_DISCONNECTED:
			ESP_LOGI(TAGO_TASK_TAG, "Tago TASK state: Wifi Disconnected\n");
			http_tago_clean_client();
			wifi_reconnect();
			break;
		default:
			break;
		}
	}

	//vTaskDelete(NULL);
}
