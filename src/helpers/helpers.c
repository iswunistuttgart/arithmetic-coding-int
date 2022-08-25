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
 * @description: Helpers
 */

#define _GNU_SOURCE
#include "helpers.h"
#include <stdio.h>
#include <sched.h>

//One problem is the value INT32_MIN. If encoding it will result in INT32_MIN. Which leads to errors
uint32_t testList_int32[TESTLISTSIZE_INT] = { 0,
					      1,
					      (uint32_t)-1,
					      INT32_MAX,
					      (uint32_t)INT32_MIN,
					      (uint32_t)INT32_MIN + 1 };

struct OperationString getoperationString(enum Operation op)
{
	switch (op) {
	case ADD:
		return (struct OperationString){ "add" };
		break;
	case SUB:
		return (struct OperationString){ "sub" };
		break;
	case MUL:
		return (struct OperationString){ "mul" };
		break;
	case DIV:
		return (struct OperationString){ "div" };
		break;
	case MOD:
		return (struct OperationString){ "mod" };
		break;
	case EQ:
		return (struct OperationString){ "eq" };
		break;
	case NEQ:
		return (struct OperationString){ "neq" };
		break;
	case LEQ:
		return (struct OperationString){ "leq" };
		break;
	case GEQ:
		return (struct OperationString){ "qeq" };
		break;
	case LESS:
		return (struct OperationString){ "less" };
		break;
	case GRT:
		return (struct OperationString){ "grt" };
		break;
	case SHL:
		return (struct OperationString){ "shl" };
		break;
	case SHR:
		return (struct OperationString){ "shr" };
		break;
	case BAND:
		return (struct OperationString){ "and" };
		break;
	case BOR:
		return (struct OperationString){ "or" };
		break;
	case BXOR:
		return (struct OperationString){ "xor" };
		break;
	case BNEG:
		return (struct OperationString){ "neg" };
		break;
	case LAND:
		return (struct OperationString){ "land" };
		break;
	case LOR:
		return (struct OperationString){ "lor" };
		break;
	default:
		return (struct OperationString){ "ERR" };
		break;
	}
}

int32_t getInt32Rand()
{
	int32_t lower = rand();
	int32_t higher = rand();
	higher = higher & 1;
	higher = higher << 31;
	int32_t res = lower + higher;
	return res;
}

int64_t getInt64Rand()
{
	int64_t lower = rand();
	int64_t higher = rand();
	int64_t higher2 = rand();
	higher2 = higher2 >> 30;
	higher2 = higher2 << 62;
	higher = higher << 31;
	return lower + higher + higher2;
}

unsigned int calcHammingDistance8(uint8_t a, uint8_t b)
{
	uint8_t diffs = a ^ b;
	uint8_t bitCount = 0;
	for (; diffs > 0; diffs >>= 1) {
		bitCount += diffs & 1;
	}
	return bitCount;
}

unsigned int calcHammingDistance16(uint16_t a, uint16_t b)
{
	uint16_t diffs = a ^ b;
	uint16_t bitCount = 0;
	for (; diffs > 0; diffs >>= 1) {
		bitCount += diffs & 1;
	}
	return bitCount;
}

unsigned int calcHammingDistance32(unsigned int a, unsigned int b)
{
	unsigned int diffs = a ^ b;
	unsigned int bitCount = 0;
	for (; diffs > 0; diffs >>= 1) {
		bitCount += diffs & 1;
	}
	return bitCount;
}

unsigned int calcHammingDistance64(uint64_t a, uint64_t b)
{
	uint64_t x = a ^ b;
	uint64_t setBits = 0;
	while (x > 0) {
		setBits += x & 1ul;
		x >>= 1;
	}
	return setBits;
}

uint32_t flipBit_uint32(uint32_t val, unsigned int position)
{
	if (position > 31) {
		printf("[Warning] - Position out of Range");
	}
	val = val ^ (1 << position);
	return val;
}
uint64_t flipBit_uint64(uint64_t val, unsigned int position)
{
	if (position > 63) {
		printf("[Warning] - Position out of Range");
	}
	val = val ^ (1ul << position);
	return val;
}
uint8_t stuckAtBit_uint8(uint8_t val, unsigned int position, unsigned int stuck)
{
	if (position > 7) {
		printf("[Warning] - Position out of Range");
	}
	uint8_t mask = (1U << position);
	if (stuck == 0) {
		val = val & (~mask);
	} else if (stuck == 1) {
		val = val | mask;
	} else {
		printf("[Error] - stuck must be 0 or 1");
	}
	return val;
}
uint16_t stuckAtBit_uint16(uint16_t val, unsigned int position,
			   unsigned int stuck)
{
	if (position > 15) {
		printf("[Warning] - Position out of Range");
	}
	uint16_t mask = (1U << position);
	if (stuck == 0) {
		val = val & (~mask);
	} else if (stuck == 1) {
		val = val | mask;
	} else {
		printf("[Error] - stuck must be 0 or 1");
	}
	return val;
}

uint32_t stuckAtBit_uint32(uint32_t val, unsigned int position,
			   unsigned int stuck)
{
	if (position > 31) {
		printf("[Warning] - Position out of Range");
	}
	uint32_t mask = (1U << position);
	if (stuck == 0) {
		val = val & (~mask);
	} else if (stuck == 1) {
		val = val | mask;
	} else {
		printf("[Error] - stuck must be 0 or 1");
	}
	return val;
}

uint64_t stuckAtBit_uint64(uint64_t val, unsigned int position,
			   unsigned int stuck)
{
	if (position > 63) {
		printf("[Warning] - Position out of Range");
	}
	uint64_t mask = (1ul << position);
	if (stuck == 0) {
		val = val & (~mask);
	} else if (stuck == 1) {
		val = val | mask;
	} else {
		printf("[Error] - stuck must be 0 or 1");
	}
	return val;
}

int schedutil_sched_setFIFO(pid_t pid, unsigned int priority)
{
	struct sched_param param;
	param.sched_priority = priority;

	int ret = sched_setscheduler(pid, SCHED_FIFO, &param);
	if (ret != 0) {
		perror("Could not set realtime scheduling");
	}
	printf("[info] Set real time scheduling parameters to pol=SCHED_FIFO prio=%d\n",
	       priority);
	return ret;
}

int schedutil_pinToCore(pid_t pid, int *pinList, int sizePinList)
{
	printf("[info] Set pinning to core:");
	for (int i = 0; i < sizePinList; i++) {
		printf("%d,", pinList[i]);
	}
	printf("\n");
	cpu_set_t set;
	CPU_ZERO(&set);
	for (int i = 0; i < sizePinList; i++) {
		CPU_SET(pinList[i], &set);
	}
	int ret = sched_setaffinity(pid, sizeof(set), &set);
	if (ret != 0) {
		perror("[error] Could not set CPU pinning");
	}
	return ret;
}
