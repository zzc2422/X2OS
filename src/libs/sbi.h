#ifndef SBI_H
#define SBI_H

#include <asm.h>
#include <defs.h>

__attribute((always_inline)) static _Noreturn void shutdown() {
	asm("la a7, 8");
	asm("ecall");
}

__attribute((always_inline)) static void print_char(u32 c) {
	asm("mv a0, %0" ::"r"(c) : "a0");
	asm("li a7, 1" ::: "a7");
	asm("ecall");
}

void print_str(const char str_a[]);

void print_u32_dec(u32 n, u32 min_bit_amount);

void print_u32_hex(u32 n, u32 min_bit_amount);

#endif // SBI_H