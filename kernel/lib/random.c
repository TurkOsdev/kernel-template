#include "random.h"

/* 0 olmamalı, xorshift 0'da takılı kalıyor */
static uint32_t random_state = 123456789;

uint32_t krand(void) {
    uint32_t x = random_state;

    /* 13/17/5 Marsaglia'nın tam periyot veren üçlüsü */
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;

    random_state = x;

    return x;
}
