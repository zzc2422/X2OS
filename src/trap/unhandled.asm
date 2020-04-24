.section .text
	.globl	unhandled
# 一切中断处理程序均约定a4为scause，a5为左移2位后的scause。
unhandled:
	# 保存寄存器。由于此过程不返回，因此可以破坏寄存器。
	# s0为scause，s1为左移2位后的scause，s2为sepc。
	mv	s0, a4
	mv	s1, a5
	# 在新行显示“Unhandled exception!!!!!!”
	la	a0, n_info
	jal	print_str
	
	# 若不是中断（即s0 >= 0），跳转到后面打印信息。
	bge	s0, zero, print_no_inter
	
	# 在新行显示“It is an interrupt.”
	la	a0, n_inter
	jal	print_str
show_sepc:
	# 显示sepc提示信息
	la	a0, n_sepc
	jal	print_str
	# 以8位16进制显示sepc的值
	csrr	a0, sepc
	li	a1, 8
	jal	print_u32_hex
	# 显示cause提示信息
	la	a0, n_cause
	jal	print_str
	# 以10进制显示cause的值
	srli	a0, s1, 2
	li	a1, 1
	jal	print_u32_dec
	# 显示一个回车
	li	a0, '\n'
	li	a7, 1
	ecall
	
	# 休眠
sleep:	wfi
	j	sleep
print_no_inter:
	# 在新行显示“It is not an interrupt.”
	la	a0, n_no_inter
	la	ra, show_sepc
	j	print_str
	
.section .data
n_info:		.string	"\nUnhandled exception!!!!!!"
n_inter:	.string	"\nIt is an interrupt."
n_no_inter:	.string	"\nIt is not an interrupt."
n_sepc:		.string	"\nSepc: "
n_cause:	.string	"\nCause: "
