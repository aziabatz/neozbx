/**
 * @ Author: Ahmed Ziabat Ziabat (aka) BLACKBURN
 * @ Created: 2022-06-07
 * @ Last revision: 2022-06-10
 * @ Description: Copyright (c) 2021-2022, Ahmed Ziabat
All rights reserved.
Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
Neither the name of copyright holders nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

.section .text

.global __install_idt


/**
 * EBX: Gate address
 * EAX: Offset
 */
__set_offset:
    push %eax
    movw %ax, 0(%ebx)
    shr $16, %eax
    movw %ax, 6(%ebx)
    pop %eax
ret

/** 
 * EBX: Gate address
 * EAX: Segment Selector
 */
__set_segsel:
    movw %ax, 2(%ebx)
ret

/**
 * EBX: Gate address
 * EAX: Gate type
 * ECX: DPL
 */
__set_flags:
    push %edx
    
    xor $0b1111, %al

    xor %edx,%edx
    movb %cl, %dl
    shrb $1, %dl
    and $0b110, %dl
    or $0b1000, %dl
    shrb $4, %dl // -> 1XX0 0000

    or %dl, %al
    movb %al, 5(%ebx)

    pop %edx
ret

__set_gates:
    push %eax
    push %ebx
    push %ecx
    push %edx
    push %edi
    push %esi
        
    //set offset
    mov _exceptions_table(,%ecx,8), %eax //offset
    //set segment

    //set flags


    pop %esi
    pop %edi
    pop %edx
    pop %ecx
    pop %ebx
    pop %eax
ret


__install_idt:

    call __set_gates
    #cli
    lidtl _idtr
    #sti

ret

.section .data

_idtr:
.word (_idt_end - _idt_start)
.long _idt_start

_idt_start:

.space (_IDT_GATE_SIZE * 256)

_idt_end:

_exceptions_table:

.long __int_0x00
.long __int_0x01
.long __int_0x02
.long __int_0x03
.long __int_0x04
.long __int_0x05
.long __int_0x06
.long __int_0x07
.long __int_error_0x08
.long __int_0x09
.long __int_error_0x0A
.long __int_error_0x0B
.long __int_error_0x0C
.long __int_error_0x0D
.long __int_error_0x0E
.long __int_0x0F
.long __int_0x10
.long __int_error_0x11
.long __int_0x12
.long __int_0x13
.long __int_0x14
.long __int_0x15
.long __int_0x16
.long __int_0x17
.long __int_0x18
.long __int_0x19
.long __int_0x1A
.long __int_0x1B
.long __int_0x1C
.long __int_0x1D
.long __int_error_0x1E
.long __int_0x1F

.section .bss

_idt_gate_start:

offset1         : .space 2
segsec          : .space 2
reserved        : .space 1
p_dpl_0_gate    : .space 1
offset2         : .space 2

_idt_gate_end:

.set _IDT_GATE_SIZE, (_idt_gate_end - _idt_gate_start)
.set _KERNEL_CS, 0x08
.set _IDT_GATE_FLAGS, 0x8E



