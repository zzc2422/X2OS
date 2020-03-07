#include <asm.h>

inline static shutdown() {
	set_reg_from_i12bit(a7, 8);
	ecall();
}