#include <sbi.h>
#include <trap_reg.h>

void all_trap();

_Noreturn void boot_c() {
	asm("csrwi sscratch, 0");
	stvec_t stvec = get_stvec((u32)all_trap, 0);
	asm("csrw stvec, %0" ::"r"(stvec));
	asm("ebreak");
	shutdown();
}