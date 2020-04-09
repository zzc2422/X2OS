#ifndef SBI_H
#define SBI_H

inline static _Noreturn void shutdown() {
	asm("la a7, 8");
	asm("ecall");
}

#endif // SBI_H