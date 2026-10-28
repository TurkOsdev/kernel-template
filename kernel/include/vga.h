#ifndef KERNEL_VGA_H
#define KERNEL_VGA_H

#include <stddef.h>

/* her hücre 2 byte: alt byte karakter, üst byte renk (arka plan << 4 | ön plan) */

#define BLACK   0x00
#define BLUE    0x01
#define GREEN   0x02
#define CYAN    0x03
#define RED     0x04
#define MAGENTA 0x05
#define BROWN   0x06
#define GREY    0x07
#define WHITE   0x0F

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDRESS 0xB8000     /* identity map'li, direkt yazabiliyoruz */

/* ekran dışını sessizce yok sayar */
void vga_putchar(char c, size_t x, size_t y);

#endif /* KERNEL_VGA_H */
