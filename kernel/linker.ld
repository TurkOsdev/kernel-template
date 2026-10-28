/* objcopy ile ham binary'ye çevriliyor, yani kernel.bin'in 0. byte'ı = 0x10000 */

ENTRY(kmain)
SECTIONS
{
    . = 0x10000;    /* config.inc'teki KERNEL_ADDR ile aynı olmalı */

    /* The bootloader calls the first byte of the raw kernel image. */
    .text : { *(.text.entry) *(.text .text.*) }
    .rodata : { *(.rodata .rodata.*) }
    .data : { *(.data .data.*) }

    /* .bss dosyaya yazılmıyor ve kimse sıfırlamıyor, terminal.c'ye bak */
    .bss : { *(.bss .bss.*) *(COMMON) }

    /DISCARD/ : { *(.comment) *(.note*) *(.eh_frame*) }
}
