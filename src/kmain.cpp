/**
 * @ Author: Ahmed Ziabat Ziabat (aka) BLACKBURN
 * @ Created: 2022-01-27
 * @ Last revision: 2022-06-07
 * @ Description: Copyright (c) 2021-2022, Ahmed Ziabat
All rights reserved.
Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
Neither the name of copyright holders nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <System/InputOutput/Output/Screen.hpp>
#include <System/InputOutput/SystemPort.hpp>
#include <System/InputOutput/IODriver.hpp>

typedef void (*ctor)();
typedef void (*dtor)();

extern "C" ctor __ctor_start;
extern "C" ctor __ctor_end;

extern "C" void _create_instances_()
{
	for(ctor * instance = &__ctor_start;
		instance != &__ctor_end;
		instance++)
	{
		(*instance)();
	}
}

extern "C" int __kmain()
{
	SystemPort sp = SystemPort(0x3f8);
	
	InputOutputDriver::DriverData ddata;


	BasicVGA vga(80,25);

	char const* str = "Hola";

	ddata.data =(void *) str;
	ddata.size = 4;
	
	vga.write(&ddata);

	for(int i = 0;i<10;i++){
		ddata.data = (void*)str[i%4];
		ddata.size = 1;
		sp.write(&ddata);
	}
		
	
	for(;;){}
}
