/**
 * shapes.h- Interface for a Line class
 * Author: larsonma@msoe.edu <Mitchell Larson>
 * Date: march 29 2018
 */

#ifndef _LINE_H
#define _LINE_H

#include "matrix.h"
#include "gcontext.h"
#include "Colors.h"
#include "Shape.h"
#include "ViewContext.h"

#include <string>

class Line: public Shape{

    public:
        /* 
        * This is a constructor for a Line object.
        * 
        * Parameters:
        * 	x0 - x coordinate of first point
        *  y0 - y coordinate of first point
        *  x1 - x coordinate of second point
        *  y2 - y coordinate of second point
        */
        Line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1);

        /* 
        * This is a constructor for a Line object.
        * 
        * Parameters:
        * 	x0 - x coordinate of first point
        *  y0 - y coordinate of first point
        *  x1 - x coordinate of second point
        *  y2 - y coordinate of second point
        *  red - color value for red
        *  green - color value for green
        *  blue - color value for blue
        */
        Line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1,
             int red, int green, int blue);

        /* 
        * This is a constructor for a Line object.
        * 
        * Parameters:
        * 	x0 - x coordinate of first point
        *  y0 - y coordinate of first point
        *  x1 - x coordinate of second point
        *  y2 - y coordinate of second point
        *  color - integer color value.
        */
        Line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1,
             unsigned int color);

        /* 
        * This is a copy constructor for a Line object.
        * 
        * Parameters:
        * 	from - reference to line that will be copied.
        */
        Line(const Line& from);

        /* 
        * This is a destructor for a Line object.
        * 
        * Parameters:
        * 	none
        */
        ~Line();

        /* 
        * This method will draw the line object
        * 
        * Parameters:
        * 	gc - pointer to graphics context object
        * 
        * Returns:
        *  none
        */
        void draw(GraphicsContext*, ViewContext*);

        /* 
        * This method will print the properties of the line to an output stream
        * 
        * Parameters:
        * 	os - reference to the output stream
        * 
        * Returns:
        *  output stream being passed in
        */
        std::ostream& out(std::ostream& os) const;

        /* 
        * Reads in a line from file and instantiates and returns the line object
        * 
        * Parameters:
        * 	iStream - reference to input file
        * 
        * Returns:
        *  pointer to line object
        */
        static Line* in(std::istream& iStream);

        /* 
        * Creates a copy of a line object, but returns a refernce to the line as a shape reference
        * 
        * Parameters:
        * 	none
        * 
        * Returns:
        *  line object as a shape reference
        */
        Shape& clone();

        /* 
        * Overrides default = operator for easy assignment of line objects
        * 
        * Parameters:
        * 	from - reference to line that will be copied
        * 
        * Returns:
        *  reference to line object
        */
        Line& operator=(const Line& from);

    private:
        matrix* endPoints;


};

#endif