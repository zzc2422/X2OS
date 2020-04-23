OUTPUT_ARCH(riscv)
ENTRY(_start)

START_ADDRESS = 0x80400000;

SECTIONS {
	. = START_ADDRESS;
	.text : {
		tmp/boot/boot.asm.o(.text)
		tmp/boot/boot.c.o(.text)
		*(.text .text.*)
	}
	.data : {
		*(.data)
	}
}