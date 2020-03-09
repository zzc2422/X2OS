.section .text.entry
	.globl	_start
_start:
	ebreak
loop:
	j	loop
all_trap:
	