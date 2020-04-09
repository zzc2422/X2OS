#!/bin/bash

machine=virt

gcc=riscv64-unknown-elf-gcc
as=riscv64-unknown-elf-as
ld=riscv64-unknown-elf-ld
objcopy=riscv64-unknown-elf-objcopy
gdb=gdb-multiarch
qemu=qemu-system-riscv32

archabi="-march=rv32imac -mabi=ilp32"
option="-g -O2 -fno-builtin -Wall -nostdinc -fno-stack-protector"

link=scp/link.ld
gdb_init=scp/gdb_init
sbi=ext/$machine"_sbi"

rm -rf tmp bin

all_dirs=$(find src -type d)
lib_opt=""
for src_dir in $all_dirs
do
	out_dir="tmp"${src_dir: 3}
	mkdir $out_dir -p
	lib_opt=$lib_opt" -I"$src_dir
done

all_files=$(find src -type f)
for src_file in $all_files
do
	ext=${src_file##*.}
	out_file="tmp"${src_file: 3}".o"
	if [ $ext == "c" ]
	then
		$gcc $src_file -o $out_file $lib_opt -c $archabi $option
	elif [ $ext == "asm" ]
	then
		$as $src_file -o $out_file -c $archabi
	fi
done

mkdir bin -p
o_files=$(find tmp -type f)
$ld $o_files -T $link -o tmp/os.bin -m elf32lriscv
$objcopy tmp/os.bin bin/os -O binary
$qemu --machine $machine --bios $sbi -device loader,file=bin/os,addr=0x80400000 -S -s &
$gdb -x $gdb_init