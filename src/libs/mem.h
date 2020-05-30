#ifndef MEM_H
#define MEM_H

#include <defs.h>

u32 str_is_equal(const char s1_a[], const char s2_a[]);

void mem_align_4_start_end_set(u32* start_p, const u32* endn_p, u32 value);

void mem_start_end_set(void* start_p, const void* endn_p, u8 value_8_bit);

inline static void mem_align_4_set(u32 a[], u32 length, u32 value) {
	mem_align_4_start_end_set(a, a + length, value);
}

inline static void mem_set(void* a, u32 size, u8 value_8_bit) {
	mem_start_end_set(a, (const u8*)(a + size), value_8_bit);
}

#endif // MEM_H