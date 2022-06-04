/* 
 * Copyright (C) 2022 AZZ (aka) BLACKBURN
 *
 * File:    IODriver.hpp
 * Author:  Ahmed Ziabat Ziabat
 * Created: 2022-06-04
 */

#include <System/InputOutput/SystemPort.hpp>

SystemPort::SystemPort(uint16_t port)
{
    this->port = port;
}

InputOutputDriver::DriverData * SystemPort::read(unsigned int size)
{
    InputOutputDriver::DriverData ddata;
    int data;
    switch (size)
    {
        case 8:
            __asm__ __volatile__ (
			"inb %1,%0"
			:"=a" (data)
			:"dN" (this->port));
            ddata.size = 8;
            break;
        case 16:
            __asm__ __volatile__ (
			"inw %1,%0"
			:"=a" (data)
			:"dN" (this->port));
            ddata.size = 16;
            break;
        case 32:
            __asm__ __volatile__ (
			"inl %1,%0"
			:"=a" (data)
			:"dN" (this->port));
            ddata.size = 32;
            break;
        default:
            data = 0;
            ddata.size = 0;
            break;
    }
    ddata.data = &data;
    return &ddata;
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
                __asm__ __volatile__ (
                "outb %1,%0"
                :
                :"dN"(this->port),"a"(driverData->data));
                written = 8;
                break;
            case 16:
                __asm__ __volatile__ (
                "outw %1,%0"
                :
                :"dN"(this->port),"a"(driverData->data));
                written = 16;
                break;
            case 32:
                __asm__ __volatile__ (
                "outl %1,%0"
                :
                :"dN"(this->port),"a"(driverData->data));
                written = 32;
                break;
            default:
                written = 0;
                break;
        }
    }
    return written;
}

