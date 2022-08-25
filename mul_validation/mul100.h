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
 * @description: Header to include the encoded and unencoded multiplication versions
 */
#ifndef MUL100_H_
#define MUL100_H_ 1

#include <stdint.h>
void mul100(uint64_t *matA, uint64_t *matB, uint64_t *matC);
void mul100_enc(uint64_t *matA, uint64_t *matB, uint64_t *matC);

#endif