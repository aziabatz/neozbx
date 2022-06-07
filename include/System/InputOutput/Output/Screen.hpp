/**
 * @ Author: Ahmed Ziabat Ziabat (aka) BLACKBURN
 * @ Created: 2022-01-27
 * @ Last revision: 2022-06-06
 * @ Description: Copyright (c) 2021-2022, Ahmed Ziabat
All rights reserved.
Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
Neither the name of copyright holders nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <System/InputOutput/IODriver.hpp>

#ifndef NZX_SCREEN_HPP
#define NZX_SCREEN_HPP

#define NZX_VGA_BLACK		0
#define NZX_VGA_BLUE		1
#define NZX_VGA_GREEN		2
#define NZX_VGA_CYAN		3
#define NZX_VGA_RED			4
#define NZX_VGA_MAGENTA		5
#define NZX_VGA_BROWN		6
#define NZX_VGA_WHITE		0xF


#define NZX_VGA_LGRAY		7
#define NZX_VGA_GRAY		8
#define NZX_VGA_LBLUE		9
#define NZX_VGA_LGREEN		0xA
#define NZX_VGA_LCYAN		0xB
#define NZX_VGA_LRED		0xC
#define NZX_VGA_LMAGENTA	0xD
#define NZX_VGA_LBROWN		0xE

using namespace InputOutputDriver;

class BasicVGA: IODriver
{
	//TODO screen size(80x25)
	private:
		/** Screen height in pixels */
		int screenHeight;
		/** Screen width in pixels */
		int screenWidth;
		/** Screen depth in bytes */
		int screenDepth;
		
		/** X position of the cursor */
		int cursorX;
		/** Y position of the cursor */
		int cursorY;
		
		/** Framebuffer address */
		unsigned char * const frameBuffer = (unsigned char *) 0xB8000;
		

		/**
		 * @brief Clears a specific line from the screen
		 * 
		 * @param line Line to be cleared
		 */
		void clearLine(uint32_t line);

		/**
		 * @brief Clears an interval of lines
		 * 
		 * @param from From which lines to clear
		 * @param to Last line to be cleared
		 */
		void clearLines(uint32_t from, uint32_t to);

		/**
		 * @brief Clears all the lines from the screen
		 * 
		 */
		void clearScreen();

		/**
		 * @brief Puts the cursor at a specified postion
		 * 
		 * @param newX X position
		 * @param newY Y position
		 */
		void positionCursor(int newX, int newY);

		/**
		 * @brief Introduces a new line in the buffer
		 * 
		 */
		void newLine();

		/**
		 * @brief Makes a carriage return
		 * 
		 */
		void carriageReturn();

		/**
		 * @brief Scrolls the screen up 1 line
		 * 
		 */
		void scroll();

		/**
		 * @brief Scrolls the screen specified number of lines
		 * 
		 * @param lines Numbers of lines to be scrolled up
		 */
		void scrollScreen(int lines);

		/**
		 * @brief Highlights a position in the screen
		 * 
		 * @param x X position to be highlighted
		 * @param y Y position to be highlighted
		 */
		void highlightCursor(int x, int y);

		void writeToFramebuffer(int x, int y, char c);

		void writeChar(char c);

	public:

		/**
		 * @brief Construct a new Basic V G A object
		 * 
		 */
		BasicVGA();

		/**
		 * @brief Construct a new Basic V G A object
		 * 
		 * @param width 
		 * @param height 
		 */
		BasicVGA(int width, int height);

		/** 
		 * @see InputOutputDriver::IODriver#write
		 */
		int write(DriverData * driverData);
		DriverData * read();
		DriverData * read(unsigned int size);
	//TODO write IMPORTANT!! Method inherited cause of its dev FOLLOW UNIX-LIKE DESIGN
	//TODO inport and outport to write to vga mem, should be in system class if we create one
};

#endif
