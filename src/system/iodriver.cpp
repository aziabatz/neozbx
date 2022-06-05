#include <System/InputOutput/IODriver.hpp>

using namespace InputOutputDriver;

void IODriver::updateUptime(uint32_t &uptime){
    this->uptime = uptime;
}

int IODriver::write(DriverData * driverData){}
DriverData * IODriver::read(){}
DriverData * IODriver::read(unsigned int size){}