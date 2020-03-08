section .text
	global _ft_strlen
	_ft_strlen:
		mov rax, 0
		cmp	rdi, 0
		je _return
	_loop:
		cmp byte [rdi + rax], 0
		je _return
		inc rax
		jmp	_loop
	_return:
		ret