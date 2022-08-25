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
 * @description: Main file of the unencoded validation
 */
#include "mul100.h"
#include "mat.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

static inline void signal_fault()
{
	exit(2);
}

#define DATALEN 10000

uint64_t mA[DATALEN], mB[DATALEN], mC[DATALEN];
uint64_t mA_e[DATALEN], mB_e[DATALEN], mC_e[DATALEN];

void precomputation()
{
	for (int i = 0; i < DATALEN; i++) {
		mA[i] = matA[i];
		mB[i] = matB[i];
		mA_e[i] = matA[i];
		mB_e[i] = matB[i];
	}
}
void postcomputation()
{
}

int __attribute__((noinline)) computation_enc()
{
	mul100(mA, mB, mC);
}

int computation()
{
	return computation_enc();
}

#ifdef DO_TIME_MEAS
#include "logger.h"
#include "loggerinit.h"
#include "helpers.h"
#include "string.h"
#endif

int main(int argc, char *argv[])
{
#ifdef DO_TIME_MEAS
	log_init();
	int coreList = 3;
	schedutil_pinToCore(0, &coreList, 1);
	schedutil_sched_setFIFO(0, 99);
#endif

	precomputation();

#ifdef DO_TIME_MEAS
	for (int i = 0; i < 1000; i++) {
		logger_addLogEntry(TAG_PUT_START, i, 0);
#endif

		int r = computation();

#ifdef DO_TIME_MEAS
		logger_addLogEntry(TAG_PUT_END, i, 0);
	}

	logger_evaluate(evalList, 1, tagdef, TAG_COUNT, "mul100.csv");
	logger_clear();
#endif

	postcomputation();

	mul100(mA_e, mB_e, mC_e);
	printf("[Info] Result:");
	for (int i = 0; i < DATALEN; i++) {
		if (mC_e[i] != mC[i]) {
			printf("ERROR\n");
			return 1; // return ANUNEXP
		}
	}
	printf("GOOD\n");
	return 0;
}
