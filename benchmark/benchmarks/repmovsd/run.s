section .text
global run

run:
    shr rsi, 2
    mov r8,  rdi
    mov r9,  rsi
    mov r10, rdx
    mov r11, rcx

    loop:
    mov rcx, r9
    mov rsi, r10
    mov rdi, r11

    rep movsd

    dec r8
    jnz loop

    ret
