/*
 * m_https.c
 *
 *  Created on: Jun 20, 2019
 *      Author: Bruno
 */

#include "https.h"
#include "esp_err.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "utils.h"


static const char *HTTPS_TAG = "HTTPS_CLIENT";


/* Root cert for howsmyssl.com, taken from howsmyssl_com_root_cert.pem

   The PEM file was extracted from the output of this command:
   openssl s_client -showcerts -connect www.howsmyssl.com:443 </dev/null

   The CA root cert is the last cert given in the chain of certs.

   To embed it in the app binary, the PEM file is named
   in the component.mk COMPONENT_EMBED_TXTFILES variable.
*/

extern const char howsmyssl_com_root_cert_pem_start[] asm("_binary_howsmyssl_com_root_cert_pem_start");
extern const char howsmyssl_com_root_cert_pem_end[]   asm("_binary_howsmyssl_com_root_cert_pem_end");


static esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGD(HTTPS_TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGD(HTTPS_TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGD(HTTPS_TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGD(HTTPS_TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGD(HTTPS_TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            if (!esp_http_client_is_chunked_response(evt->client)) {
                // Write out data
                // printf("%.*s", evt->data_len, (char*)evt->data);
            }

            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGD(HTTPS_TAG, "HTTP_EVENT_ON_FINISH");
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGD(HTTPS_TAG, "HTTP_EVENT_DISCONNECTED");
            break;
    }
    return ESP_OK;
}

void https_with_url(char* url)
{
    esp_http_client_config_t config = {
        .url = url,
        .event_handler = _http_event_handler,
        .cert_pem = howsmyssl_com_root_cert_pem_start,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK) {
        ESP_LOGI(HTTPS_TAG, "HTTPS Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(HTTPS_TAG, "Error perform http request %s", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);
}

void https_with_hostname_path(char* url)
{
    esp_http_client_config_t config = {
        .host = url,
        .path = "/",
        .transport_type = HTTP_TRANSPORT_OVER_SSL,
        .event_handler = _http_event_handler,
        .cert_pem = howsmyssl_com_root_cert_pem_start,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK) {
        ESP_LOGI(HTTPS_TAG, "HTTPS Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(HTTPS_TAG, "Error perform http request %s", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);
}

void https_async(char* url)
{
    esp_http_client_config_t config = {
        .url = url,
        .event_handler = _http_event_handler,
        .is_async = true,
        .timeout_ms = 5000,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err;
    const char *post_data = "Using a Palantír requires a person with great strength of will and wisdom. The Palantíri were meant to "
                            "be used by the Dúnedain to communicate throughout the Realms in Exile. During the War of the Ring, "
                            "the Palantíri were used by many individuals. Sauron used the Ithil-stone to take advantage of the users "
                            "of the other two stones, the Orthanc-stone and Anor-stone, but was also susceptible to deception himself.";
    esp_http_client_set_method(client, HTTP_METHOD_POST);
    esp_http_client_set_post_field(client, post_data, strlen(post_data));
    while (1) {
        err = esp_http_client_perform(client);
        if (err != ESP_ERR_HTTP_EAGAIN) {
            break;
        }
    }
    if (err == ESP_OK) {
        ESP_LOGI(HTTPS_TAG, "HTTPS Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(HTTPS_TAG, "Error perform http request %s", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);
}
