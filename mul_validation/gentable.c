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
 * @description: This files helps to generate static tables for the validation.
 */
#include "helpers.h"
#include <stdio.h>
int main(int argc, char *argv[])
{
	printf("uint64_t matA[10000] = {\n");
	for (int i = 0; i < 10000; i++) {
		if (i != 0)
			printf(",");
		printf("%lu", getInt64Rand());
	}
	printf("};\n");
	printf("uint64_t matB[10000] = {\n");
	for (int i = 0; i < 10000; i++) {
		if (i != 0)
			printf(",");
		printf("%lu", getInt64Rand());
	}
	printf("};\n");
}