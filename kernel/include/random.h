#ifndef KERNEL_RANDOM_H
#define KERNEL_RANDOM_H

#include <stdint.h>

/* xorshift32. seed sabit, her açılışta aynı dizi gelir. güvenlik için kullanma (SADECE DEMO İÇİN KULLANILMALI)*/
uint32_t krand(void);

#endif /* KERNEL_RANDOM_H */
