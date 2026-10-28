#include <stddef.h>
#include <stdint.h>

#include "terminal.h"
#include "vga.h"

/* bunlar .bss'te ve .bss'i sıfırlayan kod yok, belleğin zaten 0 olmasına
 * güveniyoruz (qemu'da öyle). düzgün kernel'de kmain başında sıfırla */
static uint16_t cursor_x = 0;
static uint16_t cursor_y = 0;

void terminal_putchar(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
        return;
    }

    /* satır doldu, alta geç */
    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }

    /* scroll yok, ekran dolunca gerisi gidiyor */
    if (cursor_y >= VGA_HEIGHT) {
        return;
    }

    vga_putchar(c, cursor_x, cursor_y);
    cursor_x++;
}

void vga_kprint(const char *c) {
    for (size_t i = 0; c[i] != '\0'; i++) {
        terminal_putchar(c[i]);
    }
}
