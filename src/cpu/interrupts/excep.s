/**
 * @ Author: Ahmed Ziabat Ziabat (aka) BLACKBURN
 * @ Created: 2022-06-08
 * @ Last revision: 2022-07-20
 * @ Description: Copyright (c) 2021-2022, Ahmed Ziabat
All rights reserved.
Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
Neither the name of copyright holders nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

.section .text

.macro __int_ num
.global __int_\num
__int_\num:
    cli
    mov $\num, (_int_number)
    push $0
    push (_int_number)
    jmp __int_common
.endm

.macro __int_error_ num
.global __int_error_\num
__int_error_\num:
    cli
    movb $\num, (_int_number)
    push (_int_number)
    jmp __int_common
.endm

__int_common:
    //pushed EFLAGS, CS, EIP
    //pushed error, int number

    //push general purpose register
    pushal 

    //push segments registers
    push %ds
    push %es
    push %fs
    push %gs

    //clear df for c++ func
    cld

    push %esp
    call __isr_handler
    add $4, %esp

    pop %gs
    pop %fs
    pop %es
    pop %ds

    popal

    //discard int number and error code
    add $8, %esp


iret


__int_ 0x00
__int_ 0x01
__int_ 0x02
__int_ 0x03
__int_ 0x04
__int_ 0x05
__int_ 0x06
__int_ 0x07
__int_error_ 0x08
__int_ 0x09
__int_error_ 0x0A
__int_error_ 0x0B
__int_error_ 0x0C
__int_error_ 0x0D
__int_error_ 0x0E
__int_ 0x0F
__int_ 0x10
__int_error_ 0x11
__int_ 0x12
__int_ 0x13
__int_ 0x14
__int_ 0x15
__int_ 0x16
__int_ 0x17
__int_ 0x18
__int_ 0x19
__int_ 0x1A
__int_ 0x1B
__int_ 0x1C
__int_ 0x1D
__int_error_ 0x1E
__int_ 0x1F



.section .bss

_int_number: .space 1
