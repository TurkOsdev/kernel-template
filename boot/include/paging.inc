; long mode için paging şart.
; PML4 -> PDPT -> PD, PD'de 2 MiB huge page kullanıyoruz, PT'ye gerek yok.
; ilk 2 MiB identity map (sanal = fiziksel), kernel/stack/VGA hepsi içinde.

BITS 32

PAGE_PRESENT   equ 1 << 0
PAGE_WRITABLE  equ 1 << 1
PAGE_HUGE      equ 1 << 7

setup_paging:
    ; 3 tabloyu sıfırla (3 * 4096 / 4 = 3072 dword), çöp kalırsa patlar
    xor eax, eax
    mov edi, PML4_ADDR
    mov ecx, 3072
    rep stosd

    ; adresler 4G altında, üst dword zaten 0
    mov dword [PML4_ADDR], PDPT_ADDR | PAGE_PRESENT | PAGE_WRITABLE
    mov dword [PDPT_ADDR], PD_ADDR | PAGE_PRESENT | PAGE_WRITABLE
    mov dword [PD_ADDR], 0x00000000 | PAGE_HUGE | PAGE_WRITABLE | PAGE_PRESENT  ; 0x83

    ret
