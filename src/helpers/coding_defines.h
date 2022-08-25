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
 */
#ifndef CODING_DEFINES_H_
#define CODING_DEFINES_H_
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#ifdef ONECMP32
#include "ones_comp_32.h"
#define ENC_TYPE int32c1_t
#define TEST_TYPE int32_t
#define ENC_TYPE_U uint32c1_t
#define TEST_TYPE_U uint32_t
#define ENCODEDFUNCTION(fun) fun##_32c1
#define ENCODEDFUNCTION_U(fun) u_##fun##_32c1
#define MIN INT32_MIN
#define MAX INT32_MAX
#define WIDTH 32
#elif ONECMP64
#include "ones_comp_64.h"
#define ENC_TYPE int64c1_t
#define TEST_TYPE int64_t
#define ENC_TYPE_U uint64c1_t
#define TEST_TYPE_U uint64_t
#define ENCODEDFUNCTION(fun) fun##_64c1
#define ENCODEDFUNCTION_U(fun) u_##fun##_64c1
#define MIN INT64_MIN
#define MAX INT64_MAX
#define WIDTH 64
#elif TWOCMP32
#include "twos_comp_32.h"
#define ENC_TYPE_U uint32c1_t
#define TEST_TYPE_U uint32_t
#define ENC_TYPE int32c1_t
#define TEST_TYPE int32_t
#define ENCODEDFUNCTION(fun) fun##_32c1
#define ENCODEDFUNCTION_U(fun) u_##fun##_32c1
#define MIN INT32_MIN
#define MAX INT32_MAX
#define WIDTH 32
#elif TWOCMP64
#include "twos_comp_64.h"
#define ENC_TYPE_U uint64c1_t
#define TEST_TYPE_U uint64_t
#define ENC_TYPE int64c1_t
#define TEST_TYPE int64_t
#define ENCODEDFUNCTION(fun) fun##_64c1
#define ENCODEDFUNCTION_U(fun) u_##fun##_64c1
#define MIN INT64_MIN
#define MAX INT64_MAX
#define WIDTH 64
#elif RES32
#include "residue_32.h"
#define ENC_TYPE_U uint32c1_t
#define TEST_TYPE_U uint32_t
#define ENC_TYPE int32c1_t
#define TEST_TYPE int32_t
#define ENCODEDFUNCTION(fun) fun##_32c1
#define ENCODEDFUNCTION_U(fun) u_##fun##_32c1
#define MAX INT32_MAX
#define MIN INT32_MIN
#define WIDTH 32
#elif RES64
#include "residue_64.h"
#define ENC_TYPE_U uint64c1_t
#define TEST_TYPE_U uint64_t
#define ENC_TYPE int64c1_t
#define TEST_TYPE int64_t
#define ENCODEDFUNCTION(fun) fun##_64c1
#define ENCODEDFUNCTION_U(fun) u_##fun##_64c1
#define MAX INT64_MAX
#define MIN INT64_MIN
#define WIDTH 64
#elif AN32
#include "an_32.h"
#define ENC_TYPE_U uint32c1_t
#define TEST_TYPE_U uint32_t
#define ENC_TYPE int32c1_t
#define TEST_TYPE int32_t
#define ENCODEDFUNCTION(fun) fun##_32c1
#define ENCODEDFUNCTION_U(fun) u_##fun##_32c1
#define MIN INT32_MIN
#define MAX INT32_MAX
#define WIDTH 32
#elif AN64
#include "an_64.h"
#define ENC_TYPE_U uint64c1_t
#define TEST_TYPE_U uint64_t
#define ENC_TYPE int64c1_t
#define TEST_TYPE int64_t
#define ENCODEDFUNCTION(fun) fun##_64c1
#define ENCODEDFUNCTION_U(fun) u_##fun##_64c1
#define MIN INT64_MIN
#define MAX INT64_MAX
#define WIDTH 64
#elif NONE32
#include "none_32.h"
#define ENC_TYPE_U uint32_t
#define TEST_TYPE_U uint32_t
#define ENC_TYPE int32_t
#define TEST_TYPE int32_t
#define ENCODEDFUNCTION(fun) fun##_32
#define ENCODEDFUNCTION_U(fun) u_##fun##_32
#define MIN INT32_MIN
#define MAX INT32_MAX
#define WIDTH 32
#elif NONE64
#include "none_64.h"
#define ENC_TYPE_U uint64_t
#define TEST_TYPE_U uint64_t
#define ENC_TYPE int64_t
#define TEST_TYPE int64_t
#define ENCODEDFUNCTION(fun) fun##_64
#define ENCODEDFUNCTION_U(fun) u_##fun##_64
#define MIN INT64_MIN
#define MAX INT64_MAX
#define WIDTH 64
#endif

#ifdef __cplusplus
}
#endif //__cplusplus
#endif //CODING_DEFINES_H_