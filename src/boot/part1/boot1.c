#include <dtb.h>
#include <mem_man.h>
#include <page_table.h>

static pte_t _get_flpte(pa_t pt_start_addr) {
	pte_t flpte = {.v = 1,
		       .r = 0,
		       .w = 0,
		       .x = 0,
		       .u = 0,
		       .g = 1,
		       .a = 1,
		       .d = 0,
		       .ppn = pt_start_addr.page_no};
	return flpte;
}

static pte_t _get_boot_pte(pa_t page_start_addr) {
	pte_t pte = {.v = 1,
		     .r = 1,
		     .w = 1,
		     .x = 1,
		     .u = 0,
		     .g = 1,
		     .a = 1,
		     .d = 0,
		     .ppn = page_start_addr.page_no};
	return pte;
}

static pte_t _get_kern_text_pte(pa_t page_start_addr) {
	pte_t pte = {.v = 1,
		     .r = 1,
		     .w = 0,
		     .x = 1,
		     .u = 0,
		     .g = 1,
		     .a = 1,
		     .d = 0,
		     .ppn = page_start_addr.page_no};
	return pte;
}

static pte_t _get_kern_rodata_pte(pa_t page_start_addr) {
	pte_t pte = {.v = 1,
		     .r = 1,
		     .w = 0,
		     .x = 0,
		     .u = 0,
		     .g = 1,
		     .a = 1,
		     .d = 0,
		     .ppn = page_start_addr.page_no};
	return pte;
}

static pte_t _get_kern_stack_data_pt_pte(pa_t page_start_addr) {
	pte_t pte = {.v = 1,
		     .r = 1,
		     .w = 1,
		     .x = 0,
		     .u = 0,
		     .g = 1,
		     .a = 1,
		     .d = 0,
		     .ppn = page_start_addr.page_no};
	return pte;
}

static void _set_pt(u32 boot1_start_addr, u32 kern_text_start_addr,
		    u32 kern_rodata_start_addr, u32 kern_stack_start_addr,
		    u32 kern_pt_start_addr) {
	u32 kern_pt_end_n_addr = kern_pt_start_addr + PAGE_SIZE;
	pte_t* pte_a = (pte_t*)kern_pt_start_addr;
	u32 addr = boot1_start_addr;
	// 设置boot段的页表，结束地址为text段首前一个地址。
	for (; addr != kern_text_start_addr; addr += PAGE_SIZE) {
		va_t va = get_va_by_addr(addr);
		pa_t pa = get_pa_by_addr(addr);
		pte_a[va.pte_no] = _get_boot_pte(pa);
		mark_allocated(pa);
	}
	// 设置text段的页表，结束地址为rodata段首前一个地址。
	for (; addr != kern_rodata_start_addr; addr += PAGE_SIZE) {
		va_t va = get_va_by_addr(addr);
		pa_t pa = get_pa_by_addr(addr);
		pte_a[va.pte_no] = _get_kern_text_pte(pa);
		mark_allocated(pa);
	}
	// 设置rodata段的页表，结束地址为data段首前一个地址。
	for (; addr != kern_stack_start_addr; addr += PAGE_SIZE) {
		va_t va = get_va_by_addr(addr);
		pa_t pa = get_pa_by_addr(addr);
		pte_a[va.pte_no] = _get_kern_rodata_pte(pa);
		mark_allocated(pa);
	}
	// 设置data段（含stack段、内存管理结构、页表）的页表，结束地址为二级页表结尾。
	for (; addr != kern_pt_end_n_addr; addr += PAGE_SIZE) {
		va_t va = get_va_by_addr(addr);
		pa_t pa = get_pa_by_addr(addr);
		pte_a[va.pte_no] = _get_kern_stack_data_pt_pte(pa);
		mark_allocated(pa);
	}
}

static satp_t _get_init_satp(pa_t flpte_pa) {
	satp_t satp = {.ppn = flpte_pa.page_no, .mode = 1};
	return satp;
}

satp_t boot1(u32 addr_xor, const dtb_t* dtb_p, u32 boot1_start_addr,
	     u32 kern_text_start_addr, u32 kern_rodata_start_addr,
	     u32 kern_stack_start_addr, u32 kern_data_end_n_addr) {
	// 确定操作系统管理的内存地址范围，从boot1_start_addr到all_end_n_addr-1。
	u32 all_max_end_n_addr = get_whole_mem_end_n(dtb_p);
	u32 all_end_n_addr = align_down_page(all_max_end_n_addr);
	// 初始化内存管理结构，位于data段之后，获取该结构末尾（的下一个）地址。
	u32 mem_man_end_n_addr = init_mem_man(kern_data_end_n_addr,
					      boot1_start_addr, all_end_n_addr);
	// 一级页表在内存管理结构之后，二级页表在一级页表之后，获取这两个起始地址。
	u32 flpt_start_addr = align_up_page(mem_man_end_n_addr);
	u32 pt_start_addr = flpt_start_addr + PAGE_SIZE;
	// 一级页表中对应之后的二级页表的项
	pa_t pt_start_pa = get_pa_by_addr(pt_start_addr);
	pte_t pt_flpte = _get_flpte(pt_start_pa);
	// 获取物理地址boot1_start_addr对应的虚拟地址
	u32 boot1_start_vir_addr = boot1_start_addr ^ addr_xor;
	va_t boot1_start_va = get_va_by_addr(boot1_start_vir_addr);
	va_t boot1_tmp_start_va = get_va_by_addr(boot1_start_addr);
	// 将物理地址、虚拟地址都暂时看作虚拟地址，
	// 将两个地址对应的一级页表都初始化为之后的二级页表。
	pte_t* flpte_a = (pte_t*)flpt_start_addr;
	flpte_a[boot1_start_va.flpte_no] =
		flpte_a[boot1_tmp_start_va.flpte_no] = pt_flpte;
	// 设置二级页表
	_set_pt(boot1_start_addr, kern_text_start_addr, kern_rodata_start_addr,
		kern_stack_start_addr, pt_start_addr);
	// 获取satp并返回
	pa_t flpt_start_pa = get_pa_by_addr(flpt_start_addr);
	return _get_init_satp(flpt_start_pa);
}