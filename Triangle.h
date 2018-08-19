/**
 * Triangles.h- Interface for abstract Triangle class
 * Author: larsonma@msoe.edu <Mitchell Larson>
 * Date: march 29 2018
 */

#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "matrix.h"
#include "gcontext.h"
#include "Colors.h"
#include "Shape.h"
#include "ViewContext.h"

class Triangle : public Shape{

    public:
    /* 
        * This is a constructor for a Triangle object using a matrix as verticies.
        * 
        * Parameters:
        * 	verticies - pointer to the verticies object to be used as triangle coordinates
        */
        Triangle(matrix* verticies);

        /* 
        * This is a constructor for a Triangle object created with a matrix and rgb colors
        * 
        * Parameters:
        *  verticies - pointer to the verticies object to be used as triangle coordinates
        *  red - color value for red
        *  green - color value for green
        *  blue - color value for blue
        */
        Triangle(matrix* verticies, int red, int green, int blue);

        Triangle(matrix* verticies, unsigned int color);

        /* 
        * This is a constructor for a Triangle object with points specified by coordinates
        * 
        * Parameters:
        * 	x0 - x coordinate of first point
        *  y0 - y coordinate of first point
        *  x1 - x coordinate of second point
        *  y1 - y coordinate of second point
        *  x2 - x coordinate of thrid point
        *  y2 - y coordinate of third point
        */
        Triangle(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);

        /* 
        * This is a constructor for a Triangle object with points specified by coordinates and color specified by rgb
        * 
        * Parameters:
        * 	x0 - x coordinate of first point
        *  y0 - y coordinate of first point
        *  x1 - x coordinate of second point
        *  y1 - y coordinate of second point
        *  x2 - x coordinate of thrid point
        *  y2 - y coordinate of third point
        *  red - color value for red
        *  green - color value for green
        *  blue - color value for blue
        */
        Triangle(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, int red, int green, int blue);

        /* 
        * This is a copy constructor for a Triangle object.
        * 
        * Parameters:
        * 	from - reference to Triangle that will be copied.
        */
        Triangle(const Triangle& from);

        /* 
        * This is a destructor for a Triangle object.
        * 
        * Parameters:
        * 	none
        */
        ~Triangle();

        /* 
        * This method will draw the Triangle object
        * 
        * Parameters:
        * 	gc - pointer to graphics context object
        * 
        * Returns:
        *  none
        */
        void draw(GraphicsContext*, ViewContext*);

        /* 
        * This method will print the properties of the Triangle to an output stream
        * 
        * Parameters:
        * 	os - reference to the output stream
        * 
        * Returns:
        *  output stream being passed in
        */
        std::ostream& out(std::ostream& os) const;

        /* 
        * Reads in a Triangle from file and instantiates and returns the Triangle object
        * 
        * Parameters:
        * 	iStream - reference to input file
        * 
        * Returns:
        *  pointer to Triangle object
        */
        static Triangle* in(std::istream& iStream);

        /* 
        * Creates a copy of a Triangle object, but returns a refernce to the Triangle as a shape reference
        * 
        * Parameters:
        * 	none
        * 
        * Returns:
        *  Triangle object as a shape reference
        */
        Shape& clone();

        /* 
        * Overrides default = operator for easy assignment of Triangle objects
        * 
        * Parameters:
        * 	from - reference to Triangle that will be copied
        * 
        * Returns:
        *  reference to Triangle object
        */
        Triangle& operator=(const Triangle& from);

    private:
        /* 
        * Helper function for initializing verticies
        */
        void initTriangleVerticies(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
};

#endif
