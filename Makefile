machine := virt

gcc := riscv64-unknown-elf-gcc
as := riscv64-unknown-elf-as
ld := riscv64-unknown-elf-ld
objcopy := riscv64-unknown-elf-objcopy
gdb := gdb-multiarch
# gdb_front := nemiver
qemu := qemu-system-riscv32

tmp_dir := tmp
bin_dir := bin
src_dir := src
scp_dir := scp

libs_dir := $(src_dir)/libs

boot_asm := $(src_dir)/boot/boot.asm
boot_asm_o := $(tmp_dir)/boot.asm.o
boot_c := $(src_dir)/boot/boot.c
boot_c_o := $(tmp_dir)/boot.c.o

boot_o_list := $(boot_asm_o) $(boot_c_o)
boot_out := $(tmp_dir)/boot.out
boot_bin := $(bin_dir)/boot.bin

link := $(scp_dir)/link.ld
gdb_init := $(scp_dir)/gdb_init
opensbi := ../opensbi-0.6-rv32-bin/platform/qemu/$(machine)/firmware/fw_jump.bin

.PHONY : all
all :
	rm -rf $(tmp_dir) $(bin_dir)
	mkdir $(tmp_dir) -p
	mkdir $(bin_dir) -p
	$(as) $(boot_asm) -o $(boot_asm_o) -march=rv32imac -mabi=ilp32
	$(gcc) $(boot_c) -I$(libs_dir) -o $(boot_c_o) -c -g -Os -march=rv32imac -mabi=ilp32
	$(ld) $(boot_asm_o) $(boot_c_o) -T $(link) -o $(boot_out) -m elf32lriscv
	$(objcopy) $(boot_out) $(boot_bin) -O binary
	x-terminal-emulator --command="$(gdb) -x $(gdb_init)"
	# $(gdb_front) -x gdbinit &
	$(qemu) --machine $(machine) --nographic --bios $(opensbi) -device loader,file=$(boot_bin),addr=0x80400000 -S -s

.PHONY : clean
clean :
	rm -rf $(tmp_dir) $(bin_dir)