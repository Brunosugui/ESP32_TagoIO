/*
 * http_tago.c
 *
 *  Created on: Jul 8, 2019
 *      Author: Bruno
 */
#include "http_tago.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "string.h"

#define HTTP_TAGO_TAG			"::HTTP_TAGO::"

//static char device_token[] = CONFIG_ESP_DEVICE_TOKEN;
static char server_url[] = CONFIG_ESP_HTTP_SERVER_ADDR;

static esp_http_client_handle_t client;

static esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGD(HTTP_TAGO_TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGD(HTTP_TAGO_TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGD(HTTP_TAGO_TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGD(HTTP_TAGO_TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGD(HTTP_TAGO_TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            if (!esp_http_client_is_chunked_response(evt->client)) {
                // Write out data
                 printf("%.*s", evt->data_len, (char*)evt->data);
            }

            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGD(HTTP_TAGO_TAG, "HTTP_EVENT_ON_FINISH");
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGD(HTTP_TAGO_TAG, "HTTP_EVENT_DISCONNECTED");
            break;
    }
    return ESP_OK;
}

esp_err_t http_tago_init_client()
{
    esp_http_client_config_t config = {
        .url = server_url,
        .event_handler = _http_event_handler,
    };
    //esp_http_client_handle_t client_aux = esp_http_client_init(&config);
    //memcpy(&client, &client_aux, sizeof(client_aux));
    client = esp_http_client_init(&config);
    esp_http_client_set_url(client, server_url);
    return client != NULL ? ESP_OK : ESP_FAIL;
}

void http_tago_clean_client()
{
	esp_http_client_cleanup(client);
}

esp_err_t http_tago_post_data(char* data)
{
    esp_err_t err = ESP_OK;
    char *post_data = data;

	ESP_LOGI(HTTP_TAGO_TAG, "Post data = %s", post_data);
	esp_http_client_set_method(client, HTTP_METHOD_POST);
	esp_http_client_set_post_field(client, post_data, strlen(post_data));
	esp_http_client_set_header(client, "Content-type", "application/json");
	esp_http_client_set_header(client, "Device-Token", CONFIG_ESP_DEVICE_TOKEN);
	err = esp_http_client_perform(client);
	if (err == ESP_OK) {
		ESP_LOGI(HTTP_TAGO_TAG, "HTTP POST Status = %d, content_length = %d",
				esp_http_client_get_status_code(client),
				esp_http_client_get_content_length(client));
	} else {
		ESP_LOGE(HTTP_TAGO_TAG, "HTTP POST request failed: %s", esp_err_to_name(err));
	}
	return err;
}
