; A20 kapalıyken 1 MiB üstü adresler başa sarıyor (8086 uyumluluğu).
; fast A20 ile açıyoruz, qemu ve çoğu donanımda çalışıyor.

BITS 16

enable_a20:
    in al, 0x92
    or al, 0x02             ; bit 1 = A20
    and al, 0xFE            ; bit 0 reset atar, sakın 1 olmasın
    out 0x92, al
    ret
