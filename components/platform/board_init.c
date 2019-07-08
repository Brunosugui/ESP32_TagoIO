/*
 * board_init.c
 *
 *  Created on: Jun 20, 2019
 *      Author: Bruno
 */

#include "board_init.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "wifi.h"
#include "events.h"

esp_err_t board_init()
{
	esp_err_t err = ESP_OK;

	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
	  ESP_ERROR_CHECK(nvs_flash_erase());
	  ret = nvs_flash_init();
	}

	events_init();
	wifi_init();
	ESP_ERROR_CHECK(ret);
	//ESP_ERROR_CHECK(esp_event_loop_create_default());

	return err;
}
