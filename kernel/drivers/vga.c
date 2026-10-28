#include <stdint.h>

#include "vga.h"
#include "random.h"

/* volatile şart, yoksa derleyici yazmaları silebilir (okuyan ekran kartı) */
static volatile uint16_t *vga = (volatile uint16_t *)VGA_ADDRESS;

static uint16_t vga_entry(char character, uint8_t color) {
    /* uint8_t cast: char signed ise 127 üstü renk byte'ını bozar */
    return((uint16_t)color << 8) | (uint8_t)character;
}

static uint8_t vga_color(uint8_t fg, uint8_t bg) {
    return fg | (bg << 4);
}

/* % 8: arka planda bit 3 bazı yerlerde blink oluyor */
static uint8_t randomColor(void) {
    return (uint8_t)(krand() % 8);
}

void vga_putchar(char c, size_t x, size_t y) {
    uint8_t bosluk = 0;

    /* boşluklar siyah kalsın, gerisi rastgele zemin */
    if(c == ' ') {
        bosluk = BLACK;
    } else {
        bosluk = randomColor();
    }

    if (x >= VGA_WIDTH || y >= VGA_HEIGHT) {
        return;
    }

    size_t index = y * VGA_WIDTH + x;

    vga[index] = vga_entry(c, vga_color(WHITE, bosluk));
}
