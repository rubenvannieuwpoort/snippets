section .text
global run

; rdi   rsi  rdx    rcx    r8 r9 r10 r11
; times size source target

run:
    mov al, 0x12

    mov r8, rdi
    mov r9, rcx

    loop:
    mov rcx, rsi
    mov rdi, r9

    rep stosb

    dec r8
    jnz loop

    ret
