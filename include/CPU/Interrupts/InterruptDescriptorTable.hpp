/**
 * @ Author: Ahmed Ziabat Ziabat (aka) BLACKBURN
 * @ Created: 2022-06-07
 * @ Last revision: 2022-07-19
 * @ Description: Copyright (c) 2021-2022, Ahmed Ziabat
All rights reserved.
Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributins in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
Neither the name of copyright holders nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef NZX_CPU_INTERRUPTS_IDT
#define NZX_CPU_INTERRUPTS_IDT

#include <types.h>

#define IDT_TABLE_ENTRIES 256

namespace InterruptDescriptorTable{

    struct gate_descriptor{
        uint16_t offset_low;
        uint16_t selector;
        uint8_t zeroed;
        uint8_t flags;
        uint16_t offset_high;
    }__attribute__((packed));

    struct descriptor{
        uint16_t limit;
        uint32_t base;
    };

    typedef struct gate_descriptor gate_t;
    typedef struct descriptor descriptor_t;

    void install();

}

#endif