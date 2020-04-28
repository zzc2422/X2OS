_Noreturn void sleep() {
	while (1) {
		asm("wfi");
	}
}