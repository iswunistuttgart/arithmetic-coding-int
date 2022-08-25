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

#ifndef HELPERS_H_
#define HELPERS_H_
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
#include <stdint.h>
#include <stdlib.h>

//Colors on linux systems
#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

struct OperationString {
	char name[5];
};

enum Operation {
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	EQ,
	NEQ,
	LEQ,
	GEQ,
	LESS,
	GRT,
	SHL,
	SHR,
	BAND,
	BOR,
	BXOR,
	BNEG,
	LAND,
	LOR
};

struct OperationString getoperationString(enum Operation op);

int32_t getInt32Rand();

int64_t getInt64Rand();

unsigned int calcHammingDistance8(uint8_t a, uint8_t b);
unsigned int calcHammingDistance16(uint16_t a, uint16_t b);
unsigned int calcHammingDistance32(unsigned int a, unsigned int b);
unsigned int calcHammingDistance64(uint64_t a, uint64_t b);

uint32_t flipBit_uint32(uint32_t val, unsigned int position);

uint64_t flipBit_uint64(uint64_t val, unsigned int position);

uint8_t stuckAtBit_uint8(uint8_t val, unsigned int position,
			 unsigned int stuck);

uint16_t stuckAtBit_uint16(uint16_t val, unsigned int position,
			   unsigned int stuck);

uint32_t stuckAtBit_uint32(uint32_t val, unsigned int position,
			   unsigned int stuck);

uint64_t stuckAtBit_uint64(uint64_t val, unsigned int position,
			   unsigned int stuck);

int schedutil_sched_setFIFO(pid_t pid, unsigned int priority);
int schedutil_pinToCore(pid_t pid, int *pinList, int sizePinList);

#define TESTLISTSIZE_INT 6
extern uint32_t testList_int32[TESTLISTSIZE_INT];

#ifdef __cplusplus
}
#endif //__cplusplus
#endif //HELPERS_H_