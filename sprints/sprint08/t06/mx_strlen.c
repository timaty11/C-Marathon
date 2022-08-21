#include "create_agent.h"

int mx_strlen(const char *s) {
    int counter = 0;
    while (s[counter]) {
        ++counter;
    }
    return counter;
}
