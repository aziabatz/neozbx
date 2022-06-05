/**
 * @ Author: Ahmed Ziabat Ziabat (aka) BLACKBURN
 * @ Created: 2022-06-04
 * @ Last revision: 2022-06-05
 * @ Description: Copyright (c) 2021-2022, Ahmed Ziabat
All rights reserved.
Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
Neither the name of copyright holders nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <System/InputOutput/SystemPort.hpp>
#include <limits.h>

SystemPort::SystemPort(uint16_t port)
{
    this->port = port;
}

uint8_t SystemPort::in8()
{
    uint8_t data;
    __asm__ __volatile__ (
    "inb %1,%0"
    :"=a" (data)
    :"dN" (this->port));
    return data;
}
uint16_t SystemPort::in16()
{
    uint16_t data;
    __asm__ __volatile__ (
    "inw %1,%0"
    :"=a" (data)
    :"dN" (this->port));
    return data;
}
uint32_t SystemPort::in32()
{
    uint32_t data;
    __asm__ __volatile__ (
    "inl %1,%0"
    :"=a" (data)
    :"dN" (this->port));
    return data;
}

InputOutputDriver::DriverData * SystemPort::read(unsigned int size)
{
    InputOutputDriver::DriverData ddata;
    switch (size)
    {
        case 1:
            ddata.data = (void*)in8();
            ddata.size = 1;
            break;
        case 2:
            ddata.data = (void*)in16();
            ddata.size = 2;
            break;
        case 4:
            ddata.data = (void*)in32();
            ddata.size = 4;
            break;
        default:
            ddata.data = 0;
            ddata.size = 0;
            break;
    }

        return &ddata;
}

InputOutputDriver::DriverData * SystemPort::read()
{
    InputOutputDriver::driverData ddata;
    unsigned int data = in32();
    ddata.data = (void *) data;
    if(data>MAX_UWORD)
    {
        //4 bytes
        ddata.size = 4;
    }
    else if(data > MAX_UCHAR)
    {
        //2 bytes
        ddata.size = 2;
    }
    else
    {
        //1 byte
        ddata.size = 1;
    }
    return &ddata;
}

void SystemPort::out8(void * data)
{
    __asm__ __volatile__ (
    "outb %1,%0"
    :
    :"dN"(this->port),"a"((uint8_t)data));
}
void SystemPort::out16(void * data)
{
    __asm__ __volatile__ (
    "outw %1,%0"
    :
    :"dN"(this->port),"a"((uint16_t)data));
}
void SystemPort::out32(void * data)
{
    __asm__ __volatile__ (
    "outl %1,%0"
    :
    :"dN"(this->port),"a"(data));
}

int SystemPort::write(InputOutputDriver::DriverData * driverData)
{
    int written;
    if(driverData == nullptr)
    {
        written = 0;
    }
    else
    {
        switch(driverData->size)
        {
            case 1:
                out8(driverData->data);
                written = 8;
                break;
            case 2:
                out16(driverData->data);
                written = 16;
                break;
            case 4:
                out32(driverData->data);
                written = 32;
                break;
            default:
                written = 0;
                break;
        }
    }
    return written;
}

