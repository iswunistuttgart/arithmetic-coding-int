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

#ifndef AN32_H_
#define AN32_H_

#include <stdint.h>
#include <stdlib.h>
#include "common.h"
#define ENCODING_NAME "AN_32BIT"

// A for encoding AN in 32bits
// 58659, 59665, 63157, 63859, 63877 are the best As [Ulbrich,2014,Ganzheutliche Fehlertoleranz in eingebetteten Softwaresystemen]
#define A1_32 58659

typedef uint64_t uint32c1_t;
typedef int64_t int32c1_t;

AC_INLINE int32c1_t encode_32c1(int32_t x)
{
	int32c1_t r_c1 = (int32c1_t)A1_32 * (int32c1_t)x;
	return r_c1;
}
AC_INLINE uint32c1_t u_encode_32c1(uint32_t x)
{
	uint32c1_t r_c1 = (uint32c1_t)(x) * (uint32c1_t)(A1_32);
	return r_c1;
}

AC_INLINE int32_t decode_32c1(int32c1_t x_c1)
{
	int32_t r = (int32_t)(x_c1 / (int32c1_t)A1_32);
	return r;
}
AC_INLINE uint32_t u_decode_32c1(uint32c1_t x_c1)
{
	uint32_t r = (uint32c1_t)x_c1 / (uint32c1_t)A1_32;
	return r;
}

AC_INLINE int check_32c1(int32c1_t val, int32c1_t valc)
{
	return (val == decode_32c1(valc)) && (valc % A1_32 == 0);
}
AC_INLINE int u_check_32c1(uint32c1_t val, uint32c1_t valc)
{
	return val == u_decode_32c1(valc) && (valc % A1_32 == 0);
}

AC_INLINE int32c1_t add_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	return x_c1 + y_c1;
}
AC_INLINE uint32c1_t u_add_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	return x_c1 + y_c1;
}

AC_INLINE int32c1_t sub_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	return x_c1 - y_c1;
}
AC_INLINE uint32c1_t u_sub_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t r_c1 = x_c1 - y_c1;
	if (x_c1 < y_c1) {
		//(uint32c1_t)(4294967296)*((uint32c1_t)4294967296-(uint32c1_t)(A1_32)); //2^64-A*2^32=2^32(2^32-A)
		//Due to Performance reasons this calcualtion is precalculated. As it depends on A we have to recalculate it if a changes
		r_c1 = r_c1 - 18446492135222935552UL;
	}
	return r_c1;
}

AC_INLINE int32c1_t mul_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t x_d1 = x_c1 / (int32c1_t)A1_32;
	int32c1_t y_d1 = y_c1 / (int32c1_t)A1_32;
	int32_t res = (int32_t)x_d1 * (int32_t)y_d1;

	int32c1_t r = x_d1 * y_d1;
	int32c1_t quo = r / (int32c1_t)(4294967296L); //r/2^32
	int32c1_t r_c1 =
		x_c1 * y_d1 -
		quo * ((int32c1_t)251938486616064L); //(quo*(int32c1_t)(4294967296))*(int32c1_t)(A1_32);

	if (r > 0) {
		if (res < 0) {
			r_c1 = r_c1 +
			       18446492135222935552UL; //(int32c1_t)(4294967296LU)*((int32c1_t)(4294967296LU)-(int32c1_t)(A1_32));
		}
	} else {
		if (res > 0) {
			r_c1 = r_c1 -
			       18446492135222935552UL; //(int32c1_t)(4294967296LU)*((int32c1_t)(4294967296LU)-(int32c1_t)(A1_32));
		}
	}

	return r_c1;
}
AC_INLINE uint32c1_t u_mul_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t x_d1 = x_c1 / (uint32c1_t)A1_32;
	uint32c1_t y_d1 = y_c1 / (uint32c1_t)A1_32;

	uint32c1_t r = x_d1 * y_d1;
	uint32c1_t quo = r / (uint32c1_t)(4294967296L); //r/2^32
	uint32c1_t r_c1 =
		x_c1 * y_d1 -
		quo * ((int32c1_t)251938486616064L); //(quo*(uint32c1_t)(4294967296))*(uint32c1_t)(A1_32);

	return r_c1;
}

AC_INLINE int32c1_t div_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t r_c1 = (x_c1 / y_c1) * A1_32;
	return r_c1;
}
AC_INLINE uint32c1_t u_div_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t r_c1 = (x_c1 / y_c1) * A1_32;
	return r_c1;
}

AC_INLINE int32c1_t mod_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	return x_c1 % y_c1;
}
AC_INLINE uint32c1_t u_mod_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	return x_c1 % y_c1;
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
	if (x_c1 < y_c1) {
		r_c1 = A1_32;
	}
	return r_c1;
}
AC_INLINE uint32c1_t u_less_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t r_c1 = 0;
	if (x_c1 < y_c1) {
		r_c1 = A1_32;
	}
	return r_c1;
}

AC_INLINE int32c1_t grt_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t r_c1 = 0;
	if (x_c1 > y_c1) {
		r_c1 = A1_32;
	}
	return r_c1;
}
AC_INLINE uint32c1_t u_grt_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t r_c1 = 0;
	if (x_c1 > y_c1) {
		r_c1 = A1_32;
	}
	return r_c1;
}

AC_INLINE int32c1_t leq_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t r_c1 = 0;
	if (x_c1 <= y_c1) {
		r_c1 = A1_32;
	}
	return r_c1;
}
AC_INLINE uint32c1_t u_leq_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t r_c1 = 0;
	if (x_c1 <= y_c1) {
		r_c1 = A1_32;
	}
	return r_c1;
}

AC_INLINE int32c1_t geq_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t r_c1 = 0;
	if (x_c1 >= y_c1) {
		r_c1 = A1_32;
	}
	return r_c1;
}
AC_INLINE uint32c1_t u_geq_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t r_c1 = 0;
	if (x_c1 >= y_c1) {
		r_c1 = A1_32;
	}
	return r_c1;
}

AC_INLINE int32c1_t shl_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t y = decode_32c1(y_c1);
	int32c1_t r_c1 = mul_32c1(x_c1, ((int32c1_t)1 << y) * (int32c1_t)A1_32);
	return r_c1; // result already AN-encoded
}
AC_INLINE uint32c1_t u_shl_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t y = u_decode_32c1(y_c1);
	uint32c1_t r_c1 =
		u_mul_32c1(x_c1, ((uint32c1_t)1 << (y)) * (uint32c1_t)A1_32);

	return r_c1;
}

//INFO:	The behaviour of the signed right shift depends on the compiler implementation. Therfore this operation is not
//		supported and is prohibited.

AC_INLINE uint32c1_t u_shr_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t y = u_decode_32c1(y_c1);
	uint32c1_t r_c1 =
		u_div_32c1(x_c1, ((uint32c1_t)1 << y) * (uint32c1_t)A1_32);

	return r_c1;
}

AC_INLINE int32c1_t land_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t r_c1 = mul_32c1(x_c1, y_c1);
	if (r_c1 != 0) {
		r_c1 = A1_32;
	}
	return r_c1;
}
AC_INLINE uint32c1_t u_land_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t r_c1 = u_mul_32c1(x_c1, y_c1);
	if (r_c1 != 0) {
		r_c1 = A1_32;
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
AC_INLINE int32c1_t lor_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t r_c1 = x_c1 + y_c1;
	if (r_c1 != 0) {
		r_c1 = A1_32;
	}
	//Force true if one value is negative. For x=-n and y=n the addition is 0 but the result is true
	if (x_c1 < 0) {
		r_c1 = A1_32;
	}
	if (y_c1 < 0) {
		r_c1 = A1_32;
	}
	return r_c1;
}
AC_INLINE uint32c1_t u_lor_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t r_c1 = x_c1 + y_c1;
	if (r_c1 != 0) {
		r_c1 = A1_32;
	} else {
		//Force true if overlow is detected. AS the overlow can lead to a 0 which would be intepreted as False
		if (r_c1 < x_c1 && r_c1 < y_c1) {
			r_c1 = A1_32;
		}
	}
	return r_c1;
}

AC_INLINE int32c1_t and_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	//Diversify logic operations
	int32_t x_d1 = decode_32c1(x_c1);
	int32_t y_d1 = decode_32c1(y_c1);
	int32c1_t r_c = -1 - ((-1 - x_d1) | (-1 - y_d1));
	return r_c * A1_32;
}
AC_INLINE uint32c1_t u_and_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	//Diversify logic operations
	uint32_t x_d1 = u_decode_32c1(x_c1);
	uint32_t y_d1 = u_decode_32c1(y_c1);
	uint32c1_t r_c =
		0xFFFFFFFF - ((0xFFFFFFFF - x_d1) | (0xFFFFFFFF - y_d1));
	return r_c * A1_32;
}

AC_INLINE int32c1_t or_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	//Diversify logic operations
	int32_t x_d1 = decode_32c1(x_c1);
	int32_t y_d1 = decode_32c1(y_c1);
	int32c1_t r_c = -1 - ((-1 - x_d1) & (-1 - y_d1));
	return r_c * A1_32;
}
AC_INLINE uint32c1_t u_or_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	//Diversify logic operations
	uint32_t x_d1 = u_decode_32c1(x_c1);
	uint32_t y_d1 = u_decode_32c1(y_c1);
	uint32c1_t r_c =
		0xFFFFFFFF - ((0xFFFFFFFF - x_d1) & (0xFFFFFFFF - y_d1));
	return r_c * A1_32;
}

AC_INLINE int32c1_t neg_32c1(int32c1_t x_c1)
{
	//Diversify logic operations
	int32_t x_d1 = decode_32c1(x_c1);
	int32c1_t r_c = -1 - x_d1;
	return r_c * A1_32;
}
AC_INLINE uint32c1_t u_neg_32c1(uint32c1_t x_c1)
{
	//Diversify logic operations
	uint32_t x_d1 = u_decode_32c1(x_c1);
	uint32c1_t r_c = 0xFFFFFFFF - x_d1;
	return r_c * A1_32;
}

AC_INLINE int32c1_t xor_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t p1 = and_32c1(neg_32c1(x_c1), y_c1);
	int32c1_t p2 = and_32c1(x_c1, neg_32c1(y_c1));
	int32c1_t r_c1 = or_32c1(p1, p2);
	return r_c1;
}
AC_INLINE uint32c1_t u_xor_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t p1 = u_and_32c1(u_neg_32c1(x_c1), y_c1);
	uint32c1_t p2 = u_and_32c1(x_c1, u_neg_32c1(y_c1));
	uint32c1_t r_c1 = u_or_32c1(p1, p2);
	return r_c1;
}

#endif //AN32_C1_H_