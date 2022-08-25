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
 * @description: Provides all primitive functions for encoding one channel with the twos complement
 */

#ifndef TWOSCMP64_1_H_
#define TWOSCMP64_1_H_
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#include "common.h"
#include "helpers.h"
#include <stdint.h>
#include <stdlib.h>

#define ENCODING_NAME "TWOS_COMPLEMENT_64BIT"

// Encoded type definitions
typedef int64_t int64c1_t;
typedef uint64_t uint64c1_t;

// As for encoding twoscomp. Inverting+1 is the same as mul with INT_MAX
static uint64c1_t A1_64 = 0xFFFFFFFFFFFFFFFF;

AC_INLINE int64c1_t encode_64c1(int64_t x)
{
	int64c1_t r_c1 = (int64c1_t)A1_64 * (int64c1_t)x;
	return r_c1;
}
AC_INLINE uint64c1_t u_encode_64c1(uint64_t x)
{
	uint64c1_t r_c1 = (uint64c1_t)A1_64 * (uint64c1_t)x;
	return r_c1;
}

AC_INLINE int64_t decode_64c1(int64c1_t x_c1)
{
	int64_t r = (int64_t)(x_c1 * (int64c1_t)A1_64);
	return r;
}
AC_INLINE uint64_t u_decode_64c1(uint64c1_t x_c1)
{
	uint64_t r = (uint64_t)(x_c1 * (uint64c1_t)A1_64);
	return r;
}

AC_INLINE int check_64c1(int64c1_t val, int64c1_t valc)
{
	return val == decode_64c1(valc);
}
AC_INLINE int u_check_64c1(uint64c1_t val, uint64c1_t valc)
{
	return val == u_decode_64c1(valc);
}

AC_INLINE int64c1_t add_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t r_c1 = x_c1 + y_c1;
	return r_c1;
}
AC_INLINE uint64c1_t u_add_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t r_c1 = x_c1 + y_c1;
	return r_c1;
}

AC_INLINE int64c1_t sub_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t r_c1 = x_c1 - y_c1;
	return r_c1;
}
AC_INLINE uint64c1_t u_sub_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t r_c1 = x_c1 - y_c1;
	return r_c1;
}

AC_INLINE int64c1_t mul_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t r_c1 = x_c1 * y_c1 * A1_64;
	return r_c1;
}
AC_INLINE uint64c1_t u_mul_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t r_c1 = x_c1 * y_c1 * A1_64;
	return r_c1;
}

AC_INLINE int64c1_t div_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t r_c1 = (x_c1 / y_c1) * (int64c1_t)A1_64;
	return r_c1;
}
AC_INLINE uint64c1_t u_div_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	//unsigend div cannot be operate on the native operation.
	//Therefore, we decode the values and encode it back if the reverse check is valid.
	uint64c1_t x_d1 = x_c1 * A1_64;
	uint64c1_t y_d1 = y_c1 * A1_64;
	uint64c1_t r_c1 = x_d1 / y_d1;
	if (r_c1 * y_d1 + x_d1 % y_d1 == x_d1) {
		r_c1 *= A1_64;
	}
	return r_c1;
}

AC_INLINE int64c1_t mod_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t r_c1 = x_c1 % y_c1;
	return r_c1;
}
AC_INLINE uint64c1_t u_mod_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	//unsigend mod cannot be operate on the native operation.
	//Therefore, we decode the values and encode it back if the reverse check is valid.
	uint64c1_t x_d1 = x_c1 * A1_64;
	uint64c1_t y_d1 = y_c1 * A1_64;
	uint64c1_t r_c1 = x_d1 % y_d1;
	if ((x_d1 / y_d1) * y_d1 + r_c1 == x_d1) {
		r_c1 *= A1_64;
	}
	return r_c1;
}

AC_INLINE int64c1_t eq_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t r_c1 = 0;
	if (x_c1 == y_c1) {
		r_c1 = A1_64;
	}
	return r_c1;
}
AC_INLINE uint64c1_t u_eq_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t r_c1 = 0;
	if (x_c1 == y_c1) {
		r_c1 = A1_64;
	}
	return r_c1;
}

AC_INLINE int64c1_t neq_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t r_c1 = 0;
	if (x_c1 != y_c1) {
		r_c1 = A1_64;
	}
	return r_c1;
}
AC_INLINE uint64c1_t u_neq_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t r_c1 = 0;
	if (x_c1 != y_c1) {
		r_c1 = A1_64;
	}
	return r_c1;
}

AC_INLINE int64c1_t less_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t r_c1 = 0;
	if (x_c1 > y_c1) {
		r_c1 = A1_64;
	}
	return r_c1;
}
AC_INLINE uint64c1_t u_less_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t r_c1 = 0;
	if (x_c1 > y_c1) {
		r_c1 = A1_64;
	}
	// x=0 y=0 ->False
	// x>0 y=0 ->False
	// x=0 y>0 ->True
	if (y_c1 == 0) {
		r_c1 = 0;
	}
	if (x_c1 == 0 && y_c1 != 0) {
		r_c1 = A1_64;
	}
	return r_c1;
}

AC_INLINE int64c1_t grt_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t r_c1 = 0;
	if (x_c1 < y_c1) {
		r_c1 = A1_64;
	}
	return r_c1;
}
AC_INLINE uint64c1_t u_grt_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t r_c1 = 0;
	if (x_c1 < y_c1) {
		r_c1 = A1_64;
	}
	// x=0 y=0 ->False
	// x>0 y=0 ->True
	// x=0 y>0 ->False
	if (y_c1 == 0) {
		if (x_c1 == 0) {
			r_c1 = 0;
		} else {
			r_c1 = A1_64;
		}
	}
	if (x_c1 == 0 && y_c1 != 0) {
		r_c1 = 0;
	}
	return r_c1;
}

AC_INLINE int64c1_t leq_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t r_c1 = 0;
	if (x_c1 >= y_c1) {
		r_c1 = A1_64;
	}
	return r_c1;
}
AC_INLINE uint64c1_t u_leq_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t r_c1 = 0;
	if (x_c1 >= y_c1) {
		r_c1 = A1_64;
	}
	// x=0 y=0 ->True
	// x>0 y=0 ->False
	// x=0 y>0 ->True
	if (y_c1 == 0) {
		if (x_c1 == 0) {
			r_c1 = A1_64;
		} else {
			r_c1 = 0;
		}
	}
	if (x_c1 == 0) {
		r_c1 = A1_64;
	}
	return r_c1;
}

AC_INLINE int64c1_t geq_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t r_c1 = 0;
	if (x_c1 <= y_c1) {
		r_c1 = A1_64;
	}
	return r_c1;
}
AC_INLINE uint64c1_t u_geq_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t r_c1 = 0;
	if (x_c1 <= y_c1) {
		r_c1 = A1_64;
	}
	// x=0 y=0 ->True
	// x>0 y=0 ->True
	// x=0 y>0 ->False
	if (x_c1 == 0) {
		if (y_c1 == 0) {
			r_c1 = A1_64;
		} else {
			r_c1 = 0;
		}
	}
	if (y_c1 == 0) {
		r_c1 = A1_64;
	}
	return r_c1;
}

AC_INLINE int64c1_t shl_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64_t y = y_c1 * A1_64;
	int64c1_t r_c1 = x_c1 << y;
	return r_c1;
}
AC_INLINE uint64c1_t u_shl_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64_t y = y_c1 * A1_64;
	uint64c1_t r_c1 = x_c1 << y;
	return r_c1;
}

// INFO:	The behaviour of the signed right shift depends on the compiler implementation. Therfore this operation is not
//		supported and is prohibited.

AC_INLINE uint64c1_t u_shr_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64_t y = y_c1 * A1_64;
	uint64c1_t r_c1 = u_div_64c1(x_c1, (1 << (y)) * A1_64);
	return r_c1;
}

AC_INLINE int64c1_t land_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	return -(x_c1 && y_c1);
}
AC_INLINE uint64c1_t u_land_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	return -(x_c1 && y_c1);
}

AC_INLINE int64c1_t lor_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	return -(x_c1 || y_c1);
}
AC_INLINE uint64c1_t u_lor_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	return -(x_c1 || y_c1);
}

AC_INLINE int64c1_t and_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	// Diversify logic operations

	int64_t x_d1 = x_c1 * A1_64;
	int64_t y_d1 = y_c1 * A1_64;
	int64c1_t r_c = -1 - ((-1 - x_d1) | (-1 - y_d1));
	return r_c * A1_64;
}
AC_INLINE uint64c1_t u_and_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	// Diversify logic operations

	uint64_t x_d1 = x_c1 * A1_64;
	uint64_t y_d1 = y_c1 * A1_64;
	uint64c1_t r_c = -1 - ((-1 - x_d1) | (-1 - y_d1));
	return r_c * A1_64;
}

AC_INLINE int64c1_t or_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	// Diversify logic operations

	int64_t x_d1 = x_c1 * A1_64;
	int64_t y_d1 = y_c1 * A1_64;
	int64c1_t r_c = -1 - ((-1 - x_d1) & (-1 - y_d1));
	return r_c * A1_64;
}
AC_INLINE uint64c1_t u_or_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	// Diversify logic operations

	uint64_t x_d1 = x_c1 * A1_64;
	uint64_t y_d1 = y_c1 * A1_64;
	uint64c1_t r_c = -1 - ((-1 - x_d1) & (-1 - y_d1));
	return r_c * A1_64;
}

AC_INLINE int64c1_t neg_64c1(int64c1_t x_c1)
{
	int64c1_t r_c1 = (~x_c1) + 2;
	return r_c1;
}
AC_INLINE uint64c1_t u_neg_64c1(uint64c1_t x_c1)
{
	uint64c1_t r_c1 = (~x_c1) + 2;
	return r_c1;
}

AC_INLINE int64c1_t xor_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	uint64_t x_d1 = x_c1 * A1_64;
	uint64_t y_d1 = y_c1 * A1_64;
	uint64c1_t r_d1 = x_d1 ^ y_d1;
	uint64c1_t x_c_revert = (r_d1 ^ y_d1) * A1_64;
	if (x_c1 == x_c_revert) {
		r_d1 = r_d1 * A1_64;
	}
	return r_d1;
}
AC_INLINE uint64c1_t u_xor_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64_t x_d1 = x_c1 * A1_64;
	uint64_t y_d1 = y_c1 * A1_64;
	uint64c1_t r_d1 = x_d1 ^ y_d1;
	uint64c1_t x_c_revert = (r_d1 ^ y_d1) * A1_64;
	if (x_c1 == x_c_revert) {
		r_d1 = r_d1 * A1_64;
	}
	return r_d1;
}

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // TWOSCMP64_1_H_