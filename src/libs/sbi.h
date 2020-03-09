#ifndef SBI_H
#define SBI_H

#include <asm.h>
#include <defs.h>

static void shutdown() __attribute__((noreturn));

inline static void shutdown() {
	asm("ori a7, zero, 8");
	asm("ecall");
}

inline static void print_char(u32 c) {
	asm("mv a0, %0" :: "r" (c) : "a0");
	asm("or a7, zero, 1" ::: "a7");
	asm("ecall" ::: ECALL_CLOBBER);
}

void print_str(const u8 str_a[]);

void print_u32_dec(u32 n);

void print_i32_dec(i32 n);

#endif