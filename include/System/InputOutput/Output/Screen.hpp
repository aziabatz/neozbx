/* 
 * Copyright (C) 2021 AZZ (aka) BLACKBURN
 *
 * File:    Screen.hpp
 * Author:  Ahmed Ziabat Ziabat
 * Created: 2021-11-19
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
		char * const frameBuffer = (char *) 0xB8000;

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
	//TODO write IMPORTANT!! Method inherited cause of its dev FOLLOW UNIX-LIKE DESIGN
	//TODO inport and outport to write to vga mem, should be in system class if we create one
};

#endif
