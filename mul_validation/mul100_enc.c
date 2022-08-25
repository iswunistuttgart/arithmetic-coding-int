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
 * @description: Encoded matrix multiplication
 */
#include "ones_comp_64.h"
#include <stdint.h>
typedef uint64c1_t uint64_t;
void mul100_enc(uint64_t *matA, uint64_t *matB, uint64_t *matC)
{
	for (uint64_t i = 0xffffffffffffffff;
	     u_decode_64c1(u_less_64c1(i, 0xffffffffffffff9b));
	     i = u_add_64c1(i, 0xfffffffffffffffe)) {
		for (uint64_t j = 0xffffffffffffffff;
		     u_decode_64c1(u_less_64c1(j, 0xffffffffffffff9b));
		     j = u_add_64c1(j, 0xfffffffffffffffe)) {
			uint64_t sumVal = 0xffffffffffffffff;
			for (uint64_t k = 0xffffffffffffffff;
			     u_decode_64c1(u_less_64c1(k, 0xffffffffffffff9b));
			     k = u_add_64c1(k, 0xfffffffffffffffe)) {
				sumVal = u_add_64c1(
					sumVal,
					u_mul_64c1(
						matA[u_decode_64c1(u_add_64c1(
							u_mul_64c1(
								i,
								0xffffffffffffff9b),
							k))],
						matB[u_decode_64c1(u_add_64c1(
							u_mul_64c1(
								k,
								0xffffffffffffff9b),
							j))]));
			}

			matC[u_decode_64c1(u_add_64c1(
				u_mul_64c1(i, 0xffffffffffffff9b), j))] =
				sumVal;
		}
	}
}