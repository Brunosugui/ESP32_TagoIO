/*
 * json_utils.h
 *
 *  Created on: Jun 24, 2019
 *      Author: Bruno
 */

#ifndef COMPONENTS_UTILS_INCLUDE_JSON_UTILS_H_
#define COMPONENTS_UTILS_INCLUDE_JSON_UTILS_H_

#include "stdbool.h"

#define JSON_BRACES_BUFFER(buffer, string, key)			\
	sprintf(buffer, "{\"%s\":\"%s\"}", string, key)

/**< use this for constant strings, i.e. JSON_STR("Nome", "Bruno")*/
#define JSON_ATTR(string, key)		"\""string"\":\""key"\""
#define JSON_ATTRS(attr1, attr2)		attr1","attr2
#define JSON_BRACES(attr)			"{"attr"}"
#define JSON_STR(string, key)		JSON_BRACES(JSON_ATTR(string, key))

char string[] = JSON_BRACES(JSON_ATTRS(JSON_ATTR("Nome", "Bruno"),JSON_ATTR("Nome", "Mell")));

#define JSON_MAX_ATTR_VALUE			16

typedef struct{
	char string[JSON_MAX_ATTR_VALUE];
	char *key[JSON_MAX_ATTR_VALUE];
	int keys_number;
}json_attr_t;

typedef struct json_obj_t{
	json_attr_t attributes[JSON_MAX_ATTR_VALUE];
	struct json_obj_t rec_json_attr;
	bool is_json_recursive;
	int attr_number;
}json_obj_struct_t;
\
//todo test

#endif /* COMPONENTS_UTILS_INCLUDE_JSON_UTILS_H_ */
