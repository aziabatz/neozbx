/* 
 * Copyright (C) 2022 AZZ (aka) BLACKBURN
 *
 * File:    vga.cpp
 * Author:  Ahmed Ziabat Ziabat
 * Created: 2022-01-28
 */

#include <System/InputOutput/Output/Screen.hpp>

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

    
}

void BasicVGA::newLine(){
//    unsigned int temp = this->cursorY 
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
}

int BasicVGA::write(InputOutputDriver::DriverData * driverData)
{

}

InputOutputDriver::DriverData * BasicVGA::read(){

}

InputOutputDriver::DriverData * BasicVGA::read(unsigned int size){
    
}