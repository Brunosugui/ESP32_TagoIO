/*
 * m_http.h
 *
 *  Created on: Jun 20, 2019
 *      Author: Bruno
 */

#ifndef COMPONENTS_MODULES_HTTP_INCLUDE_M_HTTP_H_
#define COMPONENTS_MODULES_HTTP_INCLUDE_M_HTTP_H_

#include "esp_http_client.h"

void http_rest_with_url(esp_http_client_method_t method, char* url, char* data);
void http_rest_with_hostname_path(esp_http_client_method_t method, char* url, char* data);
void http_auth_basic(char* user, char* pass, char* url);
void http_auth_basic_redirect(char* user, char* pass, char* url);
void http_auth_digest(char* user, char* pass, char* url);
void http_relative_redirect();
void http_absolute_redirect();
void http_redirect_to_https();
void http_download_chunk();
void http_perform_as_stream_reader();


#endif /* COMPONENTS_MODULES_HTTP_INCLUDE_M_HTTP_H_ */
