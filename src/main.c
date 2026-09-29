#include <drop.h>
#include <log.h>
#include <option_i32.hpp>
#include <stdlib.h>
#include <sv.h>
#include <writer.h>

// Using C string for simplicity
Option(i32) try_parse_int(const char* cstr) {
    char* endptr;
    errno = 0;
    long val = strtol(cstr, &endptr, 10);
    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) || (errno != 0 && val == 0) ||
        endptr == cstr) {
        return (Option(i32)){.has = false};
    }
    return (Option(i32)){.value = (int)val, .has = true};
}

i32 main(i32 argc, const char* argv[]) {
    (void)argc;
    (void)argv;

    StringView s = SV("TEST_STR!\n");

    LOG_INFO("Hello, world!");
    LOG_INFO("TEST {} VALUE", SV("custom"));

    LOG_ERROR("TEST {} {} VALUE 2", SV("custom"), 123);

    LOG_INFO("PARSE INT \"123\": {}", try_parse_int("123"));
    LOG_INFO("PARSE INT \"abc\": {}", try_parse_int("abc"));

    DROP(s);
    system("pause");
    return 0;
}
