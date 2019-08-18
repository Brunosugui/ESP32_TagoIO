/*
 * events_task.c
 *
 *  Created on: Jul 7, 2019
 *      Author: Bruno
 */

#include "events_task.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "tago_task.h"
#include "esp_log.h"
#include "events.h"

#define EVENTS_TASK_TAG			"EVENTS TASK"

extern EventGroupHandle_t xTagoIOEventGroup;

#define xTicksToWait		100/portTICK_PERIOD_MS

//const TickType_t xTicksToWait = 100 / portTICK_PERIOD_MS;

void events_task()
{
	ESP_LOGI(EVENTS_TASK_TAG, "Starting Events Task!\n");
	EventBits_t uxBits;

	while(1)
	{
	    uxBits = xEventGroupWaitBits(
	    		xTagoIOEventGroup,    // The event group being tested.
				EVENTS_MASK,  // The bits within the event group to wait for.
				pdTRUE,         // EVENTs_MASK bits should be cleared before returning.
				pdFALSE,        // Don't wait for both bits, either bit will do.
				xTicksToWait ); // Wait a maximum of 100ms for either bit to be set.

	    if ((uxBits & EVENT_WF_CONNECTED) != 0)
	    {
	    	tago_set_state(TAGO_WF_CONNECTED);
	    }
	    else if ((uxBits & EVENT_WF_DISCONNECT) != 0)
	    {
	    	tago_set_state(TAGO_WF_DISCONNECTED);
	    }
	}
}
