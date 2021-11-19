/* 
 * Copyright (C) 2021 AZZ (aka) BLACKBURN
 *
 * File:    Screen.hpp
 * Author:  Ahmed Ziabat Ziabat
 * Created: 2021-11-19
 */

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

class BasicVGA
{
	//TODO screen size(80x25)
	private:
		int screenHeight;
		int screenWidth;

	public:
		BasicVGA();
		BasicVGA(int height, int width);
	//TODO write IMPORTANT!! Method inherited cause of its dev FOLLOW UNIX-LIKE DESIGN
	//TODO inport and outport to write to vga mem, should be in system class if we create one
};

#endif
