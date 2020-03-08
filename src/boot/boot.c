#include <sbi.h>

void boot_c() __attribute__((noreturn));

void boot_c() {
	u32 sp;
	set_var_from_reg(sp, sp);
	print_i32_dec(-234234);
	print_char('\n');
	shutdown();
}