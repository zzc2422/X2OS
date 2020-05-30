#include <defs.h>
#include <simple_cal.h>

u32 str_is_equal(const char s1_a[], const char s2_a[]) {
	const char *p1 = s1_a, *p2 = s2_a;
	while (1) {
		char c1 = *p1, c2 = *p2;
		if (c1 != c2) {
			return 0;
		} else if (unlikely(c1 == '\0')) {
			return 1;
		}
		p1++;
		p2++;
	}
}

void mem_align_4_start_end_set(u32* start_p, const u32* endn_p, u32 value) {
	for (u32* p = start_p; p != endn_p; p++) {
		*p = value;
	}
}

void mem_start_end_set(void* start_p, const void* endn_p, u8 value_8_bit) {
	u32 start_addr = (u32)start_p, endn_addr = (u32)endn_p;
	u32 start_align_up_addr = align_up_n_2_power(start_addr, 4);
	void* start_align_up_p = (void*)start_align_up_addr;
	u32 endn_align_down_addr = align_down_n_2_power(endn_addr, 4);
	void* endn_align_down_p = (void*)endn_align_down_addr;
	for (u8* p = start_p; p != start_align_up_p; p++) {
		*p = value_8_bit;
	}
	for (u8* p = endn_align_down_p; p != endn_p; p++) {
		*p = value_8_bit;
	}
	union {
		u8 value_a[4];
		u32 value_32_bit;
	} value;
	value.value_a[0] = value.value_a[1] = value.value_a[2] =
		value.value_a[3] = value_8_bit;
	mem_align_4_start_end_set(start_align_up_p, endn_align_down_p,
			value.value_32_bit);
}