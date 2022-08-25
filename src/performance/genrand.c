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
 * @description: This file helps to generate random numers as input for the performance test.
 */
#include "pcg_variants.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
	pcg32_random_t rng;
	pcg32_srandom_r(&rng, 51616u, 888u);

	FILE *pFile = fopen("rands.dat", "w");
	if (!pFile) {
		printf("[Error] Could not open files: %s\n", strerror(errno));
		return -2;
	}

	for (int i = 0; i < 500000; i++) {
		uint32_t val = pcg32_random_r(&rng);
		fprintf(pFile, "%u\n", val);
	}
	fclose(pFile);
}