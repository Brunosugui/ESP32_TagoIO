/*
 * json_utils.c
 *
 *  Created on: Jun 24, 2019
 *      Author: Bruno
 */

#include "json_utils.h"
#include "stdio.h"

#define TAGO_JSON_FORMAT				\
		"{\"variable\" : \"%s\","		\
		"\"value\" : \"%s\"}"


void json_utils_get_tago_json(char* variable, char* value, char* buffer)
{
	sprintf(&buffer[0], TAGO_JSON_FORMAT, variable, value);
}
