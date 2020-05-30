#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include <defs.h>
#include <simple_cal.h>

#define PAGE_SIZE_2_POWER 12
#define PAGE_SIZE (1 << PAGE_SIZE_2_POWER)

// 获取上取整的页起始地址
static u32 align_up_page(u32 addr) {
	return align_up_2_power(addr, PAGE_SIZE_2_POWER);
}

// 获取下取整的页起始地址，可用于获取给定地址所在页的起始地址。
static u32 align_down_page(u32 addr) {
	return align_down_2_power(addr, PAGE_SIZE_2_POWER);
}

typedef struct {
	u32 ppn : 22;
	u32 asid : 9;
	u32 mode : 1;
} satp_t;
_Static_assert(sizeof(satp_t) == sizeof(u32), "");

typedef struct {
	u32 v : 1;
	u32 r : 1;
	u32 w : 1;
	u32 x : 1;
	u32 u : 1;
	u32 g : 1;
	u32 a : 1;
	u32 d : 1;
	u32 rsw : 2;
	u32 ppn : 22;
} pte_t;
_Static_assert(sizeof(pte_t) == sizeof(u32), "");

typedef struct {
	u32 offset : 12;
	u32 pte_no : 10;
	u32 flpte_no : 10;
} va_t;
_Static_assert(sizeof(va_t) == sizeof(u32), "");

inline static va_t get_va_by_addr(u32 addr) {
	union {
		u32 addr;
		va_t pat;
	} vir_addr;
	vir_addr.addr = addr;
	return vir_addr.pat;
}

typedef struct {
	u32 offset : 12;
	u32 page_no : 20;
} pa_t;
_Static_assert(sizeof(pa_t) == sizeof(u32), "");

inline static pa_t get_pa_by_addr(u32 addr) {
	union {
		u32 addr;
		pa_t pat;
	} phi_addr;
	phi_addr.addr = addr;
	return phi_addr.pat;
}

#endif // PAGE_TABLE_H