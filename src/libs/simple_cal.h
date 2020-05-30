#ifndef ENDIAN_H
#define ENDIAN_H

#include <defs.h>

inline static u32 endian_change(u32 i) {
	union {
		u8 ua[4];
		u32 i;
	} in_endian, out_endian;
	_Static_assert(sizeof(u32) == sizeof(u8[4]), "");
	in_endian.i = i;
	out_endian.ua[0] = in_endian.ua[3];
	out_endian.ua[1] = in_endian.ua[2];
	out_endian.ua[2] = in_endian.ua[1];
	out_endian.ua[3] = in_endian.ua[0];
	return out_endian.i;
}

inline static u32 align_up_n_2_power(u32 n, u32 align) {
	u32 low_all_1 = align - 1, high_all_1 = ~low_all_1;
	return (n + low_all_1) & high_all_1;
}

inline static u32 align_down_n_2_power(u32 n, u32 align) {
	u32 low_all_1 = align - 1, high_all_1 = ~low_all_1;
	return n & high_all_1;
}

inline static u32 align_up_2_power(u32 n, u32 power) {
	return align_up_n_2_power(n, 1 << power);
}

inline static u32 align_down_2_power(u32 n, u32 power) {
	return align_down_n_2_power(n, 1 << power);
}

inline static u32 round_up_div_2_power(u32 n, u32 power) {
	return (n + power - 1) >> power;
}

#endif // ENDIAN_H