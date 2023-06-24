#include "../../clib/sformat.h"
#include "../../clib/strings.h"
#include "../logs.h"

int test_sprintf() {
    char* ptr = sprintf((char*)"Testing sprintf: %u, %i, %p, %c, %s\n", 29, -29, (void*)29, 'X', "abacaba");

    if (memcmp(ptr, (char*)"Testing sprintf: 29, -29, 0x0000001D, X, abacaba\n") != 0) {
        log_critical("sprintf works incorrectly. cannot continue\n", BOTH);
        return 1; // should never happen
    }

    log_info(ptr, BOTH);
    return 0;
}