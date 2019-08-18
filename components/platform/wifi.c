/*
 * wifi.c
 *
 *  Created on: Jun 20, 2019
 *      Author: Bruno
 */

#include "wifi.h"
#include "events.h"
#include "esp_err.h"
#include "esp_wifi.h"
#include "tcpip_adapter.h"
#include "string.h"
#include "esp_log.h"

#define MAX_STA_CONN       10

static const char *WIFI_TAG = "::WIFI::";

static uint8_t ssid[] = CONFIG_ESP_WIFI_SSID;
static uint8_t passwd[] = CONFIG_ESP_WIFI_PASSWORD;

static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        ESP_LOGI(WIFI_TAG, "station "MACSTR" join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGI(WIFI_TAG, "station "MACSTR" leave, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }
    else if (WIFI_EVENT_STA_START == event_id)
    {
    	esp_wifi_connect();
    	ESP_LOGI(WIFI_TAG, "Wifi Station Start event!\n");
    }
    else if (WIFI_EVENT_STA_CONNECTED == event_id)
	{
    	set_tago_wf_connected_event();
    	wifi_event_sta_connected_t *event = (wifi_event_sta_connected_t*) event_data;
    	ESP_LOGI(WIFI_TAG, "Station Connected to %s on channel %d\n", (char*) event->ssid, event->channel );
	}
    else if (WIFI_EVENT_STA_DISCONNECTED == event_id)
	{
    	set_tago_wf_disconnected_event();
    	wifi_event_sta_disconnected_t *event = (wifi_event_sta_disconnected_t*) event_data;
    	ESP_LOGI(WIFI_TAG, "Station Disconnected event for reason %d!\n", event->reason);
	}
    else
    {
    	ESP_LOGI(WIFI_TAG, "Event occured id %d\n", event_id);
    }
}



void wifi_init()
{
	tcpip_adapter_init();
	ESP_ERROR_CHECK(esp_event_loop_create_default());

	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&cfg));

	ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));

	wifi_config_t wifi_config = {
		.sta = {
			.scan_method = WIFI_FAST_SCAN
		},
	};
	strcpy((char*) wifi_config.sta.ssid, (char*) ssid);
	strcpy((char*) wifi_config.sta.password, (char*) passwd);
	if (strlen((char*)passwd) == 0) {
		wifi_config.ap.authmode = WIFI_AUTH_OPEN;
	}

	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
	ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
	//ESP_ERROR_CHECK(esp_wifi_set_auto_connect(true));
	ESP_ERROR_CHECK(esp_wifi_start());

	ESP_LOGI(WIFI_TAG, "wifi_init_softap finished. SSID:%s password:%s",
			ssid, passwd);
}

void wifi_reconnect()
{
	ESP_LOGI(WIFI_TAG, "Attempting to reconnect wifi\n");
	wifi_config_t wifi_config = {
		.sta = {
			.scan_method = WIFI_FAST_SCAN
		},
	};
	strcpy((char*) wifi_config.sta.ssid, (char*) ssid);
	strcpy((char*) wifi_config.sta.password, (char*) passwd);
	if (strlen((char*)passwd) == 0) {
		wifi_config.ap.authmode = WIFI_AUTH_OPEN;
	}
	ESP_ERROR_CHECK(esp_wifi_restore());
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
	ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
	//ESP_ERROR_CHECK(esp_wifi_set_auto_connect(true));
	ESP_ERROR_CHECK(esp_wifi_start());
}
