#include <sbi.h>

void print_str(const char str_a[]) {
	for (const char* p = str_a;; p++) {
		i32 c = *p;
		if (c == '\0') {
			break;
		}
		print_char(c);
	}
}

void print_u32_dec(u32 n) {
	if (n == 0) {
		print_char('0');
		return;
	}
	static const u32 m10_a[] = {1,	    10,	     100,      1000,	 10000,
				    100000, 1000000, 10000000, 100000000};
	// p指向m10_a最后一个元素
	const u32 *m10_endn_p = m10_a + 9, *p = m10_endn_p;
	u32 m10 = 1000000000, bit_add_value;
	if (n >= m10) {
		m10 <<= 2;
		bit_add_value = 4;
		goto il;
	}
	do {
		p--;
		m10 = *p;
	} while (m10 > n);
	// 此时p指向最后一个不大于n的元素
	// 将m10最高位变为8，此位积累的值也为8。
	while (1) {
		m10 <<= 3;
		bit_add_value = 8;
		u32 bit;
	il:
		bit = '0';
		while (1) {
			if (n >= m10) {
				n -= m10;
				bit += bit_add_value;
			}
			bit_add_value >>= 1;
			if (bit_add_value == 0) {
				break;
			}
			m10 >>= 1;
		}
		print_char(bit);
		if (p == m10_a) {
			break;
		}
		p--;
		m10 = *p;
	}
}

void print_i32_dec(i32 n) {
	if (n < 0) {
		print_char('-');
		n = -n;
	}
	print_u32_dec(n);
}

void print_u32_hex(u32 n, u32 min_bit_amount) {
	static const u8 bit_show_a[] = {'0', '1', '2', '3', '4', '5', '6', '7',
					'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
}