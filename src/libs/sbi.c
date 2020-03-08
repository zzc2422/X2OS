#include <sbi.h>

void print_str(const u8 str_a[]) {
	for (const u8* p = str_a;; p++) {
		u8 c = *p;
		if (c == '\0') {
			break;
		}
		print_char(c);
	}
}

void print_u32_dec(u32 n) {
	static u32 m10_a[] = {
		10,
		100,
		1000,
		10000,
		100000,
		1000000,
		10000000,
		100000000,
		1000000000
	};
	const u32* p;
	for (p = m10_a;; p++) {
		u32 m10 = *p;
		if (n < m10) {
			break;
		}
	}
	while (n >= 10) {
		p--;
		u32 bit = '0';
		u32 m10 = *p << 3;
		u32 bit_value = 8;
		while (1) {
			if (n >= m10) {
				n -= m10;
				bit += bit_value;
			}
			bit_value >>= 1;
			if (bit_value == 0) {
				break;
			}
			m10 >>= 1;
		}
		print_char(bit);
	}
	print_char(n + '0');
}

void print_i32_dec(i32 n) {
	if (n < 0) {
		print_char('-');
		n = -n;
	}
	print_u32_dec(n);
}