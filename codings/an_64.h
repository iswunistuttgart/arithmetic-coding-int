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
 * @description: Provides all primitive functions for AN-Encoding of one channel.
 */

#ifndef AN64_H_
#define AN64_H_

#include <stdint.h>
#include <stdlib.h>
#include "common.h"
#define ENCODING_NAME "AN_64BIT"

// A for encoding AN in 64bits
// 58659, 59665, 63157, 63859, 63877 are the best As for 32bit [Ulbrich,2014,Ganzheutliche Fehlertoleranz in eingebetteten Softwaresystemen]
// We use this just for validation and performance. This A does not have the best detection capabilities
#define A1_64 58659

typedef __uint128_t uint64c1_t;
typedef __int128_t int64c1_t;
__uint128_t sub = 0xffffffffffff1addUL;
__uint128_t pow64 = 1UL;
__uint128_t pow64A = 1UL;
static inline void init()
{
	pow64 = pow64 << 64;
	pow64A = pow64 * A1_64;
	__uint128_t interim = pow64 - A1_64;
	sub = pow64 * interim;
}

AC_INLINE int64c1_t encode_64c1(int64_t x)
{
	int64c1_t r_c1 = (int64c1_t)A1_64 * (int64c1_t)x;
	return r_c1;
}
AC_INLINE uint64c1_t u_encode_64c1(uint64_t x)
{
	uint64c1_t r_c1 = (uint64c1_t)(x) * (uint64c1_t)(A1_64);
	return r_c1;
}

AC_INLINE int64_t decode_64c1(int64c1_t x_c1)
{
	int64_t r = (int64_t)(x_c1 / (int64c1_t)A1_64);
	return r;
}
AC_INLINE uint64_t u_decode_64c1(uint64c1_t x_c1)
{
	uint64_t r = (uint64c1_t)x_c1 / (uint64c1_t)A1_64;
	return r;
}

AC_INLINE int check_64c1(int64c1_t val, int64c1_t valc)
{
	return (val == decode_64c1(valc)) && (valc % A1_64 == 0);
}
AC_INLINE int u_check_64c1(uint64c1_t val, uint64c1_t valc)
{
	return val == u_decode_64c1(valc) && (valc % A1_64 == 0);
}

AC_INLINE int64c1_t add_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	return x_c1 + y_c1;
}
AC_INLINE uint64c1_t u_add_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	return x_c1 + y_c1;
}

AC_INLINE int64c1_t sub_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	return x_c1 - y_c1;
}
AC_INLINE uint64c1_t u_sub_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t r_c1 = x_c1 - y_c1;
	if (x_c1 < y_c1) {
		//2^64(2^64-A)
		//Due to Performance reasons this calcualtion is precalculated. As it depends on A we have to recalculate it if a changes
		r_c1 = r_c1 - sub;
	}
	return r_c1;
}

AC_INLINE int64c1_t mul_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t x_d1 = x_c1 / (int64c1_t)A1_64;
	int64c1_t y_d1 = y_c1 / (int64c1_t)A1_64;
	int64_t res = (int64_t)x_d1 * (int64_t)y_d1;

	int64c1_t r = x_d1 * y_d1;
	int64c1_t quo = r / (int64c1_t)pow64; //r/2^64
	int64c1_t r_c1 =
		x_c1 * y_d1 -
		quo * ((int64c1_t)
			       pow64A); //(quo*(int64c1_t)(2^64))*(int64c1_t)(A1_64);

	if (r > 0) {
		if (res < 0) {
			r_c1 = r_c1 +
			       sub; //(int64c1_t)(2^64)*((int64c1_t)(2^64)-(int64c1_t)(A1_64));
		}
	} else {
		if (res > 0) {
			r_c1 = r_c1 -
			       sub; //(int64c1_t)(2^64)*((int64c1_t)(2^64)-(int64c1_t)(A1_64));
		}
	}

	return r_c1;
}
AC_INLINE uint64c1_t u_mul_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t x_d1 = x_c1 / (uint64c1_t)A1_64;
	uint64c1_t y_d1 = y_c1 / (uint64c1_t)A1_64;

	uint64c1_t r = x_d1 * y_d1;
	uint64c1_t quo = r / (uint64c1_t)(pow64); //r/2^64
	uint64c1_t r_c1 =
		x_c1 * y_d1 -
		quo * ((int64c1_t)
			       pow64A); //(quo*(uint64c1_t)(2^64))*(uint64c1_t)(A1_64);

	return r_c1;
}

AC_INLINE int64c1_t div_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t r_c1 = (x_c1 / y_c1) * A1_64;
	return r_c1;
}
AC_INLINE uint64c1_t u_div_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t r_c1 = (x_c1 / y_c1) * A1_64;
	return r_c1;
}

AC_INLINE int64c1_t mod_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	return x_c1 % y_c1;
}
AC_INLINE uint64c1_t u_mod_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	return x_c1 % y_c1;
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
	if (x_c1 < y_c1) {
		r_c1 = A1_64;
	}
	return r_c1;
}
AC_INLINE uint64c1_t u_less_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t r_c1 = 0;
	if (x_c1 < y_c1) {
		r_c1 = A1_64;
	}
	return r_c1;
}

AC_INLINE int64c1_t grt_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t r_c1 = 0;
	if (x_c1 > y_c1) {
		r_c1 = A1_64;
	}
	return r_c1;
}
AC_INLINE uint64c1_t u_grt_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t r_c1 = 0;
	if (x_c1 > y_c1) {
		r_c1 = A1_64;
	}
	return r_c1;
}

AC_INLINE int64c1_t leq_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t r_c1 = 0;
	if (x_c1 <= y_c1) {
		r_c1 = A1_64;
	}
	return r_c1;
}
AC_INLINE uint64c1_t u_leq_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t r_c1 = 0;
	if (x_c1 <= y_c1) {
		r_c1 = A1_64;
	}
	return r_c1;
}

AC_INLINE int64c1_t geq_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t r_c1 = 0;
	if (x_c1 >= y_c1) {
		r_c1 = A1_64;
	}
	return r_c1;
}
AC_INLINE uint64c1_t u_geq_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t r_c1 = 0;
	if (x_c1 >= y_c1) {
		r_c1 = A1_64;
	}
	return r_c1;
}

AC_INLINE int64c1_t shl_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t y = decode_64c1(y_c1);
	int64c1_t r_c1 = mul_64c1(x_c1, ((int64c1_t)1 << y) * (int64c1_t)A1_64);
	return r_c1; // result already AN-encoded
}
AC_INLINE uint64c1_t u_shl_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t y = u_decode_64c1(y_c1);
	uint64c1_t r_c1 =
		u_mul_64c1(x_c1, ((uint64c1_t)1 << (y)) * (uint64c1_t)A1_64);

	return r_c1;
}

//INFO:	The behaviour of the signed right shift depends on the compiler implementation. Therfore this operation is not
//		supported and is prohibited.

AC_INLINE uint64c1_t u_shr_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t y = u_decode_64c1(y_c1);
	uint64c1_t r_c1 =
		u_div_64c1(x_c1, ((uint64c1_t)1 << y) * (uint64c1_t)A1_64);

	return r_c1;
}

AC_INLINE int64c1_t land_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t r_c1 = mul_64c1(x_c1, y_c1);
	if (r_c1 != 0) {
		r_c1 = A1_64;
	}
	return r_c1;
}
AC_INLINE uint64c1_t u_land_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t r_c1 = u_mul_64c1(x_c1, y_c1);
	if (r_c1 != 0) {
		r_c1 = A1_64;
	}
	return r_c1;
}
/*	OR Table
 * 	| x | Y | Result |
 *	| 0 | 0 |   0    |
 *	| 0 |!=0| ENC(1) |
 *	|!=0| 0 | ENC(1) |
 *	|!=0|!=0| ENC(1) |
 */
AC_INLINE int64c1_t lor_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t r_c1 = x_c1 + y_c1;
	if (r_c1 != 0) {
		r_c1 = A1_64;
	}
	//Force true if one value is negative. For x=-n and y=n the addition is 0 but the result is true
	if (x_c1 < 0) {
		r_c1 = A1_64;
	}
	if (y_c1 < 0) {
		r_c1 = A1_64;
	}
	return r_c1;
}
AC_INLINE uint64c1_t u_lor_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t r_c1 = x_c1 + y_c1;
	if (r_c1 != 0) {
		r_c1 = A1_64;
	} else {
		//Force true if overlow is detected. AS the overlow can lead to a 0 which would be intepreted as False
		if (r_c1 < x_c1 && r_c1 < y_c1) {
			r_c1 = A1_64;
		}
	}
	return r_c1;
}

AC_INLINE int64c1_t and_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	//Diversify logic operations
	int64_t x_d1 = decode_64c1(x_c1);
	int64_t y_d1 = decode_64c1(y_c1);
	int64c1_t r_c = -1 - ((-1 - x_d1) | (-1 - y_d1));
	return r_c * A1_64;
}
AC_INLINE uint64c1_t u_and_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	//Diversify logic operations
	uint64_t x_d1 = u_decode_64c1(x_c1);
	uint64_t y_d1 = u_decode_64c1(y_c1);
	uint64c1_t r_c = 0xFFFFFFFFFFFFFFFF - ((0xFFFFFFFFFFFFFFFF - x_d1) |
					       (0xFFFFFFFFFFFFFFFF - y_d1));
	return r_c * A1_64;
}

AC_INLINE int64c1_t or_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	//Diversify logic operations
	int64_t x_d1 = decode_64c1(x_c1);
	int64_t y_d1 = decode_64c1(y_c1);
	int64c1_t r_c = -1 - ((-1 - x_d1) & (-1 - y_d1));
	return r_c * A1_64;
}
AC_INLINE uint64c1_t u_or_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	//Diversify logic operations
	uint64_t x_d1 = u_decode_64c1(x_c1);
	uint64_t y_d1 = u_decode_64c1(y_c1);
	uint64c1_t r_c = 0xFFFFFFFFFFFFFFFF - ((0xFFFFFFFFFFFFFFFF - x_d1) &
					       (0xFFFFFFFFFFFFFFFF - y_d1));
	return r_c * A1_64;
}

AC_INLINE int64c1_t neg_64c1(int64c1_t x_c1)
{
	//Diversify logic operations
	int64_t x_d1 = decode_64c1(x_c1);
	int64c1_t r_c = -1 - x_d1;
	return r_c * A1_64;
}
AC_INLINE uint64c1_t u_neg_64c1(uint64c1_t x_c1)
{
	//Diversify logic operations
	uint64_t x_d1 = u_decode_64c1(x_c1);
	uint64c1_t r_c = 0xFFFFFFFFFFFFFFFF - x_d1;
	return r_c * A1_64;
}

AC_INLINE int64c1_t xor_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t p1 = and_64c1(neg_64c1(x_c1), y_c1);
	int64c1_t p2 = and_64c1(x_c1, neg_64c1(y_c1));
	int64c1_t r_c1 = or_64c1(p1, p2);
	return r_c1;
}
AC_INLINE uint64c1_t u_xor_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t p1 = u_and_64c1(u_neg_64c1(x_c1), y_c1);
	uint64c1_t p2 = u_and_64c1(x_c1, u_neg_64c1(y_c1));
	uint64c1_t r_c1 = u_or_64c1(p1, p2);
	return r_c1;
}

#endif //AN32_C1_H_