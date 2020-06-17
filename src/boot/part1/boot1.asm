.section .text
	.globl	_start
_start:
	# 此处用la获得的地址都是相对PC的地址
	la	sp, kern_stack_end_n
	la	s2, boot2
	la	a2, boot1_start
	la	a3, kern_text_start
	la	a4, kern_rodata_start
	la	a5, kern_stack_start
	la	a6, kern_data_end_n
	srli	s0, a2, 22
	xori	s0, s0, 0x300
	slli	s0, s0, 22
	# 此时s0为内核物理、虚拟地址转换的异或码。
	mv	a0, s0
	jal	boot1
	csrw	satp, a0
	sfence.vma
	slli	a0, a0, 12
	xor	s2, s2, s0
	jr	s2