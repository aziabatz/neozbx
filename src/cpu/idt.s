/**
 * @ Author: Ahmed Ziabat Ziabat (aka) BLACKBURN
 * @ Created: 2022-06-07
 * @ Last revision: 2022-06-08
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


/*
 * EAX: idt array index
 * EBX: idt array start
 * 
 * ECX: offset
 * DX: segment selector
 * DI: flags
*/
__install_gate:

    push %eax
    push %ebx
    push %ecx
    push %edx
    push %esi
    push %edi

    mov %eax, %esi
    mov _idt_gate_start, %ebx

    //offset low 16 and high 16
    mov %ecx, %eax
    mov %ax, 0(%ebx, %esi, 8)
    shr $16, %eax
    mov %ax, 6(%ebx, %esi, 8)
    
    //segment selector
    mov %dx, 2(%ebx, %esi, 8)

    //flags and zeroed
    shl $8, %edi
    and $0xFF00, %edi
    
    mov %di, 4(%ebx, %esi, 8)
    
    pop %edi
    pop %esi
    pop %edx
    pop %ecx
    pop %ebx
    pop %eax
    

ret


/*
 * EAX: handler offset
 * EBX: idt array start
 * EDI: idt array index
*/
__set_gate_handler:

    push %eax
    push %ebx
    push %edi

    mov %ax, 0(%ebx, %edi, 8)
    shr $16, %eax
    mov %ax, 6(%ebx, %edi, 8)

    pop %edi
    pop %ebx
    pop %eax

ret

__set_gates:
    push %eax
    push %ebx
    push %ecx
    push %edx
    push %edi

    mov $32, %ecx
    __idt_spec_set:
        mov %ecx, %eax
        mov _idt_start, %ebx
        mov $_KERNEL_CS, %edx
        xor %edi,%edi
        mov $_IDT_GATE_FLAGS, %di
        //no need to modify ecx?
        push %ecx
            mov $_exceptions_table, %edi
            dec %ecx
            mov (%edi, %ecx, 4),%ecx
            call __install_gate
        pop %ecx
    loop __idt_spec_set

    pop %edi
    pop %edx
    pop %ecx
    pop %ebx
    pop %eax
ret

__install_idt:

    call __set_gates
    cli
    lidtl _idtr
    sti

ret

.section .data

_idtr:
.word (_idt_end - _idt_start)
.long _idt_start

_idt_start:

.space (_IDT_GATE_SIZE * 32)

_idt_end:

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

_exceptions_table:



