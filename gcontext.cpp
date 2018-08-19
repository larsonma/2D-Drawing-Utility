/**
 * gcontext.cpp - This is an abstract base class representing a generic graphics
 * 		context.  Most implementation specifics will need to be provided by
 * 		a concrete implementation.  See header file for specifics.
 * Author: larsonma@msoe.edu <Mitchell Larson>
 * Date: march 29 2018
 */

#define _USE_MATH_DEFINES	// for M_PI
#include <cmath>	// for trig functions
#include "gcontext.h"	

/*
 * Destructor - does nothing
 */
GraphicsContext::~GraphicsContext()
{
	// nothing to do
	// here to insure subclasses handle destruction properly
}


/* This is a Bresenham line algorithm used to draw lines in quick and
 * efficient manner. If lines are horizontal or vertical, an alternate
 * method of drawing the line is used to increase performance
 * 
 * Parameters:
 * 	x0, y0 - origin of line
 *  x1, y1 - end of line
 * 
 * Returns: void
 */
void GraphicsContext::drawLine(int x0, int y0, int x1, int y1)
{
	if(isHorizontal(x0,y0,x1,y1)){
		drawHorizontalLine(x0,x1,y0);
	}else if(isVertical(x0,y0,x1,y1)){
		drawVerticalLine(y0,y1,x0);
	}else{
		switch(resolveOctant(x0,y0,x1,y1)){
			case 1:
				drawOctantOne(x0,y0,x1,y1);
				break;
			case 2:
				drawOctantTwo(x0,y0,x1,y1);
				break;
			case 3:
				drawOctantThree(x0,y0,x1,y1);
				break;
			case 4:
				drawOctantEight(x1,y1,x0,y0);
				break;
			case 5:
				drawOctantOne(x1,y1,x0,y0);
				break;
			case 6:
				drawOctantTwo(x1,y1,x0,y0);
				break;
			case 7:
				drawOctantThree(x1,y1,x0,y0);
				break;
			case 8:
				drawOctantEight(x0,y0,x1,y1);
				break;
			default:
				break;
		}
	}

	return;
}



/* This is a cicle drawing algorithm whcih uses theBresenham line 
 * to draw a circle radius pixels from the center.
 * 
 * Parameters:
 * 	x0, y0 - center of circle
 *  radius - radius of circle
 * 
 * Returns: void
 */
void GraphicsContext::drawCircle(int x0, int y0, unsigned int radius)
{
	int x = radius - 1;
	int y = 0;
	int dx = 1;
	int dy = 1;
	int err = dx - (radius << 1);

	while(x >= y){
		setPixel(x0 + x, y0 + y);
        setPixel(x0 + y, y0 + x);
        setPixel(x0 - y, y0 + x);
        setPixel(x0 - x, y0 + y);
        setPixel(x0 - x, y0 - y);
        setPixel(x0 - y, y0 - x);
        setPixel(x0 + y, y0 - x);
        setPixel(x0 + x, y0 - y);
	

		if(err <= 0){
			y++;
			err = err + dy;
			dy = dy + 2;
		}else{
			x--;
			dx = dx + 2;
			err = err + dx - (radius << 1);
		}
	}
	
	return;	
}

void GraphicsContext::endLoop()
{
	run = false;
}

/* This is a helper function which tests if a line is vertical
 * 
 * Parameters:
 * 	x0, y0 - origin of line
 *  x1, y1 - end of line
 * 
 * Returns: true if vertical, false if not
 */
bool GraphicsContext::isVertical(int x0, int y0, int x1, int y1){
	return x0 == x1;
}

/* This is a helper function which tests if a line is horizontal
 * 
 * Parameters:
 * 	x0, y0 - origin of line
 *  x1, y1 - end of line
 * 
 * Returns: true if horizontal, false if not
 */
bool GraphicsContext::isHorizontal(int x0, int y0, int x1, int y1){
	return y0 == y1;
}

/* This is a helper function draws a vertical line for efficiently
 * than the algorithm used for lines that are not vertical or
 * horizontal
 * 
 * Parameters:
 * 	x - x coordinate that line is at
 *  y0, y1 - y coordinate endpoints
 * 
 * Returns: true if vertical, false if not
 */
void GraphicsContext::drawVerticalLine(int y0, int y1, int x){
	if(y0 <= y1){
		for(int y = y0; y <= y1; y++){
			setPixel(x,y);
		}
	}else{
		for(int y = y0; y >= y1; y--){
			setPixel(x,y);
		}
	}
}

/* This is a helper function draws a horizontal line for efficiently
 * than the algorithm used for lines that are not vertical or
 * horizontal
 * 
 * Parameters:
 * 	y - y coordinate that line is at
 *  x0, x1 - x coordinate endpoints
 * 
 * Returns: true if vertical, false if not
 */
void GraphicsContext::drawHorizontalLine(int x0, int x1, int y){
	if(x0 <= x1){
		for(int x = x0; x <= x1; x++){
			setPixel(x,y);
		}
	}else{
		for(int x = x0; x >= x1; x--){
			setPixel(x,y);
		}
	}
}

/* This is a helper function which uses the Bresenham line algorithm 
 * to draw a line in the first octant.
 * 
 * Parameters:
 * 	x0, y0 - origin of line
 *  x1, y1 - end of line
 * 
 * Returns: void
 */
void GraphicsContext::drawOctantOne(int x0, int y0, int x1, int y1){
	int dy = y1-y0;
	int dx = x1-x0;
	int y = y0;
	int err = 0;

	for(int x = x0; x <= x1; x++){
		setPixel(x,y);
		err = err + dy;
		if((err << 1) >= dx){
			y = y + 1;
			err = err - dx;
		}
	}	
}

/* This is a helper function which uses the Bresenham line algorithm 
 * to draw a line in the second octant.
 * 
 * Parameters:
 * 	x0, y0 - origin of line
 *  x1, y1 - end of line
 * 
 * Returns: void
 */
void GraphicsContext::drawOctantTwo(int x0, int y0, int x1, int y1){
	int dy = y1-y0;
	int dx = x1-x0;
	int x = x0;
	int err = 0;

	for(int y = y0; y <= y1; y++){
		setPixel(x,y);
		err = err + dx;
		if((err << 1) >= dy){
			x = x + 1;
			err = err - dy;
		}
	}
}

/* This is a helper function which uses the Bresenham line algorithm 
 * to draw a line in the eigth octant.
 * 
 * Parameters:
 * 	x0, y0 - origin of line
 *  x1, y1 - end of line
 * 
 * Returns: void
 */
void GraphicsContext::drawOctantEight(int x0, int y0, int x1, int y1){
	int dy = y1-y0;
	int dx = x1-x0;
	int y = y0;
	int err = 0;

	for(int x = x0; x <= x1; x++){
		setPixel(x,y);
		err = err + dy;
		if((err << 1) <= dx){
			y = y - 1;
			err = err + dx;
		}
	}
}

/* This is a helper function which uses the Bresenham line algorithm 
 * to draw a line in the third octant.
 * 
 * Parameters:
 * 	x0, y0 - origin of line
 *  x1, y1 - end of line
 * 
 * Returns: void
 */
void GraphicsContext::drawOctantThree(int x0, int y0, int x1, int y1){
	int dy = y1-y0;
	int dx = x1-x0;
	int x = x0;
	int err = 0;

	for(int y = y0; y <= y1; y++){
		setPixel(x,y);
		err = err + dx;
		if((err << 1) <= dy){
			x = x - 1;
			err = err + dy;
		}
	}
}

/* This is a helper function which determines the octant that a line
 * lies in space.
 * 
 * Parameters:
 * 	x0, y0 - origin of line
 *  x1, y1 - end of line
 * 
 * Returns: a value between 1 and 8 indicating octant.
 */
unsigned int GraphicsContext::resolveOctant(int x0, int y0, int x1, int y1){
	int dy = y1-y0;
	int dx = x1-x0;

	if(x0 < x1){
		if(y0 < y1){
			if(dy <= dx){
				return 1;
			}else {
				return 2;
			}
		}else {
			if(std::abs(dy) <= dx){
				return 8;
			}else{
				return 7;
			}
		}
	}else{
		if(y0 < y1){
			if(dy <= std::abs(dx)){
				return 4;
			}else{
				return 3;
			}
		}else{
			if(std::abs(dy) <= std::abs(dx)){
				return 5;
			}else{
				return 6;
			}
		}
	}
}
