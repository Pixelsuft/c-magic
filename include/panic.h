#pragma once
#include "sv.h"
#include "unreachable.h"
#include <stdio.h>
#include <stdlib.h>

static inline void _panic_impl(StringView msg) {
    fprintf(stderr, "\n\nPANIC!\nMESSAGE: %.*s\n\n", (i32)msg.size, msg.ptr);
    abort();
    UNREACHABLE();
}

#define PANIC(msg) _panic_impl(SV(msg))
