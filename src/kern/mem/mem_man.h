#ifndef MEM_MAN_H
#define MEM_MAN_H

#include <defs.h>
#include <page_table.h>

// 初始化内存管理结构，参数为最低允许的起始地址，返回该结构之后的首地址。
__attribute((always_inline)) static u32
init_mem_man(u32 min_start_addr, u32 all_start_addr, u32 all_end_n_addr) {
	return min_start_addr;
}

__attribute((always_inline)) static void mark_allocated(pa_t phi_addr) {
}

#endif // MEM_MAN_H