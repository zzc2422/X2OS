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
	sw	a4, 40(sp)

	# 将scause读入a0
	csrr	a0, scause
	# 如果不是中断（即scause >= 0），跳到后面读取非中断向量表。
	bge	a0, zero, no_inter
	la	a3, inter_vec_a
	la	a4, inter_vec_endn_p
	
read_vector_table:
	# 将a1设置为scause左移2位后的值，这会清除最高（中断）位。
	slli	a1, a0, 2
	# 获取中断向量的地址
	add	a3, a3, a1
	# 若偏移超出范围，直接转到unhandled。
	bge	a3, a4, unhandled
	# 将中断向量读入a3
	lw	a3, 0(a3)
	# 将中断向量最低位读入a4
	andi	a4, a3, 1
	# 若低位不为0，则无需保存更多寄存器
	bne	a4, zero, no_save_more
	
	# 保存其它由调用者保存的寄存器
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
	la	ra, restore_more_regs
	jr	a3
	
no_save_more:
	andi	a3, a3, -2
	la	ra, restore_base_regs
	jr	a3
	
no_inter:
	la	a3, no_inter_vec_a
	la	a4, no_inter_vec_endn_p
	j	read_vector_table

restore_more_regs:
	# 恢复其它由调用者保存的寄存器
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
	
restore_base_regs:
	lw	ra, 60(sp)
	lw	a0, 56(sp)
	lw	a1, 52(sp)
	lw	a2, 48(sp)
	lw	a3, 44(sp)
	lw	a4, 40(sp)
	addi	sp, sp, 64
	sret
	
.section .data
	.set	SAVE_BASE, 1
	.set	SAVE_ALL, 0
n_info:	.string	"Trap!\n"
inter_vec_a:
	.word	unhandled + SAVE_BASE
	.word	unhandled + SAVE_BASE
	.word	unhandled + SAVE_BASE
	.word	unhandled + SAVE_BASE
	.word	unhandled + SAVE_BASE
inter_vec_endn_p:

no_inter_vec_a:

no_inter_vec_endn_p:
