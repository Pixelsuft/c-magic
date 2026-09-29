// This file should be auto-generated
#pragma once
#include "int.h"
#define T i32
#include "option_impl.hpp" // IWYU pragma: keep
#undef T

#if !defined(_TD_1)

#define _TD_1(prefix)                                                          \
  _Option_i32:                                                                 \
  prefix##StringView
#define _TD _TD_1

#elif !defined(_TD_2)

#undef _TD
#define _TD_2(prefix) _TD_1(prefix), _Option_i32 : prefix##_Option_i32
#define _TD _TD_2

#elif !defined(_TD_3)

#undef _TD
#define _TD_3(prefix) _TD_2(prefix), _Option_i32 : prefix##_Option_i32
#define _TD _TD_3

#else

#error Too many types

#endif
