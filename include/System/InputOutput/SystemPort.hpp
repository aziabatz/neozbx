/* 
 * Copyright (C) 2022 AZZ (aka) BLACKBURN
 *
 * File:    IODriver.hpp
 * Author:  Ahmed Ziabat Ziabat
 * Created: 2022-06-04
 */

#include <types.h>
#include <System/InputOutput/IODriver.hpp>

class SystemPort: public InputOutputDriver::IODriver
{
    private:
        uint16_t port;

        uint8_t in8();
        uint16_t in16();
        uint32_t in32();

        void out8(void * data);
        void out16(void * data);
        void out32(void * data);
    public:
        SystemPort(uint16_t port);
        //~SystemPort();

        InputOutputDriver::DriverData * read();
        InputOutputDriver::DriverData * read(unsigned int size);
        int write(InputOutputDriver::DriverData * driverData);
};