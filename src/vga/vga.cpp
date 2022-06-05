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

#include <System/InputOutput/Output/Screen.hpp>
#include <System/InputOutput/SystemPort.hpp>

SystemPort *indexPort;
SystemPort *charPort;

void BasicVGA::clearLine(uint32_t line){
    uint16_t cursor = screenWidth * line * screenDepth;
    for(cursor;cursor<(this->screenWidth *(line+1)*this->screenDepth);cursor+=screenDepth){
        *(frameBuffer+cursor) = 0x0;
    }
}

void BasicVGA::clearLines(uint32_t from, uint32_t to){/*
    uint16_t cursor = screenWidth * from * screenDepth;
    for(cursor;cursor<(this->screenWidth *(to+1)*this->screenDepth);cursor+=screenDepth){
        *(frameBuffer+cursor) = 0x0;
    }*/
    //TODO TEST THIS
    for(int line = from; line < to; line++){
        this->clearLine(line);
    }
}

void BasicVGA::clearScreen(){
    this->clearLines(0, this->screenHeight);
}

void BasicVGA::positionCursor(int newX, int newY){
    uint16_t position = newY * this->screenWidth + newX;
    InputOutputDriver::DriverData ddata;
    ddata.size = 1;

    ddata.data = (void*)0xF;
    indexPort->write(&ddata);
    ddata.data = (void*) ((uint8_t)(position & 0xFF)); // first lower byte of position
    charPort->write(&ddata);
    ddata.data = (void*)0x0E;
    indexPort->write(&ddata);
    ddata.data = (void*) ((uint8_t)((position >> 8) & 0xFF));
    charPort->write(&ddata);
}

void BasicVGA::newLine()
{
    
}

void BasicVGA::scroll(){
    for(uint16_t i = 0;
        i<(this->screenWidth * (this->screenHeight - 1) * this->screenDepth);
        i++)
        {
            frameBuffer[i] = frameBuffer[i +this->screenWidth * this->screenDepth];
            clearLine(this->screenHeight-1); //clear last line
        }
    if(this->cursorY <1)
    {
        this->cursorX = 0;
        this->cursorY = 0;
    }
    else
    {
        cursorY++;
    }
}

void BasicVGA::scrollScreen(int lines){

}

void BasicVGA::highlightCursor(int x, int y){

}

BasicVGA::BasicVGA(){
    BasicVGA(25, 80);
}

BasicVGA::BasicVGA(int width, int height){
    this->screenWidth = width;
    this->screenHeight = height;
    this->cursorX = this->cursorY = 0;
    this->screenDepth = 2;
    indexPort = &(SystemPort(0x3D4));
    charPort = &(SystemPort(0x3D5));
}

int BasicVGA::write(InputOutputDriver::DriverData * driverData)
{
    
}

InputOutputDriver::DriverData * BasicVGA::read(){

}

InputOutputDriver::DriverData * BasicVGA::read(unsigned int size){
    
}