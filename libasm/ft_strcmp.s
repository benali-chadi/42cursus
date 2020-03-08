section .text
	global _ft_strcmp
	_ft_strcmp:
		mov rax, 0
		mov r9, 0
		cmp rdi, 0
		je _return
		cmp rsi, 0
		je _return
	_loop:
		mov al, byte [rdi + r9]
		movzx rbx, byte [rsi + r9] 
		sub eax, ebx
		jnz _return
		inc r9
		cmp byte [rdi + r9], 0
		je _return
		; cmp byte [rsi + r9], 0
		; je _return
		jmp _loop
	_return:
		ret