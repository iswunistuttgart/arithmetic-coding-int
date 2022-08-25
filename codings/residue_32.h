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

#ifndef RES32_1_H_
#define RES32_1_H_
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#include "common.h"
#include "helpers.h"
#include <stdint.h>
#include <stdlib.h>

#define ENCODING_NAME "RESIDUE_32BIT"

typedef struct {
	int32_t val;
	int32_t check;
} int32c1_t;
typedef struct {
	uint32_t val;
	uint32_t check;
} uint32c1_t;

// As for encoding floats
static uint32_t A1_32_U = 18;
static int32_t A1_32 = 18;
#define AC_RES_OVCORR32 14 //AC_RES_A-(AC_TWO_32%AC_RES_A)
#define AC_RES_OVCORR16 2 //AC_RES_A-(AC_TWO_16%AC_RES_A)
#define AC_RES_OVCORR8 14 //AC_RES_A-(AC_TWO_8%AC_RES_A)

#define AC_TWO_8 256
#define AC_TWO_16 65536
#define AC_TWO_32 4294967296
#define AC_TWO_64 18446744073709551616

AC_INLINE int32c1_t encode_32c1(int32_t x)
{
	int32c1_t ret;
	ret.val = x;
	ret.check = x % A1_32;
	return ret;
}
AC_INLINE uint32c1_t u_encode_32c1(uint32_t x)
{
	uint32c1_t ret;
	ret.val = x;
	ret.check = x % A1_32_U;
	return ret;
}

AC_INLINE int32_t decode_32c1(int32c1_t x_c1)
{
	return x_c1.val;
}
AC_INLINE uint32_t u_decode_32c1(uint32c1_t x_c1)
{
	return x_c1.val;
}
AC_INLINE int check_32c1(int32_t val, int32c1_t valc)
{
	int32_t tmpCheck = valc.val % A1_32;
	return tmpCheck == valc.check;
}
AC_INLINE int u_check_32c1(uint32_t val, uint32c1_t valc)
{
	uint32_t tmpCheck = valc.val % A1_32_U;
	return tmpCheck == valc.check;
}

AC_INLINE int32c1_t add_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t res;
	res.val = x_c1.val + y_c1.val;
	//overflow correction
	if ((x_c1.val > 0 && y_c1.val > 0 && res.val < 0) ||
	    (x_c1.val < 0 && y_c1.val < 0 && res.val > 0)) {
		if (res.val < 0) {
			res.check =
				(((x_c1.check + y_c1.check + AC_RES_OVCORR32) %
				  A1_32) -
				 A1_32) %
				A1_32;
		} else {
			res.check =
				(((x_c1.check + y_c1.check - AC_RES_OVCORR32) %
				  A1_32) +
				 A1_32) %
				A1_32;
		}

	} else {
		res.check = (x_c1.check + y_c1.check) % A1_32;
		if (res.val < 0 && res.check > 0) {
			res.check = -A1_32 + res.check;
		}
		if (res.val > 0 && res.check < 0) {
			res.check = A1_32 + res.check;
		}
	}
	return res;
}
AC_INLINE uint32c1_t u_add_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t res;
	res.val = x_c1.val + y_c1.val;
	//overflow correction
	if (res.val < x_c1.val) {
		res.check =
			(x_c1.check + y_c1.check + AC_RES_OVCORR32) % A1_32_U;
	} else {
		res.check = (x_c1.check + y_c1.check) % A1_32_U;
	}
	return res;
}

AC_INLINE int32c1_t sub_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t res;
	res.val = x_c1.val - y_c1.val;
	//underflow correction
	if ((x_c1.val > 0 && y_c1.val < 0 && res.val < 0) ||
	    (x_c1.val < 0 && y_c1.val > 0 && res.val > 0)) {
		if (res.val < 0) {
			res.check = (x_c1.check - y_c1.check - UINT8_MAX - 1) %
				    A1_32;
		} else {
			res.check = (x_c1.check - y_c1.check + UINT8_MAX + 1) %
				    A1_32;
		}

	} else {
		res.check = (x_c1.check - y_c1.check) % A1_32;
		if (res.val < 0 && res.check > 0) {
			res.check = -A1_32 + res.check;
		}
		if (res.val > 0 && res.check < 0) {
			res.check = A1_32 + res.check;
		}
	}
	return res;
}
AC_INLINE uint32c1_t u_sub_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t res;
	res.val = x_c1.val - y_c1.val;
	//underflow correction
	if (x_c1.val < y_c1.val) {
		res.check = (x_c1.check - y_c1.check + UINT8_MAX + 1) % A1_32_U;
	} else if (x_c1.check < y_c1.check) {
		res.check = (x_c1.check - y_c1.check + A1_32) % A1_32_U;
	} else {
		res.check = (x_c1.check - y_c1.check) % A1_32_U;
	}
	return res;
}

AC_INLINE uint32c1_t u_mul_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t res;
	res.val = x_c1.val * y_c1.val;
	uint64_t tempVal =
		((uint64_t)x_c1.val * (uint64_t)y_c1.val) / AC_TWO_32;
	if (tempVal > 0) {
		res.check =
			(x_c1.check * y_c1.check + AC_RES_OVCORR32 * tempVal) %
			A1_32_U;
	} else {
		res.check = (x_c1.check * y_c1.check) % A1_32_U;
	}
	return res;
}

AC_INLINE int32c1_t mul_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t res;
	res.val = x_c1.val * y_c1.val;
	int64_t tempVal = ((int64_t)x_c1.val * (int64_t)y_c1.val) / AC_TWO_32;
	if (tempVal != 0) {
		res.check =
			(x_c1.check * y_c1.check + AC_RES_OVCORR32 * tempVal) %
			A1_32;
	} else {
		res.check = (x_c1.check * y_c1.check) % A1_32;
		if ((x_c1.val > 0 && y_c1.val > 0 && res.val < 0) ||
		    (x_c1.val < 0 && y_c1.val < 0 && res.val < 0)) {
			res.check = -res.check;
		}
	}

	return res;
}

AC_INLINE int32c1_t div_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t r_c1;
	r_c1.val = x_c1.val / y_c1.val;
	if (r_c1.val * y_c1.val + x_c1.val % y_c1.val == x_c1.val) {
		r_c1.check = (x_c1.val / y_c1.val) % A1_32;
	} else {
		r_c1.check = 33;
	}

	return r_c1;
}

AC_INLINE uint32c1_t u_div_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t res;
	res.val = x_c1.val / y_c1.val;
	res.check = (res.val) % A1_32;
	uint32_t rem = (x_c1.val % y_c1.val) % A1_32;
	//internal check
	uint32_t checkL = 0;
	if (rem > x_c1.check) {
		checkL = (x_c1.check - rem + A1_32) % A1_32;
	} else {
		checkL = (x_c1.check - rem) % A1_32;
	}

	uint32_t checkR =
		((uint32_t)res.check * (uint32_t)y_c1.check) % (uint32_t)A1_32;

	if (checkR != checkL) {
		res.check = 33;
	}

	return res;
}

AC_INLINE int32c1_t mod_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t r_c1;
	r_c1.val = x_c1.val % y_c1.val;
	if ((x_c1.val / y_c1.val) * y_c1.val + r_c1.val == x_c1.val) {
		r_c1.check = (x_c1.val % y_c1.val) % A1_32;
	} else {
		r_c1.check = 33;
	}

	return r_c1;
}
AC_INLINE uint32c1_t u_mod_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t r_c1;
	r_c1.val = x_c1.val % y_c1.val;
	if ((x_c1.val / y_c1.val) * y_c1.val + r_c1.val == x_c1.val) {
		r_c1.check = (x_c1.val % y_c1.val) % A1_32;
	} else {
		r_c1.check = 33;
	}

	return r_c1;
}

AC_INLINE int32c1_t eq_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	return encode_32c1(x_c1.val == y_c1.val && x_c1.check == y_c1.check);
}
AC_INLINE uint32c1_t u_eq_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	return u_encode_32c1(x_c1.val == y_c1.val && x_c1.check == y_c1.check);
}

AC_INLINE int32c1_t neq_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	return encode_32c1(x_c1.val != y_c1.val && x_c1.check != y_c1.check);
}
AC_INLINE uint32c1_t u_neq_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	return u_encode_32c1(x_c1.val != y_c1.val && x_c1.check != y_c1.check);
}

AC_INLINE int32c1_t less_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t tmp = sub_32c1(x_c1, y_c1);
	int32c1_t ret;
	if (x_c1.val < y_c1.val && tmp.val > x_c1.val) {
		//uf happend --> less is true
		ret = encode_32c1(1);
	} else {
		//no uf --> less is false
		ret = encode_32c1(0);
	}
	return ret;
}
AC_INLINE uint32c1_t u_less_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t tmp = u_sub_32c1(x_c1, y_c1);
	uint32c1_t ret;
	if (x_c1.val < y_c1.val && tmp.val > x_c1.val) {
		//uf happend --> less is true
		ret = u_encode_32c1(1);
	} else {
		//no uf --> less is false
		ret = u_encode_32c1(0);
	}
	return ret;
}

AC_INLINE int32c1_t grt_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	// return -(x_c1 < y_c1) - 1;
}
AC_INLINE uint32c1_t u_grt_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	// return -(x_c1 < y_c1) - 1;
}

AC_INLINE int32c1_t leq_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t tmp = sub_32c1(y_c1, x_c1);
	int32c1_t ret;
	if (x_c1.val > y_c1.val && tmp.val > y_c1.val) {
		//uf happend --> leq is fales
		ret = encode_32c1(0);
	} else {
		//no uf --> leq is true
		ret = encode_32c1(1);
	}
	return ret;
}
AC_INLINE uint32c1_t u_leq_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t tmp = u_sub_32c1(y_c1, x_c1);
	uint32c1_t ret;
	if (x_c1.val > y_c1.val && tmp.val > y_c1.val) {
		//uf happend --> leq is fales
		ret = u_encode_32c1(0);
	} else {
		//no uf --> leq is true
		ret = u_encode_32c1(1);
	}
	return ret;
}

AC_INLINE int32c1_t geq_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t tmp = sub_32c1(x_c1, y_c1);
	int32c1_t ret;
	if (x_c1.val < y_c1.val && tmp.val > x_c1.val) {
		//uf happend -->qeq is fales
		ret = encode_32c1(0);
	} else {
		//no uf --> geq is true
		ret = encode_32c1(1);
	}
	return ret;
}
AC_INLINE uint32c1_t u_geq_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t tmp = u_sub_32c1(x_c1, y_c1);
	uint32c1_t ret;
	if (x_c1.val < y_c1.val && tmp.val > x_c1.val) {
		//uf happend -->qeq is fales
		ret = u_encode_32c1(0);
	} else {
		//no uf --> geq is true
		ret = u_encode_32c1(1);
	}
	return ret;
}

AC_INLINE int32c1_t shl_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t y = encode_32c1((int32_t)1 << y_c1.val);
	int32c1_t r_c1 = mul_32c1(x_c1, y);
	return r_c1; // result already AN-encoded
}
AC_INLINE uint32c1_t u_shl_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t y = u_encode_32c1((uint32_t)1 << y_c1.val);
	uint32c1_t r_c1 = u_mul_32c1(x_c1, y);
	return r_c1; // result already AN-encoded
}

// INFO:	The behaviour of the signed right shift depends on the compiler implementation. Therfore this operation is not
//		supported and is prohibited.

AC_INLINE uint32c1_t u_shr_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t y = u_encode_32c1((uint32_t)1 << y_c1.val);
	uint32c1_t r_c1 = u_div_32c1(x_c1, y);
	return r_c1;
}

AC_INLINE int32c1_t land_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t res = mul_32c1(x_c1, y_c1);
	if (res.val != 0) {
		res = encode_32c1(1);
	}
	return res;
}
AC_INLINE uint32c1_t u_land_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t res = u_mul_32c1(x_c1, y_c1);
	if (res.val != 0) {
		res = u_encode_32c1(1);
	}
	return res;
}

AC_INLINE int32c1_t lor_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t r_c1 = add_32c1(x_c1, y_c1);
	if (r_c1.val != 0 || x_c1.val < 0 || y_c1.val < 0) {
		r_c1 = encode_32c1(1);
	}
	return r_c1;
}
AC_INLINE uint32c1_t u_lor_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t r_c1 = u_add_32c1(x_c1, y_c1);
	if (r_c1.val != 0 || x_c1.val < 0 || y_c1.val < 0) {
		r_c1 = u_encode_32c1(1);
	}
	return r_c1;
}

AC_INLINE int32c1_t and_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t res;
	res.val = x_c1.val & y_c1.val;
	res.check = (-1 - ((-1 - x_c1.val) | (-1 - y_c1.val))) % A1_32;
	return res;
}

AC_INLINE uint32c1_t u_and_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t res;
	res.val = x_c1.val & y_c1.val;
	res.check = (0xFFFFFFFF -
		     ((0xFFFFFFFF - x_c1.val) | (0xFFFFFFFF - y_c1.val))) %
		    A1_32;
	return res;
}

AC_INLINE int32c1_t or_32c1(int32c1_t x_c1, int32c1_t y_c1)
{
	int32c1_t res;
	res.val = x_c1.val | y_c1.val;
	res.check = (-1 - ((-1 - x_c1.val) & (-1 - y_c1.val))) % A1_32;
	return res;
}
AC_INLINE uint32c1_t u_or_32c1(uint32c1_t x_c1, uint32c1_t y_c1)
{
	uint32c1_t res;
	res.val = x_c1.val | y_c1.val;
	res.check = (0xFFFFFFFF -
		     ((0xFFFFFFFF - x_c1.val) & (0xFFFFFFFF - y_c1.val))) %
		    A1_32;
	return res;
}

AC_INLINE int32c1_t neg_32c1(int32c1_t x_c1)
{
	int32c1_t res;
	res.val = ~x_c1.val;
	res.check = (-1 - x_c1.val) % A1_32;
	return res;
}
AC_INLINE uint32c1_t u_neg_32c1(uint32c1_t x_c1)
{
	uint32c1_t res;
	res.val = ~x_c1.val;
	res.check = (0xFFFFFFFF - x_c1.val) % A1_32;
	return res;
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

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // RES32_1_H_