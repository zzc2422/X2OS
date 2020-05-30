.section .text
	.globl	sleep
sleep:
	wfi
	j	sleep