#pragma once
#include "panic.h"
#include "writer.h"

static inline StringView fmt_next_split(StringView* fmt) {
    for (StringView ret = *fmt; ret.size > 1; ret.ptr++, ret.size--) {
        if (ret.ptr[0] == '{' && ret.ptr[1] == '}') {
            fmt->size = ret.ptr - fmt->ptr;
            ret.ptr += 2;
            ret.size -= 2;
            return ret;
        }
    }
    PANIC("Invalid format string");
    UNREACHABLE();
}

#define _IMPL_FMT_0(writer, fmt) writer_write(writer, fmt)
#define _IMPL_FMT_1(writer, fmt, a1)                                                               \
    StringView f1 = fmt;                                                                           \
    StringView f2 = fmt_next_split(&f1);                                                           \
    writer_write(writer, f1);                                                                      \
    OBJECT_FORMAT(writer, a1);                                                                     \
    writer_write(writer, f2);
#define _IMPL_FMT_2(writer, fmt, a1, a2)                                                           \
    StringView f1 = fmt;                                                                           \
    StringView f2 = fmt_next_split(&f1);                                                           \
    StringView f3 = fmt_next_split(&f2);                                                           \
    writer_write(writer, f1);                                                                      \
    OBJECT_FORMAT(writer, a1);                                                                     \
    writer_write(writer, f2);                                                                      \
    OBJECT_FORMAT(writer, a2);                                                                     \
    writer_write(writer, f3);
#define _IMPL_FMT_3(writer, fmt, a1, a2, a3)                                                       \
    StringView f1 = fmt;                                                                           \
    StringView f2 = fmt_next_split(&f1);                                                           \
    StringView f3 = fmt_next_split(&f2);                                                           \
    StringView f4 = fmt_next_split(&f3);                                                           \
    writer_write(writer, f1);                                                                      \
    OBJECT_FORMAT(writer, a1);                                                                     \
    writer_write(writer, f2);                                                                      \
    OBJECT_FORMAT(writer, a2);                                                                     \
    writer_write(writer, f3);                                                                      \
    OBJECT_FORMAT(writer, a3);                                                                     \
    writer_write(writer, f4);
#define _IMPL_FMT_4(writer, fmt, a1, a2, a3)                                                       \
    StringView f1 = fmt;                                                                           \
    StringView f2 = fmt_next_split(&f1);                                                           \
    StringView f3 = fmt_next_split(&f2);                                                           \
    StringView f4 = fmt_next_split(&f3);                                                           \
    StringView f5 = fmt_next_split(&f4);                                                           \
    writer_write(writer, f1);                                                                      \
    OBJECT_FORMAT(writer, a1);                                                                     \
    writer_write(writer, f2);                                                                      \
    OBJECT_FORMAT(writer, a2);                                                                     \
    writer_write(writer, f3);                                                                      \
    OBJECT_FORMAT(writer, a3);                                                                     \
    writer_write(writer, f4);                                                                      \
    OBJECT_FORMAT(writer, a4);                                                                     \
    writer_write(writer, f5);

#define _IMPL_FMT_SHIFTER(a4, a3, a2, a1, _CALLBACK, ...) _CALLBACK

// Only supports 4 formats "{}" at maximum
#define FORMAT(writer, fmt, ...)                                                                   \
    _IMPL_FMT_SHIFTER(__VA_ARGS__ __VA_OPT__(, ) _IMPL_FMT_4, _IMPL_FMT_3, _IMPL_FMT_2,            \
                      _IMPL_FMT_1, _IMPL_FMT_0)(writer, fmt __VA_OPT__(, ) __VA_ARGS__)
