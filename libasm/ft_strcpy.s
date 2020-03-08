section .text
    global _ft_strcpy
    _ft_strcpy:
        mov rax, 0
        cmp rdi, 0
        je _return
        cmp rsi, 0
        je _return
    _loop:
        cmp byte [rsi + rax], 0
        je _return
        mov dl, byte [rsi + rax]
        mov byte [rdi + rax], dl
        inc rax
        jmp _loop
    _return:
        mov byte [rdi + rax], 0
        mov rax, rdi
        ret