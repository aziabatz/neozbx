/* 
 * Copyright (C) 2022 AZZ (aka) BLACKBURN
 *
 * File:    IODriver.hpp
 * Author:  Ahmed Ziabat Ziabat
 * Created: 2022-06-04
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
        case 8:
            ddata.data = (void*)in8();
            ddata.size = 1;
            break;
        case 16:
            ddata.data = (void*)in16();
            ddata.size = 2;
            break;
        case 32:
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
            case 8:
                out8(driverData->data);
                written = 8;
                break;
            case 16:
                out16(driverData->data);
                written = 16;
                break;
            case 32:
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

