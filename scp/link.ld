OUTPUT_ARCH(riscv)
ENTRY(_start)

PROVIDE(boot1_start = 0xC0000000);

SECTIONS {
	. = boot1_start;
	.boot1 : {
		bin/boot/part1/boot1.asm.o(.text)
		bin/boot/part1/*(.*)
	}
	PROVIDE(boot2_start = .);
	.boot2 : {
		bin/boot/part2/*(.*)
	}
	
	. = ALIGN(4K);
	PROVIDE(kern_text_start = .);
	.text : {
		*(.text)
	}
	PROVIDE(kern_text_end_n = .);
	
	. = ALIGN(4K);
	PROVIDE(kern_rodata_start = .);
	.rodata : {
		*(.rodata)
	}
	.got : {
		*(.got .got.*)
	}
	PROVIDE(kern_rodata_end_n = .);
	
	. = ALIGN(4K);
	PROVIDE(kern_stack_start = .);
	. = kern_stack_start + 0x1000;
	PROVIDE(kern_stack_end_n = .);
	
	PROVIDE(kern_data_start = .);
	.bss : {
		*(.bss)
	}
	.data : {
		*(.data)
	}
	PROVIDE(kern_data_end_n = .);
}