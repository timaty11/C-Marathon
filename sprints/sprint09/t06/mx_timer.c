#include <time.h>

double mx_timer(void (*f)()) {
    clock_t start, end;
    start = clock();
    f();
    end = clock();

    return (double) ((end - start) / CLOCKS_PER_SEC);
}

