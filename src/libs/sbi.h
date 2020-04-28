#ifndef SBI_H
#define SBI_H

#include <asm.h>
#include <defs.h>

inline static _Noreturn void shutdown() {
	asm("la a7, 8");
	asm("ecall");
}

inline static void print_char(u32 c) {
	register u32 rc asm("a0") = c;
	asm("li a7, 1" ::: "a7");
	asm("ecall" ::"r"(rc));
}

inline static void set_timer(u64 next_time) {
	register u32 timel asm("a0") = (u32)next_time;
	register u32 timeh asm("a1") = next_time >> 32;
	asm("li a7, 0" ::: "a7");
	asm("ecall" ::"r"(timel), "r"(timeh));
}

void print_str(const char str_a[]);

void print_u32_dec(u32 n, u32 min_bit_amount);

void print_u32_hex(u32 n, u32 min_bit_amount);

#endif // SBI_H