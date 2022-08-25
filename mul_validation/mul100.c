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
 * @description: Matrix multiplication
 */
#include <stdint.h>
void mul100(uint64_t *matA, uint64_t *matB, uint64_t *matC)
{
	for (uint64_t i = 0UL; i < 100UL; i = i + 1) {
		for (uint64_t j = 0; j < 100UL; j = j + 1) {
			uint64_t sumVal = 0UL;
			for (uint64_t k = 0UL; k < 100UL; k = k + 1) {
				sumVal += matA[i * 100UL + k] *
					  matB[k * 100UL + j];
			}
			matC[i * 100UL + j] = sumVal;
		}
	}
}