#include <sbi.h>

void print_str(const char str_a[]) {
	for (const char* p = str_a;; p++) {
		i32 c = *p;
		if (unlikely(c == '\0')) {
			break;
		}
		print_char(c);
	}
}

void print_u32_dec(u32 n, u32 min_bit_amount) {
}

void print_i32_dec(i32 n, u32 min_bit_amount) {
	if (n < 0) {
		print_char('-');
		n = -n;
	}
	print_u32_dec(n, min_bit_amount);
}

void print_u32_hex(u32 n, u32 min_bit_amount) {
	static const u8 bit_show_a[] = {'0', '1', '2', '3', '4', '5', '6', '7',
					'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
}