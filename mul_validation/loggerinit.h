/**
 * @copyright: (c) 2022, Institute for Control Engineering of Machine Tools and Manufacturing Units,
 *             University of Stuttgart
 *             All rights reserved. Licensed under the Apache License, Version 2.0 (the "License");
 *             you may not use this file except in compliance with the License.
 *             You may obtain a copy of the License at
 *                  http://www.apache.org/licenses/LICENSE-2.0
 *             Unless required by applicable law or agreed to in writing, software
 *             distributed under the License is distributed on an "AS IS" BASIS,
 *             WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *             See the License for the specific language governing permissions and
 *             limitations under the License.
 * @author: Marc Fischer <marc.fischer@isw.uni-stuttgart.de>
 * @description: Helper file to init the logger.
 */
#ifndef LOGGERINIT_H_
#define LOGGERINIT_H_ 1

#include "logger.h"
#include <string.h>
#include <stdlib.h>

#define FOREACH_TAG(TAG) TAG(TAG_PUT)

enum TAG_ENUM { FOREACH_TAG(GENERATE_ENUM) TAG_COUNT };
static const char *TAG_STRING[] = { FOREACH_TAG(GENERATE_TAGSTRINGS) };
logger_tagDef_t *tagdef = NULL;
logger_tagPair_t evalList[1] = { { TAG_PUT_START, TAG_PUT_END } };
static inline logger_tagDef_t *makeLoggerDef()
{
	logger_tagDef_t *def = malloc(sizeof(logger_tagDef_t[TAG_COUNT]));
	for (int i = 0; i < TAG_COUNT; i++) {
		def[i].tag = i;
		strcpy(def[i].info, TAG_STRING[i]);
	}
	return def;
}
static inline void log_init()
{
	tagdef = makeLoggerDef();
	logger_config_t a = { LCLOCK_LINUX_REALTIME, 1, 2000 };
	logger_init(a);
}

#endif //LOGGERINIT_H_