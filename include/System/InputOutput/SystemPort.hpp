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
    public:
        SystemPort(uint16_t port);
        ~SystemPort();

        InputOutputDriver::DriverData * read();
        InputOutputDriver::DriverData * read(unsigned int size);
        int write(InputOutputDriver::DriverData * driverData);
};