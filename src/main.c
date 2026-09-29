#include <drop.h>
#include <log.h>
#include <stdlib.h>
#include <sv.h>
#include <writer.h>

i32 main(i32 argc, const char* argv[]) {
    (void)argc;
    (void)argv;

    StringView s = SV("TEST_STR!\n");

    LOG_INFO("Hello, world!");
    LOG_INFO("TEST {} VALUE", SV("custom"));

    LOG_ERROR("TEST {} {} VALUE 2", SV("custom"), 123);

    DROP(s);
    system("pause");
    return 0;
}
