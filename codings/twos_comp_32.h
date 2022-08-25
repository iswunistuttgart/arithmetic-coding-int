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

#ifndef TWOSCMP32_1_H_
#define TWOSCMP32_1_H_
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#include "common.h"
#include "helpers.h"
#include <stdint.h>
#include <stdlib.h>

#define ENCODING_NAME "TWOS_COMPLEMENT_32BIT"

// Encoded type definitions
typedef int32_t int32c1_t;
typedef uint32_t uint32c1_t;

// As for encoding twoscomp. Inverting+1 is the same as mul with INT_MAX
static uint32c1_t A1_32 = 0xFFFFFFFF;

AC_INLINE int32c1_t encode_32c1(int32_t x)
{
	int32c1_t r_c1 = (int32c1_t)A1_32 * (int32c1_t)x;
	return r_c1;
}
AC_INLINE uint32c1_t u_encode_32c1(uint32_t x)
{
	uint32c1_t r_c1 = (uint32c1_t)A1_32 * (uint32c1_t)x;
	return r_c1;
}

AC_INLINE int32_t decode_32c1(int32c1_t x_c1)
{
	int32_t r = (int32_t)(x_c1 * (int32c1_t)A1_32);
	return r;
}
AC_INLINE uint32_t u_decode_32c1(uint32c1_t x_c1)
{
	uint32_t r = (uint32_t)(x_c1 * (uint32c1_t)A1_32);
	return r;
}

AC_INLINE int check_32c1(int32c1_t val, int32c1_t valc)
{
	return val == decode_32c1(valc);
}
AC_INLINE int u_check_32c1(uint32c1_t val, uint32c1_t valc)
{
	return val == u_decode_32c1(valc);
}

AC_INLINE int32c1_t add_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t r_c1 = x_c1 + y_c1;
	return r_c1;
}
AC_INLINE uint32c1_t u_add_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t r_c1 = x_c1 + y_c1;
	return r_c1;
}

AC_INLINE int32c1_t sub_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t r_c1 = x_c1 - y_c1;
	return r_c1;
}
AC_INLINE uint32c1_t u_sub_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t r_c1 = x_c1 - y_c1;
	return r_c1;
}

AC_INLINE int32c1_t mul_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t r_c1 = x_c1 * y_c1 * A1_32;
	return r_c1;
}
AC_INLINE uint32c1_t u_mul_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t r_c1 = x_c1 * y_c1 * A1_32;
	return r_c1;
}

AC_INLINE int32c1_t div_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t r_c1 = (x_c1 / y_c1) * (int32c1_t)A1_32;
	return r_c1;
}
AC_INLINE uint32c1_t u_div_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	//unsigend div cannot be operate on the native operation.
	//Therefore, we decode the values and encode it back if the reverse check is valid.
	uint32c1_t x_d1 = x_c1 * A1_32;
	uint32c1_t y_d1 = y_c1 * A1_32;
	uint32c1_t r_c1 = x_d1 / y_d1;
	if (r_c1 * y_d1 + x_d1 % y_d1 == x_d1) {
		r_c1 *= A1_32;
	}
	return r_c1;
}

AC_INLINE int32c1_t mod_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t r_c1 = x_c1 % y_c1;
	return r_c1;
}
AC_INLINE uint32c1_t u_mod_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	//unsigend mod cannot be operate on the native operation.
	//Therefore, we decode the values and encode it back if the reverse check is valid.
	uint32c1_t x_d1 = x_c1 * A1_32;
	uint32c1_t y_d1 = y_c1 * A1_32;
	uint32c1_t r_c1 = x_d1 % y_d1;
	if ((x_d1 / y_d1) * y_d1 + r_c1 == x_d1) {
		r_c1 *= A1_32;
	}
	return r_c1;
}

AC_INLINE int32c1_t eq_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t r_c1 = 0;
	if (x_c1 == y_c1) {
		r_c1 = A1_32;
	}
	return r_c1;
}
AC_INLINE uint32c1_t u_eq_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t r_c1 = 0;
	if (x_c1 == y_c1) {
		r_c1 = A1_32;
	}
	return r_c1;
}

AC_INLINE int32c1_t neq_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t r_c1 = 0;
	if (x_c1 != y_c1) {
		r_c1 = A1_32;
	}
	return r_c1;
}
AC_INLINE uint32c1_t u_neq_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t r_c1 = 0;
	if (x_c1 != y_c1) {
		r_c1 = A1_32;
	}
	return r_c1;
}

AC_INLINE int32c1_t less_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t r_c1 = 0;
	if (x_c1 > y_c1) {
		r_c1 = A1_32;
	}
	return r_c1;
}
AC_INLINE uint32c1_t u_less_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t r_c1 = 0;
	if (x_c1 > y_c1) {
		r_c1 = A1_32;
	}
	// x=0 y=0 ->False
	// x>0 y=0 ->False
	// x=0 y>0 ->True
	if (y_c1 == 0) {
		r_c1 = 0;
	}
	if (x_c1 == 0 && y_c1 != 0) {
		r_c1 = A1_32;
	}
	return r_c1;
}

AC_INLINE int32c1_t grt_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t r_c1 = 0;
	if (x_c1 < y_c1) {
		r_c1 = A1_32;
	}
	return r_c1;
}
AC_INLINE uint32c1_t u_grt_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t r_c1 = 0;
	if (x_c1 < y_c1) {
		r_c1 = A1_32;
	}
	// x=0 y=0 ->False
	// x>0 y=0 ->True
	// x=0 y>0 ->False
	if (y_c1 == 0) {
		if (x_c1 == 0) {
			r_c1 = 0;
		} else {
			r_c1 = A1_32;
		}
	}
	if (x_c1 == 0 && y_c1 != 0) {
		r_c1 = 0;
	}
	return r_c1;
}

AC_INLINE int32c1_t leq_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t r_c1 = 0;
	if (x_c1 >= y_c1) {
		r_c1 = A1_32;
	}
	return r_c1;
}
AC_INLINE uint32c1_t u_leq_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t r_c1 = 0;
	if (x_c1 >= y_c1) {
		r_c1 = A1_32;
	}
	// x=0 y=0 ->True
	// x>0 y=0 ->False
	// x=0 y>0 ->True
	if (y_c1 == 0) {
		if (x_c1 == 0) {
			r_c1 = A1_32;
		} else {
			r_c1 = 0;
		}
	}
	if (x_c1 == 0) {
		r_c1 = A1_32;
	}
	return r_c1;
}

AC_INLINE int32c1_t geq_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t r_c1 = 0;
	if (x_c1 <= y_c1) {
		r_c1 = A1_32;
	}
	return r_c1;
}
AC_INLINE uint32c1_t u_geq_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t r_c1 = 0;
	if (x_c1 <= y_c1) {
		r_c1 = A1_32;
	}
	// x=0 y=0 ->True
	// x>0 y=0 ->True
	// x=0 y>0 ->False
	if (x_c1 == 0) {
		if (y_c1 == 0) {
			r_c1 = A1_32;
		} else {
			r_c1 = 0;
		}
	}
	if (y_c1 == 0) {
		r_c1 = A1_32;
	}
	return r_c1;
}

AC_INLINE int32c1_t shl_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32_t y = y_c1 * A1_32;
	int32c1_t r_c1 = x_c1 << y;
	return r_c1;
}
AC_INLINE uint32c1_t u_shl_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32_t y = y_c1 * A1_32;
	uint32c1_t r_c1 = x_c1 << y;
	return r_c1;
}

// INFO:	The behaviour of the signed right shift depends on the compiler implementation. Therfore this operation is not
//		supported and is prohibited.

AC_INLINE uint32c1_t u_shr_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32_t y = y_c1 * A1_32;
	uint32c1_t r_c1 = u_div_32c1(x_c1, (1 << (y)) * A1_32);
	return r_c1;
}

AC_INLINE int32c1_t land_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	return -(x_c1 && y_c1);
}
AC_INLINE uint32c1_t u_land_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	return -(x_c1 && y_c1);
}

AC_INLINE int32c1_t lor_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	return -(x_c1 || y_c1);
}
AC_INLINE uint32c1_t u_lor_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	return -(x_c1 || y_c1);
}

AC_INLINE int32c1_t and_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	// Diversify logic operations

	int32_t x_d1 = x_c1 * A1_32;
	int32_t y_d1 = y_c1 * A1_32;
	int32c1_t r_c = -1 - ((-1 - x_d1) | (-1 - y_d1));
	return r_c * A1_32;
}
AC_INLINE uint32c1_t u_and_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	// Diversify logic operations

	uint32_t x_d1 = x_c1 * A1_32;
	uint32_t y_d1 = y_c1 * A1_32;
	uint32c1_t r_c = -1 - ((-1 - x_d1) | (-1 - y_d1));
	return r_c * A1_32;
}

AC_INLINE int32c1_t or_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	// Diversify logic operations

	int32_t x_d1 = x_c1 * A1_32;
	int32_t y_d1 = y_c1 * A1_32;
	int32c1_t r_c = -1 - ((-1 - x_d1) & (-1 - y_d1));
	return r_c * A1_32;
}
AC_INLINE uint32c1_t u_or_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	// Diversify logic operations

	uint32_t x_d1 = x_c1 * A1_32;
	uint32_t y_d1 = y_c1 * A1_32;
	uint32c1_t r_c = -1 - ((-1 - x_d1) & (-1 - y_d1));
	return r_c * A1_32;
}

AC_INLINE int32c1_t neg_32c1(int32c1_t x_c1)
{
	int32c1_t r_c1 = (~x_c1) + 2;
	return r_c1;
}
AC_INLINE uint32c1_t u_neg_32c1(uint32c1_t x_c1)
{
	uint32c1_t r_c1 = (~x_c1) + 2;
	return r_c1;
}

AC_INLINE int32c1_t xor_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	uint32_t x_d1 = x_c1 * A1_32;
	uint32_t y_d1 = y_c1 * A1_32;
	uint32c1_t r_d1 = x_d1 ^ y_d1;
	uint32c1_t x_c_revert = (r_d1 ^ y_d1) * A1_32;
	if (x_c1 == x_c_revert) {
		r_d1 = r_d1 * A1_32;
	}
	return r_d1;
}
AC_INLINE uint32c1_t u_xor_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32_t x_d1 = x_c1 * A1_32;
	uint32_t y_d1 = y_c1 * A1_32;
	uint32c1_t r_d1 = x_d1 ^ y_d1;
	uint32c1_t x_c_revert = (r_d1 ^ y_d1) * A1_32;
	if (x_c1 == x_c_revert) {
		r_d1 = r_d1 * A1_32;
	}
	return r_d1;
}

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // TWOSCMP32_1_H_