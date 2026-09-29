#pragma once

#if defined(_MSC_VER)
#include <stddef.h>

typedef unsigned __int8 u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;

typedef signed __int8 i8;
typedef signed __int16 i16;
typedef signed __int32 i32;
typedef signed __int64 i64;

typedef size_t usize;
#else
typedef __UINT8_TYPE__ u8;
typedef __UINT16_TYPE__ u16;
typedef __UINT32_TYPE__ u32;
typedef __UINT64_TYPE__ u64;

typedef __INT8_TYPE__ i8;
typedef __INT16_TYPE__ i16;
typedef __INT32_TYPE__ i32;
typedef __INT64_TYPE__ i64;

typedef __SIZE_TYPE__ usize;
#endif

// Currently doing only for i32 for simplicity

static inline void _impl_drop_i32(i32* self) { *self = -1; }

// Should be auto generated
#if !defined(_TD_1)

#define _TD_1(prefix)                                                                              \
    i32:                                                                                           \
    prefix##i32
#define _TD _TD_1

#elif !defined(_TD_2)

#undef _TD
#define _TD_2(prefix) _TD_1(prefix), i32 : prefix##i32
#define _TD _TD_2

#elif !defined(_TD_3)

#undef _TD
#define _TD_3(prefix) _TD_2(prefix), i32 : prefix##i32
#define _TD _TD_3

#else

#error Too many types

#endif
