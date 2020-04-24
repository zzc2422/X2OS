#include <clock.h>
#include <sbi.h>

void timer_interrupt() {
	clock_set_next_event_tick();
	print_str("\nTimer interrupt happened!\n");
}