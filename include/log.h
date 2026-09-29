#pragma once
#include "fmt.h"
#include "writer.h"

#if defined(_DEBUG)
#define _LOG_STRINGIFY2(x) #x
#define _LOG_STRINGIFY(x) _LOG_STRINGIFY2(x)

// With file/line (DEBUG)
#define LOG_INFO(fmt, ...)                                                                         \
    do {                                                                                           \
        WriterStdout _writer = create_stdout_writer();                                             \
        VWriter _i_wr = stdout_writer_as_writer(&_writer);                                         \
        writer_write(_i_wr, SV("[INFO] [" __FILE__ ":" _LOG_STRINGIFY(__LINE__) "] "));            \
        FORMAT(_i_wr, SV(fmt) __VA_OPT__(, ) __VA_ARGS__);                                         \
        writer_write(_i_wr, SV("\n"));                                                             \
    } while (0)

#define LOG_ERROR(fmt, ...)                                                                        \
    do {                                                                                           \
        WriterStderr _writer = create_stderr_writer();                                             \
        VWriter _i_wr = stderr_writer_as_writer(&_writer);                                         \
        writer_write(_i_wr, SV("[ERROR] [" __FILE__ ":" _LOG_STRINGIFY(__LINE__) "] "));           \
        FORMAT(_i_wr, SV(fmt) __VA_OPT__(, ) __VA_ARGS__);                                         \
        writer_write(_i_wr, SV("\n"));                                                             \
    } while (0)
#else
// Without file/line

#define LOG_INFO(fmt, ...)                                                                         \
    do {                                                                                           \
        WriterStdout _writer = create_stdout_writer();                                             \
        VWriter _i_wr = stdout_writer_as_writer(&_writer);                                         \
        writer_write(_i_wr, SV("[INFO] "));                                                        \
        FORMAT(_i_wr, SV(fmt) __VA_OPT__(, ) __VA_ARGS__);                                         \
        writer_write(_i_wr, SV("\n"));                                                             \
    } while (0)

#define LOG_ERROR(fmt, ...)                                                                        \
    do {                                                                                           \
        WriterStderr _writer = create_stderr_writer();                                             \
        VWriter _i_wr = stderr_writer_as_writer(&_writer);                                         \
        writer_write(_i_wr, SV("[ERROR] "));                                                       \
        FORMAT(_i_wr, SV(fmt) __VA_OPT__(, ) __VA_ARGS__);                                         \
        writer_write(_i_wr, SV("\n"));                                                             \
    } while (0)
#endif
