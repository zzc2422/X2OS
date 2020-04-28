#include <clock.h>
#include <sleep.h>

_Noreturn void unhandled(i32 scause, u32 sepc) {
	print_str("\nUnhandled trap!!!!!!\nIt is ");
	if (scause >= 0) {
		print_str("not ");
	}
	print_str("an interrupt.\nCause: ");
	print_u32_dec((scause << 1) >> 2, 1);
	print_str("\nEpc: ");
	print_u32_hex(sepc, 8);
	print_char('\n');
	sleep();
}

void timer_interrupt(i32 scause, u32 scl4) {
	print_str("\nTimer interrupt happened!!!!!!\n");
	set_timer_tick();
}