#pragma once
#include "drop.h"
#include "writer.h"
#include <stdbool.h>

#ifndef T
// For code editors only
#error T was not defined

#define T int
#endif

#define _OPTION_TO_STRING_HELPER(x) #x
#define _OPTION_TO_STRING(x) _OPTION_TO_STRING_HELPER(x)
#define _OPTION_HELPER_HIDDEN(a, b) a##b
#define _OPTION_CONCAT(a, b) _OPTION_HELPER_HIDDEN(a, b)

#define Option(type) _OPTION_CONCAT(_Option_, type)

typedef struct {
  T value;
  bool has;
} Option(T);

static inline void _OPTION_CONCAT(_impl_drop__Option_, T)(Option(T) * self) {
  DROP(self->value);
  self->has = false;
}

static inline bool _OPTION_CONCAT(_impl_object_format__Option_,
                                  T)(VWriter writer, const Option(T) data) {
  if (data.has) {
    return writer_write(writer, SV("Option<" _OPTION_TO_STRING(T) ">(")) &&
           _OPTION_CONCAT(_impl_object_format_, T)(writer, data.value) &&
           writer_write(writer, SV(")"));
  } else {
    return writer_write(writer, SV("Option<" _OPTION_TO_STRING(T) ">(None)"));
  }
}
