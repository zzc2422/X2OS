.section .text
	.globl	all_trap
	
.align	2
all_trap:
	la	a0, cause_word
	jal	print_str
	csrr	a0, scause
	jal	print_u32_dec
	li	a0, '\n'
	li	a7, 1
	ecall
	ret

# 接受参数：
# a0：sepc
# a1：cause
# a2：is_interrupt
show_trap_info_no_return:
	
	
.data
cause_word:	.string "Cause: "
