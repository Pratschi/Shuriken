; Shuriken BIOS Bootloader
; 512 bytes (MBR)

[org 0x7C00]

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

; Clear screen
    mov ah, 0x00
    mov al, 0x03
    int 0x10

; Print message
    mov si, msg
.print:
    lodsb
    or al, al
    jz load_kernel
    mov ah, 0x0E
    int 0x10
    jmp .print

; Load kernel starting from LBA sector 1
load_kernel:
    mov bx, 0x1000
    mov dh, 0
    mov dl, 0x80
    mov ch, 0
    mov cl, 2
    mov ah, 0x02
    mov al, 20
    int 0x13

; Enter Protected Mode
enter_pm:
    cli
    lgdt [gdt_desc]

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp CODE_SEG:init_pm

[bits 32]
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax

    jmp 0x08:0x1000

msg: db "Shuriken BIOS Bootloader...",0

; --- GDT ---
gdt:
    dq 0
    dq 0x00CF9A000000FFFF
    dq 0x00CF92000000FFFF

gdt_desc:
    dw gdt_desc - gdt - 1
    dd gdt

CODE_SEG equ 0x08
DATA_SEG equ 0x10

times 510 - ($-$$) db 0
dw 0xAA55
