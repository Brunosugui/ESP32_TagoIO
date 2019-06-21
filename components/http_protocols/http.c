/*
 * m_http.c
 *
 *  Created on: Jun 20, 2019
 *      Author: Bruno
 */

#include "http.h"
#include "utils.h"
#include "esp_err.h"
#include "esp_log.h"


#define MAX_HTTP_RECV_BUFFER 512

static const char *HTTP_TAG = "HTTP_CLIENT";

static esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGD(HTTP_TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGD(HTTP_TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGD(HTTP_TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGD(HTTP_TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGD(HTTP_TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            if (!esp_http_client_is_chunked_response(evt->client)) {
                // Write out data
                // printf("%.*s", evt->data_len, (char*)evt->data);
            }

            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGD(HTTP_TAG, "HTTP_EVENT_ON_FINISH");
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGD(HTTP_TAG, "HTTP_EVENT_DISCONNECTED");
            break;
    }
    return ESP_OK;
}

void http_rest_with_url(esp_http_client_method_t method, char* url, char* data)
{
    esp_http_client_config_t config = {
        .url = url,
        .event_handler = _http_event_handler,
    };
    char *post_data = data;
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = ESP_OK;

    switch(method)
    {
    case HTTP_METHOD_GET:
    	esp_http_client_set_url(client, METHOD(GET, url));
    	esp_http_client_set_method(client, HTTP_METHOD_GET);
		err = esp_http_client_perform(client);
		if (err == ESP_OK) {
			ESP_LOGI(HTTP_TAG, "HTTP GET Status = %d, content_length = %d",
					esp_http_client_get_status_code(client),
					esp_http_client_get_content_length(client));
		} else {
			ESP_LOGE(HTTP_TAG, "HTTP GET request failed: %s", esp_err_to_name(err));
		}
    	break;
    case HTTP_METHOD_POST:
		esp_http_client_set_url(client, METHOD(POST, url));
		esp_http_client_set_method(client, HTTP_METHOD_POST);
		esp_http_client_set_post_field(client, post_data, strlen(post_data));
		err = esp_http_client_perform(client);
		if (err == ESP_OK) {
			ESP_LOGI(HTTP_TAG, "HTTP POST Status = %d, content_length = %d",
					esp_http_client_get_status_code(client),
					esp_http_client_get_content_length(client));
		} else {
			ESP_LOGE(HTTP_TAG, "HTTP POST request failed: %s", esp_err_to_name(err));
		}
        	break;
    case HTTP_METHOD_PUT:
    	esp_http_client_set_url(client, METHOD(PUT, url));
		esp_http_client_set_method(client, HTTP_METHOD_PUT);
		err = esp_http_client_perform(client);
		if (err == ESP_OK) {
			ESP_LOGI(HTTP_TAG, "HTTP PUT Status = %d, content_length = %d",
					esp_http_client_get_status_code(client),
					esp_http_client_get_content_length(client));
		} else {
			ESP_LOGE(HTTP_TAG, "HTTP PUT request failed: %s", esp_err_to_name(err));
		}

        	break;
    case HTTP_METHOD_PATCH:
    	esp_http_client_set_url(client, METHOD(PATCH, url));
		esp_http_client_set_method(client, HTTP_METHOD_PATCH);
		esp_http_client_set_post_field(client, NULL, 0);
		err = esp_http_client_perform(client);
		if (err == ESP_OK) {
			ESP_LOGI(HTTP_TAG, "HTTP PATCH Status = %d, content_length = %d",
					esp_http_client_get_status_code(client),
					esp_http_client_get_content_length(client));
		} else {
			ESP_LOGE(HTTP_TAG, "HTTP PATCH request failed: %s", esp_err_to_name(err));
		}
        	break;
    case HTTP_METHOD_DELETE:
    	esp_http_client_set_url(client, METHOD(DELETE, url));
		esp_http_client_set_method(client, HTTP_METHOD_DELETE);
		err = esp_http_client_perform(client);
		if (err == ESP_OK) {
			ESP_LOGI(HTTP_TAG, "HTTP DELETE Status = %d, content_length = %d",
					esp_http_client_get_status_code(client),
					esp_http_client_get_content_length(client));
		} else {
			ESP_LOGE(HTTP_TAG, "HTTP DELETE request failed: %s", esp_err_to_name(err));
		}
        	break;
    case HTTP_METHOD_HEAD:
    	esp_http_client_set_url(client, METHOD(GET, url));
		esp_http_client_set_method(client, HTTP_METHOD_HEAD);
		err = esp_http_client_perform(client);
		if (err == ESP_OK) {
			ESP_LOGI(HTTP_TAG, "HTTP HEAD Status = %d, content_length = %d",
					esp_http_client_get_status_code(client),
					esp_http_client_get_content_length(client));
		} else {
			ESP_LOGE(HTTP_TAG, "HTTP HEAD request failed: %s", esp_err_to_name(err));
		}
        	break;
    default:
    	ESP_LOGE(HTTP_TAG, "HTTP Method not found");
    	break;
    }

    esp_http_client_cleanup(client);
}

void http_rest_with_hostname_path(esp_http_client_method_t method, char* url, char* data)
{
	esp_err_t  err = ESP_OK;
    esp_http_client_config_t config = {
        .host = url,
        .path = "/get",
        .transport_type = HTTP_TRANSPORT_OVER_TCP,
        .event_handler = _http_event_handler,
    };
    char *post_data = data;
    esp_http_client_handle_t client = esp_http_client_init(&config);

    switch(method)
    {
    case HTTP_METHOD_GET:
        err = esp_http_client_perform(client);
        if (err == ESP_OK) {
            ESP_LOGI(HTTP_TAG, "HTTP GET Status = %d, content_length = %d",
                    esp_http_client_get_status_code(client),
                    esp_http_client_get_content_length(client));
        } else {
            ESP_LOGE(HTTP_TAG, "HTTP GET request failed: %s", esp_err_to_name(err));
        }

    	break;
    case HTTP_METHOD_POST:
		esp_http_client_set_url(client, "/post");
		esp_http_client_set_method(client, HTTP_METHOD_POST);
		esp_http_client_set_post_field(client, post_data, strlen(post_data));
		err = esp_http_client_perform(client);
		if (err == ESP_OK) {
			ESP_LOGI(HTTP_TAG, "HTTP POST Status = %d, content_length = %d",
					esp_http_client_get_status_code(client),
					esp_http_client_get_content_length(client));
		} else {
			ESP_LOGE(HTTP_TAG, "HTTP POST request failed: %s", esp_err_to_name(err));
		}
		break;
    case HTTP_METHOD_PUT:
        esp_http_client_set_url(client, "/put");
        esp_http_client_set_method(client, HTTP_METHOD_PUT);
        err = esp_http_client_perform(client);
        if (err == ESP_OK) {
            ESP_LOGI(HTTP_TAG, "HTTP PUT Status = %d, content_length = %d",
                    esp_http_client_get_status_code(client),
                    esp_http_client_get_content_length(client));
        } else {
            ESP_LOGE(HTTP_TAG, "HTTP PUT request failed: %s", esp_err_to_name(err));
        }
		break;
    case HTTP_METHOD_PATCH:
        esp_http_client_set_url(client, "/patch");
        esp_http_client_set_method(client, HTTP_METHOD_PATCH);
        esp_http_client_set_post_field(client, NULL, 0);
        err = esp_http_client_perform(client);
        if (err == ESP_OK) {
            ESP_LOGI(HTTP_TAG, "HTTP PATCH Status = %d, content_length = %d",
                    esp_http_client_get_status_code(client),
                    esp_http_client_get_content_length(client));
        } else {
            ESP_LOGE(HTTP_TAG, "HTTP PATCH request failed: %s", esp_err_to_name(err));
        }
		break;
    case HTTP_METHOD_DELETE:
        esp_http_client_set_url(client, "/delete");
        esp_http_client_set_method(client, HTTP_METHOD_DELETE);
        err = esp_http_client_perform(client);
        if (err == ESP_OK) {
            ESP_LOGI(HTTP_TAG, "HTTP DELETE Status = %d, content_length = %d",
                    esp_http_client_get_status_code(client),
                    esp_http_client_get_content_length(client));
        } else {
            ESP_LOGE(HTTP_TAG, "HTTP DELETE request failed: %s", esp_err_to_name(err));
        }
		break;
    case HTTP_METHOD_HEAD:
        esp_http_client_set_url(client, "/get");
        esp_http_client_set_method(client, HTTP_METHOD_HEAD);
        err = esp_http_client_perform(client);
        if (err == ESP_OK) {
            ESP_LOGI(HTTP_TAG, "HTTP HEAD Status = %d, content_length = %d",
                    esp_http_client_get_status_code(client),
                    esp_http_client_get_content_length(client));
        } else {
            ESP_LOGE(HTTP_TAG, "HTTP HEAD request failed: %s", esp_err_to_name(err));
        }
		break;
    default:
    	ESP_LOGE(HTTP_TAG, "HTTP Method not found");
    	break;

    }

    esp_http_client_cleanup(client);
}


void http_auth_basic(char* user, char* pass, char* url)
{
    esp_http_client_config_t config = {
        .url = GENERATE_BASIC_AUTH_URL(user, pass, url),
        .event_handler = _http_event_handler,
        .auth_type = HTTP_AUTH_TYPE_BASIC,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK) {
        ESP_LOGI(HTTP_TAG, "HTTP Basic Auth Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(HTTP_TAG, "Error perform http request %s", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);
}

void http_auth_basic_redirect(char* user, char* pass, char* url)
{
    esp_http_client_config_t config = {
        .url = GENERATE_BASIC_AUTH_URL(user, pass, url),
        .event_handler = _http_event_handler,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK) {
        ESP_LOGI(HTTP_TAG, "HTTP Basic Auth redirect Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(HTTP_TAG, "Error perform http request %s", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);
}

void http_auth_digest(char* user, char* pass, char* url)
{
    esp_http_client_config_t config = {
        .url = GENERATE_DIGEST_AUTH_URL(user, pass, url),
        .event_handler = _http_event_handler,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK) {
        ESP_LOGI(HTTP_TAG, "HTTP Digest Auth Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(HTTP_TAG, "Error perform http request %s", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);
}





void http_relative_redirect()
{
    esp_http_client_config_t config = {
        .url = "http://httpbin.org/relative-redirect/3",
        .event_handler = _http_event_handler,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK) {
        ESP_LOGI(HTTP_TAG, "HTTP Relative path redirect Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(HTTP_TAG, "Error perform http request %s", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);
}

void http_absolute_redirect()
{
    esp_http_client_config_t config = {
        .url = "http://httpbin.org/absolute-redirect/3",
        .event_handler = _http_event_handler,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK) {
        ESP_LOGI(HTTP_TAG, "HTTP Absolute path redirect Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(HTTP_TAG, "Error perform http request %s", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);
}

void http_redirect_to_https()
{
    esp_http_client_config_t config = {
        .url = "http://httpbin.org/redirect-to?url=https%3A%2F%2Fwww.howsmyssl.com",
        .event_handler = _http_event_handler,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK) {
        ESP_LOGI(HTTP_TAG, "HTTP redirect to HTTPS Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(HTTP_TAG, "Error perform http request %s", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);
}


void http_download_chunk()
{
    esp_http_client_config_t config = {
        .url = "http://httpbin.org/stream-bytes/8912",
        .event_handler = _http_event_handler,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK) {
        ESP_LOGI(HTTP_TAG, "HTTP chunk encoding Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(HTTP_TAG, "Error perform http request %s", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);
}

void http_perform_as_stream_reader()
{
    char *buffer = malloc(MAX_HTTP_RECV_BUFFER + 1);
    if (buffer == NULL) {
        ESP_LOGE(HTTP_TAG, "Cannot malloc http receive buffer");
        return;
    }
    esp_http_client_config_t config = {
        .url = "http://httpbin.org/get",
        .event_handler = _http_event_handler,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err;
    if ((err = esp_http_client_open(client, 0)) != ESP_OK) {
        ESP_LOGE(HTTP_TAG, "Failed to open HTTP connection: %s", esp_err_to_name(err));
        free(buffer);
        return;
    }
    int content_length =  esp_http_client_fetch_headers(client);
    int total_read_len = 0, read_len;
    if (total_read_len < content_length && content_length <= MAX_HTTP_RECV_BUFFER) {
        read_len = esp_http_client_read(client, buffer, content_length);
        if (read_len <= 0) {
            ESP_LOGE(HTTP_TAG, "Error read data");
        }
        buffer[read_len] = 0;
        ESP_LOGD(HTTP_TAG, "read_len = %d", read_len);
    }
    ESP_LOGI(HTTP_TAG, "HTTP Stream reader Status = %d, content_length = %d",
                    esp_http_client_get_status_code(client),
                    esp_http_client_get_content_length(client));
    esp_http_client_close(client);
    esp_http_client_cleanup(client);
    free(buffer);
}
