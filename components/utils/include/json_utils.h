/*
 * json_utils.h
 *
 *  Created on: Jun 24, 2019
 *      Author: Bruno
 */

#ifndef COMPONENTS_UTILS_INCLUDE_JSON_UTILS_H_
#define COMPONENTS_UTILS_INCLUDE_JSON_UTILS_H_

#include "stdbool.h"

/**< use this for constant strings, i.e. JSON_STR("Nome", "Bruno")*/
#define JSON_ATTR(string, key)					"\""string"\":\""key"\""

#define JSON_ATTRS(attr1, attr2)				attr1","attr2

#define JSON_BRACES(attr)						"{"attr"}"

#define JSON_STR_KEY(string, key)				JSON_BRACES(JSON_ATTR(string, key))

//#define JSON_STR_KEYS(format)


char string1[] = JSON_STR_KEY("Nome", "Bruno");
char string[] = JSON_BRACES(JSON_ATTRS(JSON_ATTR("Nome", "Bruno"),JSON_ATTR("Nome", "Mell")));

#define JSON_MAX_ATTR_SIZE			16
/**
typedef struct{
	char string[JSON_MAX_ATTR_SIZE];
	char *key[JSON_MAX_ATTR_SIZE];
	int keys_number;
}json_attr_t;

typedef struct json_obj_t{
	json_attr_t attributes[JSON_MAX_ATTR_SIZE];
	struct json_obj_t json_key;
	bool is_json_key;
	int attr_number;
}json_obj_struct_t;

json_obj_struct_t my_obj = {
		.attributes[0] = {
				.string = "Nome",
				.key = "Bruno",
				.keys_number = 1
		},

		.attributes[1] = {
				string = "Nome",
				.key = "Mell",
				.keys_number = 1
		},


		.is_json_key = 0,
		.attr_number = 2
};

void generate_json(json_obj_struct_t obj);
*/

#endif /* COMPONENTS_UTILS_INCLUDE_JSON_UTILS_H_ */
