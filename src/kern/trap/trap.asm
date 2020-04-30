# 所有中断处理程序参数a0为scause，a1为sepc。
.section .text
	.globl	all_trap
	.ALIGN 2
all_trap:
	# 保存部分寄存器
	addi	sp, sp, -64
	sw	ra, 60(sp)
	sw	a0, 56(sp)
	sw	a1, 52(sp)
	sw	a2, 48(sp)
	sw	a3, 44(sp)

	# 将scause读入a0
	csrr	a0, scause
	# 如果不是中断（即scause >= 0），跳到后面读取非中断向量表。
	bge	a0, zero, no_inter
	la	a2, inter_vec_a
	la	a3, inter_vec_endn_p
	
read_vector_table:
	# 将a1设置为scause左移2位后的值，这会清除最高（中断）位。
	slli	a1, a0, 2
	# 获取中断向量的地址
	add	a2, a2, a1
	# 将sepc读入a1
	csrr	a1, sepc
	# 若偏移超出范围，直接转到unhandled。
	bge	a2, a3, unhandled
	# 将中断向量读入a2
	lw	a2, 0(a2)
	# 将中断向量最低位读入a3
	andi	a3, a2, 1
	# 若低位不为0，则无需保存更多寄存器
	bne	a3, zero, no_save_more
	
	# 保存其它由调用者保存的寄存器
	sw	a4, 40(sp)
	sw	a5, 36(sp)
	sw	a6, 32(sp)
	sw	a7, 28(sp)
	sw	t0, 24(sp)
	sw	t1, 20(sp)
	sw	t2, 16(sp)
	sw	t3, 12(sp)
	sw	t4, 8(sp)
	sw	t5, 4(sp)
	sw	t6, 0(sp)
	
	# 手动设置返回地址并跳转（调用）
	la	ra, restore_regs
	jr	a2
	
no_save_more:
	andi	a2, a2, -2
	la	ra, restore_sp
	jr	a2
	
no_inter:
	la	a2, no_inter_vec_a
	la	a3, no_inter_vec_endn_p
	j	read_vector_table

restore_regs:
	# 恢复其它由调用者保存的寄存器
	lw	ra, 60(sp)
	lw	a0, 56(sp)
	lw	a1, 52(sp)
	lw	a2, 48(sp)
	lw	a3, 44(sp)
	lw	a4, 40(sp)
	lw	a5, 36(sp)
	lw	a6, 32(sp)
	lw	a7, 28(sp)
	lw	t0, 24(sp)
	lw	t1, 20(sp)
	lw	t2, 16(sp)
	lw	t3, 12(sp)
	lw	t4, 8(sp)
	lw	t5, 4(sp)
	lw	t6, 0(sp)
	
restore_sp:
	addi	sp, sp, 64
	sret
	
.section .data
	.set	NO_SAVE, 1
	.set	SAVE, 0
	
n_info:	.string	"Trap!\n"

inter_vec_a:
	.word	unhandled + NO_SAVE
	.word	unhandled + NO_SAVE
	.word	unhandled + NO_SAVE
	.word	unhandled + NO_SAVE
	.word	unhandled + NO_SAVE
	.word	timer_interrupt + SAVE
inter_vec_endn_p:

no_inter_vec_a:
no_inter_vec_endn_p:
