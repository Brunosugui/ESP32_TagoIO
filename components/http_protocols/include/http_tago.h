/*
 * http_tago.h
 *
 *  Created on: Jul 8, 2019
 *      Author: Bruno
 */

#ifndef COMPONENTS_HTTP_PROTOCOLS_INCLUDE_HTTP_TAGO_H_
#define COMPONENTS_HTTP_PROTOCOLS_INCLUDE_HTTP_TAGO_H_

#include "esp_err.h"

esp_err_t http_tago_init_client();
void http_tago_clean_client();
esp_err_t http_tago_post_data(char* data);

#endif /* COMPONENTS_HTTP_PROTOCOLS_INCLUDE_HTTP_TAGO_H_ */
