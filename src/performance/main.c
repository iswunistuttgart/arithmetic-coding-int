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
 * @description: Do perfromance measuremnts for each operation and encoding
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "logger.h"
#include "helpers.h"

#include "coding_defines.h"

#define FOREACH_TAG(TAG)                                                       \
	TAG(TAG_ADD)                                                           \
	TAG(TAG_SUB)                                                           \
	TAG(TAG_MUL)                                                           \
	TAG(TAG_DIV)                                                           \
	TAG(TAG_LEQ)                                                           \
	TAG(TAG_GEQ)                                                           \
	TAG(TAG_EQ)                                                            \
	TAG(TAG_NEQ)                                                           \
	TAG(TAG_LESS)                                                          \
	TAG(TAG_GREATER)                                                       \
	TAG(TAG_GRT)                                                           \
	TAG(TAG_AND)                                                           \
	TAG(TAG_OR)                                                            \
	TAG(TAG_XOR)                                                           \
	TAG(TAG_NOT)                                                           \
	TAG(TAG_MOD)                                                           \
	TAG(TAG_NEG)                                                           \
	TAG(TAG_LAND)                                                          \
	TAG(TAG_LOR)                                                           \
	TAG(TAG_SHL)                                                           \
	TAG(TAG_SHR)                                                           \
	TAG(TAG_ADD_U)                                                         \
	TAG(TAG_SUB_U)                                                         \
	TAG(TAG_MUL_U)                                                         \
	TAG(TAG_DIV_U)                                                         \
	TAG(TAG_LEQ_U)                                                         \
	TAG(TAG_GEQ_U)                                                         \
	TAG(TAG_EQ_U)                                                          \
	TAG(TAG_NEQ_U)                                                         \
	TAG(TAG_LESS_U)                                                        \
	TAG(TAG_GREATER_U)                                                     \
	TAG(TAG_GRT_U)                                                         \
	TAG(TAG_AND_U)                                                         \
	TAG(TAG_OR_U)                                                          \
	TAG(TAG_XOR_U)                                                         \
	TAG(TAG_NOT_U)                                                         \
	TAG(TAG_MOD_U)                                                         \
	TAG(TAG_NEG_U)                                                         \
	TAG(TAG_LAND_U)                                                        \
	TAG(TAG_LOR_U)                                                         \
	TAG(TAG_SHL_U)                                                         \
	TAG(TAG_SHR_U)

enum TAG_ENUM { FOREACH_TAG(GENERATE_ENUM) TAG_COUNT };

static const char *TAG_STRING[] = { FOREACH_TAG(GENERATE_TAGSTRINGS) };

logger_tagDef_t *makeLoggerDef()
{
	logger_tagDef_t *def = malloc(sizeof(logger_tagDef_t[TAG_COUNT]));
	for (int i = 0; i < TAG_COUNT; i++) {
		def[i].tag = i;
		strcpy(def[i].info, TAG_STRING[i]);
	}
	return def;
}

int main(int argc, char **argv)
{
	schedutil_sched_setFIFO(0, 99);
	int core = 3;
	schedutil_pinToCore(0, &core, 1);
#ifdef AN64
	init();
#endif
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Performance measurement of encoding: " ENCODING_NAME "\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	int test_count = 250000;
	int num_tests = 500;
	logger_config_t a = { LCLOCK_LINUX_REALTIME, 1,
			      num_tests * TAG_COUNT * 2 };
	logger_init(a);

	ENC_TYPE *listX = (ENC_TYPE *)malloc(sizeof(ENC_TYPE) * (test_count));
	ENC_TYPE *listY = (ENC_TYPE *)malloc(sizeof(ENC_TYPE) * (test_count));
	ENC_TYPE_U *listX_U =
		(ENC_TYPE_U *)malloc(sizeof(ENC_TYPE_U) * (test_count));
	ENC_TYPE_U *listY_U =
		(ENC_TYPE_U *)malloc(sizeof(ENC_TYPE_U) * (test_count));
	char *filename = "rands.dat";
	if (argc > 1) {
		filename = argv[1];
	}
	FILE *pFile = fopen(filename, "r");
	if (!pFile) {
		printf("[Error] Could not open files: %s\n", strerror(errno));
		return -2;
	}
	int buflen = 255;
	char buffer[buflen];
	uint64_t i = 0;
	while (fgets(buffer, buflen, pFile)) {
		uint32_t val = atol(buffer);
		if (i < test_count) {
			listX[i] = ENCODEDFUNCTION(encode)(val);
			listX_U[i] = ENCODEDFUNCTION_U(encode)(val);
		} else if (i < test_count * 2) {
			listY[i - test_count] = ENCODEDFUNCTION(encode)(val);
			listY_U[i - test_count] =
				ENCODEDFUNCTION_U(encode)(val);
		}
		i++;
	}
	fclose(pFile);

	for (int t = 0; t < num_tests; t++) {
		ENC_TYPE r_enc;

		logger_addLogEntry(TAG_ADD_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc = ENCODEDFUNCTION(add)(listX[i], listY[i]);
		}
		logger_addLogEntry(TAG_ADD_END, t, 0);

		logger_addLogEntry(TAG_SUB_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc = ENCODEDFUNCTION(sub)(listX[i], listY[i]);
		}
		logger_addLogEntry(TAG_SUB_END, t, 0);

		logger_addLogEntry(TAG_MUL_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc = ENCODEDFUNCTION(mul)(listX[i], listY[i]);
		}
		logger_addLogEntry(TAG_MUL_END, t, 0);

		logger_addLogEntry(TAG_DIV_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc = ENCODEDFUNCTION(div)(listX[i], listY[i]);
		}
		logger_addLogEntry(TAG_DIV_END, t, 0);

		logger_addLogEntry(TAG_MOD_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc = ENCODEDFUNCTION(mod)(listX[i], listY[i]);
		}
		logger_addLogEntry(TAG_MOD_END, t, 0);

		logger_addLogEntry(TAG_EQ_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc = ENCODEDFUNCTION(eq)(listX[i], listY[i]);
		}
		logger_addLogEntry(TAG_EQ_END, t, 0);

		logger_addLogEntry(TAG_NEQ_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc = ENCODEDFUNCTION(neq)(listX[i], listY[i]);
		}
		logger_addLogEntry(TAG_NEQ_END, t, 0);

		logger_addLogEntry(TAG_LEQ_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc = ENCODEDFUNCTION(leq)(listX[i], listY[i]);
		}
		logger_addLogEntry(TAG_LEQ_END, t, 0);

		logger_addLogEntry(TAG_GEQ_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc = ENCODEDFUNCTION(geq)(listX[i], listY[i]);
		}
		logger_addLogEntry(TAG_GEQ_END, t, 0);

		logger_addLogEntry(TAG_LESS_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc = ENCODEDFUNCTION(less)(listX[i], listY[i]);
		}
		logger_addLogEntry(TAG_LESS_END, t, 0);

		logger_addLogEntry(TAG_GRT_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc = ENCODEDFUNCTION(grt)(listX[i], listY[i]);
		}
		logger_addLogEntry(TAG_GRT_END, t, 0);

		logger_addLogEntry(TAG_SHL_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc = ENCODEDFUNCTION(shl)(listX[i], listY[i]);
		}
		logger_addLogEntry(TAG_SHL_END, t, 0);

		logger_addLogEntry(TAG_LAND_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc = ENCODEDFUNCTION(land)(listX[i], listY[i]);
		}
		logger_addLogEntry(TAG_LAND_END, t, 0);

		logger_addLogEntry(TAG_LOR_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc = ENCODEDFUNCTION(lor)(listX[i], listY[i]);
		}
		logger_addLogEntry(TAG_LOR_END, t, 0);

		logger_addLogEntry(TAG_AND_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc = ENCODEDFUNCTION(and)(listX[i], listY[i]);
		}
		logger_addLogEntry(TAG_AND_END, t, 0);

		logger_addLogEntry(TAG_OR_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc = ENCODEDFUNCTION(or)(listX[i], listY[i]);
		}
		logger_addLogEntry(TAG_OR_END, t, 0);

		logger_addLogEntry(TAG_XOR_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc = ENCODEDFUNCTION(xor)(listX[i], listY[i]);
		}
		logger_addLogEntry(TAG_XOR_END, t, 0);

		logger_addLogEntry(TAG_NEG_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc = ENCODEDFUNCTION(neg)(listX[i]);
		}
		logger_addLogEntry(TAG_NEG_END, t, 0);

		//Unsigned
		ENC_TYPE_U r_enc_u;
		logger_addLogEntry(TAG_ADD_U_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc_u =
				ENCODEDFUNCTION_U(add)(listX_U[i], listY_U[i]);
		}
		logger_addLogEntry(TAG_ADD_U_END, t, 0);

		logger_addLogEntry(TAG_SUB_U_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc_u =
				ENCODEDFUNCTION_U(sub)(listX_U[i], listY_U[i]);
		}
		logger_addLogEntry(TAG_SUB_U_END, t, 0);

		logger_addLogEntry(TAG_MUL_U_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc_u =
				ENCODEDFUNCTION_U(mul)(listX_U[i], listY_U[i]);
		}
		logger_addLogEntry(TAG_MUL_U_END, t, 0);

		logger_addLogEntry(TAG_DIV_U_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc_u =
				ENCODEDFUNCTION_U(div)(listX_U[i], listY_U[i]);
		}
		logger_addLogEntry(TAG_DIV_U_END, t, 0);

		logger_addLogEntry(TAG_MOD_U_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc_u =
				ENCODEDFUNCTION_U(mod)(listX_U[i], listY_U[i]);
		}
		logger_addLogEntry(TAG_MOD_U_END, t, 0);

		logger_addLogEntry(TAG_EQ_U_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc_u = ENCODEDFUNCTION_U(eq)(listX_U[i], listY_U[i]);
		}
		logger_addLogEntry(TAG_EQ_U_END, t, 0);

		logger_addLogEntry(TAG_NEQ_U_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc_u =
				ENCODEDFUNCTION_U(neq)(listX_U[i], listY_U[i]);
		}
		logger_addLogEntry(TAG_NEQ_U_END, t, 0);

		logger_addLogEntry(TAG_LEQ_U_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc_u =
				ENCODEDFUNCTION_U(leq)(listX_U[i], listY_U[i]);
		}
		logger_addLogEntry(TAG_LEQ_U_END, t, 0);

		logger_addLogEntry(TAG_GEQ_U_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc_u =
				ENCODEDFUNCTION_U(geq)(listX_U[i], listY_U[i]);
		}
		logger_addLogEntry(TAG_GEQ_U_END, t, 0);

		logger_addLogEntry(TAG_LESS_U_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc_u =
				ENCODEDFUNCTION_U(less)(listX_U[i], listY_U[i]);
		}
		logger_addLogEntry(TAG_LESS_U_END, t, 0);

		logger_addLogEntry(TAG_GRT_U_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc_u =
				ENCODEDFUNCTION_U(grt)(listX_U[i], listY_U[i]);
		}
		logger_addLogEntry(TAG_GRT_U_END, t, 0);

		logger_addLogEntry(TAG_SHL_U_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc_u =
				ENCODEDFUNCTION_U(shl)(listX_U[i], listY_U[i]);
		}
		logger_addLogEntry(TAG_SHL_U_END, t, 0);

		logger_addLogEntry(TAG_SHR_U_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc_u =
				ENCODEDFUNCTION_U(shr)(listX_U[i], listY_U[i]);
		}
		logger_addLogEntry(TAG_SHR_U_END, t, 0);

		logger_addLogEntry(TAG_LAND_U_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc_u =
				ENCODEDFUNCTION_U(land)(listX_U[i], listY_U[i]);
		}
		logger_addLogEntry(TAG_LAND_U_END, t, 0);

		logger_addLogEntry(TAG_LOR_U_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc_u =
				ENCODEDFUNCTION_U(lor)(listX_U[i], listY_U[i]);
		}
		logger_addLogEntry(TAG_LOR_U_END, t, 0);

		logger_addLogEntry(TAG_AND_U_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc_u =
				ENCODEDFUNCTION_U(and)(listX_U[i], listY_U[i]);
		}
		logger_addLogEntry(TAG_AND_U_END, t, 0);

		logger_addLogEntry(TAG_OR_U_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc_u = ENCODEDFUNCTION_U(or)(listX_U[i], listY_U[i]);
		}
		logger_addLogEntry(TAG_OR_U_END, t, 0);

		logger_addLogEntry(TAG_XOR_U_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc_u =
				ENCODEDFUNCTION_U(xor)(listX_U[i], listY_U[i]);
		}
		logger_addLogEntry(TAG_XOR_U_END, t, 0);

		logger_addLogEntry(TAG_NEG_U_START, t, 0);
		for (int i = 0; i < test_count; i++) {
			r_enc_u = ENCODEDFUNCTION_U(neg)(listX_U[i]);
		}
		logger_addLogEntry(TAG_NEG_U_END, t, 0);
	}

	logger_tagDef_t *tagdef = makeLoggerDef();
	logger_tagPair_t evalList[35] = { { TAG_ADD_START, TAG_ADD_END },
					  { TAG_ADD_U_START, TAG_ADD_U_END },
					  { TAG_SUB_START, TAG_SUB_END },
					  { TAG_SUB_U_START, TAG_SUB_U_END },
					  { TAG_MUL_START, TAG_MUL_END },
					  { TAG_MUL_U_START, TAG_MUL_U_END },
					  { TAG_DIV_START, TAG_DIV_END },
					  { TAG_DIV_U_START, TAG_DIV_U_END },
					  { TAG_EQ_START, TAG_EQ_END },
					  { TAG_EQ_U_START, TAG_EQ_U_END },
					  { TAG_NEQ_START, TAG_NEQ_END },
					  { TAG_NEQ_U_START, TAG_NEQ_U_END },
					  { TAG_LEQ_START, TAG_LEQ_END },
					  { TAG_LEQ_U_START, TAG_LEQ_U_END },
					  { TAG_GEQ_START, TAG_GEQ_END },
					  { TAG_GEQ_U_START, TAG_GEQ_U_END },
					  { TAG_LESS_START, TAG_LESS_END },
					  { TAG_LESS_U_START, TAG_LESS_U_END },
					  { TAG_GRT_START, TAG_GRT_END },
					  { TAG_GRT_U_START, TAG_GRT_U_END },
					  { TAG_SHR_U_START, TAG_SHR_U_END },
					  { TAG_SHL_START, TAG_SHL_END },
					  { TAG_SHL_U_START, TAG_SHL_U_END },
					  { TAG_LAND_START, TAG_LAND_END },
					  { TAG_LAND_U_START, TAG_LAND_U_END },
					  { TAG_LOR_START, TAG_LOR_END },
					  { TAG_LOR_U_START, TAG_LOR_U_END },
					  { TAG_AND_START, TAG_AND_END },
					  { TAG_AND_U_START, TAG_AND_U_END },
					  { TAG_OR_START, TAG_OR_END },
					  { TAG_OR_U_START, TAG_OR_U_END },
					  { TAG_XOR_START, TAG_XOR_END },
					  { TAG_XOR_U_START, TAG_XOR_U_END },
					  { TAG_NEG_START, TAG_NEG_END },
					  { TAG_NEG_U_START, TAG_NEG_U_END } };

	char bufname[300];
	sprintf(bufname, "perf_%s.csv", ENCODING_NAME);

	logger_evaluate(evalList, 35, tagdef, TAG_COUNT, bufname);
}