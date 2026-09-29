#pragma once
#include "int.h"
#include <string.h>

#define SV(str) ((StringView){.ptr = str, .size = sizeof(str) - 1})

typedef struct {
    const char* ptr;
    usize size;
} StringView;

static inline StringView sv_from_cstr(const char* cstr) {
    return (StringView){.ptr = cstr, .size = strlen(cstr)};
}

static inline void _impl_drop_StringView(StringView* self) {
    self->ptr = NULL;
    self->size = 0;
}

// Should be auto generated
#if !defined(_TD_1)

#define _TD_1(prefix)                                                                              \
    StringView:                                                                                    \
    prefix##StringView
#define _TD _TD_1

#elif !defined(_TD_2)

#undef _TD
#define _TD_2(prefix) _TD_1(prefix), StringView : prefix##StringView
#define _TD _TD_2

#elif !defined(_TD_3)

#undef _TD
#define _TD_3(prefix) _TD_2(prefix), StringView : prefix##StringView
#define _TD _TD_3

#else

#error Too many types

#endif
