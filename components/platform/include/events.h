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

#define TAGO_EVENT_TRANSMIT			BIT0
#define TAGO_EVENT_DISCONNECT		BIT1
#define TAGO_EVENT_WATCHDOG			BIT2

#define TAGO_EVENT_MASK				TAGO_EVENT_TRANSMIT | TAGO_EVENT_DISCONNECT //todo adicionar evento watchdog

#define EVENTS_MASK					TAGO_EVENT_MASK

void events_init();
esp_err_t set_tago_transmit_event();
esp_err_t set_tago_idle_event();


#endif /* COMPONENTS_PLATFORM_INCLUDE_EVENTS_H_ */
