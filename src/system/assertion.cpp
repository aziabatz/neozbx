/**
 * @ Author: Ahmed Ziabat Ziabat (aka) BLACKBURN
 * @ Created: 2022-07-19
 * @ Last revision: 2022-07-20
 * @ Description: Copyright (c) 2021-2022, Ahmed Ziabat Ziabat

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 */

#include <System/Integrity/Assertion.hpp>
#include <System/InputOutput/SystemPort.hpp>
#include <System/InputOutput/Output/Screen.hpp>
#include <System/Integrity/Panic.hpp>

void assertFail(const char * msg, const char * src, const char * line)
{
    SystemPort serial(0x3f8);
    BasicVGA vga(80,25);

    //TODO print Asertion Failed: (assertion) in file:line
    systemPanic(nullptr);    
}