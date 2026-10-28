# ASM Bootloader + C Kernel Template (x86_64)

Legacy BIOS için minimal bir boot template'i. Bootloader NASM ile, kernel C ile yazıldı. GRUB ya da Limine kullanılmıyor.

## Gereksinimler

```sh
# Arch
sudo pacman -S --needed base-devel nasm binutils qemu-desktop
# Debian / Ubuntu
sudo apt install build-essential nasm qemu-system-x86
# Fedora
sudo dnf install make gcc binutils nasm qemu-system-x86
```

## Kullanım

```sh
make run
```

Terminalde `ABCDK` görürsen kernel'e ulaşılmış demektir. Harflerin anlamı `boot/stage2.asm` dosyasının başında yazıyor.

## Lisans

[MIT](LICENSE) © Türk OSDev Topluluğu
