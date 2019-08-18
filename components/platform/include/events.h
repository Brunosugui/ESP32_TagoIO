/*
 * events.h
 *
 *  Created on: Jul 7, 2019
 *      Author: Bruno
 */

#ifndef COMPONENTS_PLATFORM_INCLUDE_EVENTS_H_
#define COMPONENTS_PLATFORM_INCLUDE_EVENTS_H_

#include "esp_bit_defs.h"
#include "esp_err.h"

#define EVENT_WF_CONNECTED			BIT0
#define EVENT_WF_DISCONNECT			BIT1
#define TAGO_EVENT_WATCHDOG			BIT2

#define TAGO_EVENT_MASK				EVENT_WF_CONNECTED | EVENT_WF_DISCONNECT //todo adicionar evento watchdog

#define EVENTS_MASK					TAGO_EVENT_MASK

void events_init();
esp_err_t set_tago_wf_connected_event();
esp_err_t set_tago_wf_disconnected_event();


#endif /* COMPONENTS_PLATFORM_INCLUDE_EVENTS_H_ */
