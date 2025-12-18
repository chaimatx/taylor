#include "vik.h"
#include <math.h>
#include <stdio.h>
#include <stddef.h>

static const double C[] = {
    1.0,
    1.0/3.0,
    2.0/15.0,
    17.0/315.0,
    62.0/2835.0,
    1382.0/155925.0,
    21844.0/6081075.0
    // можно продолжить
};

double taylor_tan(double x, double eps)
{
    (void)eps;
    double x2 = x*x;
    double sum = 0.0;
    double term = x;

    for (size_t n = 0; n < sizeof(C) / sizeof(C[0]); n++) {
        sum += C[n] * term;
        term *= x2;
    }

    return sum;
}

int test_taylor_tan()
{
    struct {
        double x;
        double eps;
        double expected;
    } tests[] = {
        {0.2, 1e-6, tan(0.2)},
        {0.1, 1e-6, tan(0.1)},
        {0.3, 1e-6, tan(0.3)}
    };

    int count = sizeof(tests)/sizeof(tests[0]);

    for (int i = 0; i < count; i++) {
        double r = taylor_tan(tests[i].x, tests[i].eps);
        double diff = fabs(r - tests[i].expected);

        if (diff > tests[i].eps) {
            printf("-1\nTest %d failed: x=%f, got=%f, expected=%f\n",
                   i, tests[i].x, r, tests[i].expected);
            return -1;
        }
    }

    printf("0\nTests Passed!");
    return 0;
}