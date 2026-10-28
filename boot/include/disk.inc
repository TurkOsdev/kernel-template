; kernel'i BIOS EDD (INT 13h AH=42h) ile LBA'dan okuyoruz, CHS hesabıyla uğraşmamak için.
; BIOS çağrıları sadece real mode'da çalışır.

BITS 16

; INT 13h AH=41h: EDD var mı? yoksa disk_error'a gider
check_edd:
    mov ah, 0x41
    mov bx, 0x55AA
    mov dl, [boot_drive]
    int 0x13

    jc disk_error
    cmp bx, 0xAA55
    jne disk_error

    test cx, 1              ; bit 0 = AH=42h destekleniyor
    jz disk_error

    ret

; disk_packet'e göre kernel'i KERNEL_ADDR'e okur
load_kernel:
    mov si, disk_packet
    mov ah, 0x42
    mov dl, [boot_drive]
    int 0x13

    jc disk_error

    ret

disk_error:
    mov al, 'E'
    out DEBUG_PORT, al

    mov si, error_text

.print:
    lodsb
    test al, al
    jz .halt

    mov ah, 0x0E
    mov bx, 0x0007
    int 0x10

    jmp .print

.halt:
    cli
    hlt
    jmp .halt

error_text db 'Stage2 disk error!', 0

; disk address packet, 16 byte
align 4
disk_packet:
    db 0x10                 ; paket boyutu
    db 0x00
    dw KERNEL_SECTORS
    dw KERNEL_ADDR & 0xF    ; offset
    dw KERNEL_ADDR >> 4     ; segment (0x1000:0000 = 0x10000)
    dq KERNEL_LBA
