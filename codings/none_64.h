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
 * @description: Provides all primitive functions for no encoding
 */

#ifndef NONE64_H_
#define NONE64_H_

#include <stdint.h>
#include <stdlib.h>
#include "common.h"

#define ENCODING_NAME "NONE_64BIT"

AC_INLINE int64_t encode_64(int64_t x)
{
	return x;
}
AC_INLINE uint64_t u_encode_64(uint64_t x)
{
	return x;
}

AC_INLINE int64_t decode_64(int64_t x)
{
	return x;
}
AC_INLINE uint64_t u_decode_64(uint64_t x)
{
	return x;
}

AC_INLINE int64_t add_64(int64_t x, int64_t y)
{
	return x + y;
}
AC_INLINE uint64_t u_add_64(uint64_t x, uint64_t y)
{
	return x + y;
}

AC_INLINE int64_t sub_64(int64_t x, int64_t y)
{
	return x - y;
}
AC_INLINE uint64_t u_sub_64(uint64_t x, uint64_t y)
{
	return x - y;
}

AC_INLINE int64_t mul_64(int64_t x, int64_t y)
{
	return x * y;
}
AC_INLINE uint64_t u_mul_64(uint64_t x, uint64_t y)
{
	return x * y;
}

AC_INLINE int64_t div_64(int64_t x, int64_t y)
{
	return x / y;
}
AC_INLINE uint64_t u_div_64(uint64_t x, uint64_t y)
{
	return x / y;
}

AC_INLINE int64_t mod_64(int64_t x, int64_t y)
{
	return x % y;
}
AC_INLINE uint64_t u_mod_64(uint64_t x, uint64_t y)
{
	return x % y;
}

AC_INLINE int64_t eq_64(int64_t x, int64_t y)
{
	return x == y;
}
AC_INLINE uint64_t u_eq_64(uint64_t x, uint64_t y)
{
	return x == y;
}

AC_INLINE int64_t neq_64(int64_t x, int64_t y)
{
	return x != y;
}
AC_INLINE uint64_t u_neq_64(uint64_t x, uint64_t y)
{
	return x != y;
}

AC_INLINE int64_t less_64(int64_t x, int64_t y)
{
	return x < y;
}
AC_INLINE uint64_t u_less_64(uint64_t x, uint64_t y)
{
	return x < y;
}

AC_INLINE int64_t grt_64(int64_t x, int64_t y)
{
	return x > y;
}
AC_INLINE uint64_t u_grt_64(uint64_t x, uint64_t y)
{
	return x > y;
}

AC_INLINE int64_t leq_64(int64_t x, int64_t y)
{
	return x <= y;
}
AC_INLINE uint64_t u_leq_64(uint64_t x, uint64_t y)
{
	return x <= y;
}

AC_INLINE int64_t geq_64(int64_t x, int64_t y)
{
	return x >= y;
}
AC_INLINE uint64_t u_geq_64(uint64_t x, uint64_t y)
{
	return x >= y;
}

AC_INLINE int64_t shl_64(int64_t x, int64_t y)
{
	return x << y;
}
AC_INLINE uint64_t u_shl_64(uint64_t x, uint64_t y)
{
	return x << y;
}

//INFO:	The behaviour of the signed right shift depends on the compiler implementation. Therfore this operation is not
//		supported and is prohibited.
AC_INLINE uint64_t u_shr_64(uint64_t x, uint64_t y)
{
	return 0;
}

AC_INLINE int64_t land_64(int64_t x, int64_t y)
{
	return x && y;
}
AC_INLINE uint64_t u_land_64(uint64_t x, uint64_t y)
{
	return x && y;
}

AC_INLINE int64_t lor_64(int64_t x, int64_t y)
{
	return x || y;
}
AC_INLINE uint64_t u_lor_64(uint64_t x, uint64_t y)
{
	return x || y;
}

AC_INLINE int64_t and_64(int64_t x, int64_t y)
{
	return x & y;
}
AC_INLINE uint64_t u_and_64(uint64_t x, uint64_t y)
{
	return x & y;
}

AC_INLINE int64_t or_64(int64_t x, int64_t y)
{
	return x | y;
}
AC_INLINE uint64_t u_or_64(uint64_t x, uint64_t y)
{
	return x | y;
}

AC_INLINE int64_t neg_64(int64_t x)
{
	return ~x;
}
AC_INLINE uint64_t u_neg_64(uint64_t x)
{
	return ~x;
}

AC_INLINE int64_t xor_64(int64_t x, int64_t y)
{
	return x ^ y;
}
AC_INLINE uint64_t u_xor_64(uint64_t x, uint64_t y)
{
	return x ^ y;
}

#endif //NONE64_H_