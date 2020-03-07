#include <defs.h>

#define CALL_CLOBBER "ra", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7"
#define set_reg_from_reg(dst, src) asm volatile("or "#dst", "#src", 0" ::: #dst)
#define set_reg_from_i12bit(dst, i12bit) asm volatile("or "#dst", zero, "#i12bit ::: #dst)
#define set_reg_from_num32bit(dst, num32bit) asm volatile("la, "#dst", "#num32bit ::: #dst)
#define ecall() asm volatile("ecall" ::: CALL_CLOBBER)