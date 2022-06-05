/* 
 * Copyright (C) 2021 AZZ (aka) BLACKBURN
 *
 * File:    kmain.cpp
 * Author:  Ahmed Ziabat Ziabat
 * Created: 2021-11-19
 */
#include <System/InputOutput/Output/Screen.hpp>
#include <System/InputOutput/SystemPort.hpp>
#include <System/InputOutput/IODriver.hpp>

extern "C" int __kmain()
{
	SystemPort sp = SystemPort(0x3f8);
	InputOutputDriver::DriverData ddata;
	ddata.data =(void*)'A';
	ddata.size = 1;
	for(int i = 0;i<10;i++)
		sp.write(&ddata);
	return 0;
}
