; GDT - flat model, base 0 limit 4G. long mode zaten base/limit'e pek bakmıyor.
; selector = tablodaki byte offseti

CODE32_SEL equ gdt_code32 - gdt_start   ; 0x08
DATA32_SEL equ gdt_data32 - gdt_start   ; 0x10
CODE64_SEL equ gdt_code64 - gdt_start   ; 0x18
DATA64_SEL equ gdt_data64 - gdt_start   ; 0x20

align 8
gdt_start:

gdt_null:
    dq 0x0000000000000000   ; ilk entry hep null olmalı

gdt_code32:
    dq 0x00CF9A000000FFFF   ; access 0x9A (ring0 kod), flags 0xC (4K gran, 32-bit)

gdt_data32:
    dq 0x00CF92000000FFFF   ; access 0x92 (ring0 veri, yazılabilir)

gdt_code64:
    dq 0x00AF9A000000FFFF   ; flags 0xA -> L=1, 64-bit kod. L=1 iken D=0 olmalı

gdt_data64:
    dq 0x00CF92000000FFFF

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; boyut - 1
    dd gdt_start
