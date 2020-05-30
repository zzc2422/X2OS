#ifndef TRAP_REG_H
#define TRAP_REG_H

#include <defs.h>

typedef struct {
	u32 cause : 31;
	u32 is_interrupt : 1;
} scause_t;
_Static_assert(sizeof(scause_t) == sizeof(u32), "");

typedef struct {
	u32 mode : 2;
	u32 trap_base_addr_high_30 : 30;
} stvec_t;
_Static_assert(sizeof(stvec_t) == sizeof(u32), "");

inline static stvec_t get_mode0_stvec_by_align4_addr(u32 addr) {
	union {
		stvec_t stvec;
		u32 u;
	} su = {.u = addr};
	return su.stvec;
}

typedef struct {
	u32 uie : 1;
	u32 sie : 1;
	u32 wpri0 : 2;
	u32 upie : 1;
	u32 spie : 1;
	u32 wpri1 : 2;
	u32 spp : 1;
	u32 wpri2 : 4;
	u32 fs : 2;
	u32 xs : 2;
	u32 wpri3 : 1;
	u32 sum : 1;
	u32 mxr : 1;
	u32 wpri4 : 11;
	u32 sd : 1;
} sstatus_t;
_Static_assert(sizeof(sstatus_t) == sizeof(u32), "");

typedef struct {
	u32 usie : 1;
	u32 ssie : 1;
	u32 wpri0 : 2;
	u32 utie : 1;
	u32 stie : 1;
	u32 wpri1 : 2;
	u32 ueie : 1;
	u32 seie : 1;
	u32 wpri2 : 22;
} sie_t;
_Static_assert(sizeof(sie_t) == sizeof(u32), "");

#endif // TRAP_REG_H