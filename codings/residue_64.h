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
 * @description: Provides all primitive functions for encoding one channel with the residue
 */

#ifndef RES64_1_H_
#define RES64_1_H_
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#include "common.h"
#include "helpers.h"
#include <stdint.h>
#include <stdlib.h>

#define ENCODING_NAME "RESIDUE_64BIT"

typedef struct {
	int64_t val;
	int64_t check;
} int64c1_t;
typedef struct {
	uint64_t val;
	uint64_t check;
} uint64c1_t;

// As for encoding floats
static uint64_t A1_64_U = 18;
static int64_t A1_64 = 18;
#define AC_RES_OVCORR64 2 //AC_RES_A-(AC_TWO_64%AC_RES_A)
#define AC_RES_OVCORR32 14 //AC_RES_A-(AC_TWO_32%AC_RES_A)
#define AC_RES_OVCORR16 2 //AC_RES_A-(AC_TWO_16%AC_RES_A)
#define AC_RES_OVCORR8 14

#define AC_TWO_8 256
#define AC_TWO_16 65536
#define AC_TWO_32 4294967296
#define AC_TWO_64 18446744073709551615U

AC_INLINE int64c1_t encode_64c1(int64_t x)
{
	int64c1_t ret;
	ret.val = x;
	ret.check = x % A1_64;
	return ret;
}
AC_INLINE uint64c1_t u_encode_64c1(uint64_t x)
{
	uint64c1_t ret;
	ret.val = x;
	ret.check = x % A1_64_U;
	return ret;
}

AC_INLINE int64_t decode_64c1(int64c1_t x_c1)
{
	return x_c1.val;
}
AC_INLINE uint64_t u_decode_64c1(uint64c1_t x_c1)
{
	return x_c1.val;
}
AC_INLINE int check_64c1(int64_t val, int64c1_t valc)
{
	int64_t tmpCheck = valc.val % A1_64;
	return tmpCheck == valc.check;
}
AC_INLINE int u_check_64c1(uint64_t val, uint64c1_t valc)
{
	uint64_t tmpCheck = valc.val % A1_64_U;
	return tmpCheck == valc.check;
}

AC_INLINE int64c1_t add_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t res;
	res.val = x_c1.val + y_c1.val;
	//overflow correction
	if ((x_c1.val > 0 && y_c1.val > 0 && res.val < 0) ||
	    (x_c1.val < 0 && y_c1.val < 0 && res.val > 0)) {
		if (res.val < 0) {
			res.check =
				(((x_c1.check + y_c1.check + AC_RES_OVCORR64) %
				  A1_64) -
				 A1_64) %
				A1_64;
		} else {
			res.check =
				(((x_c1.check + y_c1.check - AC_RES_OVCORR64) %
				  A1_64) +
				 A1_64) %
				A1_64;
		}

	} else {
		res.check = (x_c1.check + y_c1.check) % A1_64;
		if (res.val < 0 && res.check > 0) {
			res.check = -A1_64 + res.check;
		}
		if (res.val > 0 && res.check < 0) {
			res.check = A1_64 + res.check;
		}
	}
	return res;
}
AC_INLINE uint64c1_t u_add_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t res;
	res.val = x_c1.val + y_c1.val;
	//overflow correction
	if (res.val < x_c1.val) {
		res.check =
			(x_c1.check + y_c1.check + AC_RES_OVCORR64) % A1_64_U;
	} else {
		res.check = (x_c1.check + y_c1.check) % A1_64_U;
	}
	return res;
}

AC_INLINE int64c1_t sub_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t res;
	res.val = x_c1.val - y_c1.val;
	//underflow correction
	if ((x_c1.val > 0 && y_c1.val < 0 && res.val < 0) ||
	    (x_c1.val < 0 && y_c1.val > 0 && res.val > 0)) {
		if (res.val < 0) {
			res.check = (x_c1.check - y_c1.check - UINT64_MAX - 1) %
				    A1_64;
		} else {
			res.check = (x_c1.check - y_c1.check + UINT64_MAX + 1) %
				    A1_64;
		}

	} else {
		res.check = (x_c1.check - y_c1.check) % A1_64;
		if (res.val < 0 && res.check > 0) {
			res.check = -A1_64 + res.check;
		}
		if (res.val > 0 && res.check < 0) {
			res.check = A1_64 + res.check;
		}
	}
	return res;
}
AC_INLINE uint64c1_t u_sub_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t res;
	res.val = x_c1.val - y_c1.val;
	//underflow correction
	if (x_c1.val < y_c1.val) {
		res.check =
			(x_c1.check - y_c1.check + UINT16_MAX + 1) % A1_64_U;
	} else if (x_c1.check < y_c1.check) {
		res.check = (x_c1.check - y_c1.check + A1_64) % A1_64_U;
	} else {
		res.check = (x_c1.check - y_c1.check) % A1_64_U;
	}
	return res;
}

AC_INLINE uint64c1_t u_mul_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t res;
	res.val = x_c1.val * y_c1.val;
	__uint128_t m = AC_TWO_64;
	m += 1;
	__uint128_t tempVal =
		((__uint128_t)x_c1.val * (__uint128_t)y_c1.val) / m;
	if (tempVal > 0) {
		res.check =
			(x_c1.check * y_c1.check + AC_RES_OVCORR64 * tempVal) %
			A1_64_U;
	} else {
		res.check = (x_c1.check * y_c1.check) % A1_64_U;
	}
	return res;
}

AC_INLINE int64c1_t mul_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t res;
	res.val = x_c1.val * y_c1.val;
	__int128_t m = AC_TWO_64;
	m += 1;
	__int128_t tempVal =
		((__int128_t)x_c1.val * (__int128_t)y_c1.val) / AC_TWO_64;
	if (tempVal > 0) {
		res.check =
			(x_c1.check * y_c1.check + AC_RES_OVCORR64 * tempVal) %
			A1_64;

	} else {
		res.check = (x_c1.check * y_c1.check) % A1_64;
		if ((x_c1.val > 0 && y_c1.val > 0 && res.val < 0) ||
		    (x_c1.val < 0 && y_c1.val < 0 && res.val < 0)) {
			res.check = -res.check;
		}
	}
	return res;
}

AC_INLINE int64c1_t div_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t r_c1;
	r_c1.val = x_c1.val / y_c1.val;
	if (r_c1.val * y_c1.val + x_c1.val % y_c1.val == x_c1.val) {
		r_c1.check = (x_c1.val / y_c1.val) % A1_64;
	} else {
		r_c1.check = 33;
	}

	return r_c1;
}

AC_INLINE uint64c1_t u_div_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t res;
	res.val = x_c1.val / y_c1.val;
	res.check = (res.val) % A1_64;
	uint64_t rem = (x_c1.val % y_c1.val) % A1_64;
	//internal check
	uint64_t checkL = 0;
	if (rem > x_c1.check) {
		checkL = (x_c1.check - rem + A1_64) % A1_64;
	} else {
		checkL = (x_c1.check - rem) % A1_64;
	}

	uint64_t checkR =
		((uint64_t)res.check * (uint64_t)y_c1.check) % (uint64_t)A1_64;

	if (checkR != checkL) {
		res.check = 33;
	}

	return res;
}

AC_INLINE int64c1_t mod_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t r_c1;
	r_c1.val = x_c1.val % y_c1.val;
	if ((x_c1.val / y_c1.val) * y_c1.val + r_c1.val == x_c1.val) {
		r_c1.check = (x_c1.val % y_c1.val) % A1_64;
	} else {
		r_c1.check = 33;
	}

	return r_c1;
}
AC_INLINE uint64c1_t u_mod_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t r_c1;
	r_c1.val = x_c1.val % y_c1.val;
	if ((x_c1.val / y_c1.val) * y_c1.val + r_c1.val == x_c1.val) {
		r_c1.check = (x_c1.val % y_c1.val) % A1_64;
	} else {
		r_c1.check = 33;
	}

	return r_c1;
}

AC_INLINE int64c1_t eq_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	return encode_64c1(x_c1.val == y_c1.val && x_c1.check == y_c1.check);
}
AC_INLINE uint64c1_t u_eq_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	return u_encode_64c1(x_c1.val == y_c1.val && x_c1.check == y_c1.check);
}

AC_INLINE int64c1_t neq_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	return encode_64c1(x_c1.val != y_c1.val && x_c1.check != y_c1.check);
}
AC_INLINE uint64c1_t u_neq_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	return u_encode_64c1(x_c1.val != y_c1.val && x_c1.check != y_c1.check);
}

AC_INLINE int64c1_t less_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t tmp = sub_64c1(x_c1, y_c1);
	int64c1_t ret;
	if (x_c1.val < y_c1.val && tmp.val > x_c1.val) {
		//uf happend --> less is true
		ret = encode_64c1(1);
	} else {
		//no uf --> less is false
		ret = encode_64c1(0);
	}
	return ret;
}
AC_INLINE uint64c1_t u_less_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t tmp = u_sub_64c1(x_c1, y_c1);
	uint64c1_t ret;
	if (x_c1.val < y_c1.val && tmp.val > x_c1.val) {
		//uf happend --> less is true
		ret = u_encode_64c1(1);
	} else {
		//no uf --> less is false
		ret = u_encode_64c1(0);
	}
	return ret;
}

AC_INLINE int64c1_t grt_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	// return -(x_c1 < y_c1) - 1;
}
AC_INLINE uint64c1_t u_grt_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	// return -(x_c1 < y_c1) - 1;
}

AC_INLINE int64c1_t leq_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t tmp = sub_64c1(y_c1, x_c1);
	int64c1_t ret;
	if (x_c1.val > y_c1.val && tmp.val > y_c1.val) {
		//uf happend --> leq is fales
		ret = encode_64c1(0);
	} else {
		//no uf --> leq is true
		ret = encode_64c1(1);
	}
	return ret;
}
AC_INLINE uint64c1_t u_leq_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t tmp = u_sub_64c1(y_c1, x_c1);
	uint64c1_t ret;
	if (x_c1.val > y_c1.val && tmp.val > y_c1.val) {
		//uf happend --> leq is fales
		ret = u_encode_64c1(0);
	} else {
		//no uf --> leq is true
		ret = u_encode_64c1(1);
	}
	return ret;
}

AC_INLINE int64c1_t geq_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t tmp = sub_64c1(x_c1, y_c1);
	int64c1_t ret;
	if (x_c1.val < y_c1.val && tmp.val > x_c1.val) {
		//uf happend -->qeq is fales
		ret = encode_64c1(0);
	} else {
		//no uf --> geq is true
		ret = encode_64c1(1);
	}
	return ret;
}
AC_INLINE uint64c1_t u_geq_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t tmp = u_sub_64c1(x_c1, y_c1);
	uint64c1_t ret;
	if (x_c1.val < y_c1.val && tmp.val > x_c1.val) {
		//uf happend -->qeq is fales
		ret = u_encode_64c1(0);
	} else {
		//no uf --> geq is true
		ret = u_encode_64c1(1);
	}
	return ret;
}

AC_INLINE int64c1_t shl_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t y = encode_64c1((int64_t)1 << y_c1.val);
	int64c1_t r_c1 = mul_64c1(x_c1, y);
	return r_c1; // result already AN-encoded
}
AC_INLINE uint64c1_t u_shl_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t y = u_encode_64c1((uint64_t)1 << y_c1.val);
	uint64c1_t r_c1 = u_mul_64c1(x_c1, y);
	return r_c1; // result already AN-encoded
}

// INFO:	The behaviour of the signed right shift depends on the compiler implementation. Therfore this operation is not
//		supported and is prohibited.

AC_INLINE uint64c1_t u_shr_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t y = u_encode_64c1((uint64_t)1 << y_c1.val);
	uint64c1_t r_c1 = u_div_64c1(x_c1, y);
	return r_c1;
}

AC_INLINE int64c1_t land_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t res = mul_64c1(x_c1, y_c1);
	if (res.val != 0) {
		res = encode_64c1(1);
	}
	return res;
}
AC_INLINE uint64c1_t u_land_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t res = u_mul_64c1(x_c1, y_c1);
	if (res.val != 0) {
		res = u_encode_64c1(1);
	}
	return res;
}

AC_INLINE int64c1_t lor_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t r_c1 = add_64c1(x_c1, y_c1);
	if (r_c1.val != 0 || x_c1.val < 0 || y_c1.val < 0) {
		r_c1 = encode_64c1(1);
	}
	return r_c1;
}
AC_INLINE uint64c1_t u_lor_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t r_c1 = u_add_64c1(x_c1, y_c1);
	if (r_c1.val != 0 || x_c1.val < 0 || y_c1.val < 0) {
		r_c1 = u_encode_64c1(1);
	}
	return r_c1;
}

AC_INLINE int64c1_t and_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t res;
	res.val = x_c1.val & y_c1.val;
	res.check = (-1 - ((-1 - x_c1.val) | (-1 - y_c1.val))) % A1_64;
	return res;
}

AC_INLINE uint64c1_t u_and_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t res;
	res.val = x_c1.val & y_c1.val;
	res.check = (0xFFFFFFFFFFFFFFFF - ((0xFFFFFFFFFFFFFFFF - x_c1.val) |
					   (0xFFFFFFFFFFFFFFFF - y_c1.val))) %
		    A1_64;
	return res;
}

AC_INLINE int64c1_t or_64c1(int64c1_t x_c1, int64c1_t y_c1)
{
	int64c1_t res;
	res.val = x_c1.val | y_c1.val;
	res.check = (-1 - ((-1 - x_c1.val) & (-1 - y_c1.val))) % A1_64;
	return res;
}
AC_INLINE uint64c1_t u_or_64c1(uint64c1_t x_c1, uint64c1_t y_c1)
{
	uint64c1_t res;
	res.val = x_c1.val | y_c1.val;
	res.check = (0xFFFFFFFFFFFFFFFF - ((0xFFFFFFFFFFFFFFFF - x_c1.val) &
					   (0xFFFFFFFFFFFFFFFF - y_c1.val))) %
		    A1_64;
	return res;
}

AC_INLINE int64c1_t neg_64c1(int64c1_t x_c1)
{
	int64c1_t res;
	res.val = ~x_c1.val;
	res.check = (-1 - x_c1.val) % A1_64;
	return res;
}
AC_INLINE uint64c1_t u_neg_64c1(uint64c1_t x_c1)
{
	uint64c1_t res;
	res.val = ~x_c1.val;
	res.check = (0xFFFFFFFFFFFFFFFF - x_c1.val) % A1_64;
	return res;
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

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // RES64_1_H_