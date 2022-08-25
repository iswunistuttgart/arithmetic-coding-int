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
 * @description: Provides inline functionality
 */

#ifndef COMMON_H_
#define COMMON_H_
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#define DO_AC_INLINE

#ifdef __linux__
#ifdef DO_AC_INLINE
#define AC_INLINE __attribute__((always_inline)) static inline
#else
#define AC_INLINE
#endif
#endif
#ifdef _WIN32

#ifdef DO_AC_INLINE
#define AC_INLINE __forceinline
#else
#define AC_INLINE
#endif
#endif

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //COMMON_H_