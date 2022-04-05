#ifndef _COLOR_H_
#define _COLOR_H_

#include "mathlib.h"
//颜色每个分量的取值范围都在0~1
struct  Color
{
	unsigned char r;//0~1
	unsigned char g;//0~1
	unsigned char b;//0~1
	unsigned char a;//0~1
	//
	Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
	{
		unsigned char zero = 0;
		red		= glm::max(zero, red);
		green	= glm::max(zero, green);
		blue	= glm::max(zero, blue);
		alpha	= glm::max(zero, alpha);
		r = red <= 1	? red	: red / 255;
		g = green <= 1	? green : green / 255;
		b = blue <= 1	? blue	: blue / 255;
		a = alpha <= 1	? alpha	: alpha / 255;
	}
};

#define WHITE		Color{ 1, 1, 1, 1 }   // 
#define BLACK		Color{ 0, 0, 0, 1 }   // 
#define RED			Color{ 255, 0, 0, 1 }   // 
#define GREEN		Color{ 0, 1, 0, 1 }   // 
#define BLUE		Color{ 0, 0, 1, 1 }   // 
#define BLANK		Color{ 0, 0, 0, 0 }    // Blank (Transparent)
#define MAGENTA		Color{ 1, 0, 1, 1 }	// Magenta


#endif // !_COLOR_H_

