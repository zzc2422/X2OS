.section .text.entry
	.globl	_start
	auipc	sp, 0
_start:
	j	boot_c
	