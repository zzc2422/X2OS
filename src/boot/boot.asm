.section .text.entry
	.globl _start
_start:
	la	sp, 0x80400000
	j	boot_c
	