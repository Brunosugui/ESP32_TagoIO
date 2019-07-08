/*
 * events.c
 *
 *  Created on: Jul 7, 2019
 *      Author: Bruno
 */

#include "events.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_log.h"

#define EVENTGROUP_TAG			"::EVENT TAG::"

StaticEventGroup_t xEventGroupBuffer;

// Declare a variable to hold the created event group. Used on events_task.c
EventGroupHandle_t xTagoIOEventGroup;

void events_init()
{
	// Attempt to create the event group.
	xTagoIOEventGroup = xEventGroupCreate();

	// Was the event group created successfully?
	if( xTagoIOEventGroup == NULL )
	{
	    // The event group was not created because there was insufficient
	    // FreeRTOS heap available.
		ESP_LOGI(EVENTGROUP_TAG, "Error creating EventGroup. Insuficient FreeRTOS heap available. Attempting to creat static\n");
		// Create the event group without dynamically allocating any memory.
		xTagoIOEventGroup = xEventGroupCreateStatic( &xEventGroupBuffer );
		if (xTagoIOEventGroup == NULL)
		{
			ESP_LOGI(EVENTGROUP_TAG, "Error creating static EventGroup. Aborting application. \n");
		}
		else
		{
			ESP_LOGI(EVENTGROUP_TAG, "Static Event Group created successfully.\n");
		}
	}
	else
	{
	    // The event group was created.
		ESP_LOGI(EVENTGROUP_TAG, "Event Group created successfully.\n");
	}

}

static inline esp_err_t set_event(uint32_t bits)
{
	EventBits_t	uxBits = xEventGroupSetBits(
				xTagoIOEventGroup,    	// The event group being updated.
				bits					// The bits being set.
			);
	return uxBits == bits ? ESP_OK : ESP_FAIL;
}

esp_err_t set_tago_transmit_event()
{
	return set_event(TAGO_EVENT_TRANSMIT);
}

esp_err_t set_tago_idle_event()
{
	return set_event(TAGO_EVENT_DISCONNECT);
}
