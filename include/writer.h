#pragma once
#include "sv.h"
#include "unreachable.h"
#include <stdbool.h>
#include <stdio.h>

// Don't use type system for that, otherwise we will have to implement everything
// Hopefully compiler will optimize that

typedef enum { WRITER_STDOUT, WRITER_STDERR } WriterType;

typedef struct {
    void* impl;
    WriterType type;
} VWriter;

typedef struct {
    int dummy;
} WriterStdout;

static inline bool _impl_writer_stdout(const WriterStdout* self, const StringView data) {
    (void)self;

    fprintf(stdout, "%.*s", (i32)data.size, data.ptr);
    return true;
}

static inline WriterStdout create_stdout_writer() { return (WriterStdout){.dummy = 0}; }

static inline VWriter stdout_writer_as_writer(WriterStdout* self) {
    return (VWriter){.impl = self, .type = WRITER_STDOUT};
}

typedef struct {
    int dummy;
} WriterStderr;

static inline bool _impl_writer_stderr(const WriterStderr* self, const StringView data) {
    (void)self;

    fprintf(stderr, "%.*s", (i32)data.size, data.ptr);
    return true;
}

static inline WriterStderr create_stderr_writer() { return (WriterStderr){.dummy = 0}; }

static inline VWriter stderr_writer_as_writer(WriterStderr* self) {
    return (VWriter){.impl = self, .type = WRITER_STDERR};
}

static inline bool writer_write(VWriter writer, StringView data) {
    switch (writer.type) {
    case WRITER_STDOUT:
        return _impl_writer_stdout((WriterStdout*)writer.impl, data);
    case WRITER_STDERR:
        return _impl_writer_stderr((WriterStderr*)writer.impl, data);
    }
    UNREACHABLE();
}

// Impl basic types here to avoid recursive includes
static inline bool _impl_object_format_StringView(VWriter writer, const StringView data) {
    return writer_write(writer, data);
}

static inline bool _impl_object_format_i32(VWriter writer, const i32 data) {
    char buf[16];
#ifdef _MSC_VER
    _itoa_s(data, buf, sizeof(buf), 10);
#else
    _itoa(data, buf, 10);
#endif
    return writer_write(writer, sv_from_cstr(buf));
}

#define OBJECT_FORMAT(writer, obj) _Generic((obj), _TD(_impl_object_format_))(writer, obj)
