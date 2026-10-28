#ifndef KERNEL_TERMINAL_H
#define KERNEL_TERMINAL_H

/* imleç konumuna yazar, '\n' alt satıra geçer */
void terminal_putchar(char c);

/* null-terminated string yazar, format desteği yok */
void vga_kprint(const char *c);

#endif /* KERNEL_TERMINAL_H */
