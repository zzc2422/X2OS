#ifndef SBI_H
#define SBI_H

#include <defs.h>

inline static _Noreturn void shutdown() {
	register u32 a7 asm("a7") = 8;
	asm("ecall" ::"r"(a7));
}

inline static void print_char(u32 c) {
	register u32 rc asm("a0") = c;
	register u32 a7 asm("a7") = 1;
	asm("ecall" ::"r"(rc), "r"(a7));
}

inline static void set_timer(u64 next_time) {
	register u32 timel asm("a0") = (u32)next_time;
	register u32 timeh asm("a1") = next_time >> 32;
	register u32 a7 asm("a7") = 0;
	asm("ecall" ::"r"(timel), "r"(timeh), "r"(a7));
}

void print_str(const char str_a[]);

void print_u32_dec(u32 n, u32 min_bit_amount);

void print_i32_dec(i32 n, u32 min_bit_amount);

void print_u32_hex(u32 n, u32 min_bit_amount);

#endif // SBI_H