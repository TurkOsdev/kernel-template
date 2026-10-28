; stage 2: real mode -> protected mode -> long mode -> kmain
;
; debugcon çıktısı: A=stage2 başladı, B=kernel okundu, C=pmode, D=long mode,
; K=kmain, E=disk hatası. nerede takıldığını buradan anlarsın.

%include "config.inc"

BITS 16
ORG STAGE2_ADDR

stage2_start:
    cli

    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, REAL_MODE_STACK

    cld
    sti

    mov [boot_drive], dl

    mov al, 'A'
    out DEBUG_PORT, al

    call check_edd
    call load_kernel

    mov al, 'B'
    out DEBUG_PORT, al

    ; 80x25 text mode. long mode'da BIOS yok, şimdi yapmak lazım
    mov ax, 0x0003
    int 0x10

    ; IDT yok, bundan sonra interrupt gelirse triple fault
    cli

    call enable_a20

    lgdt [gdt_descriptor]

    ; CR0.PE = 1
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    ; far jump ile CS'yi yükle ve 32-bit'e geç
    jmp CODE32_SEL:protected_start

%include "disk.inc"
%include "a20.inc"

boot_drive db 0

%include "gdt.inc"

BITS 32

protected_start:
    mov ax, DATA32_SEL

    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov esp, KERNEL_STACK

    mov al, 'C'
    out DEBUG_PORT, al

    call setup_paging

    ; CR4.PAE
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    mov eax, PML4_ADDR
    mov cr3, eax

    ; EFER.LME (MSR 0xC0000080, bit 8)
    mov ecx, 0xC0000080
    rdmsr

    or eax, 1 << 8
    wrmsr

    ; CR0.PG -> compatibility mode'a girdik
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    ; 64-bit kod segmentine atla
    jmp CODE64_SEL:long_mode_start

%include "paging.inc"

BITS 64

long_mode_start:
    mov ax, DATA64_SEL

    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax

    mov rsp, KERNEL_STACK
    and rsp, -16            ; ABI call öncesi 16 byte hizalı stack istiyor

    xor rbp, rbp            ; stack trace burada bitsin

    mov al, 'D'
    out DEBUG_PORT, al

    ; kmain kernel.bin'in ilk byte'ı (linker.ld'ye bak)
    ; mutlak adres olsun diye register üzerinden çağırıyoruz
    mov rax, KERNEL_ADDR
    call rax

; kmain dönmemeli ama dönerse
halt:
    cli
.hang:
    hlt
    jmp .hang

; tam 4 sektör. sığmazsa nasm burada negatif times hatası verir
times (STAGE2_SECTORS * 512)-($-$$) db 0
