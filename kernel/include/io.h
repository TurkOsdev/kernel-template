#ifndef KERNEL_IO_H
#define KERNEL_IO_H

#include <stdint.h>

/* port'a 1 byte yaz. out komutu veriyi AL'den alıyor, port sabitse
 * direkt gömülüyor, değilse DX'e konuyor */
static inline void outb(uint16_t port, uint8_t value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

#endif /* KERNEL_IO_H */
