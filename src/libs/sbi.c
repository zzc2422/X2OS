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

static u32 _div_10(u32 n) {
	return (((u64)n + 1) * 0x66666666 - 1) >> 34;
}

void print_u32_dec(u32 n, u32 min_bit_amount) {
	if (min_bit_amount > 10) {
		min_bit_amount = 10;
	}
	char str_a[11];
	char* str_p = str_a + 10;
	*str_p = '\0';
	do {
		u32 div = _div_10(n);
		u32 mod = n - div * 10;
		n = div;
		min_bit_amount--;
		str_p--;
		*str_p = mod + '0';
	} while (n != 0);
	while ((i32)min_bit_amount > 0) {
		str_p--;
		*str_p = '0';
		min_bit_amount--;
	}
	print_str(str_p);
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
	if (min_bit_amount == 0) {
		min_bit_amount = 1;
	}
	u32 i = 7;
	while (1) {
		u32 bit = n >> 28;
		if (bit != 0 || i < min_bit_amount) {
			print_char(bit_show_a[bit]);
		}
		if (i == 0) {
			break;
		}
		i--;
		n <<= 4;
	}
}