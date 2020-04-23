.section .text
	.globl	clock_set_next_event
	.globl	clock_get_time

# void clock_set_next_event(u64 time);
clock_set_next_event:
	csrr	a3, timeh
	csrr	a2, time
	csrr	a4, timeh
	bne	a3, a4, clock_set_next_event
	add	a0, a0, a2
	add	a1, a1, a3
	sltu	a4, a0, a2
	add	a1, a1, a4
	li	a7, 0
	ecall
	ret
	
# u64 clock_get_time()
clock_get_time:
	csrr	a1, timeh
	csrr	a0, time
	csrr	a2, timeh
	bne	a1, a2, clock_get_time
	ret
