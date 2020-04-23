#ifndef CLOCK_H
#define CLOCK_H

#include <defs.h>

void clock_set_next_event(u64 time);

u64 clock_get_time();

#endif // CLOCK_H