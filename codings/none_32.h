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
 * @description: Provides all primitive functions for no enocding
 */

#ifndef NONE32_H_
#define NONE32_H_

#include <stdint.h>
#include <stdlib.h>
#include "common.h"

#define ENCODING_NAME "NONE_32BIT"

AC_INLINE int32_t encode_32(int32_t x)
{
	return x;
}
AC_INLINE uint32_t u_encode_32(uint32_t x)
{
	return x;
}

AC_INLINE int32_t decode_32(int32_t x)
{
	return x;
}
AC_INLINE uint32_t u_decode_32(uint32_t x)
{
	return x;
}

AC_INLINE int32_t add_32(int32_t x, int32_t y)
{
	return x + y;
}
AC_INLINE uint32_t u_add_32(uint32_t x, uint32_t y)
{
	return x + y;
}

AC_INLINE int32_t sub_32(int32_t x, int32_t y)
{
	return x - y;
}
AC_INLINE uint32_t u_sub_32(uint32_t x, uint32_t y)
{
	return x - y;
}

AC_INLINE int32_t mul_32(int32_t x, int32_t y)
{
	return x * y;
}
AC_INLINE uint32_t u_mul_32(uint32_t x, uint32_t y)
{
	return x * y;
}

AC_INLINE int32_t div_32(int32_t x, int32_t y)
{
	return x / y;
}
AC_INLINE uint32_t u_div_32(uint32_t x, uint32_t y)
{
	return x / y;
}

AC_INLINE int32_t mod_32(int32_t x, int32_t y)
{
	return x % y;
}
AC_INLINE uint32_t u_mod_32(uint32_t x, uint32_t y)
{
	return x % y;
}

AC_INLINE int32_t eq_32(int32_t x, int32_t y)
{
	return x == y;
}
AC_INLINE uint32_t u_eq_32(uint32_t x, uint32_t y)
{
	return x == y;
}

AC_INLINE int32_t neq_32(int32_t x, int32_t y)
{
	return x != y;
}
AC_INLINE uint32_t u_neq_32(uint32_t x, uint32_t y)
{
	return x != y;
}

AC_INLINE int32_t less_32(int32_t x, int32_t y)
{
	return x < y;
}
AC_INLINE uint32_t u_less_32(uint32_t x, uint32_t y)
{
	return x < y;
}

AC_INLINE int32_t grt_32(int32_t x, int32_t y)
{
	return x > y;
}
AC_INLINE uint32_t u_grt_32(uint32_t x, uint32_t y)
{
	return x > y;
}

AC_INLINE int32_t leq_32(int32_t x, int32_t y)
{
	return x <= y;
}
AC_INLINE uint32_t u_leq_32(uint32_t x, uint32_t y)
{
	return x <= y;
}

AC_INLINE int32_t geq_32(int32_t x, int32_t y)
{
	return x >= y;
}
AC_INLINE uint32_t u_geq_32(uint32_t x, uint32_t y)
{
	return x >= y;
}

AC_INLINE int32_t shl_32(int32_t x, int32_t y)
{
	return x << y;
}
AC_INLINE uint32_t u_shl_32(uint32_t x, uint32_t y)
{
	return x << y;
}

//INFO:	The behaviour of the signed right shift depends on the compiler implementation. Therfore this operation is not
//		supported and is prohibited.
AC_INLINE uint32_t u_shr_32(uint32_t x, uint32_t y)
{
	return 0;
}

AC_INLINE int32_t land_32(int32_t x, int32_t y)
{
	return x && y;
}
AC_INLINE uint32_t u_land_32(uint32_t x, uint32_t y)
{
	return x && y;
}

AC_INLINE int32_t lor_32(int32_t x, int32_t y)
{
	return x || y;
}
AC_INLINE uint32_t u_lor_32(uint32_t x, uint32_t y)
{
	return x || y;
}

AC_INLINE int32_t and_32(int32_t x, int32_t y)
{
	return x & y;
}
AC_INLINE uint32_t u_and_32(uint32_t x, uint32_t y)
{
	return x & y;
}

AC_INLINE int32_t or_32(int32_t x, int32_t y)
{
	return x | y;
}
AC_INLINE uint32_t u_or_32(uint32_t x, uint32_t y)
{
	return x | y;
}

AC_INLINE int32_t neg_32(int32_t x)
{
	return ~x;
}
AC_INLINE uint32_t u_neg_32(uint32_t x)
{
	return ~x;
}

AC_INLINE int32_t xor_32(int32_t x, int32_t y)
{
	return x ^ y;
}
AC_INLINE uint32_t u_xor_32(uint32_t x, uint32_t y)
{
	return x ^ y;
}

#endif //NONE32_H_