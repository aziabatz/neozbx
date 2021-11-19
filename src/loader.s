//
// Copyright (C) 2021 AZZ (aka) BLACKBURN
//
// File:    loader.S
// Author:  Ahmed Ziabat Ziabat
// Created: 2021-11-19
//

// Multiboot header
.set ALIGN, (1<<0)
.set MEMINFO, (1<<1)
.set FLAGS, ALIGN | MEMINFO
.set MAGIC, 0x1badb002
.set CHECKSUM, -(MAGIC+FLAGS)

// Multiboot section for linker

.section multiboot
.align 4 # Align 32-bit
.long MAGIC
.long FLAGS
.long CHECKSUM

// And now the loader code :)

.section .text
.globl __load_entry
.globl __global_halt
.extern __kmain

__load_entry:
	mov $loader_stack, %esp
	//TODO push multiboot header
	call __kmain

	__global_halt:
	cli
	hlt
	jmp __global_halt


// Uninitialized area
.section .bss
.align 16
loader_stack:
.skip (16*1024) #16 Kb

//TODO initialize start ld symbol(for traces)
