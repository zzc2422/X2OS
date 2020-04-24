.section .text
	.globl	all_trap
.ALIGN 2
all_trap:
	# 保存寄存器
	addi	sp, sp, -16
	sw	a5, 12(sp)
	sw	a4, 8(sp)
	sw	a1, 4(sp)
	sw	a0, 0(sp)

	# scause读入a4
	csrr	a4, scause
	
	# 根据是否为中断设置中断向量表的起始（读入a0）、终止地址（读入a1）
	# 若a4大于等于0，则跳转到后面处理非中断程序
	bge	a4, zero, no_inter
	la	a0, inter_vec_a
	la	a1, inter_vec_endn_p
goto_trap:
	# 将scause左移2位后读入a5，这会使a5不再有符号位
	slli	a5, a4, 2
	# 将a0设为中断向量表相应项的地址（即原a0加上左移2位后的cause）
	add	a0, a0, a5
	# 判断中断号是否超出范围，若超出范围，直接转到unhandled。
	bge	a0, a1, unhandled
	# 取出中断处理程序地址并跳转
	lw	a0, 0(a0)
	jalr	a0
	
	# 恢复寄存器
	lw	a5, 12(sp)
	lw	a4, 8(sp)
	lw	a1, 4(sp)
	lw	a0, 0(sp)
	addi	sp, sp, 16
	sret
	
no_inter:
	la	a0, no_inter_vec_a
	la	a1, no_inter_vec_endn_p
	j	goto_trap
	
.section .data
inter_vec_a:	.word	unhandled
		.word	unhandled
		.word	unhandled
		.word	unhandled
		.word	unhandled
		.word	timer_interrupt
		.word	unhandled
		.word	unhandled
		.word	unhandled
		.word	unhandled
		.word	unhandled
		.word	unhandled
inter_vec_endn_p:

no_inter_vec_a:	.word	unhandled
		.word	unhandled
		.word	unhandled
		.word	unhandled
		.word	unhandled
		.word	unhandled
		.word	unhandled
		.word	unhandled
		.word	unhandled
		.word	unhandled
		.word	unhandled
		.word	unhandled
		.word	unhandled
		.word	unhandled
		.word	unhandled
		.word	unhandled
no_inter_vec_endn_p:
