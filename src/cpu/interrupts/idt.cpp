/**
 * @ Author: Ahmed Ziabat Ziabat (aka) BLACKBURN
 * @ Created: 2022-07-18
 * @ Last revision: 2022-07-20
 * @ Description: Copyright (c) 2021-2022, Ahmed Ziabat Ziabat

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 */

#include <CPU/Interrupts/InterruptDescriptorTable.hpp>
#include <bitwise.h>

using namespace InterruptDescriptorTable;

extern "C" void __int_0x00();
extern "C" void __int_0x01();
extern "C" void __int_0x02();
extern "C" void __int_0x03();
extern "C" void __int_0x04();
extern "C" void __int_0x05();
extern "C" void __int_0x06();
extern "C" void __int_0x07();
extern "C" void __int_error_0x08();
extern "C" void __int_0x09();
extern "C" void __int_error_0x0A();
extern "C" void __int_error_0x0B();
extern "C" void __int_error_0x0C();
extern "C" void __int_error_0x0D();
extern "C" void __int_error_0x0E();
extern "C" void __int_0x0F();
extern "C" void __int_0x10();
extern "C" void __int_error_0x11();
extern "C" void __int_0x12();
extern "C" void __int_0x13();
extern "C" void __int_0x14();
extern "C" void __int_0x15();
extern "C" void __int_0x16();
extern "C" void __int_0x17();
extern "C" void __int_0x18();
extern "C" void __int_0x19();
extern "C" void __int_0x1A();
extern "C" void __int_0x1B();
extern "C" void __int_0x1C();
extern "C" void __int_0x1D();
extern "C" void __int_error_0x1E();
extern "C" void __int_0x1F();

gate_t gates[IDT_TABLE_ENTRIES];
descriptor_t idtDescriptor;

static void setGate(uint32_t gate, uint32_t offset, uint16_t segmentSelector, uint8_t flags)
{
    gates[gate].offset_low = LOW_16_BITS(offset);
    gates[gate].offset_high = HIGH_16_BITS(offset);
    
    gates[gate].selector = segmentSelector;
    gates[gate].flags = flags;
}

#define KERNEL_CS 0x8
#define INTERRUPT_GATE 0x8E

static void installGates()
{
    setGate(0, (uint32_t)__int_0x00, KERNEL_CS, INTERRUPT_GATE);
    setGate(1, (uint32_t)__int_0x01, KERNEL_CS, INTERRUPT_GATE);
    setGate(2, (uint32_t)__int_0x02, KERNEL_CS, INTERRUPT_GATE);
    setGate(3, (uint32_t)__int_0x03, KERNEL_CS, INTERRUPT_GATE);
    setGate(4, (uint32_t)__int_0x04, KERNEL_CS, INTERRUPT_GATE);
    setGate(5, (uint32_t)__int_0x05, KERNEL_CS, INTERRUPT_GATE);
    setGate(6, (uint32_t)__int_0x06, KERNEL_CS, INTERRUPT_GATE);
    setGate(7, (uint32_t)__int_0x07, KERNEL_CS, INTERRUPT_GATE);
    setGate(8, (uint32_t)__int_error_0x08, KERNEL_CS, INTERRUPT_GATE);
    setGate(9, (uint32_t)__int_0x09, KERNEL_CS, INTERRUPT_GATE);
    setGate(10, (uint32_t)__int_error_0x0A, KERNEL_CS, INTERRUPT_GATE);
    setGate(11, (uint32_t)__int_error_0x0B, KERNEL_CS, INTERRUPT_GATE);
    setGate(12, (uint32_t)__int_error_0x0C, KERNEL_CS, INTERRUPT_GATE);
    setGate(13, (uint32_t)__int_error_0x0D, KERNEL_CS, INTERRUPT_GATE);
    setGate(14, (uint32_t)__int_error_0x0E, KERNEL_CS, INTERRUPT_GATE);
    setGate(15, (uint32_t)__int_0x0F, KERNEL_CS, INTERRUPT_GATE);
    setGate(16, (uint32_t)__int_0x10, KERNEL_CS, INTERRUPT_GATE);
    setGate(17, (uint32_t)__int_error_0x11, KERNEL_CS, INTERRUPT_GATE);
    setGate(18, (uint32_t)__int_0x12, KERNEL_CS, INTERRUPT_GATE);
    setGate(19, (uint32_t)__int_0x13, KERNEL_CS, INTERRUPT_GATE);
    setGate(20, (uint32_t)__int_0x14, KERNEL_CS, INTERRUPT_GATE);
    setGate(21, (uint32_t)__int_0x15, KERNEL_CS, INTERRUPT_GATE);
    setGate(22, (uint32_t)__int_0x16, KERNEL_CS, INTERRUPT_GATE);
    setGate(23, (uint32_t)__int_0x17, KERNEL_CS, INTERRUPT_GATE);
    setGate(24, (uint32_t)__int_0x18, KERNEL_CS, INTERRUPT_GATE);
    setGate(25, (uint32_t)__int_0x19, KERNEL_CS, INTERRUPT_GATE);
    setGate(26, (uint32_t)__int_0x1A, KERNEL_CS, INTERRUPT_GATE);
    setGate(27, (uint32_t)__int_0x1B, KERNEL_CS, INTERRUPT_GATE);
    setGate(28, (uint32_t)__int_0x1C, KERNEL_CS, INTERRUPT_GATE);
    setGate(29, (uint32_t)__int_0x1D, KERNEL_CS, INTERRUPT_GATE);
    setGate(30, (uint32_t)__int_error_0x1E, KERNEL_CS, INTERRUPT_GATE);
    setGate(31, (uint32_t)__int_0x1F, KERNEL_CS, INTERRUPT_GATE);
}

static inline void loadIDTRegister()
{
    idtDescriptor.base = (uint32_t) &gates;
    idtDescriptor.limit = (IDT_TABLE_ENTRIES * sizeof(gate_t)) - 1;

    __asm__ __volatile__("lidtl (%0)"::"r"(&idtDescriptor));
}

void install()
{
    installGates();
    loadIDTRegister();
}