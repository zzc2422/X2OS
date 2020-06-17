#include <clock.h>
#include <sleep.h>
#include <trap.h>
#include <trap_reg.h>

static void _enable_inter() {
	sstatus_t sstatus = {.sie = 1};
	asm("csrs sstatus, %0" ::"r"(sstatus));
}

static void _init_sscratch() {
	asm("csrwi sscratch, 0");
}

static void _init_stvec() {
	stvec_t stvec = get_mode0_stvec_by_align4_addr((u32)all_trap);
	asm("csrw stvec, %0" ::"r"(stvec));
}

static void _enable_sie() {
	sie_t sie = {.stie = 1};
	asm("csrs sie, %0" ::"r"(sie));
}

_Noreturn void boot2(u32 flpte_addr) {
	_enable_inter();
	_init_sscratch();
	_init_stvec();
	_enable_sie();
	set_timer_tick();
	sleep();
}