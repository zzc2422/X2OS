#include <clock.h>
#include <sbi.h>
#include <sleep.h>
#include <trap_reg.h>

void all_trap();

ainline static void enable_inter() {
	sstatus_t sstatus = {.sie = 1};
	asm("csrs sstatus, %0" ::"r"(sstatus));
}

ainline static void init_sscratch() {
	asm("csrwi sscratch, 0");
}

ainline static void init_stvec() {
	stvec_t stvec = get_stvec_by_addr((u32)all_trap);
	asm("csrw stvec, %0" ::"r"(stvec));
}

ainline static void enable_sie() {
	sie_t sie = {.stie = 1};
	asm("csrs sie, %0" ::"r"(sie));
}

_Noreturn void boot_c() {
	enable_inter();
	init_sscratch();
	init_stvec();
	enable_sie();
	set_timer_tick();
	sleep();
}