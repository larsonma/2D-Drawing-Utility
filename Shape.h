/**
 * shapes.h- Interface for abstract shape class
 * Author: larsonma@msoe.edu <Mitchell Larson>
 * Date: march 29 2018
 */

#ifndef _SHAPE_H
#define _SHAPE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

#include "matrix.h"
#include "gcontext.h"
#include "Colors.h"
#include "ViewContext.h"

class ViewContext;

class Shape{

    class Color{
        public:
            unsigned int color;

            /* 
            * This is a default constructor for a Color object. Color becomes white
            * 
            * Parameters:
            *  noen
            */
            Color();

            /* 
            * This is a constructor for a Line object in which color is specified as hex or an integer.
            * 
            * Parameters:
            *  color - integer value of color
            */
            Color(unsigned int color);

            /* 
            * This is a constructor for a Line object in which color is specified as rgb
            * 
            * Parameters:
            *  red - color value for red
            *  green - color value for green
            *  blue - color value for blue
            */
            Color(int red, int green, int blue);

            /* 
            * Returns red value of color
            * 
            * Parameters:
            *  none
            * 
            * Returns:
            *  red value as integer
            */
            int getRed();

            /* 
            * Returns green value of color
            * 
            * Parameters:
            *  none
            * 
            * Returns:
            *  green color as integer
            */
            int getGreen();

            /* 
            * Returns blue value of color
            * 
            * Parameters:
            *  none
            * 
            * Returns:
            *  blue color as integer
            */
            int getBlue();
    };

    public:
        /* 
        * This is a constructor for a Shape object. A default shape is created.
        * 
        * Parameters:
        * 	none
        */
        Shape();

        /* 
        * This is a constructor for a Shape object with location specified
        * 
        * Parameters:
        * 	x0 - x coordinate of first point
        *  y0 - y coordinate of first point
        */
        Shape(unsigned int x0, unsigned int y0);

        /* 
        * This is a constructor for a Line object in which color is specified
        * 
        * Parameters:
        *  red - color value for red
        *  green - color value for green
        *  blue - color value for blue
        */
        Shape(int red, int green, int blue);

        /* 
        * This is a constructor for a Line object in which color is specified as a single integer
        * 
        * Parameters:
        *  color - integer value for color
        */
        Shape(unsigned int color);

        /* 
        * This is a constructor for a Shape object with location specified and a color specified as
        * a single integer value.
        * 
        * Parameters:
        * 	x0 - x coordinate of first point
        *  y0 - y coordinate of first point
        *  color - integer value of color
        */
        Shape(unsigned int x0, unsigned int y0, unsigned int color);

        /* 
        * This is a constructor for a Shape object with location and color specified
        * 
        * Parameters:
        * 	x0 - x coordinate of first point
        *  y0 - y coordinate of first point
        *  red - color value for red
        *  green - color value for green
        *  blue - color value for blue
        */
        Shape(unsigned int x0, unsigned int y0, int red, int green, int blue);

        /* 
        * This is a copy constructor for a Shape object.
        * 
        * Parameters:
        * 	from - reference to line that will be copied.
        */
        Shape(const Shape& from);

        /* 
        * This is a destructor for a Shape object.
        * 
        * Parameters:
        * 	none
        */
        virtual ~Shape();

        virtual void draw(GraphicsContext*, ViewContext*)=0;

        /* 
        * This method will print the properties of the Shape to an output stream
        * 
        * Parameters:
        * 	os - reference to the output stream
        * 
        * Returns:
        *  output stream being passed in
        */
        virtual std::ostream& out(std::ostream& os) const;

        /* 
        * Reads in a Shape from file and assigns the shape properties. A shape object will already
        * be instantiated when this is called, so a shape object is not returned.
        * 
        * Parameters:
        * 	iStream - reference to input file
        * 
        * Returns:
        *  void
        */
        void in(std::istream& iStream);
        
        /* 
        * Returns a copy of the shape verticies. A copy is returned to prevent manipulation of the
        * shape properties.
        * 
        * Parameters:
        * 	none
        * 
        * Returns:
        *  pointer to matrix object holding the shape verticies.
        */
        matrix* getVerticies();

        virtual Shape& clone()=0;

    protected:
        /* 
        * Overrides default = operator for easy assignment of shape properties
        * 
        * Parameters:
        * 	from - reference to shape that will be copied
        * 
        * Returns:
        *  void
        */
        void operator=(const Shape& from);

        Color* color;
        matrix* verticies;

};

/* 
 * This is a global function not associated with a class which allows shapes to be read from
 * file and instantiated.
 * 
 * Parameters:
 *  in - reference to input stream
 * 
 * Returns:
 *  vector of shape objects
 */
std::vector<Shape*> readShapesFromFile(std::istream& in);

#endif