; ortak sabitler, boot.asm ve stage2.asm ikisi de bunu include ediyor

%define STAGE1_ADDR         0x7C00      ; BIOS MBR'yi hep buraya yükler
%define REAL_MODE_STACK     0x7C00      ; stack aşağı büyüyor, stage1'i ezmez

%define STAGE2_ADDR         0x8000
%define STAGE2_SECTORS      4
%define STAGE2_CHS_SECTOR   2           ; CHS sektörleri 1'den başlıyor, yani LBA 1

%define KERNEL_ADDR         0x10000     ; linker.ld ile aynı olmalı
%define KERNEL_LBA          5

; Makefile -D ile veriyor, vermezse 32
%ifndef KERNEL_SECTORS
%define KERNEL_SECTORS      32
%endif

%define KERNEL_STACK        0x90000

; her tablo 4 KiB ve 4 KiB hizalı olmalı
%define PML4_ADDR           0x1000
%define PDPT_ADDR           0x2000
%define PD_ADDR             0x3000

%define DEBUG_PORT          0xE9        ; qemu debugcon
