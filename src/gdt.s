/**
 * @ Author: Ahmed Ziabat Ziabat (aka) BLACKBURN
 * @ Created: 2022-06-07
 * @ Last revision: 2022-06-07
 * @ Description: Copyright (c) 2021-2022, Ahmed Ziabat
All rights reserved.
Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
Neither the name of copyright holders nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

.section .text
.global __load_gdt
__load_gdt:

    lgdt _gdtr
    movl %cr0, %eax
    orl $1, %eax
    mov %eax, %cr0

    ljmp $0x08, $__protected_mode

    __protected_mode:
        cli
        movw $0x10, %ax
        movw %ax, %ds
        movw %ax, %es
        movw %ax, %fs
        movw %ax, %gs
        movw %ax, %gs
        
    ret



.section .data

.align 8

_gdtr:
    .word (_gdt_end - _gdt_start)
    .long _gdt_start

_gdt_start:

    /*
    For code and data segments
    Base: 0x0
    Limit: 0xFFFF.FFFF
    Granularity: 0xC
    */

    //Null entry
    .quad 0

    //Code entry
    .word 0xFFFF //limit 1
    .word 0x0    //base 1
    .byte 0x0    //base 2
    .byte 0x9A   //access
    .byte 0xCF   //flags | limit
    .byte 0x0    //base 3

    //Data entry
    .word 0xFFFF //limit 1
    .word 0x0    //base 1
    .byte 0x0    //base 2
    .byte 0x92   //access
    .byte 0xCF   //flags | limit
    .byte 0x0    //base 3

_gdt_end:


