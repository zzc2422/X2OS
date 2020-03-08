#ifndef SBI_H
#define SBI_H

#include <asm.h>

static void shutdown() __attribute__((noreturn));

inline static void shutdown() {
	set_reg_from_i12bit(a7, 8);
	ecall();
}

inline static void print_char(u32 c) {
	set_reg_from_var(a0, c);
	set_reg_from_i12bit(a7, 1);
	ecall();
}

void print_str(const u8 str_a[]);

void print_u32_dec(u32 n);

void print_i32_dec(i32 n);

#endif