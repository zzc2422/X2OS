#include <sbi.h>
#include <sleep.h>

_Noreturn void unhandled(u32 a0, u32 a1, u32 a2, u32 a3, i32 scause, u32 scl4) {
	print_str("\nUnhandled trap!!!!!!\nIt is ");
	if (scause >= 0) {
		print_str("not ");
	}
	print_str("an interrupt.\nCause: ");
	print_u32_dec(scl4 >> 2, 1);
	sleep();
}