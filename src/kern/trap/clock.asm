.section .text
	.globl	get_time
get_time:
	csrr	a1, timeh
	csrr	a0, time
	csrr	a2, timeh
	bne	a1, a2, get_time
	ret
	