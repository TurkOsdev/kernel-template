; stage 1 - MBR
; BIOS bizi 0x7C00'e yükleyip DL'ye disk numarasını koyuyor.
; 512 byte'a fazla bir şey sığmıyor, o yüzden tek işimiz stage2'yi okuyup atlamak.

%include "config.inc"

BITS 16
ORG STAGE1_ADDR

start:
    jmp 0:main          ; bazı BIOS'lar 07C0:0000 ile çağırıyor, CS'yi 0'a sabitle

main:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, REAL_MODE_STACK
    cld
    sti

    mov [boot_drive], dl

    ; INT 13h AH=02h, CHS ile sektör oku -> ES:BX
    mov ah, 0x02
    mov al, STAGE2_SECTORS
    xor ch, ch                  ; silindir 0
    mov cl, STAGE2_CHS_SECTOR
    xor dh, dh                  ; kafa 0
    mov dl, [boot_drive]
    mov bx, STAGE2_ADDR
    int 0x13
    jc disk_error
    cmp al, STAGE2_SECTORS      ; eksik okuduysa da hata
    jne disk_error

    mov dl, [boot_drive]        ; stage2 de DL'de bekliyor
    jmp 0:STAGE2_ADDR

disk_error:
    mov si, message
.print:
    lodsb
    test al, al
    jz .hang
    mov ah, 0x0e                ; BIOS teletype
    mov bx, 7
    int 0x10
    jmp .print
.hang:
    cli
    hlt
    jmp .hang                   ; NMI uyandırırsa diye

boot_drive db 0
message db 'stage1 disk error', 0

; 510'a kadar doldur, sonra boot imzası (diskte 55 AA)
times 510-($-$$) db 0
dw 0xaa55
