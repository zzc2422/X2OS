.section .text
	.globl	_start
_start:
	# 此处用la获得的地址都是相对PC的地址
	la	sp, kern_stack_end_n
	la	s1, boot1_start
	la	s2, boot2_start
	la	s3, kern_stack_start
	la	s4, kern_text_start
	la	s5, kern_rodata_start
	la	s6, kern_data_start
	la	s7, kern_data_end_n
	srli	s0, s1, 22
	xori	s0, s0, 0x300
	slli	s0, s0, 22
	# 此时s0为内核物理、虚拟地址转换的异或码。
	mv	a0, s0
	mv	a2, s1
	mv	a3, s4
	mv	a4, s5
	mv	a5, s3
	mv	a6, s7
	jal	boot1
	csrw	satp, a0
	sfence.vma
	slli	a0, a0, 12
	xor	s2, s2, s0
	jr	s2