#ifndef CLOCK_H
#define CLOCK_H

#include <sbi.h>

u64 get_time();

inline static void set_timer_next(u64 time_gap) {
	set_timer(get_time() + time_gap);
}

inline static void set_timer_tick() {
	set_timer_next(10000000);
}

#endif // CLOCK_H