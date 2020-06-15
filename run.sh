#!/bin/bash

machine=virt

gcc=riscv64-linux-gnu-gcc
as=riscv64-linux-gnu-as
ld=riscv64-linux-gnu-ld
objcopy=riscv64-linux-gnu-objcopy
gdb=gdb-multiarch
qemu=qemu-system-riscv32

archabi="-march=rv32imac -mabi=ilp32"
option="-g -O2 -fno-builtin -Wall -nostdinc -fno-stack-protector -fno-omit-frame-pointer"
boot_opt=$option" -fPIC"

link=scp/link.ld
gdb_init=scp/gdb_init
sbi=ext/$machine"_sbi"

rm -rf bin/*

all_dirs=$(find src -type d)
lib_opt=""
for src_dir in $all_dirs
do
	out_dir="bin"${src_dir: 3}
	mkdir $out_dir -p
	lib_opt=$lib_opt" -I"$src_dir
done

all_files=$(find src -type f)
for src_file in $all_files
do
	ext=${src_file##*.}
	out_file="bin"${src_file: 3}".o"
	if [ $ext == "c" ]
	then
		if [ ${src_file: 0: 15} == "src/boot/part1/" ]
		then
			$gcc $src_file -o $out_file $lib_opt -c $archabi $boot_opt
		else
			$gcc $src_file -o $out_file $lib_opt -c $archabi $option
		fi
	elif [ $ext == "asm" ]
	then
		$as $src_file -o $out_file -c $archabi
	fi
done

o_files=$(find -L bin -type f)
$ld $o_files -T $link -o bin/os.bin -m elf32lriscv
$objcopy bin/os.bin bin/os -O binary
$qemu --machine $machine --bios $sbi -device loader,file=bin/os,addr=0x80400000 -S -s &
$gdb -x $gdb_init