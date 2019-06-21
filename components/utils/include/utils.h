/*
 * utils.h
 *
 *  Created on: Jun 20, 2019
 *      Author: Bruno
 */

#ifndef COMPONENTS_MODULES_UTILS_INCLUDE_UTILS_H_
#define COMPONENTS_MODULES_UTILS_INCLUDE_UTILS_H_

#include "string.h"

#define METHOD_GET(url)						strcat(url, "/get")
#define METHOD_POST(url)					strcat(url,  "/post")
#define METHOD_PUT(url)						strcat(url,  "/put")
#define METHOD_PATCH(url)					strcat(url,  "/patch")
#define METHOD_DELETE(url)					strcat(url,  "/delete")
#define METHOD_HEAD(url)					strcat(url,  "/head")

#define METHOD(method, url)						METHOD_ ## method (url)

#define CAT_SYMBOL(word1, symbol, word2)		strcat((char*)strcat((char*) word1, symbol), word2)

#define USER_PASS(user, pass)					CAT_SYMBOL(user, ":", pass)
#define FIRST_ADDR(user,pass)					strcat("http://", (char*) USER_PASS(user, pass))

#define _BASIC_AUTH_SEC_ADDR(url)				CAT_SYMBOL(url, "/", "basic_auth")
#define USER_PASS_ADDR(user, pass)				CAT_SYMBOL(user, "/", pass)

#define BASIC_AUTH_SEC_ADDR(user, pass, url)	CAT_SYMBOL(_BASIC_AUTH_SEC_ADDR(url), "/", USER_PASS_ADDR(user, pass))


#define __DIGEST_AUTH_SEC_ADDR(url)				CAT_SYMBOL(url, "/", "digest-auth/auth")
#define _DIGEST_AUTH_SEC_ADDR(user, pass, url)	CAT_SYMBOL(__DIGEST_AUTH_SEC_ADDR(url), "/", USER_PASS_ADDR(user, pass))
#define DIGEST_AUTH_SEC_ADDR(user, pass, url)	CAT_SYMBOL(_DIGEST_AUTH_SEC_ADDR(user, pass, url), "/", "MD5/never")


#define GENERATE_BASIC_AUTH_URL(user, pass, url)		\
	CAT_SYMBOL(FIRST_ADDR(user, pass), 					\
	"@", BASIC_AUTH_SEC_ADDR(user, pass, url))

#define GENERATE_DIGEST_AUTH_URL(user, pass, url)		\
	CAT_SYMBOL(FIRST_ADDR(user, pass), "@", 			\
	DIGEST_AUTH_SEC_ADDR(user, pass, url)		)


#endif /* COMPONENTS_MODULES_UTILS_INCLUDE_UTILS_H_ */
